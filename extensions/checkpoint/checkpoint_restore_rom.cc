#include "checkpoint/checkpoint_restore_rom.h"

#include "byteorder.h"
#include "dts.h"
#include "encoding.h"
#include "platform.h"
#include "sim.h"
#include "simif.h"

#include <cstdint>
#include <iostream>
#include <vector>

#define VSEW8 (0x0)
#define VLMUL8 (0x3)

int fdt_parse_clint(const void* fdt, reg_t* clint_addr, const char* compatible)
    __attribute__((weak));

namespace {

struct hart_restore_section_t {
  size_t hart_id = 0;
  processor_t* proc = nullptr;
  uint32_t dispatch_jal_pos = 0;
  uint32_t body_pos = 0;
};

[[noreturn]] void fail_restore_rom(const char* message)
{
  std::cerr << message << std::endl;
  std::exit(-6);
}

static uint32_t create_csrrw(int rs, uint32_t csrn)
{
  return 0x1073 | ((csrn & 0xFFF) << 20) | ((rs & 0x1F) << 15);
}

static uint32_t create_csrrs(int rd, uint32_t csrn)
{
  return 0x2073 | ((csrn & 0xFFF) << 20) | ((rd & 0x1F) << 7);
}

static uint32_t create_auipc(int rd, uint32_t addr)
{
  if (addr & 0x800)
    addr += 0x800;
  return 0x17 | ((rd & 0x1F) << 7) | ((addr >> 12) << 12);
}

static uint32_t create_addi(int rd, uint32_t addr)
{
  uint32_t pos = addr & 0xFFF;
  return 0x13 | ((rd & 0x1F) << 7) | ((rd & 0x1F) << 15) |
         ((pos & 0xFFF) << 20);
}

static uint32_t create_seti(int rd, uint32_t data)
{
  return 0x13 | ((rd & 0x1F) << 7) | ((data & 0xFFF) << 20);
}

static uint32_t create_ld(int rd, int rs1)
{
  return 3 | ((rd & 0x1F) << 7) | (3 << 12) | ((rs1 & 0x1F) << 15);
}

static uint32_t create_sd(int rs1, int rs2)
{
  return 0x23 | ((rs2 & 0x1F) << 20) | (3 << 12) | ((rs1 & 0x1F) << 15);
}

static uint32_t create_fld(int rd, int rs1)
{
  return 7 | ((rd & 0x1F) << 7) | (0x3 << 12) | ((rs1 & 0x1F) << 15);
}

static uint32_t create_vtypei(int vlmul, int vsew, int vta, int vma)
{
  return (vlmul & 0x7) | (vsew & 0x7) << 3 | (vta & 0x1) << 4 |
         (vma & 0x1) << 5;
}

static uint32_t create_vsetvli(int rd, int rs1, uint32_t vtypei)
{
  return 87 | ((rd & 0x1F) << 7) | (7 << 12) | ((rs1 & 0x1F) << 15) |
         ((vtypei & 0x7FF) << 20);
}

static uint32_t create_vle8(int vd, int rs1)
{
  return 7 | ((vd & 0x1F) << 7) | ((rs1 & 0x1F) << 15) | (1 << 25);
}

static uint32_t create_bne(int rs1, int rs2, int32_t offset)
{
  if ((offset & 0x1) != 0 || offset < -4096 || offset > 4094) {
    fail_restore_rom("ERROR: restore ROM BNE branch offset out of range.");
  }

  const uint32_t imm = static_cast<uint32_t>(offset) & 0x1FFFu;
  return 0x63 | ((imm >> 11) & 0x1) << 7 | ((imm >> 1) & 0xF) << 8 |
         (1u << 12) | ((rs1 & 0x1F) << 15) | ((rs2 & 0x1F) << 20) |
         ((imm >> 5) & 0x3F) << 25 | ((imm >> 12) & 0x1) << 31;
}

static uint32_t create_jal(int rd, int32_t offset)
{
  if ((offset & 0x1) != 0 || offset < -1048576 || offset > 1048574) {
    fail_restore_rom("ERROR: restore ROM JAL offset out of range.");
  }

  const uint32_t imm = static_cast<uint32_t>(offset) & 0x1FFFFFu;
  return 0x6F | ((rd & 0x1F) << 7) | ((imm >> 12) & 0xFF) << 12 |
         ((imm >> 11) & 0x1) << 20 | ((imm >> 1) & 0x3FF) << 21 |
         ((imm >> 20) & 0x1) << 31;
}

static void create_csr12_recovery(uint32_t* rom, uint32_t* code_pos,
                                  uint32_t csrn, uint16_t val)
{
  rom[(*code_pos)++] = create_seti(1, val & 0xFFF);
  rom[(*code_pos)++] = create_csrrw(1, csrn);
}

static void create_csr64_recovery(uint32_t* rom, uint32_t* code_pos,
                                  uint32_t* data_pos, uint32_t csrn,
                                  uint64_t val)
{
  uint32_t data_off = sizeof(uint32_t) * (*data_pos - *code_pos);

  rom[(*code_pos)++] = create_auipc(1, data_off);
  rom[(*code_pos)++] = create_addi(1, data_off);
  rom[(*code_pos)++] = create_ld(1, 1);
  rom[(*code_pos)++] = create_csrrw(1, csrn);

  rom[(*data_pos)++] = val & 0xFFFFFFFF;
  rom[(*data_pos)++] = val >> 32;
}

static void create_reg_recovery(uint32_t* rom, uint32_t* code_pos,
                                uint32_t* data_pos, int rn, uint64_t val)
{
  uint32_t data_off = sizeof(uint32_t) * (*data_pos - *code_pos);

  rom[(*code_pos)++] = create_auipc(rn, data_off);
  rom[(*code_pos)++] = create_addi(rn, data_off);
  rom[(*code_pos)++] = create_ld(rn, rn);

  rom[(*data_pos)++] = val & 0xFFFFFFFF;
  rom[(*data_pos)++] = val >> 32;
}

static void create_vreg_recovery(uint32_t* rom, uint32_t* code_pos,
                                 uint32_t* data_pos, int vn,
                                 uint32_t* vreg_data, uint32_t size)
{
  uint32_t data_off = sizeof(uint32_t) * (*data_pos - *code_pos);

  rom[(*code_pos)++] = create_auipc(1, data_off);
  rom[(*code_pos)++] = create_addi(1, data_off);
  rom[(*code_pos)++] = create_vle8(vn, 1);

  for (uint32_t i = 0; i < size; i++) {
    rom[(*data_pos)++] = *vreg_data;
    vreg_data++;
  }
}

static void create_io64_recovery(uint32_t* rom, uint32_t* code_pos,
                                 uint32_t* data_pos, uint64_t addr,
                                 uint64_t val)
{
  uint32_t data_off = sizeof(uint32_t) * (*data_pos - *code_pos);

  rom[(*code_pos)++] = create_auipc(1, data_off);
  rom[(*code_pos)++] = create_addi(1, data_off);
  rom[(*code_pos)++] = create_ld(1, 1);

  rom[(*data_pos)++] = addr & 0xFFFFFFFF;
  rom[(*data_pos)++] = addr >> 32;

  uint32_t data_off2 = sizeof(uint32_t) * (*data_pos - *code_pos);
  rom[(*code_pos)++] = create_auipc(2, data_off2);
  rom[(*code_pos)++] = create_addi(2, data_off2);
  rom[(*code_pos)++] = create_ld(2, 2);

  rom[(*code_pos)++] = create_sd(1, 2);

  rom[(*data_pos)++] = val & 0xFFFFFFFF;
  rom[(*data_pos)++] = val >> 32;
}

static reg_t resolve_clint_base(const std::string& dtb)
{
  reg_t clint_base = CLINT_BASE;
  if (!fdt_parse_clint) {
    return clint_base;
  }

  void* fdt = (void*)dtb.c_str();
  if (fdt_parse_clint(fdt, &clint_base, "riscv,clint0") != 0) {
    std::cerr << "Could not find the address of clint, failed to create bootrom"
              << std::endl;
    std::exit(-4);
  }
  return clint_base;
}

static void append_restore_body(
    processor_t& proc,
    clint_t& clint,
    reg_t clint_base,
    size_t hart_id,
    uint32_t* rom,
    uint32_t* code_pos,
    uint32_t* data_pos)
{
  state_t* state = proc.get_state();

  if (state->prv == PRV_M &&
      state->pc >= kCheckpointBootromBase &&
      state->pc < (kCheckpointBootromBase + kCheckpointBootromSize)) {
    std::cerr << "ERROR: could not checkpoint when running inside the checkpoint ROM."
              << std::endl;
    std::exit(-4);
  }

  create_csr64_recovery(rom, code_pos, data_pos, 0x7b1, state->pc);
  if (PRV_HS == state->prv) {
    std::cerr << "UNSUPPORTED Priv mode (no hyper)" << std::endl;
    std::exit(-4);
  }
  create_csr12_recovery(rom, code_pos, 0x7b0, 0x600 | state->prv);

  create_csr64_recovery(rom, code_pos, data_pos, 0x300,
                        state->csrmap[CSR_MSTATUS]->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x301, state->misa->read());

  const reg_t sstatus = state->csrmap[CSR_SSTATUS]->read();
  if (sstatus & SSTATUS_FS) {
    create_csr12_recovery(rom, code_pos, 0x001, state->fflags->read());
    create_csr12_recovery(rom, code_pos, 0x002, state->frm->read());
    create_csr12_recovery(rom, code_pos, 0x003,
                          state->fflags->read() | (state->frm->read() << 5));

    for (int i = 0; i < 32; i++) {
      uint32_t data_off = sizeof(uint32_t) * (*data_pos - *code_pos);
      rom[(*code_pos)++] = create_auipc(1, data_off);
      rom[(*code_pos)++] = create_addi(1, data_off);
      rom[(*code_pos)++] = create_fld(i, 1);

      rom[(*data_pos)++] = static_cast<uint32_t>(state->FPR[i].v[0] & 0xFFFFFFFF);
      rom[(*data_pos)++] = static_cast<uint32_t>(state->FPR[i].v[0] >> 32);
    }
  }

  if (proc.extension_enabled('V') && (sstatus & SSTATUS_VS)) {
    rom[(*code_pos)++] = create_seti(1, -1);
    rom[(*code_pos)++] = create_vsetvli(1, 1, create_vtypei(VLMUL8, VSEW8, 0, 0));

    uint32_t size = proc.VU.VLEN * 8 / 32;
    uint32_t* vreg_data = nullptr;

    vreg_data = &proc.VU.elt<uint32_t>(0, 0, false);
    create_vreg_recovery(rom, code_pos, data_pos, 0, vreg_data, size);
    vreg_data = &proc.VU.elt<uint32_t>(8, 0, false);
    create_vreg_recovery(rom, code_pos, data_pos, 8, vreg_data, size);
    vreg_data = &proc.VU.elt<uint32_t>(16, 0, false);
    create_vreg_recovery(rom, code_pos, data_pos, 16, vreg_data, size);
    vreg_data = &proc.VU.elt<uint32_t>(24, 0, false);
    create_vreg_recovery(rom, code_pos, data_pos, 24, vreg_data, size);

    create_csr64_recovery(rom, code_pos, data_pos, CSR_VSTART, proc.VU.vstart->read());
    create_csr64_recovery(rom, code_pos, data_pos, CSR_VXSAT, proc.VU.vxsat->read());
    create_csr64_recovery(rom, code_pos, data_pos, CSR_VXRM, proc.VU.vxrm->read());
    create_csr64_recovery(rom, code_pos, data_pos, CSR_VCSR,
                          proc.get_state()->csrmap[CSR_VCSR]->read());

    volatile uint32_t vl = proc.VU.vl->read();
    volatile uint32_t vtype = proc.VU.vtype->read();
    rom[(*code_pos)++] = create_seti(1, vl);
    rom[(*code_pos)++] = create_vsetvli(1, 1, vtype);
  }

  for (int i = 0; i < 29; i++) {
    create_csr12_recovery(rom, code_pos, 0xb03 + i, 0);
    create_csr64_recovery(rom, code_pos, data_pos, 0x323 + i,
                          state->csrmap[CSR_MHPMEVENT3 + i]->read());
  }

  create_csr64_recovery(rom, code_pos, data_pos, 0x7a0, state->tselect->read());

  create_csr64_recovery(rom, code_pos, data_pos, 0x302, state->medeleg->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x303, state->mideleg->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x304, state->mie->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x305, state->mtvec->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x105, state->stvec->read());
  create_csr12_recovery(rom, code_pos, 0x320, state->csrmap[CSR_MCOUNTINHIBIT]->read());
  create_csr12_recovery(rom, code_pos, 0x306, state->mcounteren->read());
  create_csr12_recovery(rom, code_pos, 0x106, state->scounteren->read());

  for (uint32_t i = 0; i < proc.n_pmp; ++i) {
    create_csr64_recovery(rom, code_pos, data_pos, 0x3B0 + i, state->pmpaddr[i]->read());
  }
  for (uint32_t i = 0; i < proc.n_pmp / 4; i += 2) {
    create_csr64_recovery(rom, code_pos, data_pos, 0x3A0 + i,
                          state->csrmap[CSR_PMPCFG0 + i]->read());
  }

  create_csr64_recovery(rom, code_pos, data_pos, 0x340, state->csrmap[CSR_MSCRATCH]->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x341, state->mepc->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x342, state->mcause->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x343, state->mtval->read());

  create_csr64_recovery(rom, code_pos, data_pos, 0x140, state->csrmap[CSR_SSCRATCH]->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x141, state->sepc->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x142, state->scause->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0x143, state->stval->read());

  create_csr64_recovery(rom, code_pos, data_pos, 0x344, state->csrmap[CSR_MIP]->read());

  for (int i = 3; i < 32; i++) {
    create_reg_recovery(rom, code_pos, data_pos, i, state->XPR[i]);
  }

  const reg_t mtimecmp_addr = clint_base + 0x4000 + static_cast<reg_t>(hart_id) * 8;
  create_io64_recovery(rom, code_pos, data_pos, mtimecmp_addr, clint.get_mtimecmp(hart_id));
  create_csr64_recovery(rom, code_pos, data_pos, 0xb02, state->minstret->read());
  create_csr64_recovery(rom, code_pos, data_pos, 0xb00, state->mcycle->read());
  create_io64_recovery(rom, code_pos, data_pos, clint_base + 0xbff8, clint.get_mtime());

  for (int i = 1; i < 3; i++) {
    create_reg_recovery(rom, code_pos, data_pos, i, state->XPR[i]);
  }

  rom[(*code_pos)++] = create_csrrw(1, 0x7b2);
  create_csr64_recovery(rom, code_pos, data_pos, 0x180, state->satp->read());
  rom[(*code_pos)++] = create_csrrs(1, 0x7b2);
  rom[(*code_pos)++] = 0x7b200073;  // dret
}

}  // namespace

std::vector<char> build_checkpoint_trampoline_rom(unsigned xlen, reg_t target_pc)
{
  const int trampoline_size = 8;
  uint32_t trampoline[trampoline_size] = {
    0x297,
    0x28593 + (trampoline_size * 4 << 20),
    0xf1402573,
    (xlen == 32) ? 0x0182a283u : 0x0182b283u,
    0x28067,
    0,
    static_cast<uint32_t>(target_pc & 0xffffffffu),
    static_cast<uint32_t>((static_cast<uint64_t>(target_pc) >> 32) & 0xffffffffu),
  };
  for (int i = 0; i < trampoline_size; i++) {
    trampoline[i] = to_le(trampoline[i]);
  }

  std::vector<char> tramp_rom(reinterpret_cast<char*>(trampoline),
                              reinterpret_cast<char*>(trampoline) + sizeof(trampoline));
  return tramp_rom;
}

std::vector<char> build_checkpoint_restore_rom(
    sim_t& sim,
    clint_t& clint,
    const std::string& dtb)
{
  uint32_t rom[kCheckpointBootromSize / 4] = {0};

  uint32_t code_pos = 0;
  uint32_t data_pos = 0xB00;
  const uint32_t data_pos_start = data_pos;

  const reg_t clint_base = resolve_clint_base(dtb);
  std::vector<hart_restore_section_t> sections;
  sections.reserve(sim.get_harts().size());

  for (const auto& [hart_id, proc] : sim.get_harts()) {
    if (!proc) {
      std::cerr << "ERROR: null hart pointer in simulator hart map." << std::endl;
      std::exit(-4);
    }

    create_reg_recovery(rom, &code_pos, &data_pos, 6, hart_id);
    rom[code_pos++] = create_bne(10, 6, 8);

    hart_restore_section_t section;
    section.hart_id = hart_id;
    section.proc = proc;
    section.dispatch_jal_pos = code_pos;
    sections.push_back(section);
    rom[code_pos++] = 0;
  }

  // Unknown harts should not execute an arbitrary restore body.
  rom[code_pos++] = 0x10500073;  // wfi
  rom[code_pos++] = create_jal(0, -4);

  for (auto& section : sections) {
    section.body_pos = code_pos;
    append_restore_body(
        *section.proc, clint, clint_base, section.hart_id, rom, &code_pos, &data_pos);
  }

  for (const auto& section : sections) {
    const int32_t jal_off =
        static_cast<int32_t>((section.body_pos - section.dispatch_jal_pos) * sizeof(uint32_t));
    rom[section.dispatch_jal_pos] = create_jal(0, jal_off);
  }

  if ((kCheckpointBootromSize / 4) <= data_pos || data_pos_start <= code_pos) {
    std::cerr << "ERROR: ROM is too small. ROM_SIZE should increase." << std::endl;
    std::cerr << "Current code_pos=" << code_pos << " data_pos=" << data_pos
              << std::endl;
    std::exit(-6);
  }

  for (size_t i = 0; i < (kCheckpointBootromSize / 4); ++i) {
    rom[i] = to_le(rom[i]);
  }

  std::vector<char> bytes(reinterpret_cast<char*>(rom),
                          reinterpret_cast<char*>(rom) + sizeof(rom));
  return bytes;
}

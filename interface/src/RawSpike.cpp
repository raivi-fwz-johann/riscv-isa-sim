#include "RawSpike.hpp"

#include <algorithm>
#include <sstream>
#include <iostream>

#include "spike_init.h"
#include "SpikeRoiState.hpp"
#include "SpikeSimObjHooker.hpp"
#include "SpikeStateExporter.hpp"
#include "mmu.h"

namespace {

constexpr uint32_t kIntRegBase = 0x00;
constexpr uint32_t kFpRegBase = 0x20;
constexpr uint32_t kVecRegBase = 0x40;

uint32_t int_reg(uint32_t reg) { return kIntRegBase + reg; }
uint32_t fp_reg(uint32_t reg) { return kFpRegBase + reg; }
uint32_t vec_reg(uint32_t reg) { return kVecRegBase + reg; }

void push_unique(std::vector<RegValue>& regs, uint32_t flat_id)
{
  for (const auto& reg : regs) {
    if (reg.flat_id == flat_id) {
      return;
    }
  }
  regs.push_back({.flat_id = flat_id});
}

std::vector<PTWStep> build_ptw(sim_t* sim, processor_t* p, uint64_t vaddr)
{
  std::vector<PTWStep> steps;
  if (!sim || !p || p->get_xlen() != 64) {
    return steps;
  }

  const reg_t satp = p->get_state()->satp->read();
  if ((satp & SATP64_PPN) == 0) {
    return steps;
  }

  reg_t base = (satp & SATP64_PPN) << PGSHIFT;
  for (int level = 2; level >= 0; --level) {
    const reg_t idx = (vaddr >> (PGSHIFT + level * 9)) & 0x1ff;
    const reg_t pte_paddr = base + idx * 8;
    const reg_t pte = sim->from_target(sim->memif().read_uint64(pte_paddr));
    steps.push_back({.paddr = pte_paddr, .pte = pte});
    if (PTE_TABLE(pte)) {
      base = ((pte >> PTE_PPN_SHIFT) & SATP64_PPN) << PGSHIFT;
    } else {
      break;
    }
  }

  return steps;
}

void decode_src_regs(uint32_t bits, std::vector<RegValue>& src_regs)
{
  insn_t insn(bits);
  if (insn.length() != 4) {
    return;
  }

  switch (insn.opcode()) {
    case 0x03:
    case 0x13:
    case 0x1b:
    case 0x67:
      push_unique(src_regs, int_reg(insn.rs1()));
      break;
    case 0x07:
      push_unique(src_regs, int_reg(insn.rs1()));
      break;
    case 0x17:
    case 0x37:
    case 0x6f:
      break;
    case 0x23:
      push_unique(src_regs, int_reg(insn.rs1()));
      push_unique(src_regs, int_reg(insn.rs2()));
      break;
    case 0x27:
      push_unique(src_regs, int_reg(insn.rs1()));
      push_unique(src_regs, fp_reg(insn.rs2()));
      break;
    case 0x33:
    case 0x3b:
    case 0x63:
    case 0x2f:
      push_unique(src_regs, int_reg(insn.rs1()));
      push_unique(src_regs, int_reg(insn.rs2()));
      break;
    case 0x43:
    case 0x47:
    case 0x4b:
    case 0x4f:
      push_unique(src_regs, fp_reg(insn.rs1()));
      push_unique(src_regs, fp_reg(insn.rs2()));
      push_unique(src_regs, fp_reg(insn.rs3()));
      break;
    case 0x53:
      push_unique(src_regs, fp_reg(insn.rs1()));
      if (insn.funct7() != 0x70 && insn.funct7() != 0x78) {
        push_unique(src_regs, fp_reg(insn.rs2()));
      }
      break;
    case 0x57: {
      const auto funct3 = insn.funct3();
      if (funct3 == 7) {
        push_unique(src_regs, int_reg(insn.rs1()));
        if (insn.rs2() != 0) {
          push_unique(src_regs, int_reg(insn.rs2()));
        }
      } else {
        push_unique(src_regs, vec_reg(insn.rs2()));
        if (funct3 == 4 || funct3 == 6) {
          push_unique(src_regs, int_reg(insn.rs1()));
        } else {
          push_unique(src_regs, vec_reg(insn.rs1()));
        }
      }
      break;
    }
    case 0x73: {
      const auto funct3 = insn.funct3();
      if (funct3 == 1 || funct3 == 2 || funct3 == 3) {
        push_unique(src_regs, int_reg(insn.rs1()));
      }
      break;
    }
    default:
      break;
  }
}

void log_fetch_inst_trace(const InstTrace& trace)
{
  const auto trap = trace.GetTrapInfo();
  std::cout << "fetchInstOnly return {"
            << std::hex
            << "id=0x" << trace.getId()
            << ", pc=0x" << trace.getPc()
            << ", npc=0x" << trace.getNPc()
            << ", bits=0x" << trace.getBits()
            << ", ppn=0x" << trace.getPcPAddr()
            << ", ppn2=0x" << trace.getPcPAddr2()
            << std::boolalpha
            << ", in_trap=" << trace.inTrap()
            << ", in_wfi=" << trace.inWFI()
            << std::hex
            << ", cause=0x" << trap.cause
            << ", tval=0x" << trap.tval
            << ", has_tval2=" << trap.has_tval2
            << ", tval2=0x" << trap.tval2
            << ", mmu_paddr=0x" << trace.m_mmuTrace.paddr
            << "}"
            << std::noboolalpha
            << std::dec
            << std::endl;
}

}  // namespace

static Float128 toFloat128(float128_t val) {
  Float128 res;
  res.v[0] = val.v[0];
  res.v[1] = val.v[1];
  return res;
}

RawSpike::RawSpike() {}

RawSpike::~RawSpike() {}

void RawSpike::init(const std::string &ArgsStr) {
  std::vector<std::string> Args;
  std::stringstream ss(ArgsStr);
  std::string word;
  while (ss >> word) {
    Args.push_back(word);
  }

  m_Boot.reset();
  m_Simulator.reset();
  m_Cfg.reset();
  m_StateExporter.reset();
  m_RoiState.reset();

  int argc = static_cast<int>(Args.size());
  char **argv = new char *[argc+1];
  for (int i = 0; i < argc; ++i) {
    argv[i] = const_cast<char *>(Args[i].c_str());
  }
  argv[argc] = nullptr;
  sim_t *TmpSim = nullptr;
  m_Cfg = std::make_unique<cfg_t>();
  m_Boot = spike_init(argc, argv, TmpSim, *m_Cfg, [this](sim_t *s) {
    std::cout << "Processor count: " << s->nprocs() << std::endl;
    m_StateExporter = std::make_unique<spike_state_exporter_t>();
    m_StateExporter->reset(s->nprocs());
    m_RoiState = std::make_unique<spike_roi_state_t>();
    s->runtime_context()->set_hook_dispatcher(std::make_unique<SpikeSimObjHooker>(this));
  });
  (void)TmpSim;
  m_Simulator = std::move(m_Boot->sim);
  delete[] argv;
}

void RawSpike::start() {
  m_RunHelper.start(m_Simulator.get());
}

void RawSpike::stop() {
  m_RunHelper.stop(m_Simulator.get());
}

bool RawSpike::done() const { return m_Simulator->done() || m_Simulator->is_end(); }

size_t RawSpike::step(size_t n, uint32_t CId) {
  return m_RunHelper.step(m_Simulator.get(), n, CId);
}

int RawSpike::record(InstTrace &data, uint32_t CId) {
  if (!inROI(CId)) {
    return 1;
  }
  if (!m_StateExporter) {
    return -1;
  }

  auto p = m_Simulator->get_core(CId);
  auto* snapshot = m_StateExporter->snapshot(CId);
  if (!snapshot) {
    return -1;
  }
  if (!snapshot->in_trap && !snapshot->exec.valid) {
    return -1;
  }

  const bool in_trap = snapshot->in_trap;
  data.m_InTrap = in_trap;
  data.m_InWFI = inWFI(CId);
  data.cause_ = 0;
  data.tval_ = 0;
  data.has_tval2_ = false;
  data.tval2_ = 0;

  if (in_trap) {
    data.m_Pc = snapshot->epc;
    data.m_NPc = snapshot->trap_npc;
  } else {
    data.m_Pc = snapshot->exec.pc;
    data.m_NPc = snapshot->exec.npc;
  }
  if (data.m_NPc == ERROR_PC_ADDR) {
    data.m_NPc = p->get_state()->pc;
  }

  /* paddr: for trap use stale_fetch (pre-getNextInst-overwrite), else fetch > exec. */
  if (in_trap && snapshot->stale_fetch.valid) {
    data.m_PPN = snapshot->stale_fetch.paddr;
    data.m_PPN2 = snapshot->stale_fetch.paddr2;
  } else if (snapshot->fetch.valid) {
    data.m_PPN = snapshot->fetch.paddr;
    data.m_PPN2 = snapshot->fetch.paddr2;
  } else {
    data.m_PPN = snapshot->exec.paddr;
    data.m_PPN2 = snapshot->exec.paddr2;
  }
  if (data.m_PPN2 == ERROR_PC_ADDR || data.m_PPN2 == 0) {
    data.m_PPN2 = data.m_PPN;
  }

  /* bits: pre_exec (pc match) > stale_fetch (trap) > fetch > exec. */
  if (in_trap && snapshot->pre_exec.valid &&
      snapshot->pre_exec.pc == snapshot->epc) {
    data.m_Bits = snapshot->pre_exec.bits;
  } else if (in_trap && snapshot->stale_fetch.valid) {
    data.m_Bits = snapshot->stale_fetch.bits;
  } else if (in_trap && snapshot->fetch.valid) {
    data.m_Bits = snapshot->fetch.bits;
  } else if (snapshot->exec.valid) {
    data.m_Bits = snapshot->exec.bits;
  } else if (snapshot->fetch.valid) {
    data.m_Bits = snapshot->fetch.bits;
  }
  if (in_trap && data.m_Bits == 0) {
    data.m_Bits = (data.m_NPc - data.m_Pc == 4) ? 0x13 : 0x1;
  }

  if (!in_trap && data.m_Bits != 0) {
    const auto inst_len = static_cast<uint64_t>(insn_t(data.m_Bits).length());
    const auto page0 = std::min<uint64_t>(inst_len, PGSIZE - (data.m_Pc % PGSIZE));
    if (page0 != inst_len) {
      try {
        data.m_PPN2 = p->get_mmu()->vaddr2paddr(data.m_Pc + page0, 1, FETCH);
      } catch (...) {
        data.m_PPN2 = ERROR_PC_ADDR;
      }
    }
  }
  if (in_trap) {
    data.cause_ = snapshot->cause;
    data.tval_ = snapshot->tval;
    data.has_tval2_ = snapshot->has_tval2;
    data.tval2_ = snapshot->tval2;
  }
  data.m_mmuTrace = m_StateExporter->get_mmu_trace(CId);
  if (data.m_mmuTrace.paddr == 0 && snapshot->fetch.paddr != ERROR_PC_ADDR) {
    data.m_mmuTrace.paddr = snapshot->fetch.paddr;
  }
  if (in_trap && data.m_mmuTrace.excp_cause == 0) {
    data.m_mmuTrace.excp_cause = snapshot->cause;
  }
  data.m_FetchPtw.clear();
  auto walked_fetch_ptw = build_ptw(m_Simulator.get(), p, data.m_Pc);
  if (!walked_fetch_ptw.empty()) {
    data.m_FetchPtw = std::move(walked_fetch_ptw);
  } else {
    for (size_t i = 0; i < 5; ++i) {
      if (data.m_mmuTrace.pte_paddr[i] != 0) {
        data.m_FetchPtw.push_back({.paddr = data.m_mmuTrace.pte_paddr[i], .pte = 0});
      }
    }
  }
  data.m_SrcRegs.clear();
  decode_src_regs(data.m_Bits, data.m_SrcRegs);
  data.m_DstRegs.clear();
  data.m_VType = p->VU.vtype ? p->VU.vtype->read() : 0;
  data.m_Vl = p->VU.vl ? p->VU.vl->read() : 0;
  data.m_VStart = p->VU.vstart ? p->VU.vstart->read() : 0;
  data.m_ActiveMask = 0;
  if (p->any_vector_extensions()) {
    const auto mask_limit = std::min<uint64_t>(data.m_Vl, 64);
    for (uint64_t i = 0; i < mask_limit; ++i) {
      if (p->VU.mask_elt(0, i)) {
        data.m_ActiveMask |= (uint64_t(1) << i);
      }
    }
  }
  data.m_MemOps.clear();
  data.m_BranchTaken =
      !in_trap &&
      data.m_NPc != ERROR_PC_ADDR &&
      data.m_NPc != data.m_Pc + static_cast<uint64_t>(insn_t(data.m_Bits).length());
  data.m_Exception = in_trap ? static_cast<uint32_t>(snapshot->cause) : 0;

#if defined (FULL_TRACE) || defined (MEM_TRACE)
  // parse log_mem_read
  data.m_MemRs.clear();
  data.m_MemWs.clear();
  if (m_LogMem) {
    for (auto &item : p->get_state()->log_mem_read) {
      uint64_t paddr = std::get<3>(item);
    if (paddr == 0) {
      try {
        paddr = p->get_mmu()->vaddr2paddr(std::get<0>(item), std::get<2>(item), LOAD);
      } catch (...) {
        paddr = 0;
      }
    }
    uint64_t paddr2 = paddr;
    const auto page0 = std::min<uint64_t>(std::get<2>(item), PGSIZE - (std::get<0>(item) % PGSIZE));
    if (page0 != std::get<2>(item)) {
      try {
        paddr2 = p->get_mmu()->vaddr2paddr(std::get<0>(item) + page0, std::get<2>(item) - page0, LOAD);
      } catch (...) {
        paddr2 = paddr;
      }
    }
	    data.m_MemRs.emplace_back(std::get<0>(item), std::get<2>(item), std::get<1>(item), paddr, paddr2);
	    data.m_mmuTrace.paddr = paddr;
	    TraceMemOp op{.vaddr = std::get<0>(item), .paddr = paddr, .size_bytes = static_cast<uint8_t>(std::get<2>(item))};
	    op.ptw_steps = build_ptw(m_Simulator.get(), p, std::get<0>(item));
	    data.m_MemOps.push_back(std::move(op));
	  }
	  for (auto &item : p->get_state()->log_mem_write) {
    uint64_t paddr = std::get<3>(item);
    if (paddr == 0) {
      try {
        paddr = p->get_mmu()->vaddr2paddr(std::get<0>(item), std::get<2>(item), STORE);
      } catch (...) {
        paddr = 0;
      }
    }
    uint64_t paddr2 = paddr;
    const auto page0 = std::min<uint64_t>(std::get<2>(item), PGSIZE - (std::get<0>(item) % PGSIZE));
    if (page0 != std::get<2>(item)) {
      try {
        paddr2 = p->get_mmu()->vaddr2paddr(std::get<0>(item) + page0, std::get<2>(item) - page0, STORE);
      } catch (...) {
        paddr2 = paddr;
      }
    }
	    data.m_MemWs.emplace_back(std::get<0>(item), std::get<2>(item), std::get<1>(item), paddr, paddr2);
	    data.m_mmuTrace.paddr = paddr;
	    TraceMemOp op{.vaddr = std::get<0>(item), .paddr = paddr, .size_bytes = static_cast<uint8_t>(std::get<2>(item))};
	    op.ptw_steps = build_ptw(m_Simulator.get(), p, std::get<0>(item));
	    data.m_MemOps.push_back(std::move(op));
	  }
	  }
#endif

#if defined (FULL_TRACE)
  auto state = p->get_state();
  int xlen = state->last_inst_xlen;
  int flen = state->last_inst_flen;

  // parse log_reg_write
  {
    for (auto &item : state->log_reg_write) {
      if (item.first == 0) continue;

      int size = 0;
      int rd = item.first >> 4;
      bool is_vec = false;
      bool is_vreg = false;
      switch (item.first & 0xf) {
        case 0:
          size = xlen;
          break;
        case 1:
          size = flen;
          break;
        case 2:
          size = p->VU.VLEN;
          is_vreg = true;
          break;
        case 3:
          is_vec = true;
          break;
        case 4:
          size = xlen;
          break;
        default:
          assert("can't been here" && 0);
          break;
      }

      if (!is_vec) {
        size_t bytes = size / 8;

	        if (is_vreg) {
	          // malloc mem for reg value
	          char *value = new char[bytes];
	          memcpy(value, &p->VU.elt<uint8_t>(rd, 0), bytes);
	          data.m_RegWs.emplace_back(item.first, toFloat128(item.second), std::move(value), bytes);
	        } else {
	          data.m_RegWs.emplace_back(item.first, toFloat128(item.second), nullptr, bytes);
	        }
	        data.m_DstRegs.push_back({.flat_id = static_cast<uint32_t>(item.first)});
	      }
	    }
	  }

  data.m_LastInstPriv = state->last_inst_priv;
  data.m_LastInstXLen = state->last_inst_xlen;
  data.m_LastInstFLen = state->last_inst_flen;

  auto satp = p->get_state()->satp->read();
  data.satp_ = satp;
  data.m_Asid = get_field(satp, xlen == 32 ? SATP32_ASID : SATP64_ASID);

  data.m_Status = {p->get_state()->prv, p->get_state()->v,
              p->get_state()->debug_mode,
              p->get_csr(0x300)};
#endif

	  return 0;
}

InstTrace RawSpike::fetchInstOnly(uint64_t Pc, uint32_t CId, uint64_t IId) {
  InstTrace res(IId, Pc);
  try {
    auto insn = m_Simulator->get_core(CId)->get_mmu()->ext_fetch_insn(Pc);
  res = InstTrace(IId, Pc, insn.insn.bits(), insn.pc_ppn);
  } catch (...) {
  }
  log_fetch_inst_trace(res);
  return res;
}

uint64_t RawSpike::vaddr2paddr(uint64_t vaddr, uint32_t CId) {
  try {
    auto paddr = m_Simulator->get_core(CId)->get_mmu()->vaddr2paddr(vaddr);
    if (m_StateExporter) {
      m_StateExporter->set_mmu_paddr(CId, paddr);
    }
    return paddr;
  } catch (...) {
    return vaddr;
  }
}

MmuTrace RawSpike::getMmuTrace(uint32_t CId)
{
    return m_StateExporter ? m_StateExporter->get_mmu_trace(CId) : MmuTrace{};
}

bool RawSpike::inROI(uint32_t cid) const {
  (void)cid;
  return !m_RoiState || m_RoiState->in_roi();
}

void RawSpike::setupROI(bool val) {
  if (m_RoiState) {
    m_RoiState->set_enabled(val);
  }
}

size_t RawSpike::nproc() const { return m_Simulator->nprocs(); }

uint64_t RawSpike::getCurrPc(uint32_t cid) const { return m_Simulator->get_core(cid)->get_state()->pc; }

bool RawSpike::inTrap(uint32_t CId) const {
  return m_StateExporter && m_StateExporter->in_trap(CId);
}

bool RawSpike::inWFI(uint32_t CId) const {
  return m_Simulator->get_core(CId)->is_waiting_for_interrupt();
}

void RawSpike::setInterleave(size_t val) {
  m_Simulator->set_interleave(val);
}

void RawSpike::setLogCommits(bool LogCommits, bool IsFast, [[maybe_unused]]uint32_t cid) {
  m_Simulator->configure_log(false, LogCommits && !IsFast);
  if (auto* runtime = m_Simulator->runtime_context()) {
    if (auto* manager = runtime->log_manager()) {
      manager->set_enable_fast_commit_log(IsFast);
      manager->set_enable_fast_mem_log(IsFast);
    }
  }
}

void RawSpike::setLogMem(bool val) {
  m_LogMem = val;
  if (auto* runtime = m_Simulator->runtime_context()) {
    if (auto* manager = runtime->log_manager()) {
      manager->set_enable_fast_mem_log(val);
    }
  }
}

void RawSpike::setCycle(uint64_t Value, uint32_t cid) {
  auto* state = m_Simulator->get_core(cid)->get_state();
  auto& mcycle = state->mcycle;

  // setCycle is an external synchronization hook, not an architectural CSR
  // write. Clear any previous explicit-write bookkeeping before overriding
  // the counter value again in the same host-side control flow.
  mcycle->bump(0);
  if (mcycle->read() != Value) {
    mcycle->write(Value);
  }
}

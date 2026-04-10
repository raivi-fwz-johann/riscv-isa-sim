#include "RawSpike.hpp"

#include <sstream>

#include "spike_init.h"
#include "SpikeSimObjHooker.hpp"
#include "mmu.h"

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
    m_Shadow = std::vector<RawSpikeShadowState>(s->nprocs());
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

bool RawSpike::done() const { return m_Simulator->done(); }

size_t RawSpike::step(size_t n, uint32_t CId) {
  m_CurrCId = CId;
  return m_RunHelper.step(m_Simulator.get(), n, CId);
}

int RawSpike::record(InstTrace &data, uint32_t CId) {
  if (!inROI(CId)) {
    return 1;
  }
  if (CId >= m_Shadow.size()) {
    return -1;
  }

  auto p = m_Simulator->get_core(CId);
  auto &shadow = m_Shadow[CId];
  auto &observed = shadow.observed;
  if (!observed.valid) {
    return -1;
  }

  data.m_InTrap = observed.in_trap;
  data.m_InWFI = inWFI(CId);

  data.m_Pc = observed.pc;
  data.m_Bits = observed.bits;
  data.m_PPN = observed.paddr;
  data.m_PPN2 = observed.paddr2;
  data.m_NPc = observed.npc == ERROR_PC_ADDR ? p->get_state()->pc : observed.npc;
  if (!observed.in_trap && data.m_Bits != 0) {
    const auto inst_len = insn_t(data.m_Bits).length();
    const auto page0 = std::min<uint64_t>(inst_len, PGSIZE - (data.m_Pc % PGSIZE));
    if (page0 != inst_len) {
      try {
        data.m_PPN2 = p->get_mmu()->vaddr2paddr(data.m_Pc + page0, 1, FETCH);
      } catch (...) {
        data.m_PPN2 = ERROR_PC_ADDR;
      }
    }
  }
  if (observed.in_trap) {
    data.cause_ = observed.cause;
    data.tval_ = observed.tval;
    data.has_tval2_ = observed.has_tval2;
    data.tval2_ = observed.tval2;
  }
  shadow.mmu_trace = {};
  shadow.mmu_trace.paddr = observed.paddr;
  if (observed.in_trap) {
    shadow.mmu_trace.excp_cause = observed.cause;
  }

#if defined (FULL_TRACE) || defined (MEM_TRACE)
  // parse log_mem_read
  data.m_MemRs.clear();
  data.m_MemWs.clear();
  if (m_LogMem) {
    for (auto &item : p->get_state()->log_mem_read) {
      uint64_t paddr = 0;
    try {
      paddr = p->get_mmu()->vaddr2paddr(std::get<0>(item), std::get<2>(item), LOAD);
    } catch (...) {
      paddr = 0;
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
    shadow.mmu_trace.paddr = paddr;
  }
  for (auto &item : p->get_state()->log_mem_write) {
    uint64_t paddr = 0;
    try {
      paddr = p->get_mmu()->vaddr2paddr(std::get<0>(item), std::get<2>(item), STORE);
    } catch (...) {
      paddr = 0;
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
    shadow.mmu_trace.paddr = paddr;
  }
  }
#endif

  observed.reset();

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
  try {
    auto insn = m_Simulator->get_core(CId)->get_mmu()->ext_fetch_insn(Pc);
    return InstTrace(IId, Pc, insn.insn.bits(), insn.pc_ppn);
  } catch (...) {
    return InstTrace(IId, Pc);
  }
}

uint64_t RawSpike::vaddr2paddr(uint64_t vaddr, uint32_t CId) {
  try {
    auto paddr = m_Simulator->get_core(CId)->get_mmu()->vaddr2paddr(vaddr);
    if (CId < m_Shadow.size()) {
      m_Shadow[CId].mmu_trace.paddr = paddr;
    }
    return paddr;
  } catch (...) {
    return vaddr;
  }
}

MmuTrace RawSpike::getMmuTrace(uint32_t CId)
{
    if (CId >= m_Shadow.size()) {
      return {};
    }
    return m_Shadow[CId].mmu_trace;
}

bool RawSpike::inROI(uint32_t cid) const {
  (void)cid;
  return true;
}

void RawSpike::setupROI(bool val) {
  m_ROIOn = val;
}

size_t RawSpike::nproc() const { return m_Simulator->nprocs(); }

uint64_t RawSpike::getCurrPc(uint32_t cid) const { return m_Simulator->get_core(cid)->get_state()->pc; }

bool RawSpike::inTrap(uint32_t CId) const {
  if (CId >= m_Shadow.size()) {
    return false;
  }
  return m_Shadow[CId].observed.in_trap;
}

bool RawSpike::inWFI(uint32_t CId) const {
  return m_Simulator->get_core(CId)->is_waiting_for_interrupt();
}

void RawSpike::setInterleave(size_t val) {
  (void)val;
}

void RawSpike::setLogCommits(bool LogCommits, bool IsFast, [[maybe_unused]]uint32_t cid) {
  m_Simulator->configure_log(false, LogCommits && !IsFast);
  if (auto* runtime = m_Simulator->runtime_context()) {
    if (auto* manager = runtime->log_manager()) {
      manager->set_enable_fast_commit_log(IsFast);
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

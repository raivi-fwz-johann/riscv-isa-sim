#include "RawSpike.hpp"

#include <sstream>

#include "spike_init.h"
#include "SpikeSimObjHooker.hpp"

static Float128 toFloat128(float128_t val) {
  Float128 res;
  res.v[0] = val.v[0];
  res.v[1] = val.v[1];
  return res;
}

RawSpike::RawSpike() {
  if (g_spike_hooker) {
    throw std::runtime_error("g_spike_hooker is not null");
  }
  g_spike_hooker = std::make_shared<SpikeSimObjHooker>(this);
}

RawSpike::~RawSpike() {
  g_spike_hooker.reset();
}

void RawSpike::init(const std::string &ArgsStr) {
  std::vector<std::string> Args;
  std::stringstream ss(ArgsStr);
  std::string word;
  while (ss >> word) {
    Args.push_back(word);
  }

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
  spike_init(argc, argv, TmpSim, *m_Cfg, [this](sim_t *s) {
    std::cout << "Processor count: " << s->nprocs() << std::endl;
  });
  m_Simulator.reset(TmpSim);
  delete argv;
}

void RawSpike::start() {
  m_RunHelper.start(m_Simulator.get());
}

void RawSpike::stop() {
  m_RunHelper.stop(m_Simulator.get());
}

bool RawSpike::done() const { return m_Simulator->done() or m_Simulator->is_end(); }

size_t RawSpike::step(size_t n, uint32_t CId) {
  return m_RunHelper.step(m_Simulator.get(), n, CId);
}

int RawSpike::record(InstTrace &data, uint32_t CId) {
  if (not inROI(CId)) {
    return 1;
  }
  auto p = m_Simulator->get_core(CId);
  auto &curr_info = p->curr_info;
  data.m_InTrap = curr_info.in_trap;
  data.m_InWFI = inWFI(CId);
  // if (not curr_info.in_trap and curr_info.vpc == p->pre_info_pc) {
  //   // std::cout << std::hex << "record " << p->pre_info_pc << std::dec << std::endl;
  //   return -1;
  // }

  if (curr_info.in_trap) {
    data.m_Pc = curr_info.epc;
    data.m_NPc = p->get_state()->pc;
    data.m_Bits = curr_info.bits != 0 ? curr_info.bits : (data.m_NPc - data.m_Pc == 4 ? 0x13 : 0x1);
    data.m_PPN = curr_info.ppc;
    data.m_PPN2 = curr_info.ppc2;
    data.m_InTrap = true;
    data.cause_ = curr_info.cause;
    data.tval_  = curr_info.tval;
    data.has_tval2_ = curr_info.has_tval2;
    data.tval2_ = curr_info.tval2;
  } else {
    data.m_Pc = curr_info.vpc;
    data.m_Bits = curr_info.bits;
    data.m_PPN = curr_info.ppc;
    data.m_PPN2 = curr_info.ppc2;
    data.m_NPc = p->get_state()->pc;
  }
  curr_info.bits = 0; /* Set 0 so as to determine if the bits is captured in instruction executing. */

#if defined (FULL_TRACE) || defined (MEM_TRACE)
  // parse log_mem_read
  data.m_MemRs.clear();
  for (auto &item : p->get_state()->log_mem_read) {
    data.m_MemRs.emplace_back(std::get<0>(item), std::get<2>(item), std::get<1>(item), std::get<3>(item), std::get<4>(item));
  }
  data.m_MemWs.clear();
  for (auto &item : p->get_state()->log_mem_write) {
    data.m_MemWs.emplace_back(std::get<0>(item), std::get<2>(item), std::get<1>(item), std::get<3>(item), std::get<4>(item));
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
  insn_fetch_t insn;
  try {
    insn = m_Simulator->get_core(CId)->get_mmu()->ext_fetch_insn(Pc);
  } catch (...) {
    return InstTrace(IId, Pc);
  }
  return InstTrace(IId, Pc, insn.insn.bits(), insn.pc_ppn);
}

uint64_t RawSpike::vaddr2paddr(uint64_t vaddr, uint32_t CId) {
  try {
    return m_Simulator->get_core(CId)->get_mmu()->vaddr2paddr(vaddr);
  } catch (...) {
    return vaddr;
  }
}

MmuTrace RawSpike::getMmuTrace(uint32_t CId)
{
    auto m_trace = m_Simulator->get_core(CId)->get_mmu()->mmu_trace;
    return *reinterpret_cast<MmuTrace*>(&m_trace);
}

bool RawSpike::inROI(uint32_t cid) const {
  return not m_ROIOn or m_Simulator->get_tools_module()->get_roi_match().in_roi();
}

void RawSpike::setupROI(bool val) {
  m_ROIOn = val;
}

size_t RawSpike::nproc() const { return m_Simulator->nprocs(); }

uint64_t RawSpike::getCurrPc(uint32_t cid) const { return m_Simulator->get_core(cid)->get_state()->pc; }

bool RawSpike::inTrap(uint32_t CId) const { return m_Simulator->get_core(CId)->curr_info.in_trap;}

bool RawSpike::inWFI(uint32_t CId) const {
  return m_Simulator->get_core(CId)->is_waiting_for_interrupt();
}

void RawSpike::setInterleave(size_t val) {
  m_Simulator->set_interleave(val);
}

void RawSpike::setLogCommits(bool LogCommits, bool IsFast, [[maybe_unused]]uint32_t cid) {
  if (IsFast) {
    LogCommits = false;
  }
  m_Simulator->set_log_commits(LogCommits);
  m_Simulator->set_fast_log_commits(IsFast);
}

void RawSpike::setLogMem(bool val) {
  m_Simulator->set_fast_log_mem(val);
}

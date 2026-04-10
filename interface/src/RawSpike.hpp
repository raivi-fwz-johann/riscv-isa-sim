#pragma once

#include "RawSim.hpp"

#include "Memory.hpp"
#include "RawSpikeShadowState.hpp"
#include "run_helper.h"
#include <optional>
#include <vector>

class sim_t;
class cfg_t;
struct spike_boot_result_t;
struct xlate_flags_t;
struct mmu_trace_t;

class RawSpike : public RawSim {
public:
  RawSpike();
  ~RawSpike();
  void init(const std::string &ArgsStr) override;
  void start() override;
  void stop() override;
  bool done() const override;
  size_t step(size_t n, uint32_t CId) override;
  int record(InstTrace &data, uint32_t CId) override;
  InstTrace fetchInstOnly(uint64_t Pc, uint32_t CId, uint64_t IId) override;
  uint64_t vaddr2paddr(uint64_t vaddr, uint32_t CId);
  MmuTrace getMmuTrace(uint32_t CId);
  void setupROI(bool val) override;
  bool inROI(uint32_t cid) const override;
  size_t nproc() const override;
  uint64_t getCurrPc(uint32_t cid) const override;
  bool inTrap(uint32_t CId) const override;
  bool inWFI(uint32_t CId) const override;

  void setInterleave(size_t val);
  void setLogCommits(bool LogCommits, bool IsFast, uint32_t cid);
  void setLogMem(bool val);

  sim_t *getSpikeSimulator() { return m_Simulator.get(); }

private:
  std::unique_ptr<spike_boot_result_t> m_Boot;
  std::unique_ptr<sim_t> m_Simulator;
  std::unique_ptr<cfg_t> m_Cfg;
  std::vector<RawSpikeShadowState> m_Shadow;

  run_helper_t m_RunHelper;
  bool m_ROIOn = false;
  size_t m_CurrCId = 0;

  friend class SpikeSimObjHooker;
};

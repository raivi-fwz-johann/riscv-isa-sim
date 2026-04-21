#pragma once

#include "RawSim.hpp"

#include "Memory.hpp"
#include "run_helper.h"
#include <memory>

class sim_t;
class cfg_t;
struct spike_boot_result_t;
struct xlate_flags_t;
struct mmu_trace_t;
class spike_state_exporter_t;
class spike_roi_state_t;

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
  void setCycle(uint64_t Value, uint32_t cid = 0);

  sim_t *getSpikeSimulator() { return m_Simulator.get(); }

private:
  std::unique_ptr<spike_boot_result_t> m_Boot;
  std::unique_ptr<sim_t> m_Simulator;
  std::unique_ptr<cfg_t> m_Cfg;
  std::unique_ptr<spike_state_exporter_t> m_StateExporter;
  std::unique_ptr<spike_roi_state_t> m_RoiState;

  run_helper_t m_RunHelper;
  bool m_LogMem = true;

  friend class SpikeSimObjHooker;
};

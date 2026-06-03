#pragma once

#include "FuncSimAdapter.hpp"
#include "functrace/InstInfoHolder.hpp"
#include "functrace/PathHandler.hpp"

#include <memory>
#include <mutex>
#include <vector>

class RawSpike;

class SpikeSimObjSync : public FuncSimAdapter {
public:
  static SpikeSimObjSync &globalInstance();

  SpikeSimObjSync();
  ~SpikeSimObjSync() override;

  void init(const std::string &ArgsStr) override;
  void init(const std::vector<std::string> &Args) override;
  void initROICount(int num) override;
  void start() override;
  void stop() override;
  void waitStop() override {}
  bool done() const override;
  size_t step(size_t n, uint32_t CId = 0) override;
  void resetNPc(uint64_t NPc, uint32_t CId = 0) override;
  InstUserPtr reqInst(uint32_t CId = 0) override;
  InstUserPtr requestInst(uint64_t expected_pc, uint32_t CId = 0) override;
  void freeInst(InstUserPtr &InstPtr, uint32_t CId = 0) override;
  void freeInst(uint64_t IId, uint32_t CId = 0) override;
  std::shared_ptr<InstTrace> &takeInst(uint32_t CId = 0) override;
  void resolve(uint64_t InstUId, uint32_t CId = 0) override;
  void replay(uint64_t InstUId, uint32_t CId = 0) override;
  InstTrace fetchInstOnly(uint64_t Pc, uint32_t CId = 0,
                          uint64_t IId = INVALID_INST_ID) override;
  RawSim *getRawSim() override;
  uint64_t vaddr2paddr(uint64_t vaddr, uint32_t CId) const override;
  void setCycle(uint64_t value, uint32_t CId = 0) override;
  bool inROI(uint32_t cid = 0) const override;
  bool inWFI(uint32_t cid = 0) const override;
  uint64_t getCurrPc(uint32_t cid = 0) const override;
  uint64_t getConfiguredNPc(uint32_t cid = 0) const override;
  const PathHandler &getPathHandler(uint32_t CId) const override;
  uint64_t getCurrInstNPc(uint32_t CId) const override;
  void setInterleave(size_t val) override;
  void setLogMem(bool val) override;
  void setLogCommits(bool log_commits, bool is_fast, uint32_t cid = 0) override;

  InstInfoHolder &correctHolder(uint32_t CId) override;
  const InstInfoHolder &correctHolder(uint32_t CId) const override;
  InstInfoHolder &missHolder(uint32_t CId) override;
  const InstInfoHolder &missHolder(uint32_t CId) const override;
  uint64_t &missIdCursor(uint32_t CId) override;
  uint64_t backendCurrPc(uint32_t CId) const override;

protected:
  struct CoreInfo {
    std::shared_ptr<InstTrace> m_NewInst;
    bool m_NewInstValid{false};

    uint64_t m_IdToAlloc{0};
    InstInfoHolder m_IHolder;
    PathHandler m_PathHandler;

    size_t m_stepToIgnore{0};
    uint64_t m_MissIdToAlloc{MISS_ID_FLAG};
    InstInfoHolder m_MissIHolder{false};

    uint64_t prev_rollback_id{0};
  };

  size_t stepSync(size_t n, uint32_t CId);
  void rollback(uint64_t InstUId, uint32_t CId);
  std::shared_ptr<InstTrace> &takeProducedInst(uint32_t CId);

  std::unique_ptr<RawSpike> m_SimImpl;
  std::vector<CoreInfo> m_CoreInfos;
  mutable std::mutex m_Mtx;
  std::shared_ptr<InstTrace> m_Dummy{nullptr};
};

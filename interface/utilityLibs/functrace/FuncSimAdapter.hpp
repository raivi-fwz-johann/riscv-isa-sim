/**
 * @file FuncSimAdapter.hpp
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-12-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "Memory.hpp"
#include <string>
#include <mutex>

#include "functrace/InstInfoHolder.hpp"
#include "functrace/InstTrace.hpp"
#include "functrace/PathHandler.hpp"
#include "functrace/RawSim.hpp"

#define INST_COUNT_TO_LOG 10000000

class FuncSimAdapter {
public:
  static FuncSimAdapter &globalInstance();

  FuncSimAdapter();
  virtual ~FuncSimAdapter();

  /* After setFuncSim, ptr will be nullptr. */
  void setFuncSim(RawSim *&&ptr);
  RawSim *getRawSim() { return m_SimImpl; }
  bool hasFuncSim() const { return m_SimImpl; }

  void init(const std::string &ArgsStr);
  void init(const std::vector<std::string> &Args);
  virtual void initROICount(int num);
  virtual void start();
  virtual void stop();
  virtual void waitStop() {}
  virtual bool done() const;
  virtual size_t step(size_t n, uint32_t CId = 0);
  void resetNPc(uint64_t NPc, uint32_t CId = 0);

  InstUserPtr reqInst(uint32_t CId = 0);
  InstUserPtr requestInst(uint64_t expected_pc, uint32_t CId = 0);
  void freeInst(InstUserPtr &InstPtr, uint32_t CId = 0);
  void freeInst(uint64_t IId, uint32_t CId = 0);

  /**
   * @brief Used in function model
   */
  virtual std::shared_ptr<InstTrace> &takeInst(uint32_t CId = 0);

  void resolve(uint64_t InstUId, uint32_t CId = 0);
  void replay(uint64_t InstUId, uint32_t CId = 0);

  InstTrace fetchInstOnly(uint64_t Pc, uint32_t CId = 0,
                          uint64_t IId = INVALID_INST_ID);  // -------------

  uint64_t vaddr2paddr(uint64_t vaddr, uint32_t CId) const;

  virtual bool inROI(uint32_t cid = 0) const;
  uint64_t getCurrPc(uint32_t cid = 0) const;
  uint64_t getConfiguredNPc(uint32_t cid = 0) const;

private:
  void rollback(uint64_t InstUId, uint32_t CId);

  bool getMissPredict(uint32_t CId) const;
  InstUserPtr getActiveInst(uint32_t CId) const; /* not use now, to be removed */

protected:
  RawSim *m_SimImpl{nullptr};

  // Info per core
  struct CoreInfo {
    std::shared_ptr<InstTrace> m_NewInst;
    bool m_NewInstValid{false};

    uint64_t m_IdToAlloc{0};
    InstInfoHolder m_IHolder;
    PathHandler m_PathHandler;

    size_t m_stepToIgnore{0};
    uint64_t m_MissIdToAlloc{MISS_ID_FLAG};
    InstInfoHolder m_MissIHolder;

    uint64_t prev_rollback_id{ 0 };
  };
  std::vector<CoreInfo> m_CoreInfos;

  std::mutex m_Mtx;
  std::shared_ptr<InstTrace> m_Dummy{nullptr};

  friend class SpikeSimObjHooker;
  friend class PathHandler;
  friend class BackupMgr;
  friend class SimObjDebugger;
  friend class LogCommitCtrl;
};

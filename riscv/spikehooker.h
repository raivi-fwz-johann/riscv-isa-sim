/**
 * @file spikehooker.h
 * @author rick (binglin.qiu@rivai.ai)
 * @brief The base class which define serveal interface function to hook spike action, the actual behaviors should be defined in sub-class. 
 * @version 0.1
 * @date 2024-12-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _SPIKE_HOOKER_H_
#define _SPIKE_HOOKER_H_

#include <memory>
#include <iostream>

class insn_fetch_t;
class trap_t;
class simif_t;
using SimID = simif_t*;

class SpikeHooker {
public:
  virtual bool backupOn() const { return false; }
  virtual char *getHostAddr(uint64_t, char *spike_host_addr, SimID) { return spike_host_addr; }
  virtual void load(uint64_t, char *, uint64_t, uint8_t *, SimID) {}
  virtual void store(uint64_t, char *, uint64_t, const uint8_t *, SimID) {}
  virtual bool isMissPredict() const { return false; }
  virtual bool hook_exit(int) { return true; }
  virtual bool exitHook(int code) { return hook_exit(code); }
  virtual void decodeHook(void*, uint64_t, uint64_t) {}
  virtual bool commitHook() { return false; }
  virtual uint64_t getNpcHook(uint64_t spike_npc) { return spike_npc; }
  virtual uint64_t excptionHook(void *, uint64_t, trap_t &) { return 0; }
  virtual void catchDataBeforeWriteHook(uint64_t, uint64_t, uint32_t, std::shared_ptr<bool>) {}
  virtual void catchDataBeforeCsrHook(int, uint64_t, std::shared_ptr<bool>) {}

  void setCid(int cid) { cid_ = cid; }
  void setDummyStored(bool val) { dummy_stored_ = val; }
  bool getDummyStored() const { return dummy_stored_; }
  void setDebug(bool val) { debug_ = val; }
  bool getDebug() const { return debug_; }
  void setSim(SimID sim1, SimID sim2) {
    sim_ = sim1 ? sim1 : sim_;
    sim_fast_ = sim2 ? sim2 : sim_fast_;
  }

  static void exit(int code);

  virtual void onExecInsn(insn_fetch_t*, uint64_t, uint64_t) {}
  virtual void onHandleFakeStep(size_t, size_t) {}

protected:
  int cid_ = 0;
  bool dummy_stored_ = false;
  bool debug_ = false;
  SimID sim_ = nullptr;
  SimID sim_fast_ = nullptr;
};

inline std::shared_ptr<SpikeHooker> g_spike_hooker = nullptr;

inline void SpikeHooker::exit(int code) {
  if (g_spike_hooker) {
    g_spike_hooker->hook_exit(code);
  } else {
    exit(code);
  }
}

#define HOOK_EXEC(func, ...) if (g_spike_hooker) g_spike_hooker->func(__VA_ARGS__)

#define HOOK_BOOL(boolfunc) (g_spike_hooker and g_spike_hooker->boolfunc())
#define BACKUP_ON (g_spike_hooker and g_spike_hooker->backupOn())
#define BACKUP_BOOL(boolfunc) (BACKUP_ON and g_spike_hooker->boolfunc())
#define BACKUP_EXEC(func) if (BACKUP_ON) g_spike_hooker->func()
#define BACKUP_EXEC_ARG(func, arg) if (BACKUP_ON) g_spike_hooker->func(arg)

#endif

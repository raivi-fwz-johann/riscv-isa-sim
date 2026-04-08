#pragma once

#include "runtime/hook_events.h"

class spike_hook_dispatcher_t {
public:
  virtual ~spike_hook_dispatcher_t() = default;

  virtual void on_decode(void*, reg_t, reg_t) {}
  virtual bool on_commit() { return false; }
  virtual reg_t on_next_pc(reg_t candidate_npc) { return candidate_npc; }
  virtual reg_t on_trap(void*, reg_t, trap_t&) { return 0; }
  virtual bool should_continue() { return true; }
  virtual void on_pre_store(reg_t, reg_t, uint32_t, std::shared_ptr<bool>) {}
  virtual bool allow_csr_write(int, reg_t) { return true; }
  virtual void on_pre_csr(int, reg_t, std::shared_ptr<bool>) {}
  virtual bool on_exit(int) { return true; }
  virtual void on_exec_observe(insn_fetch_t*, reg_t, reg_t) {}
  virtual void on_fake_step(size_t, size_t) {}
};

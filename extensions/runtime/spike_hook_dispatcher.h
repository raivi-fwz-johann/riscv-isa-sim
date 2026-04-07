#pragma once

#include "runtime/hook_events.h"

class spike_hook_dispatcher_t {
public:
  virtual ~spike_hook_dispatcher_t() = default;

  virtual void on_decode(const decode_event_t&) {}
  virtual bool on_commit(const commit_event_t&) { return false; }
  virtual next_pc_decision_t on_next_pc(const next_pc_event_t&) { return {}; }
  virtual trap_decision_t on_trap(const trap_event_t&) { return {}; }
  virtual bool should_continue(const continue_event_t&) { return true; }
  virtual void on_pre_store(pre_store_event_t&) {}
  virtual bool allow_csr_write(const csr_gate_event_t&) { return true; }
  virtual void on_pre_csr(pre_csr_event_t&) {}
  virtual exit_decision_t on_exit(const exit_event_t&) { return {.allow_exit = true}; }
  virtual void on_exec_observe(const exec_observe_event_t&) {}
  virtual void on_fake_step(const fake_step_event_t&) {}
};

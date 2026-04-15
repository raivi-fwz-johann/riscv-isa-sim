#pragma once

#include "runtime/spike_hook_dispatcher.h"

class sparta_legacy_hook_adapter_t final : public spike_hook_dispatcher_t {
public:
  void on_decode(const decode_event_t&) override;
  bool on_commit(const commit_event_t&) override;
  next_pc_decision_t on_next_pc(const next_pc_event_t&) override;
  trap_decision_t on_trap(const trap_event_t&) override;
  bool should_continue(const continue_event_t&) override;
  void on_pre_store(pre_store_event_t&) override;
  bool allow_csr_write(const csr_gate_event_t&) override;
  void on_pre_csr(pre_csr_event_t&) override;
  exit_decision_t on_exit(const exit_event_t&) override;
};

#pragma once

#include "runtime/spike_hook_dispatcher.h"

class legacy_hook_adapter_t final : public spike_hook_dispatcher_t {
public:
  void on_decode(void*, reg_t, reg_t) override;
  bool on_commit() override;
  reg_t on_next_pc(reg_t) override;
  reg_t on_trap(void*, reg_t, trap_t&) override;
  bool should_continue() override;
  void on_pre_store(reg_t, reg_t, uint32_t, std::shared_ptr<bool>) override;
  bool allow_csr_write(int, reg_t) override;
  void on_pre_csr(int, reg_t, std::shared_ptr<bool>) override;
  bool on_exit(int) override;
};

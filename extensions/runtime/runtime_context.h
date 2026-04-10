#pragma once

#include "runtime/spike_step_policy.h"
#include "runtime/spike_log_manager.h"
#include "runtime/spike_hook_dispatcher.h"
#include <memory>

class spike_runtime_context_t {
public:
  spike_runtime_context_t();

  spike_hook_dispatcher_t* hook_dispatcher() const { return hook_dispatcher_.get(); }
  void set_hook_dispatcher(std::unique_ptr<spike_hook_dispatcher_t> hook) { hook_dispatcher_ = std::move(hook); }

  spike_log_manager_t* log_manager() const { return log_manager_.get(); }
  void set_log_manager(std::unique_ptr<spike_log_manager_t> log_manager) { log_manager_ = std::move(log_manager); }

  spike_step_policy_t* step_policy() const { return step_policy_.get(); }
  void set_step_policy(std::unique_ptr<spike_step_policy_t> step_policy) { step_policy_ = std::move(step_policy); }

private:
  std::unique_ptr<spike_hook_dispatcher_t> hook_dispatcher_;
  std::unique_ptr<spike_log_manager_t> log_manager_;
  std::unique_ptr<spike_step_policy_t> step_policy_;
};

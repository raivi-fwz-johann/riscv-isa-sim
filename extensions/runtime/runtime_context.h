#pragma once

#include "checkpoint/checkpoint_controller.h"
#include "runtime/spike_host_policy.h"
#include "runtime/spike_hook_dispatcher.h"
#include "runtime/spike_log_manager.h"
#include "runtime/spike_model_compat.h"
#include <memory>

class spike_runtime_context_t {
public:
  spike_runtime_context_t();

  spike_hook_dispatcher_t* hook_dispatcher() const { return hook_dispatcher_.get(); }
  void set_hook_dispatcher(std::unique_ptr<spike_hook_dispatcher_t> hook) { hook_dispatcher_ = std::move(hook); }

  spike_log_manager_t* log_manager() const { return log_manager_.get(); }
  void set_log_manager(std::unique_ptr<spike_log_manager_t> log_manager) { log_manager_ = std::move(log_manager); }

  spike_model_compat_t* model_compat() const { return model_compat_.get(); }
  void set_model_compat(std::unique_ptr<spike_model_compat_t> model_compat) {
    model_compat_ = std::move(model_compat);
  }

  spike_host_policy_t* host_policy() const { return host_policy_.get(); }
  void set_host_policy(std::unique_ptr<spike_host_policy_t> host_policy) { host_policy_ = std::move(host_policy); }

  checkpoint_controller_t* checkpoint_controller() const { return checkpoint_controller_.get(); }
  void set_checkpoint_controller(std::unique_ptr<checkpoint_controller_t> controller) {
    checkpoint_controller_ = std::move(controller);
  }

private:
  std::unique_ptr<spike_hook_dispatcher_t> hook_dispatcher_;
  std::unique_ptr<spike_log_manager_t> log_manager_;
  std::unique_ptr<spike_model_compat_t> model_compat_;
  std::unique_ptr<spike_host_policy_t> host_policy_;
  std::unique_ptr<checkpoint_controller_t> checkpoint_controller_;
};

#pragma once

#include "checkpoint/checkpoint_controller.h"
#include "runtime/spike_host_policy.h"
#include "runtime/spike_hook_dispatcher.h"
#include "runtime/spike_log_manager.h"
#include "runtime/spike_model_compat.h"
#include <memory>

// Central runtime bus owned by sim_t.  Provides uniform access to all
// extension services so that sim_t / processor_t / mmu_t do not need
// individual members for each extension object.
//
// All setters take unique_ptr, transferring ownership to the context.
// All getters return a raw (non-owning) pointer, or nullptr if not set.
class spike_runtime_context_t {
public:
  spike_runtime_context_t();

  // -- hook dispatcher -------------------------------------------------------
  // Returns the currently installed hook dispatcher, or nullptr.
  // [return] non-owning pointer, lifetime managed by this context
  spike_hook_dispatcher_t* hook_dispatcher() const { return hook_dispatcher_.get(); }
  // Install a hook dispatcher.  Pass nullptr to remove.
  // [in] hook  unique_ptr, ownership transferred
  void set_hook_dispatcher(std::unique_ptr<spike_hook_dispatcher_t> hook) { hook_dispatcher_ = std::move(hook); }

  // -- log manager -----------------------------------------------------------
  // Returns the log manager that controls commit / mem / fast log flags.
  // [return] non-owning pointer, or nullptr
  spike_log_manager_t* log_manager() const { return log_manager_.get(); }
  // [in] log_manager  unique_ptr, ownership transferred
  void set_log_manager(std::unique_ptr<spike_log_manager_t> log_manager) { log_manager_ = std::move(log_manager); }

  // -- model compat ----------------------------------------------------------
  // Returns the model-compatibility policy object (LR/SC interleave, …).
  // [return] non-owning pointer, or nullptr
  spike_model_compat_t* model_compat() const { return model_compat_.get(); }
  // [in] model_compat  unique_ptr, ownership transferred
  void set_model_compat(std::unique_ptr<spike_model_compat_t> model_compat) {
    model_compat_ = std::move(model_compat);
  }

  // -- host policy -----------------------------------------------------------
  // Returns the host-interaction policy (e.g. disable htif host).
  // [return] non-owning pointer, or nullptr
  spike_host_policy_t* host_policy() const { return host_policy_.get(); }
  // [in] host_policy  unique_ptr, ownership transferred
  void set_host_policy(std::unique_ptr<spike_host_policy_t> host_policy) { host_policy_ = std::move(host_policy); }

  // -- checkpoint controller -------------------------------------------------
  // Returns the checkpoint controller, or nullptr.
  // [return] non-owning pointer
  checkpoint_controller_t* checkpoint_controller() const { return checkpoint_controller_.get(); }
  // [in] controller  unique_ptr, ownership transferred
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

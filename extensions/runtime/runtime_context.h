#pragma once

#include "runtime/runtime_log_ext.h"
#include "runtime/spike_hook_dispatcher.h"
#include <memory>

class spike_runtime_context_t {
public:
  spike_runtime_context_t();

  spike_hook_dispatcher_t* hook_dispatcher() const { return hook_dispatcher_.get(); }
  void set_hook_dispatcher(std::unique_ptr<spike_hook_dispatcher_t> hook) { hook_dispatcher_ = std::move(hook); }

  runtime_log_ext_t* runtime_log_ext() const { return runtime_log_ext_.get(); }
  void set_runtime_log_ext(std::unique_ptr<runtime_log_ext_t> runtime_log_ext) { runtime_log_ext_ = std::move(runtime_log_ext); }

private:
  std::unique_ptr<spike_hook_dispatcher_t> hook_dispatcher_;
  std::unique_ptr<runtime_log_ext_t> runtime_log_ext_;
};

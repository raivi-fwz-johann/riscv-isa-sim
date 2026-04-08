#pragma once

#include "runtime/spike_hook_dispatcher.h"
#include <memory>

class runtime_ext_t {
public:
  runtime_ext_t();

  spike_hook_dispatcher_t* hook_dispatcher() const { return hook_dispatcher_.get(); }
  void set_hook_dispatcher(std::unique_ptr<spike_hook_dispatcher_t> hook) { hook_dispatcher_ = std::move(hook); }

private:
  std::unique_ptr<spike_hook_dispatcher_t> hook_dispatcher_;
};

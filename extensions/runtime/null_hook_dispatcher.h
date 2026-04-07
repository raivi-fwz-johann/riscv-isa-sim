#pragma once

#include "runtime/spike_hook_dispatcher.h"

class null_hook_dispatcher_t final : public spike_hook_dispatcher_t {
public:
  ~null_hook_dispatcher_t() override = default;
};

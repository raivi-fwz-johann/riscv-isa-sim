#include "runtime/runtime_context.h"

spike_runtime_context_t::spike_runtime_context_t()
  : hook_dispatcher_(std::make_unique<spike_hook_dispatcher_t>()),
    runtime_log_ext_(std::make_unique<runtime_log_ext_t>())
{
}

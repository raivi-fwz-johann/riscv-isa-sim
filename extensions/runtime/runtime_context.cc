#include "runtime/runtime_context.h"

spike_runtime_context_t::spike_runtime_context_t()
  : hook_dispatcher_(std::make_unique<spike_hook_dispatcher_t>()),
    log_manager_(std::make_unique<spike_log_manager_t>()),
    host_policy_(std::make_unique<spike_host_policy_t>())
{
}

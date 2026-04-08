#include "runtime/runtime_context.h"
#include "runtime/null_hook_dispatcher.h"

spike_runtime_context_t::spike_runtime_context_t()
  : hook_dispatcher_(std::make_unique<null_hook_dispatcher_t>()),
    runtime_log_ext_(std::make_unique<runtime_log_ext_t>())
{
}

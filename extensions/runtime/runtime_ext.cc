#include "runtime/runtime_ext.h"
#include "runtime/null_hook_dispatcher.h"

runtime_ext_t::runtime_ext_t()
  : hook_dispatcher_(std::make_unique<null_hook_dispatcher_t>())
{
}

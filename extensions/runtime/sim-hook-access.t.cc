#include "sim.h"
#include "runtime/runtime_context.h"
#include "runtime/runtime_log_ext.h"
#include "runtime/spike_hook_dispatcher.h"
#include <type_traits>
#include <utility>

int main()
{
  static_assert(std::is_same_v<decltype(std::declval<const sim_t&>().runtime_context()), spike_runtime_context_t*>);
  static_assert(std::is_same_v<decltype(std::declval<const spike_runtime_context_t&>().hook_dispatcher()), spike_hook_dispatcher_t*>);
  static_assert(std::is_same_v<decltype(std::declval<const spike_runtime_context_t&>().runtime_log_ext()), runtime_log_ext_t*>);
  return 0;
}

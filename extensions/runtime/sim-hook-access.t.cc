#include "sim.h"
#include "runtime/spike_host_policy.h"
#include "runtime/runtime_context.h"
#include "runtime/spike_log_manager.h"
#include "runtime/spike_hook_dispatcher.h"
#include <type_traits>
#include <utility>

int main()
{
  static_assert(std::is_same_v<decltype(std::declval<const sim_t&>().runtime_context()), spike_runtime_context_t*>);
  static_assert(std::is_same_v<decltype(std::declval<const spike_runtime_context_t&>().hook_dispatcher()), spike_hook_dispatcher_t*>);
  static_assert(std::is_same_v<decltype(std::declval<const spike_runtime_context_t&>().log_manager()), spike_log_manager_t*>);
  static_assert(std::is_same_v<decltype(std::declval<const spike_runtime_context_t&>().host_policy()), spike_host_policy_t*>);
  static_assert(std::is_member_object_pointer_v<decltype(&sim_t::INTERLEAVE)>);
  static_assert(std::is_same_v<
      decltype(std::declval<sim_t&>().set_interleave(std::declval<size_t>())),
      void>);
  return 0;
}

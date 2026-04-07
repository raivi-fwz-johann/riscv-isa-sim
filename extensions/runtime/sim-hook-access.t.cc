#include "sim.h"
#include "runtime/spike_hook_dispatcher.h"
#include <type_traits>
#include <utility>

int main()
{
  static_assert(std::is_same_v<decltype(std::declval<const sim_t&>().hook_dispatcher()), spike_hook_dispatcher_t*>);
  return 0;
}

#include "integration/spike_bootstrap.h"
#include "sim.h"
#include <type_traits>
#include <utility>

int main()
{
  static_assert(std::is_same_v<
      decltype(spike_parse_argv_options(std::declval<int>(), std::declval<char**>())),
      spike_boot_options_t>);

  static_assert(std::is_same_v<
      decltype(spike_bootstrap(std::declval<spike_boot_options_t>())),
      spike_boot_result_t>);

  static_assert(std::is_same_v<
      decltype(std::declval<spike_boot_result_t&>().sim.get()),
      sim_t*>);

  return 0;
}

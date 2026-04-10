#include "integration/spike_bootstrap.h"
#include "sim.h"
#include <cstring>
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

  const char* argv_raw[] = {
      "spike",
      "--log-commits-stant",
      "--step=123",
      "--disable_host",
      "pk",
  };
  auto argv = const_cast<char**>(argv_raw);
  auto options = spike_parse_argv_options(static_cast<int>(std::size(argv_raw)), argv);
  if (!options.log_commits_stant)
    return 1;
  if (options.step_interleave != 123)
    return 2;
  if (!options.disable_host)
    return 3;

  return 0;
}

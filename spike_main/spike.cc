// See LICENSE for license details.

#include "integration/spike_bootstrap.h"
#include <cstdio>
#include <utility>

int main(int argc, char** argv)
{
  auto options = spike_parse_argv_options(argc, argv);
  auto boot = spike_bootstrap(std::move(options));

  if (boot.dump_dts_only) {
    printf("%s", boot.sim->get_dts());
    return 0;
  }

  return boot.sim->run();
}

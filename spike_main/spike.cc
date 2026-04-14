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

  const int return_code = boot.sim->run();

  if (auto* runtime = boot.sim->runtime_context()) {
    if (auto* controller = runtime->checkpoint_controller()) {
      if (controller->has_save_target() && controller->save_requested()) {
        controller->save(*boot.sim);
      }
    }
  }

  return return_code;
}

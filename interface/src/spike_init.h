#ifndef SPIKE_INIT_H
#define SPIKE_INIT_H

#include "cfg.h"
#include "integration/spike_bootstrap.h"
#include "sim.h"
#include <cstdio>
#include <functional>
#include <memory>

static std::unique_ptr<spike_boot_result_t> spike_init(
    int argc,
    char** argv,
    sim_t*& spike_sim,
    cfg_t& cfg,
    std::function<void(sim_t*)> callback = [](sim_t*) {})
{
  auto options = spike_parse_argv_options(argc, argv);
  auto boot = std::make_unique<spike_boot_result_t>(
      spike_bootstrap(std::move(options), callback));

  cfg = *boot->cfg;
  spike_sim = boot->sim.get();

  if (boot->dump_dts_only) {
    std::printf("%s", spike_sim->get_dts());
  }

  return boot;
}

#endif

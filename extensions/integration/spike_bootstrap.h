#pragma once

#include "cfg.h"
#include "sim.h"
#include "cachesim.h"
#include "extension.h"
#include "remote_bitbang.h"
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct spike_boot_options_t {
  bool debug = false;
  bool halted = false;
  bool histogram = false;
  bool log = false;
  bool dump_dts = false;
  bool dtb_enabled = true;
  bool dtb_discovery = false;
  bool socket_enabled = false;
  bool log_cache = false;
  bool log_commits = false;
  bool memory_option = false;
  bool use_rbb = false;
  const char* kernel = nullptr;
  const char* initrd = nullptr;
  const char* dtb_file = nullptr;
  const char* log_path = nullptr;
  reg_t blocksz = 64;
  uint16_t rbb_port = 0;
  unsigned dmi_rti = 0;
  std::optional<unsigned long long> instructions;
  FILE* cmd_file = nullptr;
  cfg_t cfg;
  cfg_arg_t<size_t> nprocs = cfg_arg_t<size_t>(1);
  debug_module_config_t dm_config;
  std::vector<device_factory_sargs_t> plugin_device_factories;
  std::vector<std::function<extension_t*()>> extensions;
  std::unique_ptr<icache_sim_t> ic;
  std::unique_ptr<dcache_sim_t> dc;
  std::unique_ptr<cache_sim_t> l2;
  std::vector<std::string> htif_args;
};

struct spike_boot_result_t {
  std::unique_ptr<sim_t> sim;
  std::vector<std::pair<reg_t, abstract_mem_t*>> mems;
  std::unique_ptr<icache_sim_t> ic;
  std::unique_ptr<dcache_sim_t> dc;
  std::unique_ptr<cache_sim_t> l2;
  std::unique_ptr<remote_bitbang_t> remote_bitbang;
  std::unique_ptr<jtag_dtm_t> jtag_dtm;
  bool dump_dts_only = false;

  spike_boot_result_t() = default;
  spike_boot_result_t(const spike_boot_result_t&) = delete;
  spike_boot_result_t& operator=(const spike_boot_result_t&) = delete;
  spike_boot_result_t(spike_boot_result_t&&) noexcept = default;
  spike_boot_result_t& operator=(spike_boot_result_t&&) noexcept = default;
  ~spike_boot_result_t();
};

spike_boot_options_t spike_parse_argv_options(int argc, char** argv);
void spike_prepare_boot_options(spike_boot_options_t& options);
spike_boot_result_t spike_bootstrap(
    spike_boot_options_t options,
    const std::function<void(sim_t*)>& on_sim_created = {});

#include "integration/spike_bootstrap.h"
#include "checkpoint/checkpoint_restore_rom.h"
#include "platform.h"
#include "sim.h"
#include <sys/wait.h>
#include <unistd.h>
#include <string>
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
  static_assert(std::is_same_v<
      decltype(std::declval<spike_boot_options_t>().log_commits_stant),
      bool>);
  static_assert(std::is_same_v<
      decltype(std::declval<spike_boot_options_t>().disable_host),
      bool>);
  static_assert(std::is_same_v<
      decltype(std::declval<spike_boot_options_t>().step_interleave),
      size_t>);
  static_assert(std::is_same_v<
      decltype(std::declval<spike_boot_options_t>().checkpoint.snapshot_load_name),
      const char*>);
  static_assert(std::is_same_v<
      decltype(std::declval<spike_boot_options_t>().checkpoint.snapshot_compress),
      bool>);
  static_assert(std::is_same_v<
      decltype(std::declval<spike_boot_options_t>().explicit_isa),
      std::optional<std::string>>);

  {
    const char* argv_raw[] = {"spike", "--save=snap-save", "pk", nullptr};
    auto options = spike_parse_argv_options(
        3,
        const_cast<char**>(argv_raw));
    if (options.checkpoint.snapshot_save_name == nullptr) return 10;
    if (std::string(options.checkpoint.snapshot_save_name) != "snap-save")
      return 11;
  }

  {
    const char* argv_raw[] = {"spike", "--load=snap-load", nullptr};
    auto options = spike_parse_argv_options(
        2,
        const_cast<char**>(argv_raw));
    if (options.checkpoint.snapshot_load_name == nullptr) return 20;
    if (std::string(options.checkpoint.snapshot_load_name) != "snap-load")
      return 21;
    if (options.htif_args.empty()) return 22;
    if (options.htif_args.front() != "none") return 23;
    if (!options.cfg.start_pc.has_value()) return 24;
    if (*options.cfg.start_pc != kCheckpointBootromBase) return 25;
  }

  {
    const char* argv_raw[] = {"spike", "--isa", "rv64gc", nullptr};
    auto options = spike_parse_argv_options(
        3,
        const_cast<char**>(argv_raw));
    if (!options.explicit_isa.has_value()) return 26;
    if (*options.explicit_isa != "rv64gc") return 27;
    if (std::string(options.cfg.isa) != "rv64gc") return 28;
  }

  {
    pid_t pid = fork();
    if (pid < 0) return 30;
    if (pid == 0) {
      spike_boot_options_t options;
      options.checkpoint.snapshot_compress = true;
      options.checkpoint.snapshot_compress_zstd = true;
      spike_prepare_boot_options(options);
      _exit(0);
    }

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) return 31;
    if (!WIFEXITED(status)) return 32;
    if (WEXITSTATUS(status) == 0) return 33;
  }

  {
    const char* argv_raw[] = {"spike", "--memsize=4", "pk", nullptr};
    auto options = spike_parse_argv_options(
        3,
        const_cast<char**>(argv_raw));
    if (options.cfg.mem_layout.size() != 1) return 34;
    if (options.cfg.mem_layout.front().get_base() != 0x00020000ULL) return 35;
    if (options.cfg.mem_layout.front().get_size() != (4ULL << 30)) return 36;
    if (s_platform_cfg.rstvec != 0x100000000ULL) return 37;
    if (s_platform_cfg.dram_base != 0x00020000ULL) return 38;
    if (s_platform_cfg.ns16550_reg_io_width != 4) return 39;
  }

  {
    const char* argv_raw[] = {"spike", "pk", nullptr};
    auto options = spike_parse_argv_options(
        2,
        const_cast<char**>(argv_raw));
    if (options.cfg.mem_layout.size() != 1) return 40;
    if (options.cfg.mem_layout.front().get_base() != 0x80000000ULL) return 41;
    if (options.cfg.mem_layout.front().get_size() != (2ULL << 30)) return 42;
    if (s_platform_cfg.rstvec != 0x00001000ULL) return 43;
    if (s_platform_cfg.dram_base != 0x80000000ULL) return 44;
  }

  return 0;
}

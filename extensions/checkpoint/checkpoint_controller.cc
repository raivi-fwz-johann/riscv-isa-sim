#include "checkpoint/checkpoint_controller.h"

#include "checkpoint/checkpoint_files.h"
#include "checkpoint/checkpoint_restore_rom.h"
#include "platform.h"
#include "sim.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <unistd.h>

namespace fs = std::filesystem;

namespace {

extern "C" void spike_checkpoint_install_rom(
    sim_t* sim, reg_t base, const char* bytes, size_t size)
    __attribute__((weak));
extern "C" int spike_checkpoint_save_mainram(
    sim_t* sim, reg_t mainram_base, const char* output_path)
    __attribute__((weak));

reg_t checkpoint_mainram_base()
{
  return s_platform_cfg.checkpoint_mainram_base;
}

std::vector<char> read_binary_file(const fs::path& path)
{
  std::ifstream in(path, std::ios::binary | std::ios::ate);
  if (!in.good()) {
    std::cerr << "can't find file: " << path << std::endl;
    std::exit(-1);
  }

  const std::streamsize size = in.tellg();
  in.seekg(0, std::ios::beg);
  if (size < 0) {
    std::cerr << "error: invalid file size: " << path << std::endl;
    std::exit(-1);
  }

  std::vector<char> data(static_cast<size_t>(size));
  if (!data.empty()) {
    in.read(data.data(), size);
  }
  return data;
}

void require_core0(sim_t& sim, const char* action)
{
  if (!sim.get_core(0)) {
    std::cerr << "error: core0 is unavailable during checkpoint " << action
              << std::endl;
    std::exit(-1);
  }
}

void restore_mainram(sim_t& sim, const checkpoint_paths_t& paths, checkpoint_legacy_config_t& config)
{
  const fs::path selected = select_checkpoint_mainram_for_load(paths, config);

  fs::path mainram_file = selected;
  std::optional<fs::path> temp_dir;
  if (config.snapshot_compress || config.snapshot_compress_zstd) {
    temp_dir = fs::temp_directory_path() /
               ("spike-checkpoint-" + std::to_string(::getpid()));
    fs::create_directories(*temp_dir);
    decompress_checkpoint_mainram(selected, *temp_dir, config);
    mainram_file = *temp_dir / paths.mainram.filename();
  }

  std::ifstream in(mainram_file, std::ios::binary | std::ios::ate);
  if (!in.good()) {
    std::cerr << "can't find mainram: " << mainram_file << std::endl;
    std::exit(-1);
  }

  const std::streamsize size = in.tellg();
  in.seekg(0, std::ios::beg);
  if (size < 0) {
    std::cerr << "error: invalid mainram size in " << mainram_file << std::endl;
    std::exit(-1);
  }

  std::vector<uint8_t> data(static_cast<size_t>(size));
  if (!data.empty()) {
    in.read(reinterpret_cast<char*>(data.data()), size);
  }
  in.close();

  if (!data.empty()) {
    simif_t* simif = static_cast<simif_t*>(&sim);
    if (!simif->mmio_store(checkpoint_mainram_base(), data.size(), data.data())) {
      std::cerr << "error: failed to restore mainram into target memory"
                << std::endl;
      std::exit(-1);
    }
  }

  if (temp_dir.has_value()) {
    std::error_code ec;
    fs::remove(mainram_file, ec);
    fs::remove(*temp_dir, ec);
  }
}

void save_regs(sim_t& sim, const checkpoint_paths_t& paths)
{
  auto* proc = sim.get_core(0);
  if (!proc) {
    std::cerr << "error: core0 is unavailable while saving checkpoint regs"
              << std::endl;
    std::exit(-1);
  }

  std::ofstream out(paths.regs);
  if (!out.is_open()) {
    std::cerr << "error: cannot create " << paths.regs << std::endl;
    std::exit(-1);
  }

  state_t* state = proc->get_state();
  out << "# spike serialization file" << std::endl;
  out << "pc:0x" << std::hex << state->pc << std::endl;
  for (int i = 0; i < 32; ++i) {
    out << "reg_x" << std::dec << i << ":" << std::hex << state->XPR[i]
        << std::endl;
  }

  if (proc->get_flen()) {
    for (int i = 0; i < 32; ++i) {
      out << "reg_f" << std::dec << i << ":" << std::hex << state->FPR[i].v[0]
          << std::endl;
    }
    out << "fflags:" << state->fflags->read() << std::endl;
    out << "frm:" << state->frm->read() << std::endl;
  }

  if (proc->extension_enabled('V')) {
    out << "vl:" << std::hex << proc->VU.vl->read() << std::endl;
    out << "vtype:" << std::hex << proc->VU.vtype->read() << std::endl;
    out << "vlenb:" << std::hex << state->csrmap[CSR_VLENB]->read() << std::endl;
  }
}

void save_bootram(sim_t& sim, const checkpoint_paths_t& paths)
{
  auto* clint = sim.get_clint();
  if (!clint) {
    std::cerr << "error: missing clint while saving checkpoint bootram"
              << std::endl;
    std::exit(-1);
  }

  auto bytes = build_checkpoint_restore_rom(sim, *clint, sim.get_dtb());
  std::ofstream out(paths.bootram, std::ios::binary);
  if (!out.is_open()) {
    std::cerr << "error: cannot create " << paths.bootram << std::endl;
    std::exit(-1);
  }

  if (!bytes.empty()) {
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  }
}

void save_mainram(sim_t& sim, const checkpoint_paths_t& paths, const checkpoint_legacy_config_t& config)
{
  const reg_t mainram_base = checkpoint_mainram_base();
  if (!spike_checkpoint_save_mainram) {
    std::cerr << "error: checkpoint mainram saver bridge is unavailable"
              << std::endl;
    std::exit(-1);
  }
  if (spike_checkpoint_save_mainram(&sim, mainram_base, paths.mainram.c_str()) !=
      0) {
    std::cerr << "error: failed to save mainram at base 0x" << std::hex
              << mainram_base << std::endl;
    std::exit(-1);
  }

  compress_checkpoint_mainram(paths.mainram, config);
}

void restore_htif(sim_t& sim, const checkpoint_paths_t& paths)
{
  if (!fs::exists(paths.htif)) {
    return;
  }
  auto htif = load_checkpoint_htif(paths);
  sim.set_tohost_addr(htif.tohost_addr);
  sim.set_fromhost_addr(htif.fromhost_addr);
}

void install_checkpoint_bootrom(sim_t& sim, const checkpoint_paths_t& paths)
{
  if (!spike_checkpoint_install_rom) {
    std::cerr << "error: checkpoint ROM installation bridge is unavailable"
              << std::endl;
    std::exit(-1);
  }

  const auto bytes = read_binary_file(paths.bootram);
  spike_checkpoint_install_rom(
      &sim, kCheckpointBootromBase, bytes.data(), bytes.size());
}

void install_trampoline(sim_t& sim)
{
  auto* proc = sim.get_core(0);
  if (!proc) {
    std::cerr << "error: core0 is unavailable while installing checkpoint trampoline"
              << std::endl;
    std::exit(-1);
  }

  auto bytes = build_checkpoint_trampoline_rom(
      proc->get_isa().get_max_xlen(),
      kCheckpointBootromBase);
  if (!spike_checkpoint_install_rom) {
    std::cerr << "error: checkpoint ROM installation bridge is unavailable"
              << std::endl;
    std::exit(-1);
  }
  spike_checkpoint_install_rom(&sim, DEFAULT_RSTVEC, bytes.data(), bytes.size());
}

void prepare_restore_harts(sim_t& sim)
{
  for (const auto& [hartid, proc] : sim.get_harts()) {
    (void)hartid;
    if (!proc) {
      std::cerr << "error: null hart during checkpoint restore prepare"
                << std::endl;
      std::exit(-1);
    }
    state_t* state = proc->get_state();
    state->debug_mode = true;
    state->prv = PRV_M;
    state->prev_prv = PRV_M;
    state->v = false;
    state->prev_v = false;
  }
}

}  // namespace

class legacy_checkpoint_controller_t final : public checkpoint_controller_t {
public:
  explicit legacy_checkpoint_controller_t(checkpoint_legacy_config_t config)
      : config_(config) {}

  bool enabled() const override {
    return has_load_target() || has_save_target();
  }

  bool has_load_target() const override { return config_.snapshot_load_name != nullptr; }
  bool has_save_target() const override { return config_.snapshot_save_name != nullptr; }

  void prepare_restore(sim_t& sim, bool has_elf) override
  {
    save_requested_ = has_save_target();
    pending_ram_overlay_ = false;
    pending_htif_restore_ = false;
    pending_post_reset_restore_ = false;
    restore_mode_ = checkpoint_restore_mode_t::disabled;

    if (!has_load_target()) {
      return;
    }

    require_core0(sim, "load");
    prepare_restore_harts(sim);

    const auto paths = checkpoint_paths_t::from_prefix(config_.snapshot_load_name);
    install_checkpoint_bootrom(sim, paths);
    pending_post_reset_restore_ = true;

    if (has_elf) {
      restore_mode_ = checkpoint_restore_mode_t::elf_bootstrap_then_ram_overlay;
      pending_ram_overlay_ = true;
      pending_htif_restore_ = true;
      return;
    }

    restore_htif(sim, paths);
    restore_mode_ = checkpoint_restore_mode_t::self_contained_none;
    install_trampoline(sim);
    restore_mainram(sim, paths, config_);
  }

  void on_post_reset(sim_t& sim) override
  {
    if (!has_load_target() || !pending_post_reset_restore_ ||
        restore_mode_ == checkpoint_restore_mode_t::disabled) {
      return;
    }

    prepare_restore_harts(sim);

    if (!pending_ram_overlay_ &&
        !pending_htif_restore_ &&
        restore_mode_ != checkpoint_restore_mode_t::elf_bootstrap_then_ram_overlay) {
      pending_post_reset_restore_ = false;
      return;
    }

    if (restore_mode_ != checkpoint_restore_mode_t::elf_bootstrap_then_ram_overlay) {
      pending_post_reset_restore_ = false;
      return;
    }

    const auto paths = checkpoint_paths_t::from_prefix(config_.snapshot_load_name);
    if (pending_ram_overlay_) {
      restore_mainram(sim, paths, config_);
      pending_ram_overlay_ = false;
    }
    if (pending_htif_restore_) {
      restore_htif(sim, paths);
      pending_htif_restore_ = false;
    }

    pending_post_reset_restore_ = false;
  }

  void request_save() override { save_requested_ = has_save_target(); }
  bool save_requested() const override { return save_requested_; }

  void save(sim_t& sim) override
  {
    if (!has_save_target() || !save_requested_) {
      return;
    }

    const auto paths = checkpoint_paths_t::from_prefix(config_.snapshot_save_name);
    save_regs(sim, paths);
    save_bootram(sim, paths);
    save_mainram(sim, paths, config_);

    checkpoint_htif_state_t htif;
    htif.tohost_addr = sim.get_tohost_addr();
    htif.fromhost_addr = sim.get_fromhost_addr();
    save_checkpoint_htif(paths, htif);

    save_requested_ = false;
  }

private:
  checkpoint_legacy_config_t config_;
  checkpoint_restore_mode_t restore_mode_ = checkpoint_restore_mode_t::disabled;
  bool save_requested_ = false;
  bool pending_ram_overlay_ = false;
  bool pending_htif_restore_ = false;
  bool pending_post_reset_restore_ = false;
};

std::unique_ptr<checkpoint_controller_t> make_checkpoint_controller(
    checkpoint_legacy_config_t config)
{
  return std::make_unique<legacy_checkpoint_controller_t>(config);
}

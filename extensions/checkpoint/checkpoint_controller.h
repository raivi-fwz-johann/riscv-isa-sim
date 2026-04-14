#pragma once

#include "decode.h"
#include <memory>

class sim_t;

enum class checkpoint_restore_mode_t {
  disabled = 0,
  self_contained_none,
  elf_bootstrap_then_ram_overlay,
};

struct checkpoint_legacy_config_t {
  const char* snapshot_load_name = nullptr;
  const char* snapshot_save_name = nullptr;
  bool snapshot_compress = false;
  bool snapshot_compress_zstd = false;
};

class checkpoint_controller_t {
public:
  virtual ~checkpoint_controller_t() = default;
  virtual bool enabled() const = 0;
  virtual bool has_load_target() const = 0;
  virtual bool has_save_target() const = 0;
  virtual void prepare_restore(sim_t& sim, bool has_elf) = 0;
  virtual void on_post_reset(sim_t& sim) = 0;
  virtual void request_save() = 0;
  virtual bool save_requested() const = 0;
  virtual void save(sim_t& sim) = 0;
};

inline std::unique_ptr<checkpoint_controller_t> make_checkpoint_controller(
    checkpoint_legacy_config_t config)
{
  (void)config;
  return {};
}

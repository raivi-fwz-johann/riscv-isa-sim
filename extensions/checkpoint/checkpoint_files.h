#pragma once

#include "checkpoint/checkpoint_controller.h"
#include <filesystem>
#include <string>

struct checkpoint_paths_t {
  std::filesystem::path bootram;
  std::filesystem::path mainram;
  std::filesystem::path mainram_zip;
  std::filesystem::path mainram_zst;
  std::filesystem::path htif;
  std::filesystem::path regs;

  static checkpoint_paths_t from_prefix(const std::string& prefix);
};

struct checkpoint_htif_state_t {
  reg_t tohost_addr = 0;
  reg_t fromhost_addr = 0;
};

std::filesystem::path select_checkpoint_mainram_for_load(
    const checkpoint_paths_t& paths,
    checkpoint_legacy_config_t& config);
checkpoint_htif_state_t load_checkpoint_htif(const checkpoint_paths_t& paths);
void save_checkpoint_htif(const checkpoint_paths_t& paths, const checkpoint_htif_state_t& state);
void compress_checkpoint_mainram(
    const std::filesystem::path& source,
    const checkpoint_legacy_config_t& config);
void decompress_checkpoint_mainram(
    const std::filesystem::path& source,
    const std::filesystem::path& output_dir,
    const checkpoint_legacy_config_t& config);

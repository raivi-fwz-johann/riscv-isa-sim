#pragma once

#include "devices.h"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class sim_t;

constexpr reg_t kCheckpointBootromBase = 0x10000;
constexpr reg_t kCheckpointBootromSize = 0x10000;

std::vector<char> build_checkpoint_trampoline_rom(unsigned xlen, reg_t target_pc);
std::vector<char> build_checkpoint_restore_rom(
    sim_t& sim,
    clint_t& clint,
    const std::string& dtb);

inline std::unique_ptr<rom_device_t> load_checkpoint_bootrom_file(const std::string& path)
{
  std::ifstream boot_fin(path, std::ios::binary);
  if (!boot_fin.good()) {
    std::cerr << "can't find bootram: " << path << std::endl;
    std::exit(-1);
  }

  std::stringstream boot_stream;
  boot_stream << boot_fin.rdbuf();
  std::string boot_image = boot_stream.str();
  std::vector<char> rom;
  rom.insert(rom.begin(), boot_image.begin(), boot_image.end());

  return std::make_unique<rom_device_t>(rom);
}

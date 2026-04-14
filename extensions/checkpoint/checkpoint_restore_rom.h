#pragma once

#include "devices.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

constexpr reg_t kCheckpointBootromBase = 0x10000;
constexpr reg_t kCheckpointBootromSize = 0x10000;

std::vector<char> build_checkpoint_trampoline_rom(unsigned xlen, reg_t target_pc);
std::vector<char> build_checkpoint_restore_rom(
    processor_t& proc,
    clint_t& clint,
    const std::string& dtb);
std::unique_ptr<rom_device_t> load_checkpoint_bootrom_file(const std::string& path);

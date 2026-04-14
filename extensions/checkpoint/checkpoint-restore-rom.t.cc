#include "checkpoint/checkpoint_restore_rom.h"
#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

rom_device_t::rom_device_t(std::vector<char> data)
  : data(data)
{
}

bool rom_device_t::load(reg_t addr, size_t len, uint8_t* bytes)
{
  if (addr + len > data.size())
    return false;
  std::memcpy(bytes, &data[addr], len);
  return true;
}

bool rom_device_t::store(reg_t, size_t, const uint8_t*)
{
  return false;
}

int main()
{
  auto rom32 = build_checkpoint_trampoline_rom(32, 0x10000);
  auto rom64 = build_checkpoint_trampoline_rom(64, 0x10000);
  if (rom32.empty()) return 10;
  if (rom64.empty()) return 11;
  if (rom32.size() != rom64.size()) return 12;

  namespace fs = std::filesystem;
  const fs::path dir = fs::temp_directory_path() / "checkpoint-restore-rom-utst";
  fs::remove_all(dir);
  fs::create_directories(dir);

  const fs::path bootrom_path = dir / "sample.bootram";
  const std::vector<char> expected = {0x00, 0x11, 0x22, 0x33, 0x44};
  {
    std::ofstream out(bootrom_path, std::ios::binary);
    out.write(expected.data(), expected.size());
  }

  auto dev = load_checkpoint_bootrom_file(bootrom_path.string());
  if (!dev) return 20;
  const auto& contents = dev->contents();
  if (contents.size() != expected.size()) return 21;
  for (size_t i = 0; i < expected.size(); ++i) {
    if (contents[i] != expected[i]) return 22;
  }
  return 0;
}

#include "checkpoint/checkpoint_files.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

static bool has_tool(const char* tool)
{
  const std::string cmd = "command -v " + std::string(tool) + " >/dev/null 2>&1";
  return std::system(cmd.c_str()) == 0;
}

int main()
{
  namespace fs = std::filesystem;
  const fs::path dir = fs::temp_directory_path() / "checkpoint-files-utst";
  fs::remove_all(dir);
  fs::create_directories(dir);

  const auto paths = checkpoint_paths_t::from_prefix((dir / "sp").string());
  if (paths.bootram.filename() != "sp.bootram") return 10;
  if (paths.mainram.filename() != "sp.mainram") return 11;
  if (paths.htif.filename() != "sp.htif") return 12;
  if (paths.regs.filename() != "sp.re_regs") return 13;

  checkpoint_htif_state_t htif_in;
  htif_in.tohost_addr = 0x1000;
  htif_in.fromhost_addr = 0x2000;
  save_checkpoint_htif(paths, htif_in);
  auto htif = load_checkpoint_htif(paths);
  if (htif.tohost_addr != 0x1000) return 20;
  if (htif.fromhost_addr != 0x2000) return 21;

  {
    checkpoint_legacy_config_t cfg;
    std::ofstream(paths.mainram, std::ios::binary) << "plain";
    const auto selected = select_checkpoint_mainram_for_load(paths, cfg);
    if (selected != paths.mainram) return 30;
    if (cfg.snapshot_compress) return 31;
    if (cfg.snapshot_compress_zstd) return 32;
    fs::remove(paths.mainram);
  }

  {
    checkpoint_legacy_config_t cfg;
    std::ofstream(paths.mainram_zip, std::ios::binary) << "zip";
    const auto selected = select_checkpoint_mainram_for_load(paths, cfg);
    if (selected != paths.mainram_zip) return 40;
    if (!cfg.snapshot_compress) return 41;
    if (cfg.snapshot_compress_zstd) return 42;
    fs::remove(paths.mainram_zip);
  }

  {
    checkpoint_legacy_config_t cfg;
    std::ofstream(paths.mainram_zst, std::ios::binary) << "zst";
    const auto selected = select_checkpoint_mainram_for_load(paths, cfg);
    if (selected != paths.mainram_zst) return 50;
    if (cfg.snapshot_compress) return 51;
    if (!cfg.snapshot_compress_zstd) return 52;
    fs::remove(paths.mainram_zst);
  }

  if (!has_tool("zip")) {
    std::cerr << "missing required tool: zip" << std::endl;
    return 90;
  }
  if (!has_tool("unzip")) {
    std::cerr << "missing required tool: unzip" << std::endl;
    return 91;
  }

  {
    const fs::path roundtrip_dir = dir / "round trip;special";
    fs::create_directories(roundtrip_dir);
    const fs::path source = roundtrip_dir / "main ram;payload.bin";
    const std::string payload = "checkpoint payload with spaces and ; metachar";
    std::ofstream(source, std::ios::binary) << payload;

    checkpoint_legacy_config_t cfg;
    cfg.snapshot_compress = true;
    compress_checkpoint_mainram(source, cfg);
    const fs::path zip_file = source.string() + ".zip";
    if (!fs::exists(zip_file)) return 60;
    if (fs::exists(source)) return 61;

    decompress_checkpoint_mainram(zip_file, roundtrip_dir, cfg);
    if (!fs::exists(source)) return 62;

    std::ifstream fin(source, std::ios::binary);
    std::string restored((std::istreambuf_iterator<char>(fin)),
                         std::istreambuf_iterator<char>());
    if (restored != payload) return 63;
  }

  return 0;
}

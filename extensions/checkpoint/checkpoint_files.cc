#include "checkpoint/checkpoint_files.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>

checkpoint_paths_t checkpoint_paths_t::from_prefix(const std::string& prefix)
{
  checkpoint_paths_t paths;
  paths.bootram = prefix + ".bootram";
  paths.mainram = prefix + ".mainram";
  paths.mainram_zip = prefix + ".mainram.zip";
  paths.mainram_zst = prefix + ".mainram.zst";
  paths.htif = prefix + ".htif";
  paths.regs = prefix + ".re_regs";
  return paths;
}

std::filesystem::path select_checkpoint_mainram_for_load(
    const checkpoint_paths_t& paths,
    checkpoint_legacy_config_t& config)
{
  bool mainram_zip_file_exist = false;
  bool mainram_zst_file_exist = false;
  uint8_t found_mainram = 0;

  std::list<std::filesystem::path> mainram_types = {
      paths.mainram,
      paths.mainram_zip,
      paths.mainram_zst};
  std::list<std::filesystem::path> missing_mainram_names;
  std::ifstream main_fin;

  for (const auto& mainram_path : mainram_types) {
    main_fin.open(mainram_path, std::ios::binary);
    if (main_fin.good()) {
      std::cerr << "found mainram: " << mainram_path << std::endl;
      found_mainram++;
      if (mainram_path == paths.mainram_zip)
        mainram_zip_file_exist = true;
      if (mainram_path == paths.mainram_zst)
        mainram_zst_file_exist = true;
    } else {
      missing_mainram_names.push_back(mainram_path);
    }
    main_fin.close();
  }

  if (found_mainram != 1) {
    if (found_mainram == 0) {
      for (const auto& missing_name : missing_mainram_names)
        std::cerr << "not found mainram: " << missing_name << std::endl;
    }
    std::cerr << "found " << static_cast<int>(found_mainram) << " mainram files"
              << std::endl;
    std::exit(-1);
  }

  if (mainram_zip_file_exist || mainram_zst_file_exist) {
    config.snapshot_compress = mainram_zip_file_exist;
    config.snapshot_compress_zstd = mainram_zst_file_exist;
    return mainram_zip_file_exist ? paths.mainram_zip : paths.mainram_zst;
  }

  return paths.mainram;
}

checkpoint_htif_state_t load_checkpoint_htif(const checkpoint_paths_t& paths)
{
  checkpoint_htif_state_t state;

  std::ifstream htif_fin(paths.htif);
  if (!htif_fin.good()) return state;

  std::string line;
  while (std::getline(htif_fin, line)) {
    auto pos = line.find(':');
    if (pos == std::string::npos) continue;
    std::string key = line.substr(0, pos);
    std::string val = line.substr(pos + 1);
    if (key == "tohost_addr")
      state.tohost_addr = strtoull(val.c_str(), nullptr, 16);
    else if (key == "fromhost_addr")
      state.fromhost_addr = strtoull(val.c_str(), nullptr, 16);
  }

  return state;
}

void save_checkpoint_htif(const checkpoint_paths_t& paths, const checkpoint_htif_state_t& state)
{
  std::ofstream fout(paths.htif);
  if (!fout.is_open()) {
    std::cerr << "warning: cannot create " << paths.htif << std::endl;
    return;
  }

  fout << "tohost_addr:0x" << std::hex << state.tohost_addr << std::endl;
  fout << "fromhost_addr:0x" << std::hex << state.fromhost_addr << std::endl;
}

void compress_checkpoint_mainram(
    const std::filesystem::path& source,
    const checkpoint_legacy_config_t& config)
{
  std::string command;
  const std::string source_file = source.string();
  if (config.snapshot_compress) {
    command = "zip -qjm " + source_file + ".zip " + source_file;
  } else if (config.snapshot_compress_zstd) {
    command = "zstd --rm -T0 -q " + source_file;
  } else {
    return;
  }

  std::cerr << "command: " + command << std::endl;

  int ret = std::system(command.c_str());
  if (ret != 0) {
    std::cerr << "error: compress " << source_file << " failed." << std::endl;
    std::exit(ret);
  }
}

void decompress_checkpoint_mainram(
    const std::filesystem::path& source,
    const std::filesystem::path& output_dir,
    const checkpoint_legacy_config_t& config)
{
  std::string command;
  const std::string source_file = source.string();
  const std::string output_directory = output_dir.string();
  if (config.snapshot_compress) {
    command = "unzip -o " + source_file + " -d " + output_directory;
  } else if (config.snapshot_compress_zstd) {
    command = "zstd -dfq -T0 " + source_file +
              " --output-dir-flat=" + output_directory;
  } else {
    return;
  }

  std::cerr << "command: " + command << std::endl;

  int ret = std::system(command.c_str());
  if (ret != 0) {
    std::cerr << "error: decompress " << source_file << " failed."
              << std::endl;
    std::exit(ret);
  }
}

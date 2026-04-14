#include "checkpoint/checkpoint_files.h"
#include <filesystem>
#include <fstream>

int main()
{
  namespace fs = std::filesystem;
  const fs::path dir = fs::temp_directory_path() / "checkpoint-files-utst";
  fs::create_directories(dir);

  const auto paths = checkpoint_paths_t::from_prefix((dir / "sp").string());
  if (paths.bootram.filename() != "sp.bootram") return 10;
  if (paths.mainram.filename() != "sp.mainram") return 11;
  if (paths.htif.filename() != "sp.htif") return 12;
  if (paths.regs.filename() != "sp.re_regs") return 13;

  std::ofstream(paths.htif) << "tohost_addr:0x1000\nfromhost_addr:0x2000\n";
  auto htif = load_checkpoint_htif(paths);
  if (htif.tohost_addr != 0x1000) return 20;
  if (htif.fromhost_addr != 0x2000) return 21;

  return 0;
}

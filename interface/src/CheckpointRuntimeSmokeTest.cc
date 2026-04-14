#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

namespace {

constexpr const char* kGcc = "/usr/bin/riscv64-linux-gnu-gcc";

fs::path spike_bin()
{
  return fs::path("/workspace/johann/code/spike-diff/.worktrees/master-checkpoint/riscv-isa-sim-master/interface/build/thirdparty/riscv-isa-sim/bin/spike");
}

std::string q(const fs::path& path)
{
  return "'" + path.string() + "'";
}

fs::path write_file(const fs::path& path, const std::string& contents)
{
  std::ofstream out(path);
  if (!out.is_open()) {
    throw std::runtime_error("cannot open " + path.string());
  }
  out << contents;
  out.close();
  return path;
}

bool run_cmd(const std::string& cmd)
{
  const int rc = std::system(cmd.c_str());
  return rc == 0;
}

std::string bare_linker_script()
{
  return
      "OUTPUT_ARCH(riscv)\n"
      "ENTRY(_start)\n"
      "SECTIONS {\n"
      "  . = 0x80000000;\n"
      "  .text : { *(.text*) }\n"
      "  .rodata : { *(.rodata*) }\n"
      "  .tohost : { *(.tohost*) }\n"
      "  .data : { *(.data*) }\n"
      "  .bss : { *(.bss*) *(COMMON) }\n"
      "}\n";
}

std::string single_hart_program()
{
  return
      ".option norvc\n"
      ".section .text\n"
      ".globl _start\n"
      "_start:\n"
      "  la t0, progress\n"
      "  ld t1, 0(t0)\n"
      "  addi t1, t1, 1\n"
      "  sd t1, 0(t0)\n"
      "  li t2, 5\n"
      "  bne t1, t2, 1f\n"
      "  li t3, 0x800\n"
      "  csrw 0x800, t3\n"
      "1:\n"
      "  li t2, 10\n"
      "  blt t1, t2, _start\n"
      "  la t0, tohost\n"
      "  li t1, 1\n"
      "  sd t1, 0(t0)\n"
      "2:\n"
      "  j 2b\n"
      "\n"
      ".section .tohost,\"aw\",@progbits\n"
      ".align 8\n"
      "tohost:   .dword 0\n"
      "fromhost: .dword 0\n"
      "\n"
      ".section .data\n"
      ".align 8\n"
      "progress: .dword 0\n";
}

std::string multi_hart_program()
{
  return
      ".option norvc\n"
      ".section .text\n"
      ".globl _start\n"
      "_start:\n"
      "  csrr t0, mhartid\n"
      "  la t1, ready\n"
      "  slli t2, t0, 3\n"
      "  add t3, t1, t2\n"
      "  li t4, 1\n"
      "  sd t4, 0(t3)\n"
      "\n"
      "wait_all:\n"
      "  ld t5, 0(t1)\n"
      "  ld t6, 8(t1)\n"
      "  and t5, t5, t6\n"
      "  beqz t5, wait_all\n"
      "\n"
      "  beqz t0, hart0_path\n"
      "secondary_spin:\n"
      "  la t1, done\n"
      "  ld t2, 0(t1)\n"
      "  beqz t2, secondary_spin\n"
      "  la t1, tohost\n"
      "  li t2, 1\n"
      "  sd t2, 0(t1)\n"
      "  j .\n"
      "\n"
      "hart0_path:\n"
      "  la t1, counter\n"
      "  ld t2, 0(t1)\n"
      "  addi t2, t2, 1\n"
      "  sd t2, 0(t1)\n"
      "  li t3, 4\n"
      "  bne t2, t3, keep_running\n"
      "  li t4, 1\n"
      "  la t5, done\n"
      "  sd t4, 0(t5)\n"
      "  li t6, 0x800\n"
      "  csrw 0x800, t6\n"
      "keep_running:\n"
      "  li t3, 8\n"
      "  blt t2, t3, hart0_path\n"
      "  la t1, tohost\n"
      "  li t2, 1\n"
      "  sd t2, 0(t1)\n"
      "  j .\n"
      "\n"
      ".section .tohost,\"aw\",@progbits\n"
      ".align 8\n"
      "tohost:   .dword 0\n"
      "fromhost: .dword 0\n"
      "\n"
      ".section .data\n"
      ".align 8\n"
      "ready:   .dword 0, 0\n"
      "counter: .dword 0\n"
      "done:    .dword 0\n";
}

fs::path build_bare_elf(const fs::path& dir, const std::string& name, const std::string& source)
{
  const fs::path ld = dir / (name + ".ld");
  const fs::path src = dir / (name + ".S");
  const fs::path elf = dir / (name + ".elf");
  write_file(ld, bare_linker_script());
  write_file(src, source);

  const std::string cmd =
      std::string(kGcc) + " -nostdlib -static -march=rv64imafd -mabi=lp64d -T " +
      q(ld) + " -o " + q(elf) + " " + q(src);
  if (!run_cmd(cmd)) {
    throw std::runtime_error("failed to build " + elf.string());
  }
  return elf;
}

bool artifact_set_exists(const fs::path& prefix)
{
  const fs::path bootram = prefix.string() + ".bootram";
  const fs::path mainram = prefix.string() + ".mainram";
  const fs::path mainram_zip = prefix.string() + ".mainram.zip";
  const fs::path mainram_zst = prefix.string() + ".mainram.zst";
  const fs::path htif = prefix.string() + ".htif";
  const fs::path regs = prefix.string() + ".re_regs";

  const int mainram_count =
      (fs::exists(mainram) ? 1 : 0) + (fs::exists(mainram_zip) ? 1 : 0) + (fs::exists(mainram_zst) ? 1 : 0);
  return fs::exists(bootram) && mainram_count == 1 && fs::exists(htif) && fs::exists(regs);
}

bool artifact_set_absent(const fs::path& prefix)
{
  return !fs::exists(prefix.string() + ".bootram") && !fs::exists(prefix.string() + ".mainram") &&
         !fs::exists(prefix.string() + ".mainram.zip") && !fs::exists(prefix.string() + ".mainram.zst") &&
         !fs::exists(prefix.string() + ".htif") && !fs::exists(prefix.string() + ".re_regs");
}

int test_bare_none_restore(const fs::path& dir)
{
  const fs::path elf = build_bare_elf(dir, "bare-none", single_hart_program());
  const fs::path prefix = dir / "snap-none";
  const fs::path other_prefix = dir / "snap-none-load";

  const std::string run_save = spike_bin().string() + " --save=" + prefix.string() + " " + elf.string();
  const std::string run_load = spike_bin().string() + " --load=" + prefix.string();
  if (!run_cmd(run_save)) {
    return 10;
  }
  if (!artifact_set_exists(prefix)) {
    return 11;
  }
  if (!run_cmd(run_load)) {
    return 12;
  }
  if (!artifact_set_absent(other_prefix)) {
    return 13;
  }
  return 0;
}

int test_bare_overlay_restore(const fs::path& dir)
{
  const fs::path elf = build_bare_elf(dir, "bare-overlay", single_hart_program());
  const fs::path prefix = dir / "snap-overlay";
  const fs::path other_prefix = dir / "snap-overlay-load";

  const std::string run_save = spike_bin().string() + " --save=" + prefix.string() + " " + elf.string();
  const std::string run_load_overlay =
      spike_bin().string() + " --load=" + prefix.string() + " " + elf.string();
  if (!run_cmd(run_save)) {
    return 20;
  }
  if (!artifact_set_exists(prefix)) {
    return 21;
  }
  if (!run_cmd(run_load_overlay)) {
    return 22;
  }
  if (!artifact_set_absent(other_prefix)) {
    return 23;
  }
  return 0;
}

int test_bare_multihart_restore(const fs::path& dir);

int test_bare_zstd_restore(const fs::path& dir)
{
  const fs::path elf = build_bare_elf(dir, "bare-zstd", single_hart_program());
  const fs::path prefix = dir / "snap-zstd";
  const fs::path other_prefix = dir / "snap-zstd-load";

  const std::string run_save_zstd =
      spike_bin().string() + " --compress-zstd --save=" + prefix.string() + " " + elf.string();
  const std::string run_load_none = spike_bin().string() + " --load=" + prefix.string();
  if (!run_cmd(run_save_zstd)) {
    return 40;
  }
  if (!artifact_set_exists(prefix)) {
    return 41;
  }
  if (!fs::exists(prefix.string() + ".mainram.zst")) {
    return 42;
  }
  if (!run_cmd(run_load_none)) {
    return 43;
  }
  if (!artifact_set_absent(other_prefix)) {
    return 44;
  }
  return 0;
}

int test_bare_multihart_restore(const fs::path& dir)
{
  const fs::path elf = build_bare_elf(dir, "bare-multihart", multi_hart_program());
  const fs::path prefix = dir / "snap-multihart";
  const fs::path other_prefix = dir / "snap-multihart-load";

  const std::string run_save = spike_bin().string() + " -p2 --save=" + prefix.string() + " " + elf.string();
  const std::string run_load = spike_bin().string() + " -p2 --load=" + prefix.string() + " " + elf.string();
  if (!run_cmd(run_save)) {
    return 30;
  }
  if (!artifact_set_exists(prefix)) {
    return 31;
  }
  if (!run_cmd(run_load)) {
    return 32;
  }
  if (!artifact_set_absent(other_prefix)) {
    return 33;
  }
  return 0;
}

}  // namespace

int main()
{
  const fs::path dir = fs::temp_directory_path() / "checkpoint-runtime-smoke";
  fs::remove_all(dir);
  fs::create_directories(dir);

  if (const int rc = test_bare_none_restore(dir)) {
    std::cerr << "test_bare_none_restore rc=" << rc << std::endl;
    return rc;
  }
  if (const int rc = test_bare_overlay_restore(dir)) {
    std::cerr << "test_bare_overlay_restore rc=" << rc << std::endl;
    return rc;
  }
  if (const int rc = test_bare_multihart_restore(dir)) {
    std::cerr << "test_bare_multihart_restore rc=" << rc << std::endl;
    return rc;
  }
  if (const int rc = test_bare_zstd_restore(dir)) {
    std::cerr << "test_bare_zstd_restore rc=" << rc << std::endl;
    return rc;
  }
  return 0;
}

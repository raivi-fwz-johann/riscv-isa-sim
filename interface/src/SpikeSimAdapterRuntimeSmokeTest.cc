#include "SpikeSimObjAsync.hpp"
#include "SpikeSimObjSync.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace {

fs::path write_file(const fs::path& path, const std::string& contents)
{
  std::ofstream out(path);
  out << contents;
  out.close();
  return path;
}

bool run_cmd(const std::string& cmd)
{
  return std::system(cmd.c_str()) == 0;
}

fs::path build_elf(const fs::path& dir, const std::string& name, const std::string& source)
{
  const fs::path ld = dir / "link.ld";
  write_file(ld,
             "OUTPUT_ARCH(riscv)\n"
             "ENTRY(_start)\n"
             "SECTIONS {\n"
             "  . = 0x80000000;\n"
             "  .text : { *(.text*) }\n"
             "  .rodata : { *(.rodata*) }\n"
             "  .tohost : { *(.tohost*) }\n"
             "  .data : { *(.data*) }\n"
             "  .bss : { *(.bss*) *(COMMON) }\n"
             "}\n");
  const fs::path src = dir / (name + ".S");
  const fs::path elf = dir / (name + ".elf");
  write_file(src, source);
  const std::string cmd =
      "/usr/bin/riscv64-linux-gnu-gcc -nostdlib -static -T " + ld.string() +
      " -o " + elf.string() + " " + src.string();
  if (!run_cmd(cmd)) {
    throw std::runtime_error("failed to build " + elf.string());
  }
  return elf;
}

std::string make_cmd(const fs::path& elf)
{
  return "spike --instructions=40 --isa=rv64gc " + elf.string();
}

int test_sync_path(const fs::path& dir)
{
  const auto elf = build_elf(
      dir,
      "sync",
      ".option norvc\n"
      ".section .text\n"
      ".globl _start\n"
      "_start:\n"
      "  addi s0, zero, 1\n"
      "  addi s1, zero, 2\n"
      "  add a0, s0, s1\n"
      "  addi a1, a0, 5\n"
      "1:\n"
      "  j 1b\n");

  const uint64_t expected_bits[] = {
      0x00100413,
      0x00200493,
      0x00940533,
      0x00550593,
  };

  SpikeSimObjSync sim;
  sim.init(make_cmd(elf));
  sim.start();

  size_t seen = 0;
  while (!sim.done() && seen < std::size(expected_bits)) {
    sim.step(1, 0);
    auto inst = sim.reqInst(0);
    if (!inst || inst->getPc() < 0x80000000) {
      continue;
    }
    if (inst->getBits() != expected_bits[seen]) {
      sim.stop();
      return 10 + static_cast<int>(seen);
    }
    ++seen;
  }

  sim.stop();
  return seen == std::size(expected_bits) ? 0 : 20;
}

int test_async_path(const fs::path& dir)
{
  const auto elf = build_elf(
      dir,
      "async",
      ".option norvc\n"
      ".section .text\n"
      ".globl _start\n"
      "_start:\n"
      "  addi s0, zero, 1\n"
      "  addi s1, zero, 2\n"
      "  add a0, s0, s1\n"
      "  addi a1, a0, 5\n"
      "1:\n"
      "  j 1b\n");

  const uint64_t expected_bits[] = {
      0x00100413,
      0x00200493,
      0x00940533,
      0x00550593,
  };

  SpikeSimObjAsync sim;
  sim.init(make_cmd(elf));
  sim.start();

  size_t seen = 0;
  while (!sim.done() && seen < std::size(expected_bits)) {
    auto inst = sim.takeInst(0);
    if (!inst || inst->getPc() < 0x80000000) {
      continue;
    }
    if (inst->getBits() != expected_bits[seen]) {
      sim.stop();
      sim.waitStop();
      return 30 + static_cast<int>(seen);
    }
    ++seen;
  }

  sim.stop();
  sim.waitStop();
  return seen == std::size(expected_bits) ? 0 : 40;
}

}  // namespace

int main()
{
  const fs::path dir = fs::temp_directory_path() / "spikesim-adapter-runtime-smoke";
  fs::create_directories(dir);

  if (const int rc = test_sync_path(dir)) {
    return rc;
  }
  if (const int rc = test_async_path(dir)) {
    return rc;
  }
  return 0;
}

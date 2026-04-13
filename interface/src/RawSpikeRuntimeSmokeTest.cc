#include "RawSpike.hpp"

#include "sim.h"
#include "trap.h"

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

std::string make_cmd(const fs::path& elf, bool disable_host = false)
{
  std::string cmd = "spike --instructions=40 --isa=rv64gc ";
  if (disable_host) {
    cmd += "--disable_host ";
  }
  cmd += elf.string();
  return cmd;
}

bool next_inst(RawSpike& sim, InstTrace& inst)
{
  while (!sim.done()) {
    sim.step(1, 0);
    inst.reset();
    if (sim.record(inst, 0) == 0 && inst.perfect()) {
      return true;
    }
  }
  return false;
}

bool next_target_inst(RawSpike& sim, InstTrace& inst)
{
  while (next_inst(sim, inst)) {
    if (inst.getPc() >= 0x80000000) {
      return true;
    }
  }
  return false;
}

int test_current_info_normal(const fs::path& dir)
{
  const auto elf = build_elf(
      dir,
      "normal",
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

  RawSpike sim;
  sim.init(make_cmd(elf));
  sim.start();

  const uint64_t expected_bits[] = {
      0x00100413,
      0x00200493,
      0x00940533,
      0x00550593,
  };

  for (size_t i = 0; i < 4; ++i) {
    InstTrace inst(0);
    if (!next_target_inst(sim, inst)) {
      return 10 + i;
    }
    if (inst.getBits() != expected_bits[i]) {
      return 20 + i;
    }
    if (inst.inTrap()) {
      return 30 + i;
    }
    if (inst.m_mmuTrace.paddr == 0 || inst.m_mmuTrace.paddr == ERROR_PC_ADDR) {
      return 40 + i;
    }
  }

  sim.stop();
  return 0;
}

int test_current_info_trap(const fs::path& dir)
{
  const auto elf = build_elf(
      dir,
      "trap",
      ".option norvc\n"
      ".section .text\n"
      ".globl _start\n"
      "_start:\n"
      "  addi s0, zero, 1\n"
      "  .word 0\n"
      "1:\n"
      "  j 1b\n");

  RawSpike sim;
  sim.init(make_cmd(elf));
  sim.start();

  bool saw_trap = false;
  while (!sim.done()) {
    InstTrace inst(0);
    if (!next_inst(sim, inst)) {
      break;
    }
    if (inst.getPc() < 0x80000000) {
      continue;
    }
    if (inst.inTrap()) {
      auto trap = inst.GetTrapInfo();
      if (trap.cause != CAUSE_ILLEGAL_INSTRUCTION) {
        return 51;
      }
      if (inst.m_mmuTrace.excp_cause != CAUSE_ILLEGAL_INSTRUCTION) {
        return 52;
      }
      saw_trap = true;
      break;
    }
  }

  sim.stop();
  return saw_trap ? 0 : 53;
}

int test_disable_host_smoke(const fs::path& dir)
{
  const auto elf = build_elf(
      dir,
      "disable_host",
      ".option norvc\n"
      ".section .tohost,\"aw\",@progbits\n"
      ".align 8\n"
      ".globl tohost\n"
      "tohost:\n"
      "  .dword 0\n"
      ".globl fromhost\n"
      "fromhost:\n"
      "  .dword 0\n"
      ".section .text\n"
      ".globl _start\n"
      "_start:\n"
      "  la t0, tohost\n"
      "  li t1, 1\n"
      "  sd t1, 0(t0)\n"
      "1:\n"
      "  j 1b\n");

  auto run_case = [&](bool disable_host) -> uint64_t {
    RawSpike sim;
    sim.init(make_cmd(elf, disable_host));
    sim.start();
    for (int i = 0; i < 16 && !sim.done(); ++i) {
      sim.step(1, 0);
      InstTrace inst(0);
      sim.record(inst, 0);
    }
    auto* spike = sim.getSpikeSimulator();
    const auto tohost_addr = spike->get_tohost_addr();
    const auto value = spike->from_target(spike->memif().read_uint64(tohost_addr));
    sim.stop();
    return value;
  };

  const uint64_t enabled_value = run_case(false);
  const uint64_t disabled_value = run_case(true);

  if (enabled_value != 0) {
    return 61;
  }
  if (disabled_value == 0) {
    return 62;
  }
  return 0;
}

}  // namespace

int main()
{
  const fs::path dir = fs::temp_directory_path() / "rawspike-runtime-smoke";
  fs::create_directories(dir);

  if (const int rc = test_current_info_normal(dir)) {
    return rc;
  }
  if (const int rc = test_current_info_trap(dir)) {
    return rc;
  }
  if (const int rc = test_disable_host_smoke(dir)) {
    return rc;
  }
  return 0;
}

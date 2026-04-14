#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/wait.h>
#include <vector>

namespace fs = std::filesystem;

namespace {

constexpr int kCompileTimeoutSec = 30;
constexpr int kRunTimeoutSec = 90;

enum class cmd_status_t
{
  ok,
  failed,
  timed_out,
};

std::string sh_quote(std::string_view arg)
{
  std::string out;
  out.reserve(arg.size() + 2);
  out.push_back('\'');
  for (const char c : arg) {
    if (c == '\'') {
      out += "'\\''";
    } else {
      out.push_back(c);
    }
  }
  out.push_back('\'');
  return out;
}

std::string join_argv(const std::vector<std::string>& argv)
{
  std::string cmd;
  for (size_t i = 0; i < argv.size(); ++i) {
    if (i != 0) {
      cmd.push_back(' ');
    }
    cmd += sh_quote(argv[i]);
  }
  return cmd;
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

cmd_status_t run_cmd_with_timeout(const std::string& cmd, int timeout_sec)
{
  const std::string wrapped = "timeout --foreground --signal=TERM --kill-after=2s " +
                              std::to_string(timeout_sec) + "s /bin/bash -lc " + sh_quote(cmd);
  const int rc = std::system(wrapped.c_str());
  if (rc == 0) {
    return cmd_status_t::ok;
  }
  if (rc == -1) {
    return cmd_status_t::failed;
  }
  if (WIFEXITED(rc)) {
    const int exit_code = WEXITSTATUS(rc);
    if (exit_code == 124 || exit_code == 137) {
      return cmd_status_t::timed_out;
    }
  }
  return cmd_status_t::failed;
}

int run_checked(const std::string& cmd, int fail_rc, int timeout_rc)
{
  switch (run_cmd_with_timeout(cmd, kRunTimeoutSec)) {
    case cmd_status_t::ok:
      return 0;
    case cmd_status_t::timed_out:
      std::cerr << "timeout: " << cmd << std::endl;
      return timeout_rc;
    case cmd_status_t::failed:
      return fail_rc;
  }
  return fail_rc;
}

bool is_executable_file(const fs::path& path)
{
  std::error_code ec;
  const auto status = fs::status(path, ec);
  if (ec || !fs::is_regular_file(status)) {
    return false;
  }
  const auto perms = status.permissions();
  return (perms & fs::perms::owner_exec) != fs::perms::none ||
         (perms & fs::perms::group_exec) != fs::perms::none ||
         (perms & fs::perms::others_exec) != fs::perms::none;
}

std::optional<fs::path> find_in_path(const std::string& name)
{
  const char* path_env = std::getenv("PATH");
  if (!path_env || *path_env == '\0') {
    return std::nullopt;
  }

  std::stringstream ss(path_env);
  std::string segment;
  while (std::getline(ss, segment, ':')) {
    const fs::path base = segment.empty() ? fs::path(".") : fs::path(segment);
    const fs::path candidate = base / name;
    if (is_executable_file(candidate)) {
      return candidate;
    }
  }
  return std::nullopt;
}

std::string riscv_gcc()
{
  if (const char* override = std::getenv("RISCV_GCC"); override && *override) {
    return std::string(override);
  }
  if (auto found = find_in_path("riscv64-linux-gnu-gcc")) {
    return found->string();
  }
  throw std::runtime_error("riscv64-linux-gnu-gcc not found; set RISCV_GCC");
}

fs::path spike_bin()
{
  if (const char* override = std::getenv("SPIKE_BIN"); override && *override) {
    return fs::path(override);
  }

  std::error_code ec;
  const fs::path self = fs::read_symlink("/proc/self/exe", ec);
  if (ec) {
    throw std::runtime_error("cannot resolve /proc/self/exe for spike path derivation");
  }
  return self.parent_path() / "thirdparty" / "riscv-isa-sim" / "bin" / "spike";
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

int build_bare_elf(const fs::path& dir, const std::string& name, const std::string& source, fs::path& elf)
{
  const fs::path ld = dir / (name + ".ld");
  const fs::path src = dir / (name + ".S");
  elf = dir / (name + ".elf");
  write_file(ld, bare_linker_script());
  write_file(src, source);

  const std::string cmd = join_argv({
      riscv_gcc(),
      "-nostdlib",
      "-static",
      "-march=rv64imafd",
      "-mabi=lp64d",
      "-T",
      ld.string(),
      "-o",
      elf.string(),
      src.string(),
  });
  switch (run_cmd_with_timeout(cmd, kCompileTimeoutSec)) {
    case cmd_status_t::ok:
      return 0;
    case cmd_status_t::timed_out:
      std::cerr << "timeout: " << cmd << std::endl;
      return 2;
    case cmd_status_t::failed:
      return 1;
  }
  return 1;
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
  fs::path elf;
  if (const int build_rc = build_bare_elf(dir, "bare-none", single_hart_program(), elf)) {
    return build_rc == 2 ? 15 : 14;
  }

  const fs::path spike = spike_bin();
  const fs::path prefix = dir / "snap-none";
  const fs::path other_prefix = dir / "snap-none-load";

  const std::string run_save = join_argv({spike.string(), "--save=" + prefix.string(), elf.string()});
  const std::string run_load =
      join_argv({spike.string(), "--load=" + prefix.string(), "--save=" + other_prefix.string()});
  if (const int rc = run_checked(run_save, 10, 16)) {
    return rc;
  }
  if (!artifact_set_exists(prefix)) {
    return 11;
  }
  if (const int rc = run_checked(run_load, 12, 17)) {
    return rc;
  }
  if (!artifact_set_absent(other_prefix)) {
    return 13;
  }
  return 0;
}

int test_bare_overlay_restore(const fs::path& dir)
{
  fs::path elf;
  if (const int build_rc = build_bare_elf(dir, "bare-overlay", single_hart_program(), elf)) {
    return build_rc == 2 ? 25 : 24;
  }

  const fs::path spike = spike_bin();
  const fs::path prefix = dir / "snap-overlay";
  const fs::path other_prefix = dir / "snap-overlay-load";

  const std::string run_save = join_argv({spike.string(), "--save=" + prefix.string(), elf.string()});
  const std::string run_load_overlay =
      join_argv({spike.string(), "--load=" + prefix.string(), "--save=" + other_prefix.string(), elf.string()});
  if (const int rc = run_checked(run_save, 20, 26)) {
    return rc;
  }
  if (!artifact_set_exists(prefix)) {
    return 21;
  }
  if (const int rc = run_checked(run_load_overlay, 22, 27)) {
    return rc;
  }
  if (!artifact_set_absent(other_prefix)) {
    return 23;
  }
  return 0;
}

int test_bare_multihart_restore(const fs::path& dir);

int test_bare_zstd_restore(const fs::path& dir)
{
  fs::path elf;
  if (const int build_rc = build_bare_elf(dir, "bare-zstd", single_hart_program(), elf)) {
    return build_rc == 2 ? 46 : 45;
  }

  const fs::path spike = spike_bin();
  const fs::path prefix = dir / "snap-zstd";
  const fs::path other_prefix = dir / "snap-zstd-load";

  const std::string run_save_zstd = join_argv({
      spike.string(),
      "--compress-zstd",
      "--save=" + prefix.string(),
      elf.string(),
  });
  const std::string run_load_none =
      join_argv({spike.string(), "--load=" + prefix.string(), "--save=" + other_prefix.string()});
  if (const int rc = run_checked(run_save_zstd, 40, 47)) {
    return rc;
  }
  if (!artifact_set_exists(prefix)) {
    return 41;
  }
  if (!fs::exists(prefix.string() + ".mainram.zst")) {
    return 42;
  }
  if (const int rc = run_checked(run_load_none, 43, 48)) {
    return rc;
  }
  if (!artifact_set_absent(other_prefix)) {
    return 44;
  }
  return 0;
}

int test_bare_multihart_restore(const fs::path& dir)
{
  fs::path elf;
  if (const int build_rc = build_bare_elf(dir, "bare-multihart", multi_hart_program(), elf)) {
    return build_rc == 2 ? 35 : 34;
  }

  const fs::path spike = spike_bin();
  const fs::path prefix = dir / "snap-multihart";
  const fs::path other_prefix = dir / "snap-multihart-load";

  const std::string run_save = join_argv({spike.string(), "-p2", "--save=" + prefix.string(), elf.string()});
  const std::string run_load =
      join_argv({spike.string(), "-p2", "--load=" + prefix.string(), "--save=" + other_prefix.string(), elf.string()});
  if (const int rc = run_checked(run_save, 30, 36)) {
    return rc;
  }
  if (!artifact_set_exists(prefix)) {
    return 31;
  }
  if (const int rc = run_checked(run_load, 32, 37)) {
    return rc;
  }
  if (!artifact_set_absent(other_prefix)) {
    return 33;
  }
  return 0;
}

}  // namespace

int main()
{
  try {
    const fs::path spike = spike_bin();
    if (!is_executable_file(spike)) {
      std::cerr << "spike binary not found or not executable: " << spike << std::endl;
      return 2;
    }

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
  } catch (const std::exception& e) {
    std::cerr << "fatal: " << e.what() << std::endl;
    return 199;
  }
}

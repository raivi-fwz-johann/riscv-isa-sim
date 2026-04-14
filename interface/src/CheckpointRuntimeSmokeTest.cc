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
#include <utility>
#include <vector>

namespace fs = std::filesystem;

namespace {

constexpr int kCompileTimeoutSec = 30;
constexpr int kRunTimeoutSec = 90;
constexpr int kPkBuildTimeoutSec = 600;

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

std::string read_file(const fs::path& path)
{
  std::ifstream in(path);
  if (!in.is_open()) {
    throw std::runtime_error("cannot open " + path.string());
  }
  std::ostringstream ss;
  ss << in.rdbuf();
  return ss.str();
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

fs::path pk_build_dir()
{
  return "/workspace/johann/code/riscv-pk/build-spike-master-ckpt";
}

fs::path pk_source_dir()
{
  return pk_build_dir() / "pk-source";
}

fs::path pk_bin()
{
  const fs::path nested = pk_build_dir() / "pk" / "pk";
  if (is_executable_file(nested)) {
    return nested;
  }
  return pk_build_dir() / "pk";
}

void prepare_pk_source_tree()
{
  if (fs::exists(pk_source_dir() / "configure")) {
    return;
  }

  fs::create_directories(pk_build_dir());
  const std::string copy_cmd =
      "rm -rf " + sh_quote(pk_source_dir().string()) + " && mkdir -p " + sh_quote(pk_source_dir().string()) +
      " && rsync -a --exclude " + sh_quote("build-spike-master-ckpt/") + " " +
      sh_quote("/workspace/johann/code/riscv-pk/") + " " + sh_quote(pk_source_dir().string()) + "/";
  switch (run_cmd_with_timeout(copy_cmd, kPkBuildTimeoutSec)) {
    case cmd_status_t::ok:
      break;
    case cmd_status_t::timed_out:
      throw std::runtime_error("pk source copy timed out");
    case cmd_status_t::failed:
      throw std::runtime_error("pk source copy failed");
  }
}

void apply_pk_compat_patch()
{
  const fs::path minit = pk_source_dir() / "machine" / "minit.c";
  {
    std::string contents = read_file(minit);
    const std::string old_line =
        "  write_csr(menvcfg, MENVCFG_SSE | MENVCFG_CBCFE | INSERT_FIELD(0, MENVCFG_CBIE, 1));";
    const std::string new_line =
        "  asm volatile (\"csrw 0x30a, %0\" :: \"rK\"(MENVCFG_SSE | MENVCFG_CBCFE | "
        "INSERT_FIELD(0, MENVCFG_CBIE, 1)));";
    const size_t pos = contents.find(old_line);
    if (pos != std::string::npos) {
      contents.replace(pos, old_line.size(), new_line);
      write_file(minit, contents);
    } else if (contents.find(new_line) == std::string::npos) {
      throw std::runtime_error("pk menvcfg compatibility patch point not found");
    }
  }

  const fs::path pk_c = pk_source_dir() / "pk" / "pk.c";
  {
    std::string contents = read_file(pk_c);
    const std::vector<std::pair<std::string, std::string>> rewrites = {
        {
            "    set_csr(senvcfg, SENVCFG_SSE);",
            "    asm volatile (\"csrs 0x10a, %0\" :: \"rK\"(SENVCFG_SSE));",
        },
        {
            "  set_csr(senvcfg, SENVCFG_CBCFE | INSERT_FIELD(0, SENVCFG_CBIE, 1));",
            "  asm volatile (\"csrs 0x10a, %0\" :: \"rK\"(SENVCFG_CBCFE | INSERT_FIELD(0, SENVCFG_CBIE, 1)));",
        },
        {
            "    set_csr(senvcfg, SENVCFG_LPE);",
            "    asm volatile (\"csrs 0x10a, %0\" :: \"rK\"(SENVCFG_LPE));",
        },
    };

    for (const auto& rewrite : rewrites) {
      const size_t pos = contents.find(rewrite.first);
      if (pos != std::string::npos) {
        contents.replace(pos, rewrite.first.size(), rewrite.second);
      } else if (contents.find(rewrite.second) == std::string::npos) {
        throw std::runtime_error("pk senvcfg compatibility patch point not found");
      }
    }
    write_file(pk_c, contents);
  }
}

void ensure_pk_built()
{
  if (is_executable_file(pk_bin())) {
    return;
  }

  std::string host = "riscv64-unknown-linux-gnu";
  const std::string gcc_name = fs::path(riscv_gcc()).filename().string();
  if (gcc_name.size() > 4 && gcc_name.rfind("-gcc") == gcc_name.size() - 4) {
    host = gcc_name.substr(0, gcc_name.size() - 4);
  }

  prepare_pk_source_tree();
  apply_pk_compat_patch();

  const std::string configure_cmd =
      "cd " + sh_quote(pk_build_dir().string()) + " && " +
      join_argv({(pk_source_dir() / "configure").string(), "--host=" + host});
  const std::string build_cmd = "cd " + sh_quote(pk_build_dir().string()) + " && " + join_argv({"make", "-j4"});

  switch (run_cmd_with_timeout(configure_cmd, kPkBuildTimeoutSec)) {
    case cmd_status_t::ok:
      break;
    case cmd_status_t::timed_out:
      throw std::runtime_error("pk configure timed out");
    case cmd_status_t::failed:
      throw std::runtime_error("pk configure failed");
  }

  switch (run_cmd_with_timeout(build_cmd, kPkBuildTimeoutSec)) {
    case cmd_status_t::ok:
      break;
    case cmd_status_t::timed_out:
      throw std::runtime_error("pk build timed out");
    case cmd_status_t::failed:
      throw std::runtime_error("pk build failed");
  }

  if (!is_executable_file(pk_bin())) {
    throw std::runtime_error("pk binary missing after build");
  }
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

fs::path build_pk_user_elf(const fs::path& dir, const std::string& name, const std::string& source)
{
  const fs::path src = dir / (name + ".c");
  const fs::path elf = dir / (name + ".elf");
  write_file(src, source);

  const std::string cmd =
      join_argv({riscv_gcc(), "-static", "-O2", "-o", elf.string(), src.string()});
  switch (run_cmd_with_timeout(cmd, kCompileTimeoutSec)) {
    case cmd_status_t::ok:
      return elf;
    case cmd_status_t::timed_out:
      std::cerr << "timeout: " << cmd << std::endl;
      throw std::runtime_error("failed to build pk user elf (timed out)");
    case cmd_status_t::failed:
      throw std::runtime_error("failed to build pk user elf");
  }
  throw std::runtime_error("failed to build pk user elf");
}

std::string pk_user_program()
{
  return
      "#include <stdint.h>\n"
      "#include <unistd.h>\n"
      "\n"
      "volatile uint64_t progress = 0;\n"
      "\n"
      "int main(void) {\n"
      "  static const char msg[] = \"pk-finished\\n\";\n"
      "  while (progress < 100000) {\n"
      "    progress++;\n"
      "  }\n"
      "  while (progress < 1100000) {\n"
      "    if (write(1, msg, sizeof(msg) - 1) < 0) {\n"
      "      return 1;\n"
      "    }\n"
      "    progress++;\n"
      "  }\n"
      "  return 0;\n"
      "}\n";
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

bool artifact_set_uses_legacy_names_only(const fs::path& prefix)
{
  const std::string base = prefix.filename().string();
  const fs::path dir = prefix.parent_path();
  if (!fs::exists(dir)) {
    return false;
  }

  const std::vector<std::string> allowed = {
      ".bootram",
      ".mainram",
      ".mainram.zip",
      ".mainram.zst",
      ".htif",
      ".re_regs",
  };

  for (const auto& entry : fs::directory_iterator(dir)) {
    if (!entry.is_regular_file()) {
      continue;
    }
    const std::string name = entry.path().filename().string();
    if (name.rfind(base + ".", 0) != 0) {
      continue;
    }

    bool ok = false;
    for (const auto& suffix : allowed) {
      if (name == base + suffix) {
        ok = true;
        break;
      }
    }
    if (!ok) {
      return false;
    }
  }
  return true;
}

bool file_contains_text(const fs::path& path, std::string_view needle)
{
  std::ifstream in(path);
  if (!in.is_open()) {
    return false;
  }
  std::string line;
  while (std::getline(in, line)) {
    if (line.find(needle) != std::string::npos) {
      return true;
    }
  }
  return false;
}

std::optional<std::string> read_saved_pc(const fs::path& prefix)
{
  std::ifstream in(prefix.string() + ".re_regs");
  if (!in.is_open()) {
    return std::nullopt;
  }

  std::string line;
  while (std::getline(in, line)) {
    if (line.rfind("pc:", 0) == 0) {
      return line.substr(3);
    }
  }
  return std::nullopt;
}

int ensure_pc_progressed(const fs::path& from_prefix, const fs::path& to_prefix, int fail_rc)
{
  const auto from_pc = read_saved_pc(from_prefix);
  const auto to_pc = read_saved_pc(to_prefix);
  if (!from_pc || !to_pc) {
    return fail_rc;
  }
  if (*from_pc == *to_pc) {
    return fail_rc;
  }
  return 0;
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
  if (!artifact_set_exists(other_prefix)) {
    return 13;
  }
  if (const int rc = ensure_pc_progressed(prefix, other_prefix, 18)) {
    return rc;
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
  if (!artifact_set_exists(other_prefix)) {
    return 23;
  }
  if (const int rc = ensure_pc_progressed(prefix, other_prefix, 28)) {
    return rc;
  }
  return 0;
}

int test_pk_single_restore(const fs::path& dir)
{
  const fs::path user_elf = build_pk_user_elf(dir, "pk-single-user", pk_user_program());
  const fs::path spike = spike_bin();
  const fs::path prefix = dir / "snap-pk-single";
  const fs::path save_log = dir / "snap-pk-single-save.log";
  const fs::path log = dir / "snap-pk-single-load.log";

  const std::string pk_save = join_argv({
                                  spike.string(),
                                  "--instructions=4000000",
                                  "--save=" + prefix.string(),
                                  pk_bin().string(),
                                  user_elf.string(),
                              }) +
                              " >" + sh_quote(save_log.string()) + " 2>&1";
  // Load-only restore shape avoids replaying a fresh pk bootstrap path.
  const std::string pk_load = join_argv({
                                  spike.string(),
                                  "--instructions=50000",
                                  "--load=" + prefix.string(),
                              }) +
                              " >" + sh_quote(log.string()) + " 2>&1";

  if (const int rc = run_checked(pk_save, 50, 56)) {
    return rc;
  }
  if (!artifact_set_exists(prefix)) {
    return 51;
  }
  if (!artifact_set_uses_legacy_names_only(prefix)) {
    return 52;
  }
  if (const int rc = run_checked(pk_load, 53, 57)) {
    return rc;
  }
  if (file_contains_text(log, "assertion failed")) {
    return 55;
  }
  if (!file_contains_text(log, "pk-finished")) {
    return 54;
  }
  return 0;
}

int test_pk_multihart_restore(const fs::path& dir)
{
  const fs::path user_elf = build_pk_user_elf(dir, "pk-p2-user", pk_user_program());
  const fs::path spike = spike_bin();
  const fs::path prefix = dir / "snap-pk-p2";
  const fs::path save_log = dir / "snap-pk-p2-save.log";
  const fs::path log = dir / "snap-pk-p2-load.log";

  const std::string pk_save = join_argv({
                                  spike.string(),
                                  "-p2",
                                  "--instructions=4000000",
                                  "--save=" + prefix.string(),
                                  pk_bin().string(),
                                  user_elf.string(),
                              }) +
                              " >" + sh_quote(save_log.string()) + " 2>&1";
  const std::string pk_load = join_argv({
                                  spike.string(),
                                  "-p2",
                                  "--instructions=50000",
                                  "--load=" + prefix.string(),
                              }) +
                              " >" + sh_quote(log.string()) + " 2>&1";

  if (const int rc = run_checked(pk_save, 60, 66)) {
    return rc;
  }
  if (!artifact_set_exists(prefix)) {
    return 61;
  }
  if (!artifact_set_uses_legacy_names_only(prefix)) {
    return 62;
  }
  if (const int rc = run_checked(pk_load, 63, 67)) {
    return rc;
  }
  if (file_contains_text(log, "assertion failed")) {
    return 65;
  }
  if (!file_contains_text(log, "pk-finished")) {
    return 64;
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
  if (!artifact_set_exists(other_prefix)) {
    return 44;
  }
  if (const int rc = ensure_pc_progressed(prefix, other_prefix, 49)) {
    return rc;
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
  if (!artifact_set_exists(other_prefix)) {
    return 33;
  }
  if (const int rc = ensure_pc_progressed(prefix, other_prefix, 38)) {
    return rc;
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

    ensure_pk_built();

    if (const int rc = test_pk_single_restore(dir)) {
      std::cerr << "test_pk_single_restore rc=" << rc << std::endl;
      return rc;
    }
    if (const int rc = test_pk_multihart_restore(dir)) {
      std::cerr << "test_pk_multihart_restore rc=" << rc << std::endl;
      return rc;
    }
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

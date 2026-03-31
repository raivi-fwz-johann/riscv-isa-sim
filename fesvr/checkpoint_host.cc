// Checkpoint host-state save/load — implemented as htif_t member functions
// so they have access to private members (syscall_proxy, targs, addr2symbol,
// expected_xlen) without needing friend declarations.
//
// This file is compiled separately to keep htif.cc close to upstream.

#include "htif.h"
#include "elfloader.h"
#include "byteorder.h"

#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

#define LEGACY_PK_MAX_FILES 128

namespace {

std::string hex_encode(const std::string& input)
{
  static const char digits[] = "0123456789abcdef";
  std::string encoded;
  encoded.reserve(input.size() * 2);
  for (unsigned char ch : input) {
    encoded.push_back(digits[ch >> 4]);
    encoded.push_back(digits[ch & 0xf]);
  }
  return encoded;
}

std::string hex_decode(const std::string& input)
{
  if (input.size() % 2 != 0)
    throw std::runtime_error("hex string has odd length");

  auto hex_value = [](char ch) -> int {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    return -1;
  };

  std::string decoded;
  decoded.reserve(input.size() / 2);
  for (size_t i = 0; i < input.size(); i += 2) {
    int hi = hex_value(input[i]);
    int lo = hex_value(input[i + 1]);
    if (hi < 0 || lo < 0)
      throw std::runtime_error("hex string contains non-hex character");
    decoded.push_back(char((hi << 4) | lo));
  }
  return decoded;
}

std::string get_fd_path(int fd)
{
  char proc_path[64];
  snprintf(proc_path, sizeof(proc_path), "/proc/self/fd/%d", fd);

  std::vector<char> path(PATH_MAX + 1);
  ssize_t len = readlink(proc_path, path.data(), path.size() - 1);
  if (len < 0) return {};
  path[len] = '\0';
  return std::string(path.data(), len);
}

bool is_restorable_host_path(const std::string& path)
{
  const std::string deleted_suffix = " (deleted)";
  return !path.empty() &&
         path.front() == '/' &&
         !(path.size() >= deleted_suffix.size() &&
           path.compare(path.size() - deleted_suffix.size(),
                        deleted_suffix.size(), deleted_suffix) == 0);
}

addr_t lookup_symbol_addr(const std::map<uint64_t, std::string>& addr2symbol,
                          const char* symbol)
{
  for (const auto& entry : addr2symbol)
    if (entry.second == symbol)
      return entry.first;
  return 0;
}

// Determine if a guest fd is one of the 3 stdio fds set up by the
// syscall_t constructor (guest fds 0, 1, 2).
bool is_stdio_guest_fd(reg_t guest_fd)
{
  return guest_fd <= 2;
}

} // namespace

// ---------------------------------------------------------------------------
// Save host state
// ---------------------------------------------------------------------------

void htif_t::save_checkpoint_host_state(std::ostream& out) const
{
  out << "# spike syscall host state" << std::endl;

  char* cwd = getcwd(nullptr, 0);
  if (cwd != nullptr) {
    out << "cwd " << hex_encode(cwd) << std::endl;
    free(cwd);
  }

  const auto& fds_vec = syscall_proxy.get_fds().raw_fds();
  for (size_t guest_fd = 0; guest_fd < fds_vec.size(); ++guest_fd) {
    int host_fd = fds_vec[guest_fd];
    if (host_fd < 0)
      continue;

    if (is_stdio_guest_fd(guest_fd)) {
      // Stdio fds: record which standard fd they map to (0=stdin, 1=stdout)
      int stdio_fd = (guest_fd == 0) ? 0 : 1;
      out << "fd " << guest_fd << " stdio " << stdio_fd << std::endl;
      continue;
    }

    const std::string path = get_fd_path(host_fd);
    if (!is_restorable_host_path(path)) {
      out << "fd " << guest_fd << " opaque" << std::endl;
      continue;
    }

    int flags = fcntl(host_fd, F_GETFL);
    if (flags < 0) {
      out << "fd " << guest_fd << " opaque" << std::endl;
      continue;
    }

    errno = 0;
    off_t offset = lseek(host_fd, 0, SEEK_CUR);
    long long saved_offset = offset >= 0 ? static_cast<long long>(offset) : -1;

    out << "fd " << guest_fd << " path " << flags << " "
        << saved_offset << " " << hex_encode(path) << std::endl;
  }
}

// ---------------------------------------------------------------------------
// Load host state
// ---------------------------------------------------------------------------

void htif_t::load_checkpoint_host_state(std::istream& in)
{
  // Build a new fd vector from the checkpoint, then replace the current one.
  // Start with an empty vector — we'll populate it from the checkpoint data.
  std::vector<int> new_fds;

  auto ensure_size = [&new_fds](reg_t fd) {
    if (fd >= new_fds.size())
      new_fds.resize(fd + 1, -1);
  };

  std::string line;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#')
      continue;

    std::istringstream iss(line);
    std::string tag;
    iss >> tag;

    if (tag == "cwd") {
      std::string encoded_cwd;
      if (!(iss >> encoded_cwd))
        throw std::runtime_error("malformed checkpoint host cwd entry");

      const std::string cwd = hex_decode(encoded_cwd);
      if (chdir(cwd.c_str()) != 0)
        throw std::runtime_error("failed to restore checkpoint cwd: " + cwd);
      continue;
    }

    if (tag != "fd")
      throw std::runtime_error("unknown checkpoint host-state record: " + tag);

    reg_t guest_fd;
    std::string type;
    if (!(iss >> guest_fd >> type))
      throw std::runtime_error("malformed checkpoint fd entry");

    if (type == "stdio") {
      int stdio_fd;
      if (!(iss >> stdio_fd))
        throw std::runtime_error("malformed stdio checkpoint fd entry");

      int host_fd = dup(stdio_fd);
      if (host_fd < 0)
        throw std::runtime_error("failed to dup stdio while restoring checkpoint state");

      ensure_size(guest_fd);
      new_fds[guest_fd] = host_fd;
      continue;
    }

    if (type == "path") {
      int flags;
      long long saved_offset;
      std::string encoded_path;
      if (!(iss >> flags >> saved_offset >> encoded_path))
        throw std::runtime_error("malformed path checkpoint fd entry");

      const std::string path = hex_decode(encoded_path);
      int host_fd = open(path.c_str(), flags);
      if (host_fd < 0)
        throw std::runtime_error("failed to reopen checkpoint fd path: " + path);

      if (saved_offset >= 0 && lseek(host_fd, static_cast<off_t>(saved_offset), SEEK_SET) < 0) {
        close(host_fd);
        throw std::runtime_error("failed to restore checkpoint fd offset for: " + path);
      }

      ensure_size(guest_fd);
      new_fds[guest_fd] = host_fd;
      continue;
    }

    if (type == "opaque") {
      std::cerr << "warning: checkpoint fd " << guest_fd
                << " is not restorable; leaving it closed" << std::endl;
      continue;
    }

    throw std::runtime_error("unknown checkpoint fd type: " + type);
  }

  // Replace the fd table atomically (closes all old host fds first)
  syscall_proxy.get_fds().replace_all(std::move(new_fds));
}

// ---------------------------------------------------------------------------
// Legacy pk restore (no .hoststate file)
// ---------------------------------------------------------------------------

bool htif_t::restore_legacy_checkpoint_host_state()
{
  if (targs.size() < 2)
    return false;

  class nop_memif_t : public memif_t {
   public:
    nop_memif_t(htif_t* htif) : memif_t(htif) {}
    void read(addr_t, size_t, void*) override {}
    void write(addr_t, size_t, const void*) override {}
  } nop_memif(this);

  addr_t files_addr = 0;
  reg_t dummy_entry = 0;
  try {
    auto symbols = load_elf(targs[0].c_str(), &nop_memif, &dummy_entry,
                            0, expected_xlen);
    auto it = symbols.find("files");
    if (it != symbols.end())
      files_addr = it->second;
  } catch (const std::exception&) {
  }

  if (files_addr == 0)
    files_addr = lookup_symbol_addr(addr2symbol, "files");

  if (files_addr == 0)
    return false;

  struct serialized_file_t {
    target_endian<int32_t> kfd;
    target_endian<uint32_t> refcnt;
  };

  std::vector<serialized_file_t> files(LEGACY_PK_MAX_FILES);
  mem.read(files_addr, files.size() * sizeof(files[0]), files.data());

  std::vector<int32_t> active_guest_kfds;
  for (const auto& file : files) {
    const int32_t guest_kfd = from_target(file.kfd);
    const uint32_t refcnt = from_target(file.refcnt);
    if (refcnt == 0 || guest_kfd < 0 || guest_kfd <= 2)
      continue;

    bool seen = false;
    for (int32_t existing : active_guest_kfds) {
      if (existing == guest_kfd) {
        seen = true;
        break;
      }
    }
    if (!seen)
      active_guest_kfds.push_back(guest_kfd);
  }

  if (active_guest_kfds.empty())
    return false;

  if (active_guest_kfds.size() != 1) {
    std::cerr << "warning: checkpoint is missing hoststate and has "
              << active_guest_kfds.size()
              << " active guest-backed files; legacy restore cannot reconstruct them"
              << std::endl;
    return false;
  }

  const std::string payload_path = targs[1];
  int host_fd = open(payload_path.c_str(), O_RDONLY);
  if (host_fd < 0) {
    std::cerr << "warning: failed to reopen payload for legacy checkpoint restore: "
              << payload_path << std::endl;
    return false;
  }

  // Insert the fd at the correct guest slot (closes old fd at that slot if any)
  syscall_proxy.get_fds().set_fd(active_guest_kfds.front(), host_fd);

  std::cerr << "warning: checkpoint missing .hoststate; restored legacy pk payload fd "
            << active_guest_kfds.front() << " from " << payload_path << std::endl;
  return true;
}

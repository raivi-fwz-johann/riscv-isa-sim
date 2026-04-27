// See LICENSE for license details.

#include "integration/spike_bootstrap.h"

#include "arith.h"
#include "checkpoint/checkpoint_restore_rom.h"
#include "config.h"
#include "mmu.h"
#include "platform.h"
#include "runtime/spike_model_compat.h"
#include "../VERSION"
#include <dlfcn.h>
#include <fesvr/option_parser.h>
#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>

static void help(int exit_code = 1)
{
  fprintf(stderr, "Spike RISC-V ISA Simulator " SPIKE_VERSION "\n\n");
  fprintf(stderr, "usage: spike [host options] <target program> [target options]\n");
  fprintf(stderr, "Host Options:\n");
  fprintf(stderr, "  -p<n>                 Simulate <n> processors [default 1]\n");
  fprintf(stderr, "  -m<n>                 Provide <n> MiB of target memory [default 2048]\n");
  fprintf(stderr, "  -m<a:m,b:n,...>       Provide memory regions of size m and n bytes\n");
  fprintf(stderr, "                          at base addresses a and b (with 4 KiB alignment)\n");
  fprintf(stderr, "  -d                    Interactive debug mode\n");
  fprintf(stderr, "  -g                    Track histogram of PCs\n");
  fprintf(stderr, "  -l                    Generate a log of execution\n");
#ifdef HAVE_BOOST_ASIO
  fprintf(stderr, "  -s                    Command I/O via socket (use with -d)\n");
#endif
  fprintf(stderr, "  -h, --help            Print this help message\n");
  fprintf(stderr, "  --halted              Start halted, allowing a debugger to connect\n");
  fprintf(stderr, "  --log=<name>          File name for option -l\n");
  fprintf(stderr, "  --debug-cmd=<name>    Read commands from file (use with -d)\n");
  fprintf(stderr, "  --isa=<name>          RISC-V ISA string [default %s]\n", DEFAULT_ISA);
  fprintf(stderr, "  --pmpregions=<n>      Number of PMP regions [default 16]\n");
  fprintf(stderr, "  --pmpgranularity=<n>  PMP Granularity in bytes [default 4]\n");
  fprintf(stderr, "  --priv=<m|mu|msu>     RISC-V privilege modes supported [default %s]\n", DEFAULT_PRIV);
  fprintf(stderr, "  --pc=<address>        Override ELF entry point\n");
  fprintf(stderr, "  --hartids=<a,b,...>   Explicitly specify hartids, default is 0,1,...\n");
  fprintf(stderr, "  --ic=<S>:<W>:<B>      Instantiate a cache model with S sets,\n");
  fprintf(stderr, "  --dc=<S>:<W>:<B>        W ways, and B-byte blocks (with S and\n");
  fprintf(stderr, "  --l2=<S>:<W>:<B>        B both powers of 2).\n");
  fprintf(stderr, "  --big-endian          Use a big-endian memory system.\n");
  fprintf(stderr, "  --device=<name>       Attach MMIO plugin device from an --extlib library,\n");
  fprintf(stderr, "                          specify --device=<name>,<args> to pass down extra args.\n");
  fprintf(stderr, "  --dtb-discovery       Enable direct device discovery from device tree blob. Requires --dtb and usage of special \"spike_plugin_params\" dts field.\n");
  fprintf(stderr, "  --log-cache-miss      Generate a log of cache miss\n");
  fprintf(stderr, "  --log-commits         Generate a log of commits info\n");
  fprintf(stderr, "  --log-commits-stant   Generate a log of commits info suitable for stant utility\n");
  fprintf(stderr, "  --extension=<name>    Specify RoCC Extension\n");
  fprintf(stderr, "                          This flag can be used multiple times.\n");
  fprintf(stderr, "  --extlib=<name>       Shared library to load\n");
  fprintf(stderr, "                        This flag can be used multiple times.\n");
  fprintf(stderr, "  --rbb-port=<port>     Listen on <port> for remote bitbang connection\n");
  fprintf(stderr, "  --dump-dts            Print device tree string and exit\n");
  fprintf(stderr, "  --dtb=<path>          Use specified device tree blob [default: auto-generate]\n");
  fprintf(stderr, "  --disable-dtb         Don't write the device tree blob into memory\n");
  fprintf(stderr, "  --disable_host        Disable communicate with host when running simulation\n");
  fprintf(stderr, "  --kernel=<path>       Load kernel flat image into memory\n");
  fprintf(stderr, "  --initrd=<path>       Load kernel initrd into memory\n");
  fprintf(stderr, "  --bootargs=<args>     Provide custom bootargs for kernel [default: %s]\n",
          DEFAULT_KERNEL_BOOTARGS);
  fprintf(stderr, "  --real-time-clint     Increment clint time at real-time rate\n");
  fprintf(stderr, "  --triggers=<n>        Number of supported triggers [default 4]\n");
  fprintf(stderr, "  --dm-progsize=<words> Progsize for the debug module [default 2]\n");
  fprintf(stderr, "  --dm-datacount=<n>    Number of data registers available for the debug module [default 2]\n");
  fprintf(stderr, "  --dm-sba=<bits>       Debug system bus access supports up to "
      "<bits> wide accesses [default 0]\n");
  fprintf(stderr, "  --dm-auth             Debug module requires debugger to authenticate\n");
  fprintf(stderr, "  --dmi-rti=<n>         Number of Run-Test/Idle cycles "
      "required for a DMI access [default 0]\n");
  fprintf(stderr, "  --dm-abstract-rti=<n> Number of Run-Test/Idle cycles "
      "required for an abstract command to execute [default 0]\n");
  fprintf(stderr, "  --dm-no-hasel         Debug module won't support hasel\n");
  fprintf(stderr, "  --dm-no-abstract-csr  Debug module won't support abstract CSR access\n");
  fprintf(stderr, "  --dm-no-abstract-fpr  Debug module won't support abstract FPR access\n");
  fprintf(stderr, "  --dm-no-halt-groups   Debug module won't support halt groups\n");
  fprintf(stderr, "  --dm-no-impebreak     Debug module won't support implicit ebreak in program buffer\n");
  fprintf(stderr, "  --dm-no-abstractauto  Debug module won't support the abstractauto register\n");
  fprintf(stderr, "  --blocksz=<size>      Cache block size (B) for CMO operations(powers of 2) [default 64]\n");
  fprintf(stderr, "  --instructions=<n>    Stop after n instructions\n");
  fprintf(stderr, "  --step=<interleave>   Set interleave for step in spike simulation\n");
  fprintf(stderr, "  --save=<name>         Save checkpoint files with prefix <name>\n");
  fprintf(stderr, "  --load=<name>         Load checkpoint files with prefix <name>\n");
  fprintf(stderr, "  --compress            Compress checkpoint mainram as .zip\n");
  fprintf(stderr, "  --compress-zstd       Compress checkpoint mainram as .zst\n");
  fprintf(stderr, "  --memsize=<size>      Memsize in unit of GB [default 2, options: 2, 4, 8]\n");

  exit(exit_code);
}

static void suggest_help()
{
  fprintf(stderr, "Try 'spike --help' for more information.\n");
  exit(1);
}

static bool check_file_exists(const char *fileName)
{
  std::ifstream infile(fileName);
  return infile.good();
}

static std::ifstream::pos_type get_file_size(const char *filename)
{
  std::ifstream in(filename, std::ios::ate | std::ios::binary);
  return in.tellg();
}

static void read_file_bytes(const char *filename, size_t fileoff,
                            abstract_mem_t* mem, size_t memoff, size_t read_sz)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  in.seekg(fileoff, std::ios::beg);

  std::vector<char> read_buf(read_sz, 0);
  in.read(&read_buf[0], read_sz);
  mem->store(memoff, read_sz, reinterpret_cast<uint8_t*>(&read_buf[0]));
}

static bool sort_mem_region(const mem_cfg_t &a, const mem_cfg_t &b)
{
  if (a.get_base() == b.get_base())
    return (a.get_size() < b.get_size());
  else
    return (a.get_base() < b.get_base());
}

static bool check_mem_overlap(const mem_cfg_t& lhs, const mem_cfg_t& rhs)
{
  return std::max(lhs.get_base(), rhs.get_base()) <= std::min(lhs.get_inclusive_end(), rhs.get_inclusive_end());
}

static bool check_if_merge_covers_64bit_space(const mem_cfg_t& lhs, const mem_cfg_t& rhs)
{
  if (!check_mem_overlap(lhs, rhs))
    return false;

  auto start = std::min(lhs.get_base(), rhs.get_base());
  auto end = std::max(lhs.get_inclusive_end(), rhs.get_inclusive_end());
  return (start == 0ull) && (end == std::numeric_limits<uint64_t>::max());
}

static mem_cfg_t merge_mem_regions(const mem_cfg_t& lhs, const mem_cfg_t& rhs)
{
  assert(check_mem_overlap(lhs, rhs));
  const auto merged_base = std::min(lhs.get_base(), rhs.get_base());
  const auto merged_end_incl = std::max(lhs.get_inclusive_end(), rhs.get_inclusive_end());
  const auto merged_size = merged_end_incl - merged_base + 1;
  return mem_cfg_t(merged_base, merged_size);
}

static std::vector<mem_cfg_t> merge_overlapping_memory_regions(std::vector<mem_cfg_t> mems)
{
  if (mems.empty())
    return {};

  std::sort(mems.begin(), mems.end(), sort_mem_region);

  std::vector<mem_cfg_t> merged_mem;
  merged_mem.push_back(mems.front());

  for (auto it = std::next(mems.begin()); it != mems.end(); ++it) {
    const auto& mem_int = *it;
    if (!check_mem_overlap(merged_mem.back(), mem_int)) {
      merged_mem.push_back(mem_int);
      continue;
    }
    if (check_if_merge_covers_64bit_space(merged_mem.back(), mem_int)) {
      merged_mem.clear();
      merged_mem.push_back(mem_cfg_t(0ull, 0ull - PGSIZE));
      merged_mem.push_back(mem_cfg_t(0ull - PGSIZE, PGSIZE));
      break;
    }
    merged_mem.back() = merge_mem_regions(merged_mem.back(), mem_int);
  }

  return merged_mem;
}

static mem_cfg_t create_mem_region(unsigned long long base, unsigned long long size)
{
  auto base0 = base;
  auto size0 = size;
  size += base0 % PGSIZE;
  base -= base0 % PGSIZE;
  if (size % PGSIZE != 0)
    size += PGSIZE - size % PGSIZE;

  if (size != size0) {
    fprintf(stderr, "Warning: the memory at [0x%llX, 0x%llX] has been realigned\n"
                    "to the %ld KiB page size: [0x%llX, 0x%llX]\n",
            base0, base0 + size0 - 1, long(PGSIZE / 1024), base, base + size - 1);
  }

  if (!mem_cfg_t::check_if_supported(base, size)) {
    fprintf(stderr, "Unsupported memory region "
                    "{base = 0x%llX, size = 0x%llX} specified\n",
            base, size);
    exit(EXIT_FAILURE);
  }

  return mem_cfg_t(base, size);
}

static std::vector<mem_cfg_t> parse_mem_layout(const char* arg)
{
  std::vector<mem_cfg_t> res;

  char* p;
  auto mb = strtoull(arg, &p, 0);
  if (*p == 0) {
    reg_t size = reg_t(mb) << 20;
    if ((size >> 20) != mb)
      throw std::runtime_error("Memory size too large");
    res.push_back(create_mem_region(DRAM_BASE, size));
    return res;
  }

  while (true) {
    auto base = strtoull(arg, &p, 0);
    if (!*p || *p != ':')
      help();
    auto size = strtoull(p + 1, &p, 0);

    res.push_back(create_mem_region(base, size));

    if (!*p)
      break;
    if (*p != ',')
      help();
    arg = p + 1;
  }

  auto merged_mem = merge_overlapping_memory_regions(res);
  assert(!merged_mem.empty());
  return merged_mem;
}

static std::vector<std::pair<reg_t, abstract_mem_t*>> make_mems(const std::vector<mem_cfg_t>& layout)
{
  std::vector<std::pair<reg_t, abstract_mem_t*>> mems;
  mems.reserve(layout.size());
  for (const auto& cfg : layout)
    mems.push_back(std::make_pair(cfg.get_base(), new mem_t(cfg.get_size())));
  return mems;
}

static unsigned long atoul_safe(const char* s)
{
  char* e;
  auto res = strtoul(s, &e, 10);
  if (*e)
    help();
  return res;
}

static unsigned long atoul_nonzero_safe(const char* s)
{
  auto res = atoul_safe(s);
  if (!res)
    help();
  return res;
}

static void apply_memsize_option(spike_boot_options_t& options, const char* s)
{
  size_t memory_size_gib = 2;

  if (strcmp(s, "2") == 0) {
    s_platform_cfg.reinit(platform_cfg_t::MEMSIZE_2G);
  } else if (strcmp(s, "4") == 0) {
    s_platform_cfg.reinit(platform_cfg_t::MEMSIZE_4G);
    memory_size_gib = 4;
  } else if (strcmp(s, "8") == 0) {
    s_platform_cfg.reinit(platform_cfg_t::MEMSIZE_8G);
    memory_size_gib = 8;
  } else {
    printf("memsize args is wrong, set default memsize 2G\n");
    s_platform_cfg.reinit(platform_cfg_t::MEMSIZE_2G);
  }

  options.cfg.mem_layout = {mem_cfg_t(reg_t(DRAM_BASE), reg_t(memory_size_gib) << 30)};
  options.memory_option = true;
}

static std::vector<size_t> parse_hartids(const char* s)
{
  std::string const str(s);
  std::stringstream stream(str);
  std::vector<size_t> hartids;

  int n;
  while (stream >> n) {
    if (n < 0) {
      fprintf(stderr, "Negative hart ID %d is unsupported\n", n);
      exit(-1);
    }

    hartids.push_back(n);
    if (stream.peek() == ',')
      stream.ignore();
  }

  if (hartids.empty()) {
    fprintf(stderr, "No hart IDs specified\n");
    exit(-1);
  }

  std::sort(hartids.begin(), hartids.end());
  const auto dup = std::adjacent_find(hartids.begin(), hartids.end());
  if (dup != hartids.end()) {
    fprintf(stderr, "Duplicate hart ID %zu\n", *dup);
    exit(-1);
  }

  return hartids;
}

spike_boot_result_t::~spike_boot_result_t()
{
  for (auto& mem : mems)
    delete mem.second;
}

spike_boot_options_t spike_parse_argv_options(int argc, char** argv)
{
  s_platform_cfg.reinit(platform_cfg_t::MEMSIZE_2G);
  spike_boot_options_t options;

  auto const device_parser = [&options](const char* s) {
    const std::string device_args(s);
    std::vector<std::string> parsed_args;
    std::stringstream sstr(device_args);
    while (sstr.good()) {
      std::string substr;
      getline(sstr, substr, ',');
      parsed_args.push_back(substr);
    }
    if (parsed_args.empty())
      throw std::runtime_error("Plugin argument is empty.");

    const std::string name = parsed_args[0];
    if (name.empty())
      throw std::runtime_error("Plugin name is empty.");

    auto it = mmio_device_map().find(name);
    if (it == mmio_device_map().end())
      throw std::runtime_error("Plugin \"" + name + "\" not found in loaded extlibs.");

    parsed_args.erase(parsed_args.begin());
    options.plugin_device_factories.push_back(std::make_pair(it->second, parsed_args));
  };

  option_parser_t parser;
  parser.help(&suggest_help);
  parser.option('h', "help", 0, [&](const char UNUSED *s){help(0);});
  parser.option('d', 0, 0, [&](const char UNUSED *s){options.debug = true;});
  parser.option('g', 0, 0, [&](const char UNUSED *s){options.histogram = true;});
  parser.option('l', 0, 0, [&](const char UNUSED *s){options.log = true;});
#ifdef HAVE_BOOST_ASIO
  parser.option('s', 0, 0, [&](const char UNUSED *s){options.socket_enabled = true;});
#endif
  parser.option('p', 0, 1, [&](const char* s){options.nprocs = atoul_nonzero_safe(s);});
  parser.option('m', 0, 1, [&](const char* s){options.cfg.mem_layout = parse_mem_layout(s); options.memory_option = true;});
  parser.option(0, "halted", 0, [&](const char UNUSED *s){options.halted = true;});
  parser.option(0, "rbb-port", 1, [&](const char* s){options.use_rbb = true; options.rbb_port = atoul_safe(s);});
  parser.option(0, "pc", 1, [&](const char* s){options.cfg.start_pc = strtoull(s, 0, 0);});
  parser.option(0, "hartids", 1, [&](const char* s){
    options.cfg.hartids = parse_hartids(s);
    options.cfg.explicit_hartids = true;
  });
  parser.option(0, "ic", 1, [&](const char* s){options.ic = std::make_unique<icache_sim_t>(s);});
  parser.option(0, "dc", 1, [&](const char* s){options.dc = std::make_unique<dcache_sim_t>(s);});
  parser.option(0, "l2", 1, [&](const char* s){options.l2.reset(cache_sim_t::construct(s, "L2$"));});
  parser.option(0, "big-endian", 0, [&](const char UNUSED *s){options.cfg.endianness = endianness_big;});
  parser.option(0, "log-cache-miss", 0, [&](const char UNUSED *s){options.log_cache = true;});
  parser.option(0, "isa", 1, [&](const char* s){options.cfg.isa = s; options.explicit_isa = std::string(s);});
  parser.option(0, "pmpregions", 1, [&](const char* s){options.cfg.pmpregions = atoul_safe(s);});
  parser.option(0, "pmpgranularity", 1, [&](const char* s){options.cfg.pmpgranularity = atoul_safe(s);});
  parser.option(0, "priv", 1, [&](const char* s){options.cfg.priv = s;});
  parser.option(0, "device", 1, device_parser);
  parser.option(0, "dtb-discovery", 0, [&](const char UNUSED *s){options.dtb_discovery = true;});
  parser.option(0, "extension", 1, [&](const char* s){options.extensions.push_back(find_extension(s));});
  parser.option(0, "dump-dts", 0, [&](const char UNUSED *s){options.dump_dts = true;});
  parser.option(0, "disable-dtb", 0, [&](const char UNUSED *s){options.dtb_enabled = false;});
  parser.option(0, "dtb", 1, [&](const char* s){options.dtb_file = s;});
  parser.option(0, "kernel", 1, [&](const char* s){options.kernel = s;});
  parser.option(0, "initrd", 1, [&](const char* s){options.initrd = s;});
  parser.option(0, "bootargs", 1, [&](const char* s){options.cfg.bootargs = s;});
  parser.option(0, "real-time-clint", 0, [&](const char UNUSED *s){options.cfg.real_time_clint = true;});
  parser.option(0, "triggers", 1, [&](const char* s){options.cfg.trigger_count = atoul_safe(s);});
  parser.option(0, "extlib", 1, [&](const char* s){
    void *lib = dlopen(s, RTLD_NOW | RTLD_GLOBAL);
    if (lib == NULL) {
      fprintf(stderr, "Unable to load extlib '%s': %s\n", s, dlerror());
      exit(-1);
    }
  });
  parser.option(0, "dm-progsize", 1, [&](const char* s){options.dm_config.progbufsize = atoul_safe(s);});
  parser.option(0, "dm-datacount", 1, [&](const char* s){options.dm_config.datacount = atoul_safe(s);});
  parser.option(0, "dm-no-impebreak", 0, [&](const char UNUSED *s){options.dm_config.support_impebreak = false;});
  parser.option(0, "dm-sba", 1, [&](const char* s){options.dm_config.max_sba_data_width = atoul_safe(s);});
  parser.option(0, "dm-auth", 0, [&](const char UNUSED *s){options.dm_config.require_authentication = true;});
  parser.option(0, "dmi-rti", 1, [&](const char* s){options.dmi_rti = atoul_safe(s);});
  parser.option(0, "dm-abstract-rti", 1, [&](const char* s){options.dm_config.abstract_rti = atoul_safe(s);});
  parser.option(0, "dm-no-hasel", 0, [&](const char UNUSED *s){options.dm_config.support_hasel = false;});
  parser.option(0, "dm-no-abstract-csr", 0, [&](const char UNUSED *s){options.dm_config.support_abstract_csr_access = false;});
  parser.option(0, "dm-no-abstract-fpr", 0, [&](const char UNUSED *s){options.dm_config.support_abstract_fpr_access = false;});
  parser.option(0, "dm-no-halt-groups", 0, [&](const char UNUSED *s){options.dm_config.support_haltgroups = false;});
  parser.option(0, "dm-no-abstractauto", 0, [&](const char UNUSED *s){options.dm_config.support_abstractauto = false;});
  parser.option(0, "log-commits", 0, [&](const char UNUSED *s){options.log_commits = true;});
  parser.option(0, "log-commits-stant", 0, [&](const char UNUSED *s){options.log_commits_stant = true;});
  parser.option(0, "log", 1, [&](const char* s){options.log_path = s;});
  parser.option(0, "step", 1, [&](const char* s){options.step_interleave = atoul_safe(s);});
  parser.option(0, "disable_host", 0, [&](const char UNUSED *s){options.disable_host = true;});
  parser.option(0, "debug-cmd", 1, [&](const char* s){
    if ((options.cmd_file = fopen(s, "r")) == NULL) {
      fprintf(stderr, "Unable to open command file '%s'\n", s);
      exit(-1);
    }
  });
  parser.option(0, "blocksz", 1, [&](const char* s){
    options.blocksz = strtoull(s, 0, 0);
    const unsigned min_blocksz = 16;
    const unsigned max_blocksz = PGSIZE;
    if (options.blocksz < min_blocksz ||
        options.blocksz > max_blocksz ||
        ((options.blocksz & (options.blocksz - 1))) != 0) {
      fprintf(stderr, "--blocksz must be a power of 2 between %u and %u\n", min_blocksz, max_blocksz);
      exit(-1);
    }
    options.cfg.cache_blocksz = options.blocksz;
  });
  parser.option(0, "instructions", 1, [&](const char* s){
    options.instructions = strtoull(s, 0, 0);
  });
  parser.option(0, "save", 1, [&](const char* s){ options.checkpoint.snapshot_save_name = s; });
  parser.option(0, "load", 1, [&](const char* s){
    options.checkpoint.snapshot_load_name = s;
    options.cfg.start_pc = kCheckpointBootromBase;
  });
  parser.option(0, "compress", 0, [&](const char UNUSED *s){ options.checkpoint.snapshot_compress = true; });
  parser.option(0, "compress-zstd", 0, [&](const char UNUSED *s){ options.checkpoint.snapshot_compress_zstd = true; });
  parser.option(0, "memsize", 1, [&](const char* s){ apply_memsize_option(options, s); });

  auto argv1 = parser.parse(argv);
  options.htif_args = std::vector<std::string>(argv1, (const char*const*)argv + argc);

  if (options.checkpoint.snapshot_load_name) {
    if (!*argv1)
      options.htif_args.insert(options.htif_args.begin(), "none");
  } else if (!*argv1) {
    help();
  }

  return options;
}

void spike_prepare_boot_options(spike_boot_options_t& options)
{
  if (options.checkpoint.snapshot_compress &&
      options.checkpoint.snapshot_compress_zstd) {
    std::cerr << "--compress and --compress-zstd are mutually exclusive."
              << std::endl;
    exit(1);
  }

  if (options.cfg.explicit_hartids) {
    if (options.nprocs.overridden() && (options.nprocs() != options.cfg.nprocs())) {
      std::cerr << "Number of specified hartids ("
                << options.cfg.nprocs()
                << ") doesn't match specified number of processors ("
                << options.nprocs() << ").\n";
      exit(1);
    }
  } else {
    std::vector<size_t> default_hartids;
    default_hartids.reserve(options.nprocs());
    for (size_t i = 0; i < options.nprocs(); ++i)
      default_hartids.push_back(i);
    options.cfg.hartids = default_hartids;
  }

  if (options.dtb_discovery) {
    if (options.memory_option) {
      std::cerr << "--dtb-discovery option is not compatible with --memory/-m;." << std::endl;
      exit(1);
    }
    if (!options.plugin_device_factories.empty()) {
      std::cerr << "--dtb-discovery option is not compatible with --device option." << std::endl;
      exit(1);
    }
    if (options.dtb_file == nullptr) {
      std::cerr << "--dtb-discovery option required a dtb_file. Use --dtb option." << std::endl;
      exit(1);
    }
    if (!options.dtb_enabled) {
      std::cerr << "--dtb-discovery option is not compatible with --disable-dtb" << std::endl;
      exit(1);
    }
  }
}

spike_boot_result_t spike_bootstrap(
    spike_boot_options_t options,
    const std::function<void(sim_t*)>& on_sim_created)
{
  spike_prepare_boot_options(options);

  spike_boot_result_t result;
  result.cfg = std::make_unique<cfg_t>(options.cfg);
  result.ic = std::move(options.ic);
  result.dc = std::move(options.dc);
  result.l2 = std::move(options.l2);
  result.mems = make_mems(result.cfg->mem_layout);

  if (options.kernel && check_file_exists(options.kernel)) {
    const char* isa = result.cfg->isa;
    const reg_t kernel_size = get_file_size(options.kernel);
    const reg_t kernel_offset = (isa[2] == '6' && isa[3] == '4') ? 0x200000 : 0x400000;
    for (auto& mem : result.mems) {
      if (kernel_size && (kernel_offset + kernel_size) < mem.second->size()) {
        read_file_bytes(options.kernel, 0, mem.second, kernel_offset, kernel_size);
        break;
      }
    }
  }

  if (options.initrd && check_file_exists(options.initrd)) {
    size_t initrd_size = get_file_size(options.initrd);
    for (auto& mem : result.mems) {
      if (initrd_size && (initrd_size + 0x1000) < mem.second->size()) {
        reg_t initrd_end = mem.first + mem.second->size() - 0x1000;
        reg_t initrd_start = initrd_end - initrd_size;
        result.cfg->initrd_bounds = std::make_pair(initrd_start, initrd_end);
        read_file_bytes(options.initrd, 0, mem.second, initrd_start - mem.first, initrd_size);
        break;
      }
    }
  }

  spike_explicit_isa_scope_t explicit_isa_scope(options.explicit_isa);
  result.sim = std::make_unique<sim_t>(
      result.cfg.get(),
      options.halted,
      result.mems,
      options.plugin_device_factories,
      options.dtb_discovery,
      options.htif_args,
      options.dm_config,
      options.log_path,
      options.dtb_enabled,
      options.dtb_file,
      options.socket_enabled,
      options.cmd_file,
      options.instructions);

  if (auto* runtime = result.sim->runtime_context()) {
    runtime->set_checkpoint_controller(make_checkpoint_controller(options.checkpoint));
    if (auto* compat = runtime->model_compat()) {
      compat->set_preserve_lr_sc_reservation_across_interleave(true);
    }
  }

  const bool has_elf = !options.htif_args.empty() && options.htif_args.front() != "none";
  if (auto* runtime = result.sim->runtime_context()) {
    if (auto* controller = runtime->checkpoint_controller()) {
      controller->prepare_restore(*result.sim, has_elf);
    }
  }

  result.jtag_dtm = std::make_unique<jtag_dtm_t>(&result.sim->debug_module, options.dmi_rti);
  if (options.use_rbb) {
    result.remote_bitbang = std::make_unique<remote_bitbang_t>(options.rbb_port, result.jtag_dtm.get());
    result.sim->set_remote_bitbang(result.remote_bitbang.get());
  }

  if (on_sim_created)
    on_sim_created(result.sim.get());

  if (result.ic && result.l2)
    result.ic->set_miss_handler(result.l2.get());
  if (result.dc && result.l2)
    result.dc->set_miss_handler(result.l2.get());
  if (result.ic)
    result.ic->set_log(options.log_cache);
  if (result.dc)
    result.dc->set_log(options.log_cache);

  for (size_t i = 0; i < result.cfg->nprocs(); ++i) {
    if (result.ic)
      result.sim->get_core(i)->get_mmu()->register_memtracer(result.ic.get());
    if (result.dc)
      result.sim->get_core(i)->get_mmu()->register_memtracer(result.dc.get());
    for (auto& extension_factory : options.extensions)
      result.sim->get_core(i)->register_extension(extension_factory());
  }

  result.sim->set_debug(options.debug);
  result.sim->configure_log(options.log, options.log_commits);
  if (options.log_commits_stant) {
    if (auto* runtime = result.sim->runtime_context()) {
      if (auto* manager = runtime->log_manager()) {
        manager->set_enable_commit_log_stant(true);
      }
    }
  }
  if (options.disable_host) {
    if (auto* runtime = result.sim->runtime_context()) {
      if (auto* host_policy = runtime->host_policy()) {
        host_policy->set_disable_host(true);
      }
    }
  }
  if (options.step_interleave != 0) {
    result.sim->set_interleave(options.step_interleave);
  }
  result.sim->set_histogram(options.histogram);
  result.dump_dts_only = options.dump_dts;
  return result;
}

#include "SpikeSimObjSync.hpp"

#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {

std::vector<std::string> collect_args(int argc, char **argv) {
  std::vector<std::string> args;
  args.reserve(argc > 1 ? static_cast<size_t>(argc) : 1);
  args.emplace_back("spike");
  for (int i = 1; i < argc; ++i) {
    args.emplace_back(argv[i]);
  }
  return args;
}

std::string format_hex(uint64_t value) {
  std::ostringstream oss;
  oss << "0x" << std::hex << value;
  return oss.str();
}

void dump_xlate_flags(std::ostream &os, const XlateFlags &flags) {
  os << "{forced_virt=" << static_cast<int>(flags.forced_virt)
     << ",hlvx=" << static_cast<int>(flags.hlvx)
     << ",lr=" << static_cast<int>(flags.lr)
     << ",ss_access=" << static_cast<int>(flags.ss_access)
     << ",clean_inval=" << static_cast<int>(flags.clean_inval)
     << ",special_access=" << static_cast<int>(flags.is_special_access())
     << "}";
}

void dump_mmu_trace(std::ostream &os, const MmuTrace &trace) {
  os << "{paddr=" << format_hex(trace.paddr) << ",pte_paddr=[";
  for (size_t i = 0; i < 5; ++i) {
    if (i != 0) {
      os << ",";
    }
    os << format_hex(trace.pte_paddr[i]);
  }
  os << "],levels=" << std::dec << static_cast<int>(trace.levels)
     << ",xf_log=";
  dump_xlate_flags(os, trace.xf_log);
  os << "}";
}

void dump_trap_info(std::ostream &os, const TrapInfo &info) {
  os << "{cause=" << format_hex(info.cause)
     << ",tval=" << format_hex(info.tval)
     << ",tval2=" << format_hex(info.tval2)
     << ",in_trap=" << static_cast<int>(info.in_trap)
     << ",has_tval2=" << static_cast<int>(info.has_tval2)
     << "}";
}

std::string format_inst_trace(const InstTrace &inst) {
  std::ostringstream os;
  os << "{id=" << std::dec << inst.getId()
     << ",correct=" << static_cast<int>(inst.isCorrect())
     << ",first_miss=" << static_cast<int>(inst.isFirstMiss())
     << ",rvc=" << static_cast<int>(inst.isRvc())
     << ",load=" << static_cast<int>(inst.isLoad())
     << ",store=" << static_cast<int>(inst.isStore())
     << ",pc=" << format_hex(inst.getPc())
     << ",pc_paddr=" << format_hex(inst.getPcPAddr())
     << ",pc_paddr2=" << format_hex(inst.getPcPAddr2())
     << ",npc=" << format_hex(inst.getNPc())
     << ",bits=" << format_hex(inst.getBits())
     << ",inst_len=" << std::dec << inst.getInstLen()
     << ",in_trap=" << static_cast<int>(inst.inTrap())
     << ",in_wfi=" << static_cast<int>(inst.inWFI())
     << ",trap_info=";
  dump_trap_info(os, inst.GetTrapInfo());
  os << ",mmu_trace=";
  dump_mmu_trace(os, inst.m_mmuTrace);
  os << ",perfect=" << static_cast<int>(inst.perfect()) << "}";
  return os.str();
}

std::string format_step_trace(size_t step_count, bool is_done, uint64_t curr_pc,
                              const InstTrace &inst) {
  std::ostringstream os;
  os << "step=" << std::dec << step_count
     << " done=" << static_cast<int>(is_done)
     << " curr_pc=" << format_hex(curr_pc)
     << " inst=" << format_inst_trace(inst);
  return os.str();
}

bool starts_with(const std::string &value, const std::string &prefix) {
  return value.rfind(prefix, 0) == 0;
}

size_t parse_limit_value(const std::string &raw) {
  if (raw.empty()) {
    throw std::runtime_error("missing step limit value");
  }

  size_t parsed = 0;
  const auto value = std::stoull(raw, &parsed, 0);
  if (parsed != raw.size()) {
    throw std::runtime_error("invalid step limit value: " + raw);
  }
  return value;
}

std::optional<size_t> parse_step_limit(const std::vector<std::string> &args) {
  std::optional<size_t> instructions_limit;
  std::optional<size_t> maxinsns_limit;

  for (size_t i = 0; i < args.size(); ++i) {
    const auto &arg = args[i];
    if (starts_with(arg, "--instructions=")) {
      instructions_limit =
          parse_limit_value(arg.substr(sizeof("--instructions=") - 1));
      continue;
    }
    if (arg == "--instructions") {
      if (i + 1 >= args.size()) {
        throw std::runtime_error("missing value for --instructions");
      }
      instructions_limit = parse_limit_value(args[i + 1]);
      ++i;
      continue;
    }
    if (starts_with(arg, "--maxinsns=")) {
      maxinsns_limit = parse_limit_value(arg.substr(sizeof("--maxinsns=") - 1));
      continue;
    }
    if (arg == "--maxinsns") {
      if (i + 1 >= args.size()) {
        throw std::runtime_error("missing value for --maxinsns");
      }
      maxinsns_limit = parse_limit_value(args[i + 1]);
      ++i;
    }
  }

  return instructions_limit.has_value() ? instructions_limit : maxinsns_limit;
}

bool should_continue_step_trace(bool sim_done, size_t executed_steps,
                                const std::optional<size_t> &step_limit) {
  if (sim_done) {
    return false;
  }
  return !step_limit.has_value() || executed_steps < *step_limit;
}

void print_usage(const char *prog) {
  std::cerr << "Usage: " << prog
            << " <spike-arg> [<spike-arg> ...]" << std::endl;
}

void print_step_trace(size_t step_count, bool is_done, uint64_t curr_pc,
                      const InstTrace &inst) {
  std::cout << format_step_trace(step_count, is_done, curr_pc, inst)
            << std::endl;
}

int run(int argc, char **argv) {
  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  const auto args = collect_args(argc, argv);
  const auto step_limit = parse_step_limit(args);
  SpikeSimObjSync sim;
  bool started = false;
  size_t executed_steps = 0;

  try {
    sim.init(args);
    sim.start();
    started = true;

    while (should_continue_step_trace(sim.done(), executed_steps,
                                      step_limit)) {
      const auto step_count = sim.step(1);
      executed_steps += step_count;
      const auto curr_pc = sim.getCurrPc();
      auto fetched_inst = sim.fetchInstOnly(curr_pc);
      print_step_trace(step_count, sim.done(), curr_pc, fetched_inst);
    }

    sim.stop();
    return 0;
  } catch (const std::exception &ex) {
    std::cerr << "SpikeStepTraceTest error: " << ex.what() << std::endl;
    if (started) {
      sim.stop();
    }
    return 2;
  }
}

}  // namespace

int main(int argc, char **argv) { return run(argc, argv); }

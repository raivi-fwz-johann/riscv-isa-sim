#include "SpikeSimObjSync.hpp"

#include <cstddef>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <iostream>
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
  std::cout << "step=" << step_count
            << " done=" << static_cast<int>(is_done)
            << " curr_pc=" << format_hex(curr_pc)
            << " inst_pc=" << format_hex(inst.getPc())
            << " inst_npc=" << format_hex(inst.getNPc())
            << " bits=" << format_hex(inst.getBits())
            << " perfect=" << static_cast<int>(inst.perfect()) << std::endl;
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

#include "SpikeBase.hpp"

#include <iostream>

#include "SpikeProc.hpp"

void SpikeStat::print() const {
  std::cout << std::hex << "pc: 0x" << pc << std::endl;
  for (size_t i = 0; i < regs.size(); ++i) {
    std::cout << "reg " << i << std::hex << ": 0x" << regs[i] << std::endl;
  }
  for (size_t i = 0; i < vregs.size(); ++i) {
    std::cout << "vreg " << i << ": ";
    for (size_t j = 0; j < vregs[i].size(); ++j) {
      std::cout << "[" << j << "]:0x" << std::hex << vregs[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

std::unique_ptr<SpikeBase> SpikeBase::create(const std::string &type) {
  if (type == "process") {
    return std::make_unique<SpikeProc>();
  } else {
    return nullptr;
  }
}

void SpikeBase::init(const std::string &args_str) {
  std::vector<std::string> args;
  std::stringstream ss(args_str);
  std::string word;
  while (ss >> word) {
    args.push_back(word);
  }
  init(args);
}

const SpikeStat &SpikeBase::getStat(uint64_t proc) {
  updateStat(proc);
  return spike_stat_map_[proc];
}

void SpikeBase::updateStat(uint64_t proc) {
  if (spike_stat_map_.count(proc) == 0) {
    spike_stat_map_[proc] = SpikeStat();
  }
  spike_stat_map_[proc].pc = getPC(proc);

  // // regs
  // spike_stat_map_[proc].regs.resize(32);
  // for (size_t i = 0; i < spike_stat_map_[proc].regs.size(); ++i) {
  //   spike_stat_map_[proc].regs[i] = getReg(proc, i);
  // }

  // // vregs
  // spike_stat_map_[proc].vregs.resize(32);
  // for (size_t i = 0; i < spike_stat_map_[proc].vregs.size(); ++i) {
  //   getVReg(proc, i, spike_stat_map_[proc].vregs[i]);
  // }
}
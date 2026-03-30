#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <sstream>
#include "Memory.hpp"
#include <memory>
#include <unordered_map>

struct SpikeStat {
  uint64_t pc;
  std::vector<uint64_t> regs;
  std::vector<std::vector<uint64_t>> vregs;

  void print() const;
};

class SpikeBase {
public:
  static std::unique_ptr<SpikeBase> create(const std::string &type);

  virtual ~SpikeBase() = default;
  virtual void init(std::vector<std::string> &args) = 0;
  void init(const std::string &args_str);
  virtual void step(size_t n) = 0;
  const SpikeStat &getStat(uint64_t proc = 0);
  virtual bool isEnd() const = 0;

protected:
  virtual void updateStat(uint64_t proc);

  virtual uint64_t getPC(uint64_t proc) = 0;
  virtual uint64_t getReg(uint64_t proc, uint64_t reg) = 0;
  virtual void getVReg(uint64_t proc, uint64_t reg, std::vector<uint64_t> &output) = 0;

protected:
  std::unordered_map<uint64_t, SpikeStat> spike_stat_map_;
};
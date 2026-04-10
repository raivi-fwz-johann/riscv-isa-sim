#pragma once

#include "SpikeBase.hpp"
#include "ProcProxy.hpp"

class SpikeProc : public SpikeBase {
public:
  SpikeProc();
  ~SpikeProc();
  void init(std::vector<std::string> &args) override;
  void step(size_t n = 1) override;
  bool isEnd() const override;

private:
  void updateStat(uint64_t proc) override;
  uint64_t getPC(uint64_t proc) override;
  uint64_t getReg(uint64_t proc, uint64_t reg) override;
  void getVReg(uint64_t proc, uint64_t reg, std::vector<uint64_t> &output) override;

  void launchProc();
  void updatePC();

private:
  bool is_init_ = false;
  bool first_run_ = true;
  std::string program_path_;
  std::vector<std::string> args_;

  ProcProxy pproxy_;

  bool async_step_ = false;
};
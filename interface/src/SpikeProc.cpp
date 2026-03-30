#include "SpikeProc.hpp"

#include <stdexcept>
#include <iostream>

#include <string.h>
#include <stdio.h>

#include "patch/endflag.h"

static const char end_flag[] = COMMAND_ENDFLAG;

[[maybe_unused]] static const char *reg_name[32] = {
  "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2",
  "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9",
  "s10", "s11", "t3", "t4", "t5", "t6"
};

[[maybe_unused]] static const char *fpreg_name[32] = {
  "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7", "fs0", "fs1", 
  "fa0", "fa1", "fa2", "fa3", "fa4", "fa5", "fa6", "fa7", "fs2", "fs3", "fs4",
  "fs5", "fs6", "fs7", "fs8", "fs9", "fs10", "fs11", "ft8", "ft9", "ft10", "ft11"
};

[[maybe_unused]] static const char *vreg_name[32] = {
  "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9",
  "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20",
  "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"
};

[[maybe_unused]] static const char *vreg_elem[8] = {
  "[7]","[6]","[5]","[4]","[3]","[2]","[1]","[0]"
};

[[maybe_unused]] int get_vec_reg_num(char *vstr, char reg_idx) {
  int reg_num = -1;
  int reg_len = strlen(vstr);
  char *ptr;
  char reg_num_in_substr[64]; //max str len is 64, register str is less than 64 as usual

  memset(reg_num_in_substr, 0, reg_len);
  memcpy(reg_num_in_substr, vstr+1, reg_len-1); //skip 1st char "V"
  reg_num = strtoul(reg_num_in_substr, &ptr, 10); // change str to num @base10

  // register number is 1~31
  if (0 < reg_num && 31 >= reg_num)
  {
    return reg_num;
  }

  // reg_num maybe 0, for reg_num_in_substr is not begin with a 'number'
  if ( (0 == reg_num) && (memcmp(reg_num_in_substr, "0", 1) == 0) )
  {
    return 0;
  }

  return -1;
}

// class MsgParser {
// public:
//   void parse(const char *res, SpikeStat &out) {}
// };

SpikeProc::SpikeProc() {
  pproxy_.setCommEndFlag(CONNECT_ENDFLAG);
}

SpikeProc::~SpikeProc() {}

void SpikeProc::init(std::vector<std::string> &args) {
  args_.clear();
  args_ = {args[0], "-d"};
  if (args[1] == "-d") {
    args_.insert(args_.end(), args.begin() + 2, args.end());
  } else {
    args_.insert(args_.end(), args.begin() + 1, args.end());
  }

  std::cout << "Spike args: ";
  for (auto &arg : args_) {
    std::cout << arg << ' ';
  }
  std::cout << std::endl;

  launchProc();
  is_init_ = true;
}

void SpikeProc::step(size_t n) {
  if (n == 0 or n > 1) {
    std::runtime_error("SpikeProc only support step 1 for now");
  }
  if (!is_init_) {
    std::runtime_error("SpikeProc is not initialized");
  }
  if (first_run_) {
    pproxy_.readRes(PROC_BUF_SIZE, end_flag);
    first_run_ = false;
  }
  if (async_step_) {
    pproxy_.readRes(PROC_BUF_SIZE, end_flag);
    async_step_ = false;
  }

  pproxy_.execCmd("\n");
  async_step_ = true;
}

bool SpikeProc::isEnd() const {
  return pproxy_.isCommEnd();
}

void SpikeProc::updateStat(uint64_t proc) {
  if (first_run_) {
    pproxy_.readRes(PROC_BUF_SIZE, end_flag);
    first_run_ = false;
  }
  if (async_step_) {
    pproxy_.readRes(PROC_BUF_SIZE, end_flag);
    async_step_ = false;
  }
  SpikeBase::updateStat(proc);
}

uint64_t SpikeProc::getPC(uint64_t proc) {
  char cmd[8];
  sprintf(cmd, "pc %lu\n", proc);
  pproxy_.execCmdWithRes(cmd, PROC_BUF_SIZE, end_flag);
  char *buf = pproxy_.buf;
  return strtoull(&buf[0], NULL, 16);
}

uint64_t SpikeProc::getReg(uint64_t proc, uint64_t reg) {
  char cmd[16];
  sprintf(cmd, "reg %lu %lu\n", proc, reg);
  pproxy_.execCmdWithRes(cmd, PROC_BUF_SIZE, end_flag);
  char *buf = pproxy_.buf;
  return strtoull(&buf[0], NULL, 16);
}

void SpikeProc::getVReg(uint64_t proc, uint64_t reg, std::vector<uint64_t> &output) {
  char cmd[16];
  sprintf(cmd, "vreg %lu %lu\n", proc, reg);
  pproxy_.execCmdWithRes(cmd, PROC_BUF_SIZE, end_flag);
  char *buf = pproxy_.buf;

  output.resize(8);
  for (int i = 0, num = output.size() - 1; num >= 0; ++i) {
    if (buf[i] == '0' && buf[i + 1] == 'x') {
      output[num--] = strtoull(&buf[i], NULL, 16);
    }
  }
}

void SpikeProc::launchProc() {
  std::cout << "launching spike" << std::endl;
  pproxy_.launchProc(args_);
}

#pragma once

#include <vector>
#include <string>

#define PROC_BUF_SIZE (1024 * 16)

struct ProcProxy {
  ProcProxy();
  ~ProcProxy();
  void launchProc(const std::vector<std::string> &args);
  int execCmdWithRes(const char *cmd, int size, const char *end_flag);
  int execCmd(const char *cmd);
  int readRes(int size, const char *end_flag);
  bool exists() const;
  bool connecting() const;
  bool isCommEnd() const { return is_comm_end_; }
  void setCommEndFlag(const std::string &str) { comm_end_flag_ = str; }

public:
  char *buf = nullptr;

private:
  int pid_ = 0;
  int fd_ = 0;

  bool is_comm_end_ = false;
  std::string comm_end_flag_ = "***END***\n";
};
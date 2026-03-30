#include "ProcProxy.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#include <stdexcept>
#include <iostream>

bool isEqual(const char *s1, const char *s2, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (s1[i] != s2[i]) {
      return false;
    }
  }
  return true;
}

int is_valid_fd(int fd) {
  return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

ProcProxy::ProcProxy() {
  buf = new char[PROC_BUF_SIZE];
}

ProcProxy::~ProcProxy() {
  if (buf) {
    delete[] buf;
  }
  close(fd_);
  if (pid_ > 0) {
    int status = 0;
    if (kill(pid_, SIGKILL) == 0) {
      waitpid(pid_, &status, 0);
    }
    std::cout << "successfully kill process. pid: " << pid_ << std::endl;
  }
}

void ProcProxy::launchProc(const std::vector<std::string> &args) {
  int fd[2];
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd) != 0) {
    throw std::runtime_error("socketpair error!");
  }

  int pid = fork();
  if (pid < 0) {
    throw std::runtime_error("process fork error!");

  } else if (pid > 0) {
    std::cout << "fork process successfully, child pid: " << pid << std::endl;
    pid_ = pid;
    fd_ = fd[0];
    close(fd[1]);
    sleep(1);
    fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL) | O_NONBLOCK);
    
    if (!exists()) {
      std::cerr << "child process does not exist!" << std::endl;
    }
  } else {
    close(fd[0]);
    dup2(fd[1], STDERR_FILENO);

    std::vector<char *> argv;
    for (auto &arg : args) {
      argv.push_back((char *)arg.c_str());
    }
    argv.push_back(NULL);
    execvp(argv[0], argv.data());
    std::cout << "execvp program error!! errno: " << errno << std::endl;
    std::abort();
  }
}

int ProcProxy::execCmdWithRes(const char *cmd, int size, const char *end_flag) {
  execCmd(cmd);
  return readRes(size, end_flag);
}

int ProcProxy::execCmd(const char *cmd) {
  int ret = write(fd_, cmd, strlen(cmd));
  if (ret == -1) {
    throw std::runtime_error("ProcProxy exec cmd error!");
  }
  return ret;
}

int ProcProxy::readRes(int size, const char *end_flag) {
  int try_count = 0;
  int len = 0;
  int len_total = 0;
  int end_flag_len = end_flag == nullptr ? 0 : strlen(end_flag);
  int comm_end_flag_len = (int)comm_end_flag_.size();

  while (true) {
    len = read(fd_, buf + len_total, size);
    len_total += len >= 0 ? len : 0;
    if ((len < 0 && end_flag_len == 0) ||
        (end_flag_len > 0 && len_total >= end_flag_len && isEqual(end_flag, buf + len_total - end_flag_len, end_flag_len))) {
      break;
    }
    if (len_total >= comm_end_flag_len && isEqual(comm_end_flag_.c_str(), buf + len_total - comm_end_flag_len, comm_end_flag_len)) {
      is_comm_end_ = true;
      break;
    }
    usleep(10);
    if (++try_count >= 2000000) {
      buf[len_total] = '\0';
      std::cerr << "final read res: " << buf << std::endl;
      std::cerr << "fd valid: " << connecting() << std::endl;
      std::cerr << "process exists: " << exists() << std::endl;
      std::cerr << "read process result timeout" << std::endl;
      throw std::runtime_error("read process result timeout");
    }
  }
  buf[len_total] = '\0';
  // std::cout << "res: " << buf << std::endl;
  return len_total;
}

bool ProcProxy::exists() const {
  return (getpgid(pid_) >= 0);
}

bool ProcProxy::connecting() const {
  return is_valid_fd(fd_);
}

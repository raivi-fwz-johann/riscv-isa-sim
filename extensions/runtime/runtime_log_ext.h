#pragma once

class runtime_log_ext_t {
public:
  bool fast_log_commits_enabled() const { return fast_log_commits_; }
  void set_fast_log_commits(bool value) { fast_log_commits_ = value; }

  bool log_commits_stant_enabled() const { return log_commits_stant_; }
  void set_log_commits_stant(bool value) { log_commits_stant_ = value; }

  bool fast_log_mem_enabled() const { return fast_log_mem_; }
  void set_fast_log_mem(bool value) { fast_log_mem_ = value; }

  bool debug_info_enabled() const { return debug_info_; }
  void set_debug_info(bool value) { debug_info_ = value; }

  bool term_log_enabled() const { return term_log_; }
  void set_term_log(bool value) { term_log_ = value; }

private:
  bool fast_log_commits_ = false;
  bool log_commits_stant_ = false;
  bool fast_log_mem_ = false;
  bool debug_info_ = false;
  bool term_log_ = false;
};

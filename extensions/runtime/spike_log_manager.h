#pragma once

struct spike_log_config_t {
  bool enable_commit_log_stant = false;
  bool enable_fast_commit_log = false;
};

class spike_log_manager_t {
public:
  const spike_log_config_t& config() const { return config_; }
  void set_config(const spike_log_config_t& config) { config_ = config; }

  bool enable_commit_log_stant() const { return config_.enable_commit_log_stant; }
  void set_enable_commit_log_stant(bool value) { config_.enable_commit_log_stant = value; }

  bool enable_fast_commit_log() const { return config_.enable_fast_commit_log; }
  void set_enable_fast_commit_log(bool value) { config_.enable_fast_commit_log = value; }

private:
  spike_log_config_t config_;
};

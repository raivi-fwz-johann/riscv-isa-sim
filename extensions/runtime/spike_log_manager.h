#pragma once

// Per-core log configuration.  Controls which commit / mem log flavours
// are active for a given processor.
struct spike_log_config_t {
  // Standard (non-fast) commit log, always prints to file.
  bool enable_commit_log_stant = false;
  // Fast commit log path — trades file output for lower overhead.
  bool enable_fast_commit_log = false;
  // Fast memory-operation logging — records load/store metadata inline
  // so that it survives traps.
  bool enable_fast_mem_log = false;
  // Raw (unformatted) commit log output.
  bool enable_raw_commit_log = true;
};

// Owns the current log configuration and exposes typed accessors.
// Instances are typically held by spike_runtime_context_t.
class spike_log_manager_t {
public:
  // Returns the full config struct (read-only).
  // [return] const reference to current config
  const spike_log_config_t& config() const { return config_; }
  // Replace the entire config in one call.
  // [in] config  new config to copy
  void set_config(const spike_log_config_t& config) { config_ = config; }

  // Per-field getters / setters for convenience.
  // [return] current value
  bool enable_commit_log_stant() const { return config_.enable_commit_log_stant; }
  // [in] value  new flag value
  void set_enable_commit_log_stant(bool value) { config_.enable_commit_log_stant = value; }

  // [return] whether fast commit log is active
  bool enable_fast_commit_log() const { return config_.enable_fast_commit_log; }
  // [in] value  new flag value
  void set_enable_fast_commit_log(bool value) { config_.enable_fast_commit_log = value; }

  // [return] whether fast memory-operation logging is active
  bool enable_fast_mem_log() const { return config_.enable_fast_mem_log; }
  // [in] value  new flag value
  void set_enable_fast_mem_log(bool value) { config_.enable_fast_mem_log = value; }

  // [return] whether raw commit log output is enabled
  bool enable_raw_commit_log() const { return config_.enable_raw_commit_log; }
  // [in] value  new flag value
  void set_enable_raw_commit_log(bool value) { config_.enable_raw_commit_log = value; }

private:
  spike_log_config_t config_;
};

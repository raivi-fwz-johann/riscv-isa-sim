#include "runtime/spike_log_manager.h"

int main()
{
  spike_log_manager_t log_manager;

  if (log_manager.enable_fast_commit_log())
    return 1;
  if (log_manager.enable_commit_log_stant())
    return 2;
  if (!log_manager.enable_raw_commit_log())
    return 3;

  spike_log_config_t config;
  config.enable_fast_commit_log = true;
  config.enable_commit_log_stant = true;
  config.enable_raw_commit_log = false;
  log_manager.set_config(config);

  if (!log_manager.enable_fast_commit_log())
    return 4;
  if (!log_manager.enable_commit_log_stant())
    return 5;
  if (log_manager.enable_raw_commit_log())
    return 6;

  return 0;
}

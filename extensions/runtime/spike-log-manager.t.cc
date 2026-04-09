#include "runtime/spike_log_manager.h"

int main()
{
  spike_log_manager_t log_manager;

  if (log_manager.enable_fast_commit_log())
    return 1;
  if (log_manager.enable_commit_log_stant())
    return 2;

  spike_log_config_t config;
  config.enable_fast_commit_log = true;
  config.enable_commit_log_stant = true;
  log_manager.set_config(config);

  if (!log_manager.enable_fast_commit_log())
    return 3;
  if (!log_manager.enable_commit_log_stant())
    return 4;

  return 0;
}

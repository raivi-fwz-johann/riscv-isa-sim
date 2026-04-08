#include "runtime/runtime_log_ext.h"

int main()
{
  runtime_log_ext_t log_ext;

  if (log_ext.fast_log_commits_enabled())
    return 1;
  if (log_ext.log_commits_stant_enabled())
    return 2;
  if (log_ext.fast_log_mem_enabled())
    return 3;
  if (log_ext.debug_info_enabled())
    return 4;
  if (log_ext.term_log_enabled())
    return 5;

  log_ext.set_fast_log_commits(true);
  log_ext.set_log_commits_stant(true);
  log_ext.set_fast_log_mem(true);
  log_ext.set_debug_info(true);
  log_ext.set_term_log(true);

  if (!log_ext.fast_log_commits_enabled())
    return 6;
  if (!log_ext.log_commits_stant_enabled())
    return 7;
  if (!log_ext.fast_log_mem_enabled())
    return 8;
  if (!log_ext.debug_info_enabled())
    return 9;
  if (!log_ext.term_log_enabled())
    return 10;

  return 0;
}

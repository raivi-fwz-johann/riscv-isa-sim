#include "runtime/runtime_context.h"

int main()
{
  spike_runtime_context_t ctx;
  if (!ctx.host_policy()) {
    return 1;
  }
  if (ctx.host_policy()->disable_host()) {
    return 2;
  }
  ctx.host_policy()->set_disable_host(true);
  if (!ctx.host_policy()->disable_host()) {
    return 3;
  }
  return 0;
}

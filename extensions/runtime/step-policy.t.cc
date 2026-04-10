#include "runtime/runtime_context.h"

int main()
{
  spike_runtime_context_t ctx;
  if (!ctx.step_policy()) {
    return 1;
  }
  if (ctx.step_policy()->interleave() != 0) {
    return 2;
  }
  ctx.step_policy()->set_interleave(123);
  if (ctx.step_policy()->interleave() != 123) {
    return 3;
  }
  return 0;
}

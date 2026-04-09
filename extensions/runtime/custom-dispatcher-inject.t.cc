#include "runtime/runtime_context.h"
#include "runtime/spike_hook_dispatcher.h"

class test_dispatcher_t final : public spike_hook_dispatcher_t {
public:
  void on_decode(void*, reg_t, reg_t) override { decode_called = true; }
  bool on_commit() override { return true; }

  bool decode_called = false;
};

int main()
{
  auto custom = std::make_unique<test_dispatcher_t>();
  auto* custom_ptr = custom.get();

  spike_runtime_context_t ctx;
  ctx.set_hook_dispatcher(std::move(custom));

  if (ctx.hook_dispatcher() != custom_ptr)
    return 1;

  ctx.hook_dispatcher()->on_decode(nullptr, 0x1000, 0x1004);
  if (!custom_ptr->decode_called)
    return 2;

  if (!ctx.hook_dispatcher()->on_commit())
    return 3;

  return 0;
}

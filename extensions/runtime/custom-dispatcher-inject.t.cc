#include "runtime/runtime_context.h"
#include "runtime/spike_hook_dispatcher.h"

class test_dispatcher_t final : public spike_hook_dispatcher_t {
public:
  void on_decode(void*, reg_t, reg_t) override { decode_called = true; }
  bool on_commit() override { return true; }
  void on_device_uart_tx(abstract_device_t*, uint8_t byte) override {
    uart_called = true;
    last_uart_byte = byte;
  }
  void on_mmu_walk(const spike_mmu_walk_observe_t& event) override {
    mmu_called = true;
    last_mmu_paddr = event.paddr;
  }

  bool decode_called = false;
  bool uart_called = false;
  bool mmu_called = false;
  uint8_t last_uart_byte = 0;
  reg_t last_mmu_paddr = 0;
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

  ctx.hook_dispatcher()->on_device_uart_tx(nullptr, 0x5a);
  if (!custom_ptr->uart_called || custom_ptr->last_uart_byte != 0x5a)
    return 4;

  spike_mmu_walk_observe_t mmu_walk;
  mmu_walk.paddr = 0x4000;
  ctx.hook_dispatcher()->on_mmu_walk(mmu_walk);
  if (!custom_ptr->mmu_called || custom_ptr->last_mmu_paddr != 0x4000)
    return 5;

  return 0;
}

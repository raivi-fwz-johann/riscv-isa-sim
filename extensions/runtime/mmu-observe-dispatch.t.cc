#include "runtime/spike_hook_dispatcher.h"

class test_dispatcher_t final : public spike_hook_dispatcher_t {
public:
  void on_device_uart_tx(abstract_device_t*, uint8_t byte) override
  {
    uart_called = true;
    uart_byte = byte;
  }

  void on_mmu_walk(const spike_mmu_walk_observe_t& event) override
  {
    mmu_called = true;
    last_event = event;
  }

  bool uart_called = false;
  bool mmu_called = false;
  uint8_t uart_byte = 0;
  spike_mmu_walk_observe_t last_event{};
};

int main()
{
  test_dispatcher_t dispatcher;

  spike_mmu_walk_observe_t event{};
  event.hart_id = 3;
  event.vaddr = 0x1000;
  event.paddr = 0x2000;
  event.pte_paddr[0] = 0x10;
  event.pte_paddr[1] = 0x20;
  event.levels = 4;
  event.excp_cause = 0xf;
  event.xf_log.hlvx = true;

  dispatcher.on_mmu_walk(event);
  dispatcher.on_device_uart_tx(nullptr, 0x41);

  if (!dispatcher.mmu_called)
    return 1;
  if (dispatcher.last_event.hart_id != 3)
    return 2;
  if (dispatcher.last_event.pte_paddr[0] != 0x10 || dispatcher.last_event.pte_paddr[1] != 0x20)
    return 3;
  if (dispatcher.last_event.levels != 4)
    return 4;
  if (dispatcher.last_event.excp_cause != 0xf)
    return 5;
  if (!dispatcher.last_event.xf_log.hlvx)
    return 6;
  if (!dispatcher.uart_called || dispatcher.uart_byte != 0x41)
    return 7;

  return 0;
}

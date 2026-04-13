#include "runtime/spike_hook_dispatcher.h"
#include "trap.h"
#include <memory>

int main()
{
  spike_hook_dispatcher_t hook;

  trap_illegal_instruction trap(0);

  if (hook.on_commit() != false)
    return 1;

  if (!hook.should_continue())
    return 2;

  if (hook.on_next_pc(0x1004) != 0x1004)
    return 3;

  if (hook.on_trap(0, nullptr, 0x1000, trap) != 0)
    return 4;

  if (!hook.on_exit(0))
    return 5;

  auto store_real = std::make_shared<bool>(false);
  hook.on_pre_store(0x2000, 0x33, 8, store_real);
  if (*store_real)
    return 6;

  auto csr_real = std::make_shared<bool>(false);
  hook.on_pre_csr(0x305, 0x1, csr_real);
  if (*csr_real)
    return 7;

  hook.on_exec_observe(0, nullptr, 0x1000, 0x1004);
  hook.on_fake_step(1, 1);
  hook.on_device_uart_tx(nullptr, 0x41);

  spike_mmu_walk_observe_t mmu_walk;
  mmu_walk.hart_id = 0;
  mmu_walk.vaddr = 0x1000;
  mmu_walk.paddr = 0x2000;
  mmu_walk.levels = 3;
  hook.on_mmu_walk(mmu_walk);

  return 0;
}

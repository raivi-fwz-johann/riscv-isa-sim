#include "integration/legacy_hook_adapter.h"
#include "integration/legacy_hook_abi.h"

void legacy_hook_adapter_t::on_decode(void* fetch, reg_t pc, reg_t npc)
{
  decodeHook(fetch, pc, npc);
}

bool legacy_hook_adapter_t::on_commit()
{
  return commitHook();
}

reg_t legacy_hook_adapter_t::on_next_pc(reg_t candidate_npc)
{
  return getNpcHook(candidate_npc);
}

reg_t legacy_hook_adapter_t::on_trap(void* fetch, reg_t epc, trap_t& trap)
{
  return excptionHook(fetch, epc, trap);
}

bool legacy_hook_adapter_t::should_continue()
{
  return continueHook();
}

void legacy_hook_adapter_t::on_pre_store(reg_t addr, reg_t data, uint32_t len, std::shared_ptr<bool> real_store)
{
  catchDataBeforeWriteHook(addr, data, len, real_store);
}

bool legacy_hook_adapter_t::allow_csr_write(int which, reg_t value)
{
  return getCsrHook(which, value);
}

void legacy_hook_adapter_t::on_pre_csr(int which, reg_t value, std::shared_ptr<bool> real_store)
{
  catchDataBeforeCsrHook(which, value, real_store);
}

bool legacy_hook_adapter_t::on_exit(int code)
{
  return exitHook(code);
}

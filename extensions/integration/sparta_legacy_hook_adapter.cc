#include "integration/sparta_legacy_hook_adapter.h"
#include "integration/sparta_legacy_hook_abi.h"
#include <memory>

void sparta_legacy_hook_adapter_t::on_decode(const decode_event_t& event)
{
  decodeHook(event.fetch, event.pc, event.npc);
}

bool sparta_legacy_hook_adapter_t::on_commit(const commit_event_t& event)
{
  (void)event;
  return commitHook();
}

next_pc_decision_t sparta_legacy_hook_adapter_t::on_next_pc(const next_pc_event_t& event)
{
  next_pc_decision_t decision;
  const auto next_pc = getNpcHook(event.candidate_npc);
  decision.override_next_pc = next_pc != event.candidate_npc;
  decision.next_pc = next_pc;
  return decision;
}

trap_decision_t sparta_legacy_hook_adapter_t::on_trap(const trap_event_t& event)
{
  trap_decision_t decision;
  const auto code = excptionHook(event.fetch, event.epc, event.trap);
  if (code != 0) {
    decision.consume_trap = true;
    decision.return_code = code;
  }
  return decision;
}

bool sparta_legacy_hook_adapter_t::should_continue(const continue_event_t& event)
{
  (void)event;
  return continueHook();
}

void sparta_legacy_hook_adapter_t::on_pre_store(pre_store_event_t& event)
{
  auto real_store = std::make_shared<bool>(event.real_store);
  catchDataBeforeWriteHook(event.addr, event.data, event.len, real_store);
  event.real_store = *real_store;
}

bool sparta_legacy_hook_adapter_t::allow_csr_write(const csr_gate_event_t& event)
{
  return getCsrHook(event.which, event.value);
}

void sparta_legacy_hook_adapter_t::on_pre_csr(pre_csr_event_t& event)
{
  auto real_store = std::make_shared<bool>(event.real_store);
  catchDataBeforeCsrHook(event.which, event.value, real_store);
  event.real_store = *real_store;
}

exit_decision_t sparta_legacy_hook_adapter_t::on_exit(const exit_event_t& event)
{
  exit_decision_t decision;
  decision.allow_exit = exitHook(event.code);
  return decision;
}

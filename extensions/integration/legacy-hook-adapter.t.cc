#include "integration/sparta_legacy_hook_adapter.h"
#include "integration/sparta_legacy_hook_abi.h"
#include "trap.h"
#include <memory>

static int decode_calls = 0;
static int commit_calls = 0;
static int continue_calls = 0;
static int csr_gate_calls = 0;
static int pre_store_calls = 0;
static int pre_csr_calls = 0;
static int exit_calls = 0;

void decodeHook(void*, uint64_t, uint64_t) { decode_calls++; }
bool commitHook() { commit_calls++; return true; }
uint64_t getNpcHook(uint64_t npc) { return npc + 4; }
reg_t excptionHook(void*, uint64_t, trap_t&) { return 1; }
void catchDataBeforeWriteHook(uint64_t, uint64_t, uint32_t, std::shared_ptr<bool> real_store) {
  pre_store_calls++;
  *real_store = true;
}
void catchDataBeforeCsrHook(int, uint64_t, std::shared_ptr<bool> real_store) {
  pre_csr_calls++;
  *real_store = true;
}
bool getCsrHook(int, uint64_t) { csr_gate_calls++; return false; }
bool continueHook() { continue_calls++; return false; }
bool exitHook(int) { exit_calls++; return false; }

int main()
{
  sparta_legacy_hook_adapter_t hook;
  trap_illegal_instruction trap(0);

  hook.on_decode(decode_event_t{nullptr, nullptr, 0x1000, 0x1004});
  if (decode_calls != 1) return 1;

  if (!hook.on_commit(commit_event_t{nullptr, 0x1000})) return 2;
  if (commit_calls != 1) return 12;

  auto next = hook.on_next_pc(next_pc_event_t{nullptr, 0x1000, 0x1004});
  if (!next.override_next_pc || next.next_pc != 0x1008) return 3;

  auto trap_decision = hook.on_trap(trap_event_t{nullptr, 0x1000, trap});
  if (!trap_decision.consume_trap || trap_decision.return_code != 1) return 4;

  if (hook.should_continue(continue_event_t{nullptr, nullptr, hook_continue_site_t::run_loop})) return 5;
  if (continue_calls != 1) return 6;

  pre_store_event_t store_ev{0x2000, 0x55, 8, false};
  hook.on_pre_store(store_ev);
  if (!store_ev.real_store || pre_store_calls != 1) return 7;

  if (hook.allow_csr_write(csr_gate_event_t{0x305, 0x1})) return 8;
  if (csr_gate_calls != 1) return 9;

  pre_csr_event_t csr_ev{0x305, 0x1, false};
  hook.on_pre_csr(csr_ev);
  if (!csr_ev.real_store || pre_csr_calls != 1) return 10;

  auto exit_decision = hook.on_exit(exit_event_t{0});
  if (exit_decision.allow_exit || exit_calls != 1) return 11;

  hook.on_exec_observe(exec_observe_event_t{nullptr, nullptr, 0x1000, 0x1004});
  hook.on_fake_step(fake_step_event_t{nullptr, 0, 0, 0x1000});
  return 0;
}

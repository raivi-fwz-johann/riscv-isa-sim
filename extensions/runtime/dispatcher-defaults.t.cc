#include "runtime/hook_events.h"
#include "runtime/null_hook_dispatcher.h"
#include "trap.h"

int main()
{
  null_hook_dispatcher_t hook;

  trap_illegal_instruction trap(0);

  if (hook.on_commit(commit_event_t{nullptr, 0x1000}) != false)
    return 1;

  if (!hook.should_continue(continue_event_t{nullptr, nullptr, hook_continue_site_t::run_loop}))
    return 2;

  next_pc_decision_t next = hook.on_next_pc(next_pc_event_t{nullptr, 0x1000, 0x1004});
  if (next.override_next_pc)
    return 3;

  trap_decision_t trap_decision = hook.on_trap(trap_event_t{nullptr, 0x1000, trap});
  if (trap_decision.consume_trap)
    return 4;

  exit_decision_t exit_decision = hook.on_exit(exit_event_t{0});
  if (!exit_decision.allow_exit)
    return 5;

  pre_store_event_t store_ev{0x2000, 0x33, 8, false};
  hook.on_pre_store(store_ev);
  if (store_ev.real_store)
    return 6;

  pre_csr_event_t csr_ev{0x305, 0x1, false};
  hook.on_pre_csr(csr_ev);
  if (csr_ev.real_store)
    return 7;

  hook.on_exec_observe(exec_observe_event_t{nullptr, nullptr, 0x1000, 0x1004});
  hook.on_fake_step(fake_step_event_t{nullptr, 1, 1, 0x1000});

  return 0;
}

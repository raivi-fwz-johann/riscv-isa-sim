#include "integration/legacy_hook_adapter.h"
#include "integration/legacy_hook_abi.h"
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
  legacy_hook_adapter_t hook;
  trap_illegal_instruction trap(0);

  hook.on_decode(nullptr, 0x1000, 0x1004);
  if (decode_calls != 1) return 1;

  if (!hook.on_commit()) return 2;
  if (commit_calls != 1) return 12;

  if (hook.on_next_pc(0x1004) != 0x1008) return 3;

  if (hook.on_trap(nullptr, 0x1000, trap) != 1) return 4;

  if (hook.should_continue()) return 5;
  if (continue_calls != 1) return 6;

  auto store_real = std::make_shared<bool>(false);
  hook.on_pre_store(0x2000, 0x55, 8, store_real);
  if (!*store_real || pre_store_calls != 1) return 7;

  if (hook.allow_csr_write(0x305, 0x1)) return 8;
  if (csr_gate_calls != 1) return 9;

  auto csr_real = std::make_shared<bool>(false);
  hook.on_pre_csr(0x305, 0x1, csr_real);
  if (!*csr_real || pre_csr_calls != 1) return 10;

  if (hook.on_exit(0) || exit_calls != 1) return 11;

  hook.on_exec_observe(nullptr, 0x1000, 0x1004);
  hook.on_fake_step(0, 0);
  return 0;
}

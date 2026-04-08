#include "integration/sparta_legacy_hook_abi.h"

__attribute__((weak)) void decodeHook(void*, uint64_t, uint64_t) {}
__attribute__((weak)) bool commitHook() { return false; }
__attribute__((weak)) uint64_t getNpcHook(uint64_t npc) { return npc; }
__attribute__((weak)) reg_t excptionHook(void*, uint64_t, trap_t&) { return 0; }
__attribute__((weak)) void catchDataBeforeWriteHook(uint64_t, uint64_t, uint32_t, std::shared_ptr<bool>) {}
__attribute__((weak)) void catchDataBeforeCsrHook(int, uint64_t, std::shared_ptr<bool>) {}
__attribute__((weak)) bool getCsrHook(int, uint64_t) { return true; }
__attribute__((weak)) bool continueHook() { return true; }
__attribute__((weak)) bool exitHook(int) { return true; }

#pragma once

#include "trap.h"
#include <cstdint>
#include <memory>

__attribute__((weak)) void decodeHook(void* fetch, uint64_t pc, uint64_t npc);
__attribute__((weak)) bool commitHook();
__attribute__((weak)) uint64_t getNpcHook(uint64_t npc);
__attribute__((weak)) reg_t excptionHook(void* fetch, uint64_t pc, trap_t& trap);
__attribute__((weak)) void catchDataBeforeWriteHook(uint64_t addr, uint64_t data, uint32_t len, std::shared_ptr<bool> real_store);
__attribute__((weak)) void catchDataBeforeCsrHook(int which, uint64_t value, std::shared_ptr<bool> real_store);
__attribute__((weak)) bool getCsrHook(int which, uint64_t value);
__attribute__((weak)) bool continueHook();
__attribute__((weak)) bool exitHook(int code);

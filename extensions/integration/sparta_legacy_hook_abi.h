#pragma once

#include "trap.h"
#include <cstdint>
#include <memory>

extern void decodeHook(void* fetch, uint64_t pc, uint64_t npc) __attribute__((weak));
extern bool commitHook() __attribute__((weak));
extern uint64_t getNpcHook(uint64_t npc) __attribute__((weak));
extern reg_t excptionHook(void* fetch, uint64_t pc, trap_t& trap) __attribute__((weak));
extern void catchDataBeforeWriteHook(uint64_t addr, uint64_t data, uint32_t len, std::shared_ptr<bool> real_store) __attribute__((weak));
extern void catchDataBeforeCsrHook(int which, uint64_t value, std::shared_ptr<bool> real_store) __attribute__((weak));
extern bool getCsrHook(int which, uint64_t value) __attribute__((weak));
extern bool continueHook() __attribute__((weak));
extern bool exitHook(int code) __attribute__((weak));

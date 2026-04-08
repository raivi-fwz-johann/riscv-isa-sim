#pragma once

#include "trap.h"
#include <cstdint>
#include <memory>

void decodeHook(void* fetch, uint64_t pc, uint64_t npc);
bool commitHook();
uint64_t getNpcHook(uint64_t npc);
reg_t excptionHook(void* fetch, uint64_t pc, trap_t& trap);
void catchDataBeforeWriteHook(uint64_t addr, uint64_t data, uint32_t len, std::shared_ptr<bool> real_store);
void catchDataBeforeCsrHook(int which, uint64_t value, std::shared_ptr<bool> real_store);
bool getCsrHook(int which, uint64_t value);
bool continueHook();
bool exitHook(int code);

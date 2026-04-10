#pragma once

#include "functrace/InstTrace.hpp"

struct RawSpikeObservedInsn {
  bool valid = false;
  bool in_trap = false;
  bool has_tval2 = false;
  uint64_t pc = ERROR_PC_ADDR;
  uint64_t npc = ERROR_PC_ADDR;
  uint64_t bits = 0;
  uint64_t paddr = ERROR_PC_ADDR;
  uint64_t paddr2 = ERROR_PC_ADDR;
  uint64_t cause = 0;
  uint64_t tval = 0;
  uint64_t tval2 = 0;

  void reset()
  {
    valid = false;
    in_trap = false;
    has_tval2 = false;
    pc = ERROR_PC_ADDR;
    npc = ERROR_PC_ADDR;
    bits = 0;
    paddr = ERROR_PC_ADDR;
    paddr2 = ERROR_PC_ADDR;
    cause = 0;
    tval = 0;
    tval2 = 0;
  }
};

struct RawSpikeShadowState {
  RawSpikeObservedInsn observed;
  MmuTrace mmu_trace{};
};

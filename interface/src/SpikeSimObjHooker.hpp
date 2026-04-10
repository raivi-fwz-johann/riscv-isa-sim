/**
 * @file SpikeSimObjHooker.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "Memory.hpp"
#include "runtime/spike_hook_dispatcher.h"

class RawSpike;
class SpikeSimObjHooker : public spike_hook_dispatcher_t {
public:
  SpikeSimObjHooker(RawSpike *Ptr);

  bool on_exit(int code) override;
  void on_exec_observe(insn_fetch_t* in, reg_t pc, reg_t npc) override;
  reg_t on_trap(void *in, reg_t pc, trap_t &t) override;

private:
  RawSpike *m_SimObj = nullptr;
};

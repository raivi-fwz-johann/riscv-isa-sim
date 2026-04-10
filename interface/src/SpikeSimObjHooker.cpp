/**
 * @file SpikeSimObjHooker.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "SpikeSimObjHooker.hpp"

#include "trap.h"
#include "mmu.h"
#include "sim.h"
#include "decode_macros.h"

#include "RawSpike.hpp"

SpikeSimObjHooker::SpikeSimObjHooker(RawSpike *Ptr) : m_SimObj(Ptr) {}

bool SpikeSimObjHooker::on_exit(int code) {
  (void)code;
  m_SimObj->stop();
  return false;
}

void SpikeSimObjHooker::on_exec_observe(insn_fetch_t* in, reg_t pc, reg_t npc) {
  auto& observed = m_SimObj->m_Shadow.at(m_SimObj->m_CurrCId).observed;
  observed.valid = true;
  observed.in_trap = false;
  observed.pc = pc;
  observed.bits = in ? in->insn.bits() : 0;
  observed.paddr = in ? in->pc_ppn : ERROR_PC_ADDR;
  observed.paddr2 = ERROR_PC_ADDR;
  if (npc != 0 && npc != PC_SERIALIZE_BEFORE) {
    observed.npc = npc;
  }
}

reg_t SpikeSimObjHooker::on_trap(void *in, reg_t pc, trap_t &t) {
  auto& observed = m_SimObj->m_Shadow.at(m_SimObj->m_CurrCId).observed;
  observed.valid = true;
  observed.in_trap = true;
  observed.pc = pc;
  observed.bits = in ? static_cast<insn_fetch_t*>(in)->insn.bits() : 0;
  observed.paddr = in ? static_cast<insn_fetch_t*>(in)->pc_ppn : ERROR_PC_ADDR;
  observed.paddr2 = ERROR_PC_ADDR;
  observed.cause = t.cause();
  observed.tval = t.get_tval();
  observed.has_tval2 = t.has_tval2();
  observed.tval2 = observed.has_tval2 ? t.get_tval2() : 0;
  return 0;
}

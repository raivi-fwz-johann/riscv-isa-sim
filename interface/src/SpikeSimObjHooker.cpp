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
#include "SpikeRoiState.hpp"
#include "SpikeStateExporter.hpp"

SpikeSimObjHooker::SpikeSimObjHooker(RawSpike *Ptr) : m_SimObj(Ptr) {}

bool SpikeSimObjHooker::on_exit(int code) {
  (void)code;
  m_SimObj->stop();
  return false;
}

void SpikeSimObjHooker::on_exec_observe(uint32_t hart_id, insn_fetch_t* in, reg_t pc, reg_t npc) {
  if (m_SimObj->m_StateExporter) {
    m_SimObj->m_StateExporter->observe_exec(hart_id, in, pc, npc);
  }
}

reg_t SpikeSimObjHooker::on_trap(uint32_t hart_id, void *in, reg_t pc, trap_t &t) {
  if (m_SimObj->m_StateExporter) {
    return m_SimObj->m_StateExporter->observe_trap(hart_id, in, pc, t);
  }
  return 0;
}

void SpikeSimObjHooker::on_device_uart_tx(abstract_device_t* device, uint8_t byte) {
  if (m_SimObj->m_RoiState) {
    m_SimObj->m_RoiState->on_device_uart_tx(device, byte);
  }
}

void SpikeSimObjHooker::on_mmu_walk(const spike_mmu_walk_observe_t& event) {
  if (m_SimObj->m_StateExporter) {
    m_SimObj->m_StateExporter->observe_mmu_walk(event);
  }
}

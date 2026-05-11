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

#include <cstdlib>
#include <iostream>

#include "trap.h"
#include "mmu.h"
#include "sim.h"
#include "decode_macros.h"

#include "RawSpike.hpp"
#include "SpikeRoiState.hpp"
#include "SpikeStateExporter.hpp"

namespace {

bool snapshot_debug_enabled()
{
  return std::getenv("MODEL_STATE_SNAPSHOT_DEBUG") != nullptr;
}

void log_snapshot_hook_event(
    const char* tag,
    uint32_t hart_id,
    uint64_t pc,
    uint64_t npc,
    uint64_t bits,
    uint64_t paddr,
    uint64_t cause = 0,
    uint64_t tval = 0)
{
  if (!snapshot_debug_enabled()) {
    return;
  }
  std::cout << "modelDebug " << tag
            << " core=" << hart_id
            << std::hex
            << " pc=0x" << pc
            << " npc=0x" << npc
            << " bits=0x" << bits
            << " paddr=0x" << paddr
            << " cause=0x" << cause
            << " tval=0x" << tval
            << std::dec
            << std::endl;
}

}  // namespace

SpikeSimObjHooker::SpikeSimObjHooker(RawSpike *Ptr) : m_SimObj(Ptr) {}

bool SpikeSimObjHooker::on_exit(int code) {
  (void)code;
  m_SimObj->stop();
  return false;
}

void SpikeSimObjHooker::on_pre_exec(uint32_t hart_id, insn_fetch_t* in, reg_t pc) {
  if (m_SimObj->m_StateExporter) {
    m_SimObj->m_StateExporter->observe_pre_exec(hart_id, in, pc);
  }
}

void SpikeSimObjHooker::on_exec_observe(uint32_t hart_id, insn_fetch_t* in, reg_t pc, reg_t npc) {
  log_snapshot_hook_event(
      "snapshotObserveExec",
      hart_id,
      pc,
      npc,
      in ? in->insn.bits() : 0,
      in ? in->pc_ppn : ERROR_PC_ADDR);
  if (m_SimObj->m_StateExporter) {
    m_SimObj->m_StateExporter->observe_exec(hart_id, in, pc, npc);
  }
}

reg_t SpikeSimObjHooker::on_trap(uint32_t hart_id, void *in, reg_t pc, trap_t &t) {
  auto* fetch = static_cast<insn_fetch_t*>(in);
  log_snapshot_hook_event(
      "snapshotObserveTrap",
      hart_id,
      pc,
      ERROR_PC_ADDR,
      fetch ? fetch->insn.bits() : 0,
      fetch ? fetch->pc_ppn : ERROR_PC_ADDR,
      t.cause(),
      t.get_tval());
  if (m_SimObj->m_StateExporter) {
    return m_SimObj->m_StateExporter->observe_trap(hart_id, in, pc, t);
  }
  return 0;
}

void SpikeSimObjHooker::on_trap_target(uint32_t hart_id, reg_t epc, reg_t npc) {
  log_snapshot_hook_event(
      "snapshotObserveTrapTarget",
      hart_id,
      epc,
      npc,
      0,
      ERROR_PC_ADDR);
  (void)epc;
  if (m_SimObj->m_StateExporter) {
    m_SimObj->m_StateExporter->observe_trap_target(hart_id, npc);
  }
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

void SpikeSimObjHooker::on_fetch_observe(uint32_t hart_id, reg_t vaddr, reg_t paddr, reg_t paddr2, insn_bits_t bits, unsigned length) {
  (void)paddr2;
  (void)length;
  if (m_SimObj->m_StateExporter) {
    m_SimObj->m_StateExporter->observe_fetch(hart_id, vaddr, paddr, paddr2, bits, length);
  }
}

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
  void on_exec_observe(uint32_t hart_id, insn_fetch_t* in, reg_t pc, reg_t npc) override;
  void on_pre_exec(uint32_t hart_id, insn_fetch_t* in, reg_t pc) override;
  reg_t on_trap(uint32_t hart_id, void *in, reg_t pc, trap_t &t) override;
  void on_trap_target(uint32_t hart_id, reg_t epc, reg_t npc) override;
  void on_device_uart_tx(abstract_device_t* device, uint8_t byte) override;
  void on_mmu_walk(const spike_mmu_walk_observe_t& event) override;
  void on_fetch_observe(uint32_t hart_id, reg_t vaddr, reg_t paddr, reg_t paddr2, insn_bits_t bits, unsigned length) override;
  void on_mem_log(uint32_t hart_id, reg_t addr, uint64_t val, uint8_t size, reg_t paddr, bool is_store) override;
  void on_commit_log_reset(uint32_t hart_id) override;

private:
  RawSpike *m_SimObj = nullptr;
};

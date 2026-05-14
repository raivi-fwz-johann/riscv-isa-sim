#pragma once

#include "decode.h"
#include <cstddef>
#include <cstdint>
#include <memory>

struct insn_fetch_t;
class trap_t;
class abstract_device_t;

struct spike_mmu_xlate_flags_t {
  bool forced_virt : 1 {false};
  bool hlvx : 1 {false};
  bool lr : 1 {false};
  bool ss_access : 1 {false};
  bool clean_inval : 1 {false};
  bool enable_misalign : 1 {false};
};

struct spike_mmu_walk_observe_t {
  uint32_t hart_id = 0;
  reg_t vaddr = 0;
  reg_t paddr = 0;
  reg_t pte_paddr[5] = {0};
  int8_t levels = -1;
  reg_t excp_cause = 0;
  spike_mmu_xlate_flags_t xf_log;
};

class spike_hook_dispatcher_t {
public:
  virtual ~spike_hook_dispatcher_t() = default;

  // -- instruction lifecycle -------------------------------------------------
  virtual void on_decode(void* instr, reg_t pc, reg_t npc) {}
  virtual bool on_commit() { return false; }
  virtual reg_t on_next_pc(reg_t candidate_npc) { return candidate_npc; }

  // -- trap / interrupt ------------------------------------------------------
  virtual reg_t on_trap(uint32_t hart_id, void* fetch, reg_t epc, trap_t& t) { return 0; }
  virtual void on_trap_target(uint32_t hart_id, reg_t epc, reg_t npc) {}

  // -- execution flow control ------------------------------------------------
  virtual bool should_continue() { return true; }
  virtual void on_fake_step(size_t instret, size_t prev_instret) {}

  // -- memory access ---------------------------------------------------------
  virtual void on_pre_store(reg_t addr, reg_t val, uint32_t size, std::shared_ptr<bool> real_store) {}
  virtual void on_mem_log(uint32_t hart_id, reg_t addr, uint64_t val, uint8_t size, reg_t paddr, bool is_store) {}
  virtual void on_commit_log_reset(uint32_t hart_id) {}

  // -- CSR access ------------------------------------------------------------
  virtual bool allow_csr_write(int csr, reg_t val) { return true; }
  virtual void on_pre_csr(int csr, reg_t val, std::shared_ptr<bool> allow) {}

  // -- exit ------------------------------------------------------------------
  virtual bool on_exit(int code) { return true; }

  // -- observation hooks -----------------------------------------------------
  virtual void on_exec_observe(uint32_t hart_id, insn_fetch_t* fetch, reg_t pc, reg_t npc) {}
  virtual void on_pre_exec(uint32_t hart_id, insn_fetch_t* fetch, reg_t pc) {}
  virtual void on_fetch_observe(uint32_t hart_id, reg_t vaddr, reg_t paddr, reg_t paddr2, insn_bits_t bits, unsigned length) {}

  // -- device / MMU ----------------------------------------------------------
  virtual void on_device_uart_tx(abstract_device_t* device, uint8_t byte) {}
  virtual void on_mmu_walk(const spike_mmu_walk_observe_t& event) {}
};

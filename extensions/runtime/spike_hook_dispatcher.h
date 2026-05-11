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

  virtual void on_decode(void*, reg_t, reg_t) {}
  virtual bool on_commit() { return false; }
  virtual reg_t on_next_pc(reg_t candidate_npc) { return candidate_npc; }
  virtual reg_t on_trap(uint32_t, void*, reg_t, trap_t&) { return 0; }
  virtual bool should_continue() { return true; }
  virtual void on_pre_store(reg_t, reg_t, uint32_t, std::shared_ptr<bool>) {}
  virtual bool allow_csr_write(int, reg_t) { return true; }
  virtual void on_pre_csr(int, reg_t, std::shared_ptr<bool>) {}
  virtual bool on_exit(int) { return true; }
  virtual void on_exec_observe(uint32_t, insn_fetch_t*, reg_t, reg_t) {}
  virtual void on_pre_exec(uint32_t, insn_fetch_t*, reg_t) {}
  virtual void on_trap_target(uint32_t, reg_t, reg_t) {}
  virtual void on_fake_step(size_t, size_t) {}
  virtual void on_device_uart_tx(abstract_device_t*, uint8_t) {}
  virtual void on_mmu_walk(const spike_mmu_walk_observe_t&) {}
  virtual void on_fetch_observe(uint32_t, reg_t, reg_t, reg_t, insn_bits_t, unsigned) {}
};

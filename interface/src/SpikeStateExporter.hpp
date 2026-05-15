#pragma once

#include "functrace/InstTrace.hpp"
#include "runtime/spike_hook_dispatcher.h"

#include <vector>

struct insn_fetch_t;
class trap_t;

struct spike_observed_insn_t {
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

  void reset();
};

struct spike_state_snapshot_t {
  spike_observed_insn_t observed;  // written by all observe hooks, last writer wins
  bool in_trap{false};             // written by observe_trap
  bool has_tval2{false};
  uint64_t epc{ERROR_PC_ADDR};     // trap pc, written by observe_trap
  uint64_t trap_npc{ERROR_PC_ADDR};// trap npc, written by observe_trap_target
  uint64_t cause{0};
  uint64_t tval{0};
  uint64_t tval2{0};
  MmuTrace mmu_trace{};
};

class spike_state_exporter_t {
public:
  void reset(size_t nprocs);

  void observe_exec(size_t hart_id, insn_fetch_t* in, reg_t pc, reg_t npc);
  void observe_pre_exec(size_t hart_id, insn_fetch_t* in, reg_t pc);
  reg_t observe_trap(size_t hart_id, void* in, reg_t pc, trap_t& t);
  void observe_trap_target(size_t hart_id, reg_t npc);
  void observe_mmu_walk(const spike_mmu_walk_observe_t& event);
  void observe_fetch(size_t hart_id, reg_t vaddr, reg_t paddr, reg_t paddr2, insn_bits_t bits, unsigned length);

  void set_mmu_paddr(size_t hart_id, uint64_t paddr);
  const spike_state_snapshot_t* snapshot(size_t hart_id) const;
  MmuTrace get_mmu_trace(size_t hart_id) const;
  bool in_trap(size_t hart_id) const;
  void reset_observed(size_t hart_id);

  struct MemLogItem {
    reg_t addr = 0;
    uint64_t val = 0;
    uint8_t size = 0;
    reg_t paddr = 0;
  };

  void add_mem_log(size_t hart_id, reg_t addr, uint64_t val, uint8_t size, reg_t paddr, bool is_store);
  void clear_mem_log(size_t hart_id);
  const std::vector<MemLogItem>& mem_loads(size_t hart_id) const;
  const std::vector<MemLogItem>& mem_stores(size_t hart_id) const;

private:
  struct core_state_t {
    spike_state_snapshot_t snapshot;
    MmuTrace pending_mmu_trace{};
    bool has_pending_mmu_trace = false;
    std::vector<MemLogItem> mem_loads;
    std::vector<MemLogItem> mem_stores;
  };

  core_state_t* core_state(size_t hart_id);
  const core_state_t* core_state(size_t hart_id) const;
  static MmuTrace to_mmu_trace(const spike_mmu_walk_observe_t& event);

  std::vector<core_state_t> cores_;
};

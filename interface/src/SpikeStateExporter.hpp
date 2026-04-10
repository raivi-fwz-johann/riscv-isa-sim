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
  spike_observed_insn_t observed;
  MmuTrace mmu_trace{};
};

class spike_state_exporter_t {
public:
  void reset(size_t nprocs);

  void observe_exec(size_t hart_id, insn_fetch_t* in, reg_t pc, reg_t npc);
  reg_t observe_trap(size_t hart_id, void* in, reg_t pc, trap_t& t);
  void observe_mmu_walk(const spike_mmu_walk_observe_t& event);

  void set_mmu_paddr(size_t hart_id, uint64_t paddr);
  const spike_state_snapshot_t* snapshot(size_t hart_id) const;
  MmuTrace get_mmu_trace(size_t hart_id) const;
  bool in_trap(size_t hart_id) const;
  void reset_observed(size_t hart_id);

private:
  struct core_state_t {
    spike_state_snapshot_t snapshot;
    MmuTrace pending_mmu_trace{};
    bool has_pending_mmu_trace = false;
  };

  core_state_t* core_state(size_t hart_id);
  const core_state_t* core_state(size_t hart_id) const;
  static MmuTrace to_mmu_trace(const spike_mmu_walk_observe_t& event);

  std::vector<core_state_t> cores_;
};

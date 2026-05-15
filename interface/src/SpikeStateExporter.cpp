#include "SpikeStateExporter.hpp"

#include "decode_macros.h"
#include "mmu.h"
#include "trap.h"

void spike_observed_insn_t::reset()
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

void spike_state_exporter_t::reset(size_t nprocs)
{
  cores_ = std::vector<core_state_t>(nprocs);
}

void spike_state_exporter_t::observe_pre_exec(
    size_t hart_id,
    insn_fetch_t* in,
    reg_t pc)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }
  auto& obs = core->snapshot.observed;
  obs.valid = true;
  obs.pc = pc;
  obs.bits = in ? in->insn.bits() : 0;
  obs.npc = ERROR_PC_ADDR;
}

void spike_state_exporter_t::observe_exec(
    size_t hart_id,
    insn_fetch_t* in,
    reg_t pc,
    reg_t npc)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }

  core->snapshot.in_trap = false;
  auto& obs = core->snapshot.observed;
  obs.valid = true;
  obs.pc = pc;
  obs.bits = in ? in->insn.bits() : 0;
  obs.npc = ERROR_PC_ADDR;
  if (npc != 0 && !invalid_pc(npc)) {
    obs.npc = npc;
  }

  if (core->has_pending_mmu_trace) {
    core->snapshot.mmu_trace = core->pending_mmu_trace;
    core->has_pending_mmu_trace = false;
  } else {
    core->snapshot.mmu_trace = {};
    core->snapshot.mmu_trace.paddr = 0;
  }
}

reg_t spike_state_exporter_t::observe_trap(
    size_t hart_id,
    void* in,
    reg_t pc,
    trap_t& t)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return 0;
  }

  auto& snap = core->snapshot;
  snap.in_trap = true;
  snap.epc = pc;
  snap.trap_npc = ERROR_PC_ADDR;
  snap.cause = t.cause();
  snap.tval = t.get_tval();
  snap.has_tval2 = t.has_tval2();
  snap.tval2 = snap.has_tval2 ? t.get_tval2() : 0;

  if (core->has_pending_mmu_trace) {
    snap.mmu_trace = core->pending_mmu_trace;
    core->has_pending_mmu_trace = false;
  } else {
    snap.mmu_trace = {};
    snap.mmu_trace.paddr = snap.observed.paddr;
  }
  snap.mmu_trace.excp_cause = snap.cause;

  return 0;
}

void spike_state_exporter_t::observe_trap_target(size_t hart_id, reg_t npc)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }

  if (!core->snapshot.in_trap) {
    return;
  }

  if (npc != 0 && !invalid_pc(npc)) {
    core->snapshot.trap_npc = npc;
  }
}

void spike_state_exporter_t::observe_mmu_walk(
    const spike_mmu_walk_observe_t& event)
{
  auto* core = core_state(event.hart_id);
  if (!core) {
    return;
  }

  core->pending_mmu_trace = to_mmu_trace(event);
  core->has_pending_mmu_trace = true;
  core->snapshot.mmu_trace = core->pending_mmu_trace;
}

void spike_state_exporter_t::observe_fetch(
    size_t hart_id,
    reg_t vaddr,
    reg_t paddr,
    reg_t paddr2,
    insn_bits_t bits,
    unsigned length)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }
  auto& obs = core->snapshot.observed;
  obs.valid = true;
  obs.pc = vaddr;
  obs.paddr = paddr;
  obs.paddr2 = paddr2;
  if (bits != 0) {
    obs.bits = bits;
  }
  (void)length;
}

void spike_state_exporter_t::set_mmu_paddr(size_t hart_id, uint64_t paddr)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }

  core->pending_mmu_trace = {};
  core->has_pending_mmu_trace = false;
  core->snapshot.mmu_trace = {};
  core->snapshot.mmu_trace.paddr = paddr;
}

const spike_state_snapshot_t* spike_state_exporter_t::snapshot(size_t hart_id) const
{
  auto* core = core_state(hart_id);
  return core ? &core->snapshot : nullptr;
}

MmuTrace spike_state_exporter_t::get_mmu_trace(size_t hart_id) const
{
  auto* core = core_state(hart_id);
  return core ? core->snapshot.mmu_trace : MmuTrace{};
}

bool spike_state_exporter_t::in_trap(size_t hart_id) const
{
  auto* core = core_state(hart_id);
  return core ? core->snapshot.in_trap : false;
}

void spike_state_exporter_t::reset_observed(size_t hart_id)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }

  core->snapshot.observed.reset();
  core->snapshot.in_trap = false;
  core->mem_loads.clear();
  core->mem_stores.clear();
}

void spike_state_exporter_t::add_mem_log(size_t hart_id, reg_t addr, uint64_t val, uint8_t size, reg_t paddr, bool is_store)
{
  auto* core = core_state(hart_id);
  if (!core) return;
  if (is_store)
    core->mem_stores.push_back({addr, val, size, paddr});
  else
    core->mem_loads.push_back({addr, val, size, paddr});
}

void spike_state_exporter_t::clear_mem_log(size_t hart_id)
{
  auto* core = core_state(hart_id);
  if (!core) return;
  core->mem_loads.clear();
  core->mem_stores.clear();
}

const std::vector<spike_state_exporter_t::MemLogItem>& spike_state_exporter_t::mem_loads(size_t hart_id) const
{
  static const std::vector<MemLogItem> empty;
  auto* core = core_state(hart_id);
  return core ? core->mem_loads : empty;
}

const std::vector<spike_state_exporter_t::MemLogItem>& spike_state_exporter_t::mem_stores(size_t hart_id) const
{
  static const std::vector<MemLogItem> empty;
  auto* core = core_state(hart_id);
  return core ? core->mem_stores : empty;
}

spike_state_exporter_t::core_state_t* spike_state_exporter_t::core_state(size_t hart_id)
{
  return hart_id < cores_.size() ? &cores_[hart_id] : nullptr;
}

const spike_state_exporter_t::core_state_t* spike_state_exporter_t::core_state(size_t hart_id) const
{
  return hart_id < cores_.size() ? &cores_[hart_id] : nullptr;
}

MmuTrace spike_state_exporter_t::to_mmu_trace(
    const spike_mmu_walk_observe_t& event)
{
  MmuTrace trace;
  trace.paddr = event.paddr;
  for (size_t i = 0; i < 5; ++i) {
    trace.pte_paddr[i] = event.pte_paddr[i];
  }
  trace.levels = event.levels;
  trace.excp_cause = event.excp_cause;
  trace.xf_log.forced_virt = event.xf_log.forced_virt;
  trace.xf_log.hlvx = event.xf_log.hlvx;
  trace.xf_log.lr = event.xf_log.lr;
  trace.xf_log.ss_access = event.xf_log.ss_access;
  trace.xf_log.clean_inval = event.xf_log.clean_inval;
  trace.xf_log.enable_misalign = event.xf_log.enable_misalign;
  return trace;
}

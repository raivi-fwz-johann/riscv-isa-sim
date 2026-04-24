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

  auto& observed = core->snapshot.observed;
  observed.valid = true;
  observed.in_trap = false;
  observed.has_tval2 = false;
  observed.pc = pc;
  observed.npc = ERROR_PC_ADDR;
  observed.bits = in ? in->insn.bits() : 0;
  observed.paddr = in ? in->pc_ppn : ERROR_PC_ADDR;
  observed.paddr2 = ERROR_PC_ADDR;
  observed.cause = 0;
  observed.tval = 0;
  observed.tval2 = 0;
  if (npc != 0 && !invalid_pc(npc)) {
    observed.npc = npc;
  }

  if (core->has_pending_mmu_trace) {
    core->snapshot.mmu_trace = core->pending_mmu_trace;
    core->has_pending_mmu_trace = false;
  } else {
    core->snapshot.mmu_trace = {};
    core->snapshot.mmu_trace.paddr = observed.paddr;
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

  auto& observed = core->snapshot.observed;
  observed.valid = true;
  observed.in_trap = true;
  observed.npc = ERROR_PC_ADDR;
  observed.pc = pc;
  observed.bits = in ? static_cast<insn_fetch_t*>(in)->insn.bits() : 0;
  observed.paddr = in ? static_cast<insn_fetch_t*>(in)->pc_ppn : ERROR_PC_ADDR;
  observed.paddr2 = ERROR_PC_ADDR;
  observed.cause = t.cause();
  observed.tval = t.get_tval();
  observed.has_tval2 = t.has_tval2();
  observed.tval2 = observed.has_tval2 ? t.get_tval2() : 0;

  if (core->has_pending_mmu_trace) {
    core->snapshot.mmu_trace = core->pending_mmu_trace;
    core->has_pending_mmu_trace = false;
  } else {
    core->snapshot.mmu_trace = {};
    core->snapshot.mmu_trace.paddr = observed.paddr;
  }
  core->snapshot.mmu_trace.excp_cause = observed.cause;

  return 0;
}

void spike_state_exporter_t::observe_trap_target(size_t hart_id, reg_t npc)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }

  auto& observed = core->snapshot.observed;
  if (!observed.valid || !observed.in_trap) {
    return;
  }

  if (npc != 0 && !invalid_pc(npc)) {
    observed.npc = npc;
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
  return core ? core->snapshot.observed.in_trap : false;
}

void spike_state_exporter_t::reset_observed(size_t hart_id)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }

  core->snapshot.observed.reset();
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

#include "SpikeStateExporter.hpp"

#include "decode_macros.h"
#include "mmu.h"
#include "trap.h"

#include <cstdlib>
#include <iostream>

namespace {

bool snapshot_debug_enabled()
{
  return std::getenv("MODEL_STATE_SNAPSHOT_DEBUG") != nullptr;
}

void log_snapshot_observe_exec_debug(
    size_t hart_id,
    const spike_observed_insn_t& observed,
    bool had_pending_mmu_trace,
    uint64_t backend_pc)
{
  if (!snapshot_debug_enabled()) {
    return;
  }
  std::cout << "modelDebug snapshotObserveExecState"
            << " core=" << hart_id
            << " had_pending_mmu=" << had_pending_mmu_trace
            << std::hex
            << " observed_pc=0x" << observed.pc
            << " observed_npc=0x" << observed.npc
            << " backend_pc=0x" << backend_pc
            << " bits=0x" << observed.bits
            << " paddr=0x" << observed.paddr
            << std::dec
            << " valid=" << observed.valid
            << " in_trap=" << observed.in_trap
            << std::endl;
}

}  // namespace

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
  auto& pe = core->snapshot.pre_exec;
  pe.valid = true;
  pe.pc = pc;
  pe.bits = in ? in->insn.bits() : 0;
  pe.paddr = in ? in->pc_ppn : ERROR_PC_ADDR;
  pe.paddr2 = in ? in->pc_ppn2 : ERROR_PC_ADDR;
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

  const bool had_pending_mmu_trace = core->has_pending_mmu_trace;
  core->snapshot.in_trap = false;
  auto& exec = core->snapshot.exec;
  exec.valid = true;
  exec.pc = pc;
  exec.bits = in ? in->insn.bits() : 0;
  exec.paddr = in ? in->pc_ppn : ERROR_PC_ADDR;
  exec.paddr2 = in ? in->pc_ppn2 : exec.paddr;
  exec.npc = ERROR_PC_ADDR;
  if (npc != 0 && !invalid_pc(npc)) {
    exec.npc = npc;
  }

  if (core->has_pending_mmu_trace) {
    core->snapshot.mmu_trace = core->pending_mmu_trace;
    core->has_pending_mmu_trace = false;
  } else {
    core->snapshot.mmu_trace = {};
    core->snapshot.mmu_trace.paddr = exec.paddr;
  }
  log_snapshot_observe_exec_debug(hart_id, exec, had_pending_mmu_trace, pc);
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
    snap.mmu_trace.paddr = snap.fetch.paddr;
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
  auto& snapshot = core->snapshot;
  snapshot.stale_fetch = snapshot.fetch;  // save before overwrite
  auto& fetch = snapshot.fetch;
  fetch.valid = true;
  fetch.pc = vaddr;
  fetch.paddr = paddr;
  fetch.paddr2 = paddr2;
  if (bits != 0) {
    fetch.bits = bits;
  }
  (void)length;
}

void spike_state_exporter_t::save_stale_fetch(size_t hart_id)
{
  auto* core = core_state(hart_id);
  if (!core) {
    return;
  }
  core->snapshot.stale_fetch = core->snapshot.fetch;
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

  core->snapshot.fetch.reset();
  core->snapshot.exec.reset();
  core->snapshot.pre_exec.reset();
  core->snapshot.stale_fetch.reset();
  core->snapshot.in_trap = false;
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

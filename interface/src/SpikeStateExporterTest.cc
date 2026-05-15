#include "SpikeStateExporter.hpp"

#include "decode_macros.h"
#include "mmu.h"
#include "trap.h"

int main()
{
  spike_state_exporter_t exporter;
  exporter.reset(2);

  insn_fetch_t fetch{};
  fetch.insn = insn_t(0x00000013);

  exporter.observe_fetch(1, 0x1000, 0x2000, 0x2000, 0x00000013, 4);
  exporter.observe_exec(1, &fetch, 0x1000, 0x1004);
  auto* exec_snapshot = exporter.snapshot(1);
  if (!exec_snapshot || !exec_snapshot->observed.valid)
    return 1;
  if (exec_snapshot->observed.pc != 0x1000)
    return 2;
  if (exec_snapshot->observed.npc != 0x1004)
    return 3;
  if (exec_snapshot->observed.bits != 0x00000013)
    return 4;
  if (exec_snapshot->observed.paddr != 0x2000)
    return 5;
  if (exec_snapshot->mmu_trace.paddr != 0x2000)
    return 6;

  exporter.observe_exec(1, &fetch, 0x1004, PC_SERIALIZE_AFTER);
  exec_snapshot = exporter.snapshot(1);
  if (!exec_snapshot)
    return 24;
  if (exec_snapshot->observed.pc != 0x1004)
    return 25;
  if (exec_snapshot->observed.npc != ERROR_PC_ADDR)
    return 26;

  exporter.observe_exec(1, &fetch, 0x1008, PC_SERIALIZE_BEFORE);
  exec_snapshot = exporter.snapshot(1);
  if (!exec_snapshot)
    return 27;
  if (exec_snapshot->observed.pc != 0x1008)
    return 28;
  if (exec_snapshot->observed.npc != ERROR_PC_ADDR)
    return 29;

  spike_mmu_walk_observe_t pending_walk{};
  pending_walk.hart_id = 0;
  pending_walk.paddr = 0x3000;
  pending_walk.levels = 3;
  pending_walk.pte_paddr[0] = 0x10;
  pending_walk.pte_paddr[1] = 0x20;
  pending_walk.pte_paddr[2] = 0x30;
  pending_walk.xf_log.forced_virt = true;
  exporter.observe_mmu_walk(pending_walk);

  exporter.observe_exec(0, &fetch, 0x2000, 0x2004);
  auto pending_trace = exporter.get_mmu_trace(0);
  if (pending_trace.paddr != 0x3000)
    return 7;
  if (pending_trace.pte_paddr[0] != 0x10 || pending_trace.pte_paddr[1] != 0x20 || pending_trace.pte_paddr[2] != 0x30)
    return 8;
  if (pending_trace.levels != 3)
    return 9;
  if (!pending_trace.xf_log.forced_virt)
    return 10;

  exporter.set_mmu_paddr(0, 0x4000);
  auto direct_trace = exporter.get_mmu_trace(0);
  if (direct_trace.paddr != 0x4000)
    return 11;
  if (direct_trace.pte_paddr[0] != 0 || direct_trace.pte_paddr[1] != 0 || direct_trace.pte_paddr[2] != 0)
    return 12;
  if (direct_trace.levels != -1)
    return 13;

  spike_mmu_walk_observe_t trap_walk{};
  trap_walk.hart_id = 1;
  trap_walk.paddr = 0x5000;
  trap_walk.excp_cause = CAUSE_LOAD_PAGE_FAULT;
  trap_walk.pte_paddr[0] = 0xaa;
  trap_walk.levels = 2;
  exporter.observe_mmu_walk(trap_walk);

  trap_load_page_fault trap(false, 0x44, 0x55, 0x66);
  if (exporter.observe_trap(1, &fetch, 0x1110, trap) != 0)
    return 14;

  auto* trap_snapshot = exporter.snapshot(1);
  if (!trap_snapshot || !trap_snapshot->in_trap)
    return 15;
  if (trap_snapshot->cause != CAUSE_LOAD_PAGE_FAULT)
    return 16;
  if (trap_snapshot->tval != 0x44 || trap_snapshot->tval2 != 0x55)
    return 17;
  if (!trap_snapshot->has_tval2)
    return 18;

  auto trap_trace = exporter.get_mmu_trace(1);
  if (trap_trace.excp_cause != CAUSE_LOAD_PAGE_FAULT)
    return 19;
  if (trap_trace.pte_paddr[0] != 0xaa)
    return 20;

  exporter.reset_observed(1);
  auto* cleared_snapshot = exporter.snapshot(1);
  if (!cleared_snapshot || cleared_snapshot->observed.valid)
    return 21;

  auto preserved_trace = exporter.get_mmu_trace(1);
  if (preserved_trace.excp_cause != CAUSE_LOAD_PAGE_FAULT)
    return 22;
  if (preserved_trace.pte_paddr[0] != 0xaa)
    return 23;

  return 0;
}

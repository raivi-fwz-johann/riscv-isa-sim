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

// Abstract hook dispatcher — external observer injects a concrete subclass
// via runtime_context to intercept execution events.  Every method has an
// empty default so that subclasses only override what they need.
class spike_hook_dispatcher_t {
public:
  virtual ~spike_hook_dispatcher_t() = default;

  // -- instruction lifecycle -------------------------------------------------

  // Called after instruction decode, before execution.
  // [in] instr   decoded instruction object
  // [in] pc      virtual address of the instruction
  // [in] npc     next pc (pc + insn_length)
  virtual void on_decode(void* instr, reg_t pc, reg_t npc) {}

  // Called when the commit log is about to be printed.
  // [return] true if the caller should commit, false to suppress.
  virtual bool on_commit() { return false; }

  // Called to allow the hook to override the next PC computed by execution.
  // [in]  candidate_npc  npc proposed by the instruction implementation
  // [return] the actual npc to use
  virtual reg_t on_next_pc(reg_t candidate_npc) { return candidate_npc; }

  // -- trap / interrupt ------------------------------------------------------

  // Called when a trap is taken.
  // [in]  hart_id  core id
  // [in]  fetch    insn_fetch_t* of the trapping instruction
  // [in]  epc      pc of the trapping instruction
  // [in]  t        trap descriptor (cause, tval, …)
  // [return]       non-zero to skip normal trap handling
  virtual reg_t on_trap(uint32_t hart_id, void* fetch, reg_t epc, trap_t& t) { return 0; }

  // Called after the trap handler has set the new PC.
  // [in] hart_id  core id
  // [in] epc      original trap pc
  // [in] npc      new pc (trap handler entry point)
  virtual void on_trap_target(uint32_t hart_id, reg_t epc, reg_t npc) {}

  // -- execution flow control ------------------------------------------------

  // Polled periodically; returning false pauses the hart.
  // [return] false to suspend execution of this hart
  virtual bool should_continue() { return true; }

  // Called when the step loop advanced instret without executing a real
  // instruction (e.g. after a resume from debug mode).
  // [in] instret       current instret counter
  // [in] prev_instret  instret before the fake step
  virtual void on_fake_step(size_t instret, size_t prev_instret) {}

  // -- memory access ---------------------------------------------------------

  // Called before a store is performed.
  // [in]  addr        virtual address
  // [in]  val         value to store (reg_t width)
  // [in]  size        store size in bytes
  // [out] real_store  set to true if the store should actually be performed
  virtual void on_pre_store(reg_t addr, reg_t val, uint32_t size,
                            std::shared_ptr<bool> real_store) {}

  // Called for every architecturally-visible memory access (load or store).
  // Fires before the access itself so the data survives page faults.
  // [in] hart_id   core id
  // [in] addr      virtual address
  // [in] val       data value (store data for stores, 0 for loads pre-completion)
  // [in] size      access size in bytes (1/2/4/8/…)
  // [in] paddr     translated physical address (best-effort, may fall back to addr)
  // [in] is_store  true for stores, false for loads
  virtual void on_mem_log(uint32_t hart_id, reg_t addr, uint64_t val,
                          uint8_t size, reg_t paddr, bool is_store) {}

  // Called at the start of each instruction to reset per-instruction state.
  // [in] hart_id  core id
  virtual void on_commit_log_reset(uint32_t hart_id) {}

  // -- CSR access ------------------------------------------------------------

  // Called before a CSR write to determine if it is allowed.
  // [in]  csr  CSR number
  // [in]  val  value to be written
  // [return]   true to allow, false to block the write
  virtual bool allow_csr_write(int csr, reg_t val) { return true; }

  // Called before every CSR write (even if blocked).
  // [in]  csr   CSR number
  // [in]  val   value to be written
  // [out] allow initially true; set to false to block the write
  virtual void on_pre_csr(int csr, reg_t val, std::shared_ptr<bool> allow) {}

  // -- exit ------------------------------------------------------------------

  // Called when the simulator is asked to exit (e.g. interactive 'q').
  // [in]  code   exit code
  // [return]     true to proceed with hard exit(), false to let the model
  //              handle a clean shutdown (stop() + done()).
  virtual bool on_exit(int code) { return true; }

  // -- observation hooks -----------------------------------------------------

  // Called after an instruction has been executed.
  // [in] hart_id  core id
  // [in] fetch    insn_fetch_t* with decoded instruction, pc_ppn, pc_ppn2
  // [in] pc       virtual address of the executed instruction
  // [in] npc      next pc after execution
  virtual void on_exec_observe(uint32_t hart_id, insn_fetch_t* fetch,
                               reg_t pc, reg_t npc) {}

  // Called BEFORE fetch.func() executes — survives traps where
  // on_exec_observe never fires (e.g. page faults during execution).
  // [in] hart_id  core id
  // [in] fetch    insn_fetch_t* with decoded instruction, pc_ppn, pc_ppn2
  // [in] pc       virtual address of the instruction
  virtual void on_pre_exec(uint32_t hart_id, insn_fetch_t* fetch, reg_t pc) {}

  // Called every time the icache is refilled (TLB miss, page fault, …).
  // [in] hart_id  core id
  // [in] vaddr    virtual address of the fetch
  // [in] paddr    physical address (pc_ppn — first parcel)
  // [in] paddr2   physical address (pc_ppn2 — last parcel, differs for cross-page)
  // [in] bits     raw instruction bits
  // [in] length   instruction length in bytes (2 or 4)
  virtual void on_fetch_observe(uint32_t hart_id, reg_t vaddr, reg_t paddr,
                                reg_t paddr2, insn_bits_t bits,
                                unsigned length) {}

  // -- device / MMU ----------------------------------------------------------

  // Called when the UART device transmits a byte.
  // [in] device  the UART device instance
  // [in] byte    the transmitted byte
  virtual void on_device_uart_tx(abstract_device_t* device, uint8_t byte) {}

  // Called when a page-table walk is performed.
  // [in] event  walk metadata (hart_id, vaddr, paddr, pte_paddr[], levels, …)
  virtual void on_mmu_walk(const spike_mmu_walk_observe_t& event) {}
};

#pragma once

#include "decode.h"
#include <cstddef>

class processor_t;
class sim_t;
class trap_t;

enum class hook_continue_site_t {
  mem_load,
  mem_store,
  run_loop,
};

struct decode_event_t {
  processor_t* proc;
  void* fetch;
  reg_t pc;
  reg_t npc;
};

struct commit_event_t {
  processor_t* proc;
  reg_t pc;
};

struct next_pc_event_t {
  processor_t* proc;
  reg_t current_pc;
  reg_t candidate_npc;
};

struct trap_event_t {
  void* fetch;
  reg_t epc;
  trap_t& trap;
};

struct continue_event_t {
  processor_t* proc;
  sim_t* sim;
  hook_continue_site_t site;
};

struct pre_store_event_t {
  reg_t addr;
  reg_t data;
  uint32_t len;
  bool real_store;
};

struct csr_gate_event_t {
  int which;
  reg_t value;
};

struct pre_csr_event_t {
  int which;
  reg_t value;
  bool real_store;
};

struct exit_event_t {
  int code;
};

struct exec_observe_event_t {
  processor_t* proc;
  void* fetch;
  reg_t pc;
  reg_t npc;
};

struct fake_step_event_t {
  processor_t* proc;
  size_t curr_instret;
  size_t prev_instret;
  reg_t pc;
};

struct next_pc_decision_t {
  bool override_next_pc = false;
  reg_t next_pc = 0;
};

struct trap_decision_t {
  bool consume_trap = false;
  reg_t return_code = 0;
};

struct exit_decision_t {
  bool allow_exit = true;
};

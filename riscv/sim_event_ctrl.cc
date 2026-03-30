/**
 * @file sim_event_ctrl.cc
 * @author qiubinglin (qiubinglin@outlook.com)
 * @brief
 * @version 0.1
 * @date 2025-01-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "sim_event_ctrl.h"

#include <cassert>

#include "sim.h"

sim_event_ctrl_t::sim_event_ctrl_t(sim_t &sim) : sim(sim) {}

void sim_event_ctrl_t::set_tint(const tint_t &int_arg) {
  processor_t *p = sim.get_core(int_arg.core_idx);
  p->get_state()->mip->backdoor_write_with_mask(MIP_MTIP, MIP_MTIP);
}

void sim_event_ctrl_t::do_tick() {
  bool start = false;
  size_t step_count = 0;
  bool can_tick = true;
  for (auto &[id, hart] : sim.get_harts()) {
    if (not start) {
      start = true;
      step_count = hart->get_step_count();
    }
    if (step_count != hart->get_step_count()) {
      can_tick = false;
      break;
    }
  }

  if (can_tick) {
    sim.devices_tick(sim.INTERLEAVE);
    for (auto &[id, hart] : sim.get_harts()) {
      hart->reset_step_count();
    }
  }
}

void sim_event_ctrl_t::do_host_acts() {}
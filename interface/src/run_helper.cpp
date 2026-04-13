/**
 * @file run_helper.cc
 * @author 
 * @brief Spike simulator run code extracted from htif.cc and sim.cc
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "run_helper.h"

#include "Memory.hpp"

#include "sim.h"
#include <stdexcept>

static void bad_address(const std::string& situation, reg_t addr)
{
  std::stringstream ss;
  ss << "Access exception occurred while " << situation << ": "
     << "memory address 0x" << std::hex << addr << " is invalid";
  throw std::runtime_error(ss.str());
}

void run_helper_t::start(sim_t *spike_sim) {
  spike_sim->start();
  auto enq_func = [](std::queue<reg_t>* q, uint64_t x) { q->push(x); };
  fromhost_queue = std::queue<reg_t>();
  fromhost_callback =
    std::bind(enq_func, &fromhost_queue, std::placeholders::_1);
}

void run_helper_t::stop(sim_t *spike_sim) { spike_sim->stop(); }

size_t run_helper_t::step(sim_t *sim, size_t n, size_t proc) {
  return _step(sim, n, proc);
}

size_t run_helper_t::_step(sim_t *spike_sim, size_t n, size_t proc) {
  if (n != 1) {
    throw std::runtime_error("step n must equals 1!!!");
  }
  size_t total_steps_done = 0;

  if (spike_sim->get_tohost_addr() == 0) {
    while (!spike_sim->done() && n > 0) {
      auto steps_done = spike_sim->idle_ext(n, proc);
      if (steps_done == 0) {
        break;
      }
      n -= steps_done;
      total_steps_done += steps_done;
    }
    return total_steps_done;
  }

  if (spike_sim->host_disabled()) {
    while (!spike_sim->done() && n > 0) {
      auto steps_done = spike_sim->idle_ext(n, proc);
      if (steps_done == 0) {
        break;
      }
      n -= steps_done;
      total_steps_done += steps_done;
    }
    return total_steps_done;
  }

  while (!spike_sim->done() && n > 0)
  {
    uint64_t tohost = 0;

    try {
      if ((tohost = spike_sim->from_target(
               spike_sim->memif().read_uint64(spike_sim->get_tohost_addr()))) != 0) {
        spike_sim->memif().write_uint64(
            spike_sim->get_tohost_addr(), target_endian<uint64_t>::zero);
      }
    } catch (mem_trap_t& t) {
      bad_address("accessing tohost", t.get_tval());
    }

    try {
      if (tohost != 0) {
        command_t cmd(spike_sim->memif(), tohost, fromhost_callback);
        spike_sim->get_devices().handle_command(cmd);
      } else {
        auto steps_done = spike_sim->idle_ext(n, proc);
        if (steps_done == 0) {
          break;
        }
        n -= steps_done;
        total_steps_done += steps_done;
      }

      spike_sim->get_devices().tick();
    } catch (mem_trap_t& t) {
      std::stringstream tohost_hex;
      tohost_hex << std::hex << tohost;
      bad_address("host was accessing memory on behalf of target (tohost = 0x" + tohost_hex.str() + ")", t.get_tval());
    }

    try {
      if (!fromhost_queue.empty() &&
          !spike_sim->memif().read_uint64(spike_sim->get_fromhost_addr())) {
        spike_sim->memif().write_uint64(
            spike_sim->get_fromhost_addr(),
            spike_sim->to_target(fromhost_queue.front()));
        fromhost_queue.pop();
      }
    } catch (mem_trap_t& t) {
      bad_address("accessing fromhost", t.get_tval());
    }
  }
  return total_steps_done;
}

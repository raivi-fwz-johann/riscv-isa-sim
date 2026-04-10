/**
 * @file run_helper.h
 * @author 
 * @brief Spike simulator run code extracted from htif.cc and sim.cc
 * @version 0.1
 * @date 2024-12-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef RUN_HELPER_H
#define RUN_HELPER_H

#include <cstdint>
#include <functional>
#include <queue>

class sim_t;
class run_helper_t {
public:
  void start(sim_t *sim);
  void stop(sim_t *sim);
  size_t step(sim_t *sim, size_t n, size_t proc);

private:
  size_t _step(sim_t *sim, size_t n, size_t proc);

  std::queue<uint64_t> fromhost_queue;
  std::function<void(uint64_t)> fromhost_callback;
};

#endif

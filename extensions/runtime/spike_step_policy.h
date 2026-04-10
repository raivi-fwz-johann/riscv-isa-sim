#pragma once

#include <cstddef>

class spike_step_policy_t {
public:
  size_t interleave() const { return interleave_; }
  void set_interleave(size_t value) { interleave_ = value; }

private:
  size_t interleave_ = 0;
};

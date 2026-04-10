#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

class abstract_device_t;

class spike_roi_state_t {
public:
  void set_enabled(bool enabled) { enabled_ = enabled; }
  bool enabled() const { return enabled_; }
  bool in_roi() const { return !enabled_ || (roi_begin_ && !roi_end_); }

  void on_device_uart_tx(abstract_device_t* device, uint8_t byte);

private:
  bool advance_match(size_t& matched, uint8_t byte);

  const std::string marker_ = "CURR_MINSTRET";
  bool enabled_ = false;
  bool roi_begin_ = false;
  bool roi_end_ = false;
  size_t roi_begin_matched_ = 0;
  size_t roi_end_matched_ = 0;
};

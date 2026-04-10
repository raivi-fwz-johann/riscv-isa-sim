#include "SpikeRoiState.hpp"

void spike_roi_state_t::set_enabled(bool enabled)
{
  if (enabled_ == enabled) {
    return;
  }

  enabled_ = enabled;
  reset_state();
}

void spike_roi_state_t::on_device_uart_tx(
    abstract_device_t* device,
    uint8_t byte)
{
  (void)device;
  if (!enabled_) {
    return;
  }

  if (roi_begin_ && roi_end_) {
    roi_begin_ = false;
    roi_end_ = false;
  }

  if (!roi_begin_) {
    roi_begin_ = advance_match(roi_begin_matched_, byte);
  } else if (!roi_end_) {
    roi_end_ = advance_match(roi_end_matched_, byte);
  }
}

bool spike_roi_state_t::advance_match(size_t& matched, uint8_t byte)
{
  if (byte == static_cast<uint8_t>(marker_[matched])) {
    matched += 1;
    if (matched == marker_.size()) {
      matched = 0;
      return true;
    }
    return false;
  }

  matched = byte == static_cast<uint8_t>(marker_[0]) ? 1 : 0;
  return false;
}

void spike_roi_state_t::reset_state()
{
  roi_begin_ = false;
  roi_end_ = false;
  roi_begin_matched_ = 0;
  roi_end_matched_ = 0;
}

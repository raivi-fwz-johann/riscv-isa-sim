#include "SpikeRoiState.hpp"

#include <string>

namespace {

void feed(spike_roi_state_t& roi, const std::string& bytes)
{
  for (char byte : bytes) {
    roi.on_device_uart_tx(nullptr, static_cast<uint8_t>(byte));
  }
}

}  // namespace

int main()
{
  spike_roi_state_t roi;
  if (!roi.in_roi())
    return 1;

  roi.set_enabled(true);
  if (roi.in_roi())
    return 2;

  feed(roi, "CURR_MINSTRET");
  if (!roi.in_roi())
    return 3;

  roi.set_enabled(false);
  if (!roi.in_roi())
    return 4;
  roi.set_enabled(true);
  if (roi.in_roi())
    return 5;

  feed(roi, "CURR_MINSTRET");
  if (!roi.in_roi())
    return 6;

  feed(roi, "CURR_MINSTRET");
  if (roi.in_roi())
    return 7;

  feed(roi, "CURR_MI");
  if (roi.in_roi())
    return 8;
  feed(roi, "XCURR_MINSTRET");
  if (!roi.in_roi())
    return 9;

  feed(roi, "CURR_MINSTRET");
  if (roi.in_roi())
    return 10;

  roi.set_enabled(false);
  if (!roi.in_roi())
    return 11;

  return 0;
}

#pragma once

// Controls whether the htif host (fesvr) path is active.  When the host
// is disabled, tohost/fromhost polling is skipped and the simulator runs
// in a tight loop driven entirely by the model / interface layer.
class spike_host_policy_t {
public:
  // Returns true if the htif host path is disabled.
  bool disable_host() const { return disable_host_; }
  // |value|  true to disable the host path.
  void set_disable_host(bool value) { disable_host_ = value; }

private:
  bool disable_host_ = false;
};

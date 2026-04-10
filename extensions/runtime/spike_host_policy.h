#pragma once

class spike_host_policy_t {
public:
  bool disable_host() const { return disable_host_; }
  void set_disable_host(bool value) { disable_host_ = value; }

private:
  bool disable_host_ = false;
};

#include "runtime/spike_device_observe_registry.h"
#include "runtime/runtime_context.h"

#include "../../riscv/abstract_device.h"

class dummy_device_t final : public abstract_device_t {
public:
  bool load(reg_t, size_t, uint8_t*) override { return false; }
  bool store(reg_t, size_t, const uint8_t*) override { return false; }
  reg_t size() override { return 0; }
};

int main()
{
  spike_runtime_context_t runtime;
  dummy_device_t device;

  if (spike_find_device_runtime_context(&device) != nullptr)
    return 1;

  spike_register_device_runtime_context(&device, &runtime);
  if (spike_find_device_runtime_context(&device) != &runtime)
    return 2;

  spike_unregister_device_runtime_context(&device);
  if (spike_find_device_runtime_context(&device) != nullptr)
    return 3;

  return 0;
}

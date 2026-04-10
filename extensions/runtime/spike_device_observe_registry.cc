#include "runtime/spike_device_observe_registry.h"

#include <mutex>
#include <unordered_map>

namespace {

std::mutex registry_mutex;
std::unordered_map<const abstract_device_t*, spike_runtime_context_t*> registry;

}  // namespace

void spike_register_device_runtime_context(
    abstract_device_t* device,
    spike_runtime_context_t* runtime_context)
{
  std::lock_guard<std::mutex> lock(registry_mutex);
  registry[device] = runtime_context;
}

void spike_unregister_device_runtime_context(const abstract_device_t* device)
{
  std::lock_guard<std::mutex> lock(registry_mutex);
  registry.erase(device);
}

spike_runtime_context_t* spike_find_device_runtime_context(
    const abstract_device_t* device)
{
  std::lock_guard<std::mutex> lock(registry_mutex);
  auto it = registry.find(device);
  return it == registry.end() ? nullptr : it->second;
}

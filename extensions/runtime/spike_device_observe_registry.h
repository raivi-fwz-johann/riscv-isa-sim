#pragma once

class abstract_device_t;
class spike_runtime_context_t;

// Associates a device with a runtime context so that the device can
// later retrieve its owning context via spike_find_device_runtime_context.
// |device|           the device instance (non-null).
// |runtime_context|  the context to associate (non-null).
void spike_register_device_runtime_context(
    abstract_device_t* device,
    spike_runtime_context_t* runtime_context);

// Removes the association for |device|.  Safe to call with an
// unregistered device (no-op).
void spike_unregister_device_runtime_context(const abstract_device_t* device);

// Returns the runtime context previously registered for |device|, or
// nullptr if no association exists.
spike_runtime_context_t* spike_find_device_runtime_context(
    const abstract_device_t* device);

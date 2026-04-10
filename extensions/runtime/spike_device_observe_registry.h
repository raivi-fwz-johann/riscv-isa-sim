#pragma once

class abstract_device_t;
class spike_runtime_context_t;

void spike_register_device_runtime_context(
    abstract_device_t* device,
    spike_runtime_context_t* runtime_context);

void spike_unregister_device_runtime_context(const abstract_device_t* device);

spike_runtime_context_t* spike_find_device_runtime_context(
    const abstract_device_t* device);

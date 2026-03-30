#include "spikeAdpterHooks.hpp"

bool exitHook(int code) {
    return g_spike_hooker->hook_exit(code);
}

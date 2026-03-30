#ifndef __SPIKE_ADPTER_HOOKS__
#define __SPIKE_ADPTER_HOOKS__
#include "trap.h"
#include <cstdint>

#include "Memory.hpp"

#include "spikehooker.h"

extern bool exitHook(int) __attribute__((weak));

#endif


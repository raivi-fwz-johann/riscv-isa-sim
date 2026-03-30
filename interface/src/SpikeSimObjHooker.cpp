/**
 * @file SpikeSimObjHooker.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "SpikeSimObjHooker.hpp"

#include "trap.h"
#include "mmu.h"
#include "sim.h"
#include "decode_macros.h"

#include "RawSpike.hpp"

#include "SimObjMacros.hpp"
#undef CURR_CID
#define CURR_CID (m_SimObj->m_SimWrapper.m_CurrCId)

static Float128 toFloat128(float128_t val) {
  Float128 res;
  res.v[0] = val.v[0];
  res.v[1] = val.v[1];
  return res;
}

SpikeSimObjHooker::SpikeSimObjHooker(RawSpike *Ptr) : m_SimObj(Ptr) {}

bool SpikeSimObjHooker::hook_exit(int code) {
  m_SimObj->stop();
  return false;
}
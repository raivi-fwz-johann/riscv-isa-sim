/**
 * @file SpikeSimObjHooker.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "Memory.hpp"

#include "spikehooker.h"

class RawSpike;
class SpikeSimObjHooker : public SpikeHooker {
public:
  SpikeSimObjHooker(RawSpike *Ptr);

  bool hook_exit(int code) override;

private:
  RawSpike *m_SimObj = nullptr;
};
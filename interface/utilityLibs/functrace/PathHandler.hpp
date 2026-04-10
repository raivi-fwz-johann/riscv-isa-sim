/**
 * @file PathHandler.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <cstdint>
#include <iostream>
#include "functrace/InstTrace.hpp"
#include "functrace/InstInfoHolder.hpp"

class FuncSimAdapter;
class PathHandler {
public:
  void init(FuncSimAdapter *SimObj, uint32_t CId);
  bool isMissPredict() const { return m_MissPredict; }
  void recover(uint64_t IId);
  void configurePath(uint64_t NPc);
  uint64_t getConfiguredNPc() const { return m_ConfiguredNPc; }
  void setConfiguredNPc(uint64_t cfgPc) { m_ConfiguredNPc = cfgPc; } /* This method is for replay to get npc. */

  bool isNewStep() const;

  bool inCorrectId() const;

  void setCurrId(uint64_t id);

  uint64_t getCurrId() const { return m_CurrId; }

private:
  void checkPath(InstUserPtr CurrInst, uint64_t NPc);

  void clearMissQueue();

  bool m_MissPredict = false;

  FuncSimAdapter *m_SimObj = nullptr;
  uint32_t m_CId = 0;

  uint64_t m_ConfiguredNPc = ERROR_PC_ADDR;

  uint64_t m_CurrId{0};
};
/**
 * @file PathHandler.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "PathHandler.hpp"

#include <iostream>

#include "FuncSimAdapter.hpp"

void PathHandler::init(FuncSimAdapter *SimObj, uint32_t CId) {
  m_SimObj = SimObj;
  m_CId = CId;
}

void PathHandler::recover(uint64_t IId) {
  if (InstTrace::isCorrectID(IId)) {
    clearMissQueue();
  } else {
    m_SimObj->missHolder(m_CId).popUntil(IId);
    m_SimObj->missIdCursor(m_CId) = IId + 1;
  }
}

void PathHandler::configurePath(uint64_t NPc) {
  // std::cout << "path curr id: " << ConvertId(m_CurrId) << " " << inCorrectId() << std::endl;
  auto &holder = inCorrectId() ? m_SimObj->correctHolder(m_CId) : m_SimObj->missHolder(m_CId);

  InstUserPtr CurrInst = holder.getCurrInst();
  InstUserPtr NextSavedInst = holder.getNextInst();

  if (not holder.size()) {
    /* Only correct id enter here */
    m_MissPredict = NPc != m_SimObj->backendCurrPc(m_CId);
    clearMissQueue();
  } else if (holder.inDummyHead()) {
    /* Only correct id enter here */
    m_MissPredict = NPc != holder.getFrontInst()->getPc();
    clearMissQueue();
  } else if (NextSavedInst) {
    if (NextSavedInst->getPc() != NPc) {
      recover(CurrInst->getId());
      checkPath(CurrInst, NPc);
    }
  } else {
    checkPath(CurrInst, NPc);
  }
  // std::cout << "misspredict: " << m_MissPredict << std::endl;
  m_ConfiguredNPc = NPc;
}

bool PathHandler::isNewStep() const {
  auto &holder = inCorrectId() ? m_SimObj->correctHolder(m_CId) : m_SimObj->missHolder(m_CId);
  InstUserPtr NextSavedInst = holder.getNextInst();

  if (inCorrectId()) {
    /* If in dummy head, this is not a new step. */
    return not holder.inDummyHead() and not NextSavedInst;
  }
  return not NextSavedInst;
}

void PathHandler::checkPath(InstUserPtr CurrInst, uint64_t NPc) {
  if (not CurrInst) {
    return;
  }
  // std::cout << std::hex << "checkPath: " << CurrInst->getNPc() << " " << NPc << std::dec << std::endl;
  if (InstTrace::isCorrectID(CurrInst->getId())) {
    m_MissPredict = CurrInst->getNPc() != NPc;
  } else {
    m_MissPredict = true;
  }
}

bool PathHandler::inCorrectId() const {
  if (m_SimObj->correctHolder(m_CId).size() == 0 and m_SimObj->missHolder(m_CId).size() == 0) {
    return true;
  }
  return InstTrace::isCorrectID(m_CurrId);
}

void PathHandler::setCurrId(uint64_t id) {
    m_CurrId = id;
    m_MissPredict = not InstTrace::isCorrectID(m_CurrId);
    // std::cout << "setcurrid: " << m_CurrId << " " << m_MissPredict << std::endl;
}

void PathHandler::clearMissQueue() {
  m_SimObj->missHolder(m_CId).clear();
  m_SimObj->missIdCursor(m_CId) = MISS_ID_FLAG;
  m_MissPredict = false;
}

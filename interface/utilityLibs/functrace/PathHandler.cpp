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

#include <cstdlib>
#include <iostream>

#include "FuncSimAdapter.hpp"

namespace {

bool snapshot_debug_enabled()
{
  return std::getenv("MODEL_STATE_SNAPSHOT_DEBUG") != nullptr;
}

void log_path_debug(
    const char* tag,
    uint32_t cid,
    uint64_t curr_id,
    bool in_correct,
    bool miss_predict,
    uint64_t configured_npc,
    uint64_t backend_pc,
    uint64_t requested_npc = ERROR_PC_ADDR,
    uint64_t pc = ERROR_PC_ADDR,
    uint64_t npc = ERROR_PC_ADDR,
    size_t correct_size = 0,
    size_t miss_size = 0,
    const char* reason = "")
{
  if (!snapshot_debug_enabled()) {
    return;
  }
  std::cout << "modelDebug " << tag
            << " core=" << cid
            << " curr_id=0x" << std::hex << curr_id
            << " in_correct=" << in_correct
            << " miss_predict=" << miss_predict
            << " configured_npc=0x" << configured_npc
            << " backend_pc=0x" << backend_pc
            << " req_npc=0x" << requested_npc
            << " pc=0x" << pc
            << " npc=0x" << npc
            << std::dec
            << " correct_size=" << correct_size
            << " miss_size=" << miss_size
            << " reason=" << reason
            << std::endl;
}

}  // namespace

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
  const auto backend_pc = m_SimObj->backendCurrPc(m_CId);
  const char* reason = "unchanged";

  InstUserPtr CurrInst = holder.getCurrInst();
  InstUserPtr NextSavedInst = holder.getNextInst();

  if (not holder.size()) {
    /* Only correct id enter here */
    m_MissPredict = NPc != m_SimObj->backendCurrPc(m_CId);
    clearMissQueue();
    reason = "empty-holder";
  } else if (holder.inDummyHead()) {
    /* Only correct id enter here */
    m_MissPredict = NPc != holder.getFrontInst()->getPc();
    clearMissQueue();
    reason = "dummy-head";
  } else if (NextSavedInst) {
    if (NextSavedInst->getPc() != NPc) {
      recover(CurrInst->getId());
      checkPath(CurrInst, NPc);
      reason = "recover-next-mismatch";
    } else {
      reason = "next-hit";
    }
  } else {
    checkPath(CurrInst, NPc);
    reason = "check-curr-only";
  }
  log_path_debug(
      "pathConfigure",
      m_CId,
      m_CurrId,
      inCorrectId(),
      m_MissPredict,
      m_ConfiguredNPc,
      backend_pc,
      NPc,
      CurrInst ? CurrInst->getPc() : ERROR_PC_ADDR,
      NextSavedInst ? NextSavedInst->getPc() : ERROR_PC_ADDR,
      m_SimObj->correctHolder(m_CId).size(),
      m_SimObj->missHolder(m_CId).size(),
      reason);
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
    if (snapshot_debug_enabled()) {
      log_path_debug(
          "pathSetCurrId",
          m_CId,
          m_CurrId,
          inCorrectId(),
          m_MissPredict,
          m_ConfiguredNPc,
          m_SimObj->backendCurrPc(m_CId),
          ERROR_PC_ADDR,
          ERROR_PC_ADDR,
          ERROR_PC_ADDR,
          m_SimObj->correctHolder(m_CId).size(),
          m_SimObj->missHolder(m_CId).size(),
          InstTrace::isCorrectID(m_CurrId) ? "set-correct-id" : "set-miss-id");
    }
    // std::cout << "setcurrid: " << m_CurrId << " " << m_MissPredict << std::endl;
}

void PathHandler::clearMissQueue() {
  m_SimObj->missHolder(m_CId).clear();
  m_SimObj->missIdCursor(m_CId) = MISS_ID_FLAG;
  m_MissPredict = false;
}

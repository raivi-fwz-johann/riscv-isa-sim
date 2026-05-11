/**
 * @file InstInfoHolder.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "InstInfoHolder.hpp"

#include <stdexcept>
#include <cassert>

#include <iostream>

// static constexpr size_t DEFAULT_HOLD_SIZE = 2000;

InstInfoHolder::InstInfoHolder() {}

void InstInfoHolder::insertInst(InstTrace &&Inst) {
  if (m_Insts.size() and Inst.getId() != m_Insts.back().getId() + 1) {
    std::cerr << "error! incoming id: " << Inst.getId() << ", expected id: " << m_Insts.back().getId() + 1 << std::endl;
    throw std::runtime_error("Only support continue instruction id!");
  }
  m_Insts.push_back(std::forward<InstTrace>(Inst));
  m_CurrInst = m_Insts.rbegin();
  setInDummyHead(false); /* insertInst always means a new step. */
}

InstUserPtr InstInfoHolder::getFrontInst() const {
  if (not size()) {
    return nullptr;
  }
  return &m_Insts.front();
}

InstUserPtr InstInfoHolder::getLastInst() const {
  if (not size()) {
    return nullptr;
  }
  return &m_Insts.back();
}

void InstInfoHolder::freeInst(InstUserPtr &InstToFree) {
  if (not InstToFree) {
    return;
  }
  // if (size()) {
  //   std::cout << "###" << InstToFree->getId() << " " << m_Insts.front().getId() << std::endl;
  // }
  auto IId = InstToFree->getId();
  freeInst(IId);
  
  InstToFree = nullptr;
}

void InstInfoHolder::freeInst(uint64_t IId) {
  if (not size()) {
    throw std::runtime_error("No instruction to free!");
  }
  if (IId != m_Insts.front().getId()) {
    throw std::runtime_error("Only support free inst in order, current id to free: " + std::to_string(IId) +
                             ", expected id to free: " + std::to_string(m_Insts.front().getId()));
  }
  {
    const auto &inst = m_Insts.front();
    auto trap = inst.GetTrapInfo();
    std::cout << "modelDebug holderFreeInst"
              << " free_id=0x" << std::hex << IId
              << " size=" << std::dec << m_Insts.size()
              << " in_dummy=" << static_cast<int>(m_InDummyHead)
              << " is_curr=" << static_cast<int>(IId == m_CurrInst->getId())
              << " id=0x" << std::hex << inst.getId()
              << " correct=" << static_cast<int>(inst.isCorrect())
              << " first_miss=" << static_cast<int>(inst.isFirstMiss())
              << " rvc=" << static_cast<int>(inst.isRvc())
              << " load=" << static_cast<int>(inst.isLoad())
              << " store=" << static_cast<int>(inst.isStore())
              << " pc=0x" << inst.getPc()
              << " pc_paddr=0x" << inst.getPcPAddr()
              << " pc_paddr2=0x" << inst.getPcPAddr2()
              << " npc=0x" << inst.getNPc()
              << " bits=0x" << inst.getBits()
              << " inst_len=" << std::dec << inst.getInstLen()
              << " in_trap=" << static_cast<int>(inst.inTrap())
              << " in_wfi=" << static_cast<int>(inst.inWFI())
              << " trap_cause=0x" << std::hex << trap.cause
              << " trap_tval=0x" << trap.tval
              << " trap_tval2=0x" << trap.tval2
              << " trap_has_tval2=" << static_cast<int>(trap.has_tval2)
              << " perfect=" << static_cast<int>(inst.perfect())
              << std::endl;
  }
  if (IId == m_CurrInst->getId()) {
    /* This means that after resolve to IId, inst IId is commited, so we are in dummy head now. */
    m_InDummyHead = true;
    --m_CurrInst;
  }
  m_Insts.pop_front();
}

size_t InstInfoHolder::size() const {
  return m_Insts.size();
}

void InstInfoHolder::popUntil(uint64_t IId) {
  while (size()) {
    bool UpdateIter = false;
    auto RIter = m_Insts.rbegin();
    auto &FinalElm = m_Insts.back();
    // std::cout << FinalElm.getId() << std::endl;
    if (FinalElm.getId() <= IId) {
      break;
    }
    if (m_CurrInst == RIter or m_CurrInst == ++RIter) {
      UpdateIter = true;
    }
    m_Insts.pop_back();
    if (UpdateIter) {
      m_CurrInst = m_Insts.rbegin();
    }
    // std::cout << IId << " " << m_CurrInst->getId() << std::endl;
  }
}

void InstInfoHolder::setCurrInst(uint64_t Id) {
  if (not size() or Id < m_Insts.front().getId() or Id > m_Insts.back().getId()) {
    throw std::runtime_error(std::to_string(Id) + ", No such inst!");
  }
  m_InDummyHead = false;

  for (auto iter = m_Insts.rbegin(); iter != m_Insts.rend(); ++iter) {
    if (iter->getId() == Id) {
      m_CurrInst = iter;
      break;
    }
  }
}

InstUserPtr InstInfoHolder::getCurrInst() const {
  if (not size()) {
    return nullptr;
  }
  return &*m_CurrInst;
}

InstUserPtr InstInfoHolder::getNextInst() const {
  if (not size()) {
    return nullptr;
  }
  if (m_CurrInst == m_Insts.rbegin()) {
    return nullptr;
  }
  auto tmp = m_CurrInst;
  --tmp;
  return &*(tmp);
}

size_t InstInfoHolder::step(size_t N) {
  if (not size()) {
    return 0;
  }
  auto OriN = N;
  if (m_InDummyHead) {
    m_InDummyHead = false;
    N -= 1;
  }
  while (N) {
    if (m_CurrInst == m_Insts.rbegin()) {
      break;
    }
    --m_CurrInst;
    --N;
  }

  return OriN - N;
}

void InstInfoHolder::clear() {
  m_Insts.clear();
  m_InDummyHead = false;
}

InstUserPtr InstInfoHolder::getByPc(uint64_t pc) const {
  InstUserPtr res = nullptr;
  for (const auto &inst : m_Insts) {
    if (pc == inst.getPc()) {
      res = &inst;
      break;
    }
  }
  return res;
}
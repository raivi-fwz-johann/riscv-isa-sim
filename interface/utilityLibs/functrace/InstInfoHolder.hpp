/**
 * @file InstInfoHolder.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <cstdint>
#include <vector>
#include <list>

#include "functrace/InstTrace.hpp"

class InstInfoHolder {
public:
  InstInfoHolder();

  void insertInst(InstTrace &&Inst);
  InstUserPtr getFrontInst() const;
  InstUserPtr getLastInst() const;
  void freeInst(InstUserPtr &InstToFree);
  void freeInst(uint64_t IId);

  size_t size() const;

  void popUntil(uint64_t IId);

  void setCurrInst(uint64_t IId);
  InstUserPtr getCurrInst() const;
  InstUserPtr getNextInst() const;

  size_t step(size_t N);

  void clear();

  InstUserPtr getByPc(uint64_t pc) const;

  bool has(uint64_t IId) const {
    return size() and (IId >= m_Insts.front().getId() and IId <= m_Insts.back().getId());
  }

  bool inDummyHead() const { return m_InDummyHead; }
  void setInDummyHead(bool val) { m_InDummyHead = val; }

private:
  std::list<InstTrace> m_Insts;
  std::list<InstTrace>::reverse_iterator m_CurrInst;
  bool m_InDummyHead{false};
};
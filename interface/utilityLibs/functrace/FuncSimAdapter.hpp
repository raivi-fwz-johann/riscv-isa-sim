/**
 * @file FuncSimAdapter.hpp
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-12-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "Memory.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "functrace/InstTrace.hpp"

#define INST_COUNT_TO_LOG 10000000

class InstInfoHolder;

class FuncSimAdapter {
public:
  virtual ~FuncSimAdapter() = default;

  virtual void init(const std::string &ArgsStr) = 0;
  virtual void init(const std::vector<std::string> &Args) = 0;
  virtual void initROICount(int num) = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void waitStop() = 0;
  virtual bool done() const = 0;
  virtual size_t step(size_t n, uint32_t CId = 0) = 0;
  virtual void resetNPc(uint64_t NPc, uint32_t CId = 0) = 0;
  virtual InstUserPtr reqInst(uint32_t CId = 0) = 0;
  virtual InstUserPtr requestInst(uint64_t expected_pc, uint32_t CId = 0) = 0;
  virtual void freeInst(InstUserPtr &InstPtr, uint32_t CId = 0) = 0;
  virtual void freeInst(uint64_t IId, uint32_t CId = 0) = 0;

  /**
   * @brief Used in function model
   */
  virtual std::shared_ptr<InstTrace> &takeInst(uint32_t CId = 0) = 0;
  virtual void resolve(uint64_t InstUId, uint32_t CId = 0) = 0;
  virtual void replay(uint64_t InstUId, uint32_t CId = 0) = 0;
  virtual InstTrace fetchInstOnly(uint64_t Pc, uint32_t CId = 0,
                                  uint64_t IId = INVALID_INST_ID) = 0;
  virtual uint64_t vaddr2paddr(uint64_t vaddr, uint32_t CId) const = 0;
  virtual bool inROI(uint32_t cid = 0) const = 0;
  virtual uint64_t getCurrPc(uint32_t cid = 0) const = 0;
  virtual uint64_t getConfiguredNPc(uint32_t cid = 0) const = 0;

  virtual InstInfoHolder &correctHolder(uint32_t CId) = 0;
  virtual const InstInfoHolder &correctHolder(uint32_t CId) const = 0;
  virtual InstInfoHolder &missHolder(uint32_t CId) = 0;
  virtual const InstInfoHolder &missHolder(uint32_t CId) const = 0;
  virtual uint64_t &missIdCursor(uint32_t CId) = 0;
  virtual uint64_t backendCurrPc(uint32_t CId) const = 0;
};

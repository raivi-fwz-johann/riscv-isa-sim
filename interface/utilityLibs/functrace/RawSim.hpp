#pragma once

#include "functrace/InstTrace.hpp"

/**
 * @brief An interface for simply stepping simulator and acquering information.
 * 
 */
class RawSim {
public:
  virtual ~RawSim() {}

  /**
   * @brief Pass arguments and initialize simulator such as spike or qemu.
   */
  virtual void init(const std::string &ArgsStr) = 0;

  /**
   * @brief Start the simulator, call this function after init() and before other executing relative functions.
   */
  virtual void start() = 0;

  /**
   * @brief Stop the simulator.
   */
  virtual void stop() = 0;

  /**
   * @brief Whether the simulator is done.
   */
  virtual bool done() const = 0;

  /**
   * @brief Execute n step in core CId, only support n == 1.
   * @return Step count that actually do.
   */
  virtual size_t step(size_t n, uint32_t CId) = 0;

  /**
   * @brief Fill the last instruction trace of core CId into data.
   * @return 0 means success, -1 means fail.
   */
  virtual int record(InstTrace &data, uint32_t CId) = 0;

  /**
   * @brief Get InstTrace from input pc in core CId, and set InstTrace id to IId.
   */
  virtual InstTrace fetchInstOnly(uint64_t Pc, uint32_t CId, uint64_t IId) = 0;

  /**
   * @brief convert virtual address to physical address.
   */
  virtual uint64_t vaddr2paddr(uint64_t vaddr, uint32_t CId) = 0;

  /**
   * @brief get mmu trace
   */
  virtual MmuTrace getMmuTrace(uint32_t CId) = 0;

  /**
   * @brief Setup ROI usage.
   */
  virtual void setupROI(bool val) = 0;

  /**
   * @brief Whether the core cid in region of interest.
   */
  virtual bool inROI(uint32_t cid) const = 0;

  /**
   * @brief Get cores count of simulator.
   */
  virtual size_t nproc() const = 0;

  /**
   * @brief Get current pc of core cid.
   */
  virtual uint64_t getCurrPc(uint32_t cid) const = 0;

  /**
   * @brief Whether core CId is in trap.
   */
  virtual bool inTrap(uint32_t CId) const = 0;

  /**
   * @brief Whether core CId is in WFI.
   */
  virtual bool inWFI(uint32_t CId) const = 0;

  /**
   * @brief For command extension.
   * @return 0 means success, others mean fail
   */
  virtual int command(const std::string &cmd) { return 0; }
};
/**
 * @file InsnTrace.hpp
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-12-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <cstdint>
#include <limits>
#include <vector>
#include <iostream>

#include "functrace/Memory.hpp"

// #include "../../riscv-isa-sim/riscv/processor.h"

struct XlateFlags {
  bool forced_virt : 1;
  bool hlvx : 1;
  bool lr : 1;
  bool ss_access : 1;
  bool clean_inval : 1;
  bool enable_misalign : 1;

  bool is_special_access() const { return forced_virt || hlvx || lr || ss_access || clean_inval; }
};

struct MmuTrace {
  uint64_t paddr = 0;
  uint64_t pte_paddr[5] = {0};
  int8_t levels = -1;
  uint64_t excp_cause;
  XlateFlags xf_log;
};

struct TrapInfo {
  uint64_t cause, tval, tval2;
  bool in_trap, has_tval2;
};

#define INVALID_INST_ID std::numeric_limits<uint64_t>::max()

template <typename T> class LogIterator {
  using ContainerType = std::vector<T>;

public:
  LogIterator() {}
  LogIterator(const ContainerType &Cont) { m_Container = &Cont; }
  const T &operator*() const { return m_Container->at(m_Idx); }
  const T *operator->() const { return &m_Container->at(m_Idx); }
  void operator++() { m_Idx++; }
  bool end() const { return not m_Container or m_Idx >= m_Container->size(); }
  void seekToBeg() { m_Idx = 0; }

private:
  size_t m_Idx = 0;
  const ContainerType *m_Container = nullptr;
};

struct Float128 {
  uint64_t v[2];
};

struct RegWrite {
  RegWrite() = default;
  RegWrite(uint64_t Regnum, Float128 Data, char *&&DataBuf, size_t Bytes);
  RegWrite(const RegWrite &&That) = delete;
  RegWrite(RegWrite &&That);
  ~RegWrite();

  uint64_t getRegnum() const { return m_Regnum; }
  const Float128 &getData() const { return m_Data; }
  const char *getVRegData() const { return m_DataBuf; }
  size_t size() const { return m_Bytes; }

private:
  uint64_t m_Regnum = 0;
  Float128 m_Data = {0};
  char *m_DataBuf = nullptr;
  size_t m_Bytes = 0;
};
using RegWriteIter = LogIterator<RegWrite>;

struct MemRead {
  MemRead() = default;
  MemRead(uint64_t VAddr, uint64_t PAddr, size_t Bytes);
  MemRead(uint64_t VAddr, uint64_t PAddr, size_t Bytes, uint64_t Val);
  MemRead(uint64_t VAddr, size_t Bytes, uint64_t Val, uint64_t PAddr, uint64_t PAddr2);

  uint64_t vAddr() const { return m_VAddr; }
  uint64_t pAddr() const { return m_PAddr; }
  size_t size() const { return m_Bytes; }
  uint64_t value() const { return m_Val; }

 private:
  uint64_t m_VAddr = 0;
  uint64_t m_PAddr = 0;
  uint64_t m_PAddr2 = 0;
  size_t m_Bytes = 0;
  uint64_t m_Val = 0;
};
using MemReadIter = LogIterator<MemRead>;

struct MemWrite {
  MemWrite() = default;
  MemWrite(uint64_t VAddr, uint64_t PAddr, size_t Bytes, uint64_t Val);
  MemWrite(uint64_t VAddr, size_t Bytes, uint64_t Val, uint64_t PAddr, uint64_t PAddr2);

  uint64_t vAddr() const { return m_VAddr; }
  uint64_t pAddr() const { return m_PAddr; }
  size_t size() const { return m_Bytes; }
  uint64_t value() const { return m_Val; }

private:
  uint64_t m_VAddr = 0;
  uint64_t m_PAddr = 0;
  uint64_t m_PAddr2 = 0;
  size_t m_Bytes = 0;
  uint64_t m_Val = 0;
};
using MemWriteIter = LogIterator<MemWrite>;

struct InstStatus {
  size_t m_Prv;
  bool m_V;
  bool m_DebugMode;
  size_t m_MStatus;
};

#define ERROR_ID std::numeric_limits<uint64_t>::max()
#define ERROR_PC_ADDR std::numeric_limits<uint64_t>::max()

#define MISS_ID_FLAG (uint64_t(1) << 63)

inline int64_t ConvertId(uint64_t id) {
  int64_t res = 0;
  if (id & MISS_ID_FLAG) {
    res = -(int64_t)(id - MISS_ID_FLAG + 1);
  } else {
    res = (int64_t)id;
  }
  return res;
}

#if defined (FULL_TRACE)
#define INST_ALIGNAS
#elif defined (MEM_TRACE)
#define INST_ALIGNAS
#else
#define INST_ALIGNAS alignas(64)
#endif

class INST_ALIGNAS InstTrace {
public:
  static bool isCorrectID(uint64_t id) {
    return (id & MISS_ID_FLAG) == 0;
  }

  InstTrace(uint64_t Id);
  InstTrace(uint64_t Id, uint64_t pc, uint64_t Bits = 0, uint64_t PPN = ERROR_PC_ADDR);
  InstTrace(const InstTrace &&That) = delete;
  InstTrace(InstTrace &&That) = default;
  InstTrace &operator=(InstTrace &&That) = default;
  ~InstTrace();
  bool isCorrect() const;
  bool isFirstMiss() const;
  uint64_t getId() const;
  void setId(uint64_t id);
  bool isRvc() const;
  bool isLoad() const;
  bool isStore() const;
  uint64_t getPc() const;
  uint64_t getPcPAddr() const;
  uint64_t getPcPAddr2() const;
  uint64_t getNPc() const;
  uint64_t getBits() const;
  uint32_t getInstLen() const;
  bool inTrap() const;
  bool inWFI() const;
#if defined (FULL_TRACE)
  uint64_t getSatp() const { return satp_; }
  uint64_t getAsid() const { return m_Asid; }
  InstStatus getStatus() const { return m_Status; }
  RegWriteIter getRegWs() const { return RegWriteIter(m_RegWs);}
  MemReadIter getMemRs() const { return MemReadIter(m_MemRs); }
  MemWriteIter getMemWs() const { return MemWriteIter(m_MemWs); }
#elif defined (MEM_TRACE)
  RegWriteIter getRegWs() const { return RegWriteIter();}
  MemReadIter getMemRs() const { return MemReadIter(m_MemRs); }
  MemWriteIter getMemWs() const { return MemWriteIter(m_MemWs); }
#else
  RegWriteIter getRegWs() const { return RegWriteIter();}
  MemReadIter getMemRs() const { return MemReadIter(); }
  MemWriteIter getMemWs() const { return MemWriteIter(); }
#endif

  bool perfect() const;

  void reset();

  /**
   * @brief Get the Trap Info object
   *
   */
  TrapInfo GetTrapInfo() const {
    return TrapInfo{.cause = cause_, .tval = tval_, .tval2 = tval2_, .in_trap = m_InTrap, .has_tval2 = has_tval2_};
  }

  void SetNPC(uint64_t npc) { m_NPc = npc; }

 public:
  MmuTrace m_mmuTrace;

 private:
  void free();

  uint64_t m_Id = 0;
  uint64_t m_Pc = ERROR_PC_ADDR;
  uint64_t m_NPc = ERROR_PC_ADDR;
  uint64_t m_Bits = 0;
  struct PPN_t {
    uint64_t val = ERROR_PC_ADDR;
    PPN_t() = default;
    PPN_t(uint64_t val) : val(val) {}
    PPN_t(const PPN_t &that) = default;
    PPN_t(PPN_t &&that) {
      val = that.val;
      that.val = ERROR_PC_ADDR;
    }
    PPN_t &operator=(const PPN_t &that) = default;
    PPN_t &operator=(PPN_t &&that) {
      val = that.val;
      that.val = ERROR_PC_ADDR;
      return *this;
    }
    bool operator==(uint64_t val) const {
      return this->val == val;
    }
    bool operator!=(uint64_t val) const {
      return this->val != val;
    }
  } m_PPN;
  PPN_t m_PPN2;

  /* Trap relative members */
  bool m_InTrap{false};
  bool has_tval2_{false};
  uint64_t cause_{0};
  uint64_t tval_{0};
  uint64_t tval2_{0};
  /* Trap relative members end */
#if defined (FULL_TRACE)
  uint64_t satp_ = 0;
  uint64_t m_Asid = 0;
  uint64_t m_LastInstPriv = 0;
  int m_LastInstXLen = 0;
  int m_LastInstFLen = 0;
  InstStatus m_Status;
  std::vector<RegWrite> m_RegWs;
  std::vector<MemRead> m_MemRs;
  std::vector<MemWrite> m_MemWs;
#elif defined (MEM_TRACE)
  std::vector<MemRead> m_MemRs;
  std::vector<MemWrite> m_MemWs;
#endif

  /* System status */
  bool m_InWFI{false};

  friend class InstTraceModifier;
  friend class FuncSimAdapter;
  friend class SpikeSimObjHooker;
  friend class InstInfoHolder;
  friend class InstDebugger;
  friend class RawSpike;
  friend class RawQemu;
};
using InstUserPtr = const InstTrace *;
using InstTracePtr = std::shared_ptr<InstTrace>;

class InstTraceModifier {
public:
  InstTraceModifier(InstTrace &inst) : inst_(inst) {}

  void setNpc(uint64_t val) {
    inst_.m_NPc = val;
  }
  void clearRegWrites() {
#if defined (FULL_TRACE)
    inst_.m_RegWs.clear();
#endif
  }

  void addRegWrite(RegWrite &&elm) {
#if defined (FULL_TRACE)
    inst_.m_RegWs.push_back(std::forward<RegWrite>(elm));
#endif
  }

  void clearMemWrites() {
#if defined (FULL_TRACE)
    inst_.m_MemWs.clear();
#endif
  }

  void addMemWrite(MemWrite &&elm) {
#if defined (FULL_TRACE)
    inst_.m_MemWs.push_back(std::forward<MemWrite>(elm));
#endif
  }

private:
  InstTrace &inst_;
};

class InstDebugger {
public:
  InstDebugger(const InstTrace &Inst);

  uint64_t getStatePc() const;

  std::vector<std::tuple<std::string, int, size_t *>> getRegWs() const;
  std::vector<std::tuple<size_t, int, size_t>> getMemRs() const;
  std::vector<std::tuple<size_t, int, size_t *, size_t>> getMemWs() const;

private:
  const InstTrace &m_Inst;
};

std::ostream &operator<<(std::ostream &os, const InstTrace &data);

/**
 * @file InsnTrace.cpp
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-12-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "InstTrace.hpp"

#include <sstream>
#include <stdexcept>

#define insn_length(x) \
  (((x) & 0x03) < 0x03 ? 2 : \
   ((x) & 0x1f) < 0x1f ? 4 : \
   ((x) & 0x3f) < 0x3f ? 6 : \
   8)

RegWrite::RegWrite(uint64_t Regnum, Float128 Data, char *&&DataBuf,
                   size_t Bytes)
    : m_Regnum(Regnum), m_Data(Data), m_DataBuf(DataBuf), m_Bytes(Bytes) {
  DataBuf = nullptr;
}

RegWrite::RegWrite(RegWrite &&That) {
  m_Regnum = That.m_Regnum;
  m_Data = That.m_Data;
  m_DataBuf = That.m_DataBuf;
  That.m_DataBuf = nullptr;
}

RegWrite::~RegWrite() {
  if (m_DataBuf) {
    delete m_DataBuf;
  }
}

MemRead::MemRead(uint64_t VAddr, uint64_t PAddr, size_t Bytes) {
  m_VAddr = VAddr;
  m_PAddr = PAddr;
  m_Bytes = Bytes;
}

MemRead::MemRead(uint64_t VAddr, uint64_t PAddr, size_t Bytes, uint64_t Val) {
  m_VAddr = VAddr;
  m_PAddr = PAddr;
  m_Bytes = Bytes;
  m_Val = Val;
}

MemRead::MemRead(uint64_t VAddr, size_t Bytes, uint64_t Val, uint64_t PAddr, uint64_t PAddr2) {
  m_VAddr = VAddr;
  m_PAddr = PAddr;
  m_PAddr2 = PAddr2;
  m_Bytes = Bytes;
  m_Val = Val;
}

MemWrite::MemWrite(uint64_t VAddr, uint64_t PAddr, size_t Bytes, uint64_t Val) {
  m_VAddr = VAddr;
  m_PAddr = PAddr;
  m_Bytes = Bytes;
  m_Val = Val;
}

MemWrite::MemWrite(uint64_t VAddr, size_t Bytes, uint64_t Val, uint64_t PAddr, uint64_t PAddr2) {
  m_VAddr = VAddr;
  m_PAddr = PAddr;
  m_PAddr2 = PAddr2;
  m_Bytes = Bytes;
  m_Val = Val;
}

InstTrace::InstTrace(uint64_t Id) : m_Id(Id) {}

InstTrace::InstTrace(uint64_t Id, uint64_t pc, uint64_t Bits, uint64_t PPN) 
    : m_Id(Id), m_Pc(pc), m_Bits(Bits), m_PPN(PPN), vpc(pc), ppc(PPN), instr_raw(uint32_t(Bits)) {
  newTrace.vpc = pc;
  newTrace.ppc = PPN;
  newTrace.instr_raw = static_cast<uint32_t>(Bits);
}


InstTrace::~InstTrace() { free(); }

bool InstTrace::isCorrect() const { return isCorrectID(getId()); }
bool InstTrace::isFirstMiss() const { return getId() == MISS_ID_FLAG; }

uint64_t InstTrace::getId() const { return m_Id; }
void InstTrace::setId(uint64_t id) { m_Id = id; }

bool InstTrace::isRvc() const { return getInstLen() == 2; }

#if defined (FULL_TRACE) || defined (MEM_TRACE)
bool InstTrace::isLoad() const { return not m_MemRs.empty(); }

bool InstTrace::isStore() const { return not m_MemWs.empty(); }
#else
bool InstTrace::isLoad() const { return false; }

bool InstTrace::isStore() const { return false; }
#endif

uint64_t InstTrace::getPc() const { return m_Pc; }

uint64_t InstTrace::getPcPAddr() const {
  return m_PPN.val;
}

uint64_t InstTrace::getPcPAddr2() const { return m_PPN2.val; }

uint64_t InstTrace::getNPc() const {
  return m_NPc;
}

uint64_t InstTrace::getBits() const {
  return m_Bits;
}

uint32_t InstTrace::getInstLen() const {
  return insn_length(m_Bits);
}

bool InstTrace::inTrap() const { return m_InTrap; }

bool InstTrace::inWFI() const { return m_InWFI; }

bool InstTrace::perfect() const { return m_PPN != ERROR_PC_ADDR; }

void InstTrace::reset() {
  m_Id = 0;
  m_Pc = ERROR_PC_ADDR;
  m_NPc = ERROR_PC_ADDR;
  m_Bits = 0;
  m_PPN = ERROR_PC_ADDR;
#if defined (FULL_TRACE)
  m_RegWs.clear();
  m_MemRs.clear();
  m_MemWs.clear();
#elif defined (MEM_TRACE)
  m_MemRs.clear();
  m_MemWs.clear();
#endif
  m_mmuTrace = {};
  newTrace = {};
  vpc = ERROR_PC_ADDR;
  ppc = ERROR_PC_ADDR;
  instr_raw = 0;
  fetch_ptw.clear();
  src_regs.clear();
  dst_regs.clear();
  vtype = 0;
  vl = 0;
  vstart = 0;
  active_mask = 0;
  mem_ops.clear();
  branch_taken = false;
  next_vpc = ERROR_PC_ADDR;
  exception = 0;

}

void InstTrace::free() {
  m_Bits = 0;
  m_PPN = ERROR_PC_ADDR;
}

std::ostream &operator<<(std::ostream &os, const InstTrace &data) {
  os << "id: " << data.getId() << std::hex << ", pc: 0x" << data.getPc() << ", pc_paddr: 0x" << data.getPcPAddr()
     << ", npc: 0x" << data.getNPc() << ", opcode: 0x" << data.getBits() << std::dec;
  return os;
}

std::string InstTrace::toTraceString() const {
  const auto& trace = newTrace;
  std::ostringstream os;
  os << std::hex;
  os << "vpc=0x" << trace.vpc
     << " ppc=0x" << trace.ppc
     << " instr_raw=0x" << trace.instr_raw
     << " next_vpc=0x" << trace.next_vpc
     << " branch_taken=" << std::dec << trace.branch_taken
     << " exception=" << trace.exception
     << " fetch_ptw=" << trace.fetch_ptw.size()
     << " src_regs=" << trace.src_regs.size()
     << " dst_regs=" << trace.dst_regs.size()
     << " mem_ops=" << trace.mem_ops.size()
     << " vtype=0x" << std::hex << trace.vtype
     << " vl=" << std::dec << trace.vl
     << " vstart=" << trace.vstart
     << " active_mask=0x" << std::hex << trace.active_mask;

  if (!trace.fetch_ptw.empty()) {
    os << " fetch_steps=[";
    for (size_t i = 0; i < trace.fetch_ptw.size(); ++i) {
      if (i) os << ",";
      os << "{paddr:0x" << trace.fetch_ptw[i].paddr << ",pte:0x" << trace.fetch_ptw[i].pte << "}";
    }
    os << "]";
  }

  if (!trace.dst_regs.empty()) {
    os << " dst=[";
    for (size_t i = 0; i < trace.dst_regs.size(); ++i) {
      if (i) os << ",";
      os << "0x" << std::hex << trace.dst_regs[i].flat_id;
    }
    os << "]";
  }

  if (!trace.mem_ops.empty()) {
    os << " mem=[";
    for (size_t i = 0; i < trace.mem_ops.size(); ++i) {
      if (i) os << ",";
      os << "{vaddr:0x" << std::hex << trace.mem_ops[i].vaddr
         << ",paddr:0x" << trace.mem_ops[i].paddr
         << ",size:" << std::dec << unsigned(trace.mem_ops[i].size_bytes)
         << ",ptw:" << trace.mem_ops[i].ptw_steps.size() << "}";
    }
    os << "]";
  }

  return os.str();
}

#include "SpikeSimObjSync.hpp"

#include <algorithm>
#include <iostream>

#include "RawSpike.hpp"

#define insn_length(x) \
  (((x) & 0x03) < 0x03 ? 2 : \
   ((x) & 0x1f) < 0x1f ? 4 : \
   ((x) & 0x3f) < 0x3f ? 6 : \
   8)

SpikeSimObjSync::SpikeSimObjSync() : m_SimImpl(std::make_unique<RawSpike>()) {}

SpikeSimObjSync::~SpikeSimObjSync() { stop(); }

void SpikeSimObjSync::init(const std::string &ArgsStr) {
  m_SimImpl->init(ArgsStr);
  m_CoreInfos = std::vector<CoreInfo>(m_SimImpl->nproc());
  for (size_t i = 0; i < m_SimImpl->nproc(); ++i) {
    m_CoreInfos[i].m_PathHandler.init(this, i);
    m_CoreInfos[i].m_NewInst = std::make_shared<InstTrace>(INVALID_INST_ID);
  }
}

void SpikeSimObjSync::init(const std::vector<std::string> &Args) {
  std::string ArgsStr;
  for (const auto &arg : Args) {
    ArgsStr += arg + ' ';
  }
  std::cout << "args: " << ArgsStr << std::endl;
  init(ArgsStr);
}

void SpikeSimObjSync::initROICount(int num) { m_SimImpl->setupROI(num > 0); }

void SpikeSimObjSync::start() { m_SimImpl->start(); }

void SpikeSimObjSync::stop() {
  if (m_SimImpl) {
    m_SimImpl->stop();
  }
}

bool SpikeSimObjSync::done() const { return m_SimImpl->done(); }

size_t SpikeSimObjSync::step(size_t n, uint32_t CId) { return stepSync(n, CId); }

size_t SpikeSimObjSync::stepSync(size_t n, uint32_t CId) {
  if (n > 1) {
    throw std::runtime_error("Only support step 1");
  }
  auto ignore_step = std::min(n, m_CoreInfos[CId].m_stepToIgnore);
  n -= ignore_step;
  m_CoreInfos[CId].m_stepToIgnore -= ignore_step;
  if (n == 0) {
    return 0;
  }

  std::unique_lock<std::mutex> lck(m_Mtx);

  if (m_CoreInfos[CId].m_PathHandler.isNewStep()) {
    if (m_CoreInfos[CId].m_PathHandler.isMissPredict()) {
      auto pc = m_CoreInfos[CId].m_PathHandler.getConfiguredNPc();
      *m_CoreInfos[CId].m_NewInst =
          fetchInstOnly(pc, CId, m_CoreInfos[CId].m_MissIdToAlloc++);
      m_CoreInfos[CId].m_NewInstValid = true;
      return 1;
    }

    size_t steps_done = 0;
    int record_err = 0;
    do {
      steps_done += m_SimImpl->step(n, CId);
      m_CoreInfos[CId].m_NewInst->reset();
      m_CoreInfos[CId].m_NewInst->m_Id = m_CoreInfos[CId].m_IdToAlloc;
      record_err = m_SimImpl->record(*m_CoreInfos[CId].m_NewInst, CId);
      m_CoreInfos[CId].m_NewInstValid = (record_err == 0);
      if (m_CoreInfos[CId].m_NewInstValid) {
        m_CoreInfos[CId].m_IdToAlloc += 1;
      }
      m_CoreInfos[CId].m_NewInst->m_mmuTrace = m_SimImpl->getMmuTrace(CId);
    } while (record_err < 0 and not m_SimImpl->done());
    return steps_done;
  }

  if (m_CoreInfos[CId].m_PathHandler.isMissPredict() and
      m_CoreInfos[CId].m_PathHandler.inCorrectId()) {
    auto pc = m_CoreInfos[CId].m_PathHandler.getConfiguredNPc();
    *m_CoreInfos[CId].m_NewInst =
        fetchInstOnly(pc, CId, m_CoreInfos[CId].m_MissIdToAlloc++);
    m_CoreInfos[CId].m_NewInstValid = true;
    return 1;
  }

  auto &holder = m_CoreInfos[CId].m_PathHandler.inCorrectId()
                     ? m_CoreInfos[CId].m_IHolder
                     : m_CoreInfos[CId].m_MissIHolder;
  auto stepped_num = holder.step(n);
  if (holder.getCurrInst()) {
    m_CoreInfos[CId].m_PathHandler.setCurrId(holder.getCurrInst()->getId());
  }
  return stepped_num;
}

void SpikeSimObjSync::resetNPc(uint64_t NPc, uint32_t CId) {
  if (m_CoreInfos[CId].m_NewInst and m_CoreInfos[CId].m_NewInstValid) {
    throw std::runtime_error("please reqInst before");
  }
  m_CoreInfos[CId].m_PathHandler.configurePath(NPc);
}

InstUserPtr SpikeSimObjSync::reqInst(uint32_t CId) {
  InstUserPtr res = nullptr;
  if (m_CoreInfos[CId].m_NewInst and m_CoreInfos[CId].m_NewInstValid) {
    auto &holder = m_CoreInfos[CId].m_PathHandler.isMissPredict()
                       ? m_CoreInfos[CId].m_MissIHolder
                       : m_CoreInfos[CId].m_IHolder;
    holder.insertInst(std::move(*m_CoreInfos[CId].m_NewInst));
    m_CoreInfos[CId].m_PathHandler.setCurrId(holder.getCurrInst()->getId());
    m_CoreInfos[CId].m_NewInstValid = false;
    res = holder.getCurrInst();
    holder.setInDummyHead(false);
  } else {
    auto &holder = m_CoreInfos[CId].m_PathHandler.inCorrectId()
                       ? m_CoreInfos[CId].m_IHolder
                       : m_CoreInfos[CId].m_MissIHolder;
    res = holder.getCurrInst();
    holder.setInDummyHead(false);
  }

  if (res && res->m_NPc == ERROR_PC_ADDR) {
    throw std::runtime_error("res && res->m_NPc == ERROR_PC_ADDR");
  }
  return res;
}

InstUserPtr SpikeSimObjSync::requestInst(uint64_t expected_pc, uint32_t CId) {
  auto res = reqInst(CId);
  if (res and expected_pc != res->getPc())
    [[unlikely]] {
      std::cout << "requestInst error: expected pc: 0x" << std::hex
                << expected_pc << " getting pc: 0x" << res->getPc()
                << " configured npc: 0x" << getConfiguredNPc(CId) << std::dec
                << " correct inst queue size: "
                << m_CoreInfos[CId].m_IHolder.size()
                << " previous rollback id: "
                << ConvertId(m_CoreInfos[CId].prev_rollback_id) << std::endl;
      if (m_CoreInfos[CId].m_IHolder.size()) {
        std::cout
            << "current front inst id: "
            << m_CoreInfos[CId].m_IHolder.getFrontInst()->getId()
            << " current last inst id: "
            << m_CoreInfos[CId].m_IHolder.getLastInst()->getId() << std::endl;
      }
    }
  return res;
}

void SpikeSimObjSync::freeInst(InstUserPtr &InstPtr, uint32_t CId) {
  if (InstPtr == nullptr) {
    return;
  }
  if (InstPtr->getId() >= m_CoreInfos[CId].m_IdToAlloc) {
    throw std::runtime_error("Can not free miss inst");
  }
  m_CoreInfos[CId].m_IHolder.freeInst(InstPtr);
}

void SpikeSimObjSync::freeInst(uint64_t IId, uint32_t CId) {
  if (IId >= m_CoreInfos[CId].m_IdToAlloc) {
    std::cout << "current front id: "
              << m_CoreInfos[CId].m_IHolder.getFrontInst()->getId()
              << std::endl;
    throw std::runtime_error("Can not free miss inst, free ID: " +
                             std::to_string(ConvertId(IId)) +
                             " corrent id end at: " +
                             std::to_string(m_CoreInfos[CId].m_IdToAlloc));
  }
  m_CoreInfos[CId].m_IHolder.freeInst(IId);
}

std::shared_ptr<InstTrace> &SpikeSimObjSync::takeInst(uint32_t CId) {
  return takeProducedInst(CId);
}

std::shared_ptr<InstTrace> &SpikeSimObjSync::takeProducedInst(uint32_t CId) {
  if (not (m_CoreInfos[CId].m_NewInst and m_CoreInfos[CId].m_NewInstValid)) {
    return m_Dummy;
  }
  m_CoreInfos[CId].m_NewInstValid = false;
  return m_CoreInfos[CId].m_NewInst;
}

void SpikeSimObjSync::resolve(uint64_t InstUId, uint32_t CId) {
  m_CoreInfos[CId].m_stepToIgnore = 0;
  rollback(InstUId, CId);
}

void SpikeSimObjSync::replay(uint64_t InstUId, uint32_t CId) {
  m_CoreInfos[CId].m_stepToIgnore = 1;
  rollback(InstUId, CId);
}

InstTrace SpikeSimObjSync::fetchInstOnly(uint64_t Pc, uint32_t CId, uint64_t IId) {
  auto res = m_SimImpl->fetchInstOnly(Pc, CId, IId);
  if (not res.perfect()) {
    auto ptr = m_CoreInfos[CId].m_IHolder.getByPc(Pc);
    if (ptr) {
      res.m_Bits = ptr->getBits();
      res.m_PPN = ptr->getPcPAddr();
      res.m_NPc = ptr->getNPc();
    } else {
      res.m_Bits = 0x1;
      res.m_NPc = res.m_Pc + insn_length(res.m_Bits);
    }
  } else {
    res.m_NPc = res.m_Pc + insn_length(res.m_Bits);
  }
  if (res.m_NPc == ERROR_PC_ADDR) {
    throw std::runtime_error("res.m_NPc == ERROR_PC_ADDR");
  }
  return res;
}

uint64_t SpikeSimObjSync::vaddr2paddr(uint64_t vaddr, uint32_t CId) const {
  return m_SimImpl->vaddr2paddr(vaddr, CId);
}

bool SpikeSimObjSync::inROI(uint32_t cid) const { return m_SimImpl->inROI(cid); }

uint64_t SpikeSimObjSync::getConfiguredNPc(uint32_t cid) const {
  return m_CoreInfos[cid].m_PathHandler.getConfiguredNPc();
}

uint64_t SpikeSimObjSync::getCurrPc(uint32_t cid) const {
  bool in_replay = m_CoreInfos[cid].m_stepToIgnore == 1;
  auto &holder = m_CoreInfos[cid].m_PathHandler.inCorrectId()
                     ? m_CoreInfos[cid].m_IHolder
                     : m_CoreInfos[cid].m_MissIHolder;

  auto next_inst = holder.getNextInst();
  if ((holder.size() == 0) or (next_inst == nullptr and not in_replay)) {
    return m_SimImpl->getCurrPc(cid);
  }
  auto curr_inst = holder.getCurrInst();
  return in_replay ? curr_inst->getPc() : next_inst->getPc();
}

void SpikeSimObjSync::rollback(uint64_t InstUId, uint32_t CId) {
  if (m_CoreInfos[CId].m_NewInst and m_CoreInfos[CId].m_NewInstValid) {
    throw std::runtime_error("please reqInst before");
  }
  m_CoreInfos[CId].prev_rollback_id = InstUId;
  bool is_correct_id = InstTrace::isCorrectID(InstUId);
  auto &inst_holder =
      is_correct_id ? m_CoreInfos[CId].m_IHolder : m_CoreInfos[CId].m_MissIHolder;

  m_CoreInfos[CId].m_NewInstValid = false;
  if (not inst_holder.size() and is_correct_id) {
    m_CoreInfos[CId].m_PathHandler.setCurrId(InstUId);
    m_CoreInfos[CId].m_PathHandler.setConfiguredNPc(m_SimImpl->getCurrPc(CId));
    inst_holder.setInDummyHead(true);
  } else if (inst_holder.has(InstUId)) {
    m_CoreInfos[CId].m_PathHandler.setCurrId(InstUId);
    inst_holder.setCurrInst(InstUId);
    m_CoreInfos[CId].m_PathHandler.setConfiguredNPc(
        inst_holder.getCurrInst()->getPc());
  } else if (is_correct_id) {
    m_CoreInfos[CId].m_PathHandler.setCurrId(InstUId);
    inst_holder.setCurrInst(inst_holder.getFrontInst()->getId());
    inst_holder.setInDummyHead(true);
  }
}

InstInfoHolder &SpikeSimObjSync::correctHolder(uint32_t CId) {
  return m_CoreInfos[CId].m_IHolder;
}

const InstInfoHolder &SpikeSimObjSync::correctHolder(uint32_t CId) const {
  return m_CoreInfos[CId].m_IHolder;
}

InstInfoHolder &SpikeSimObjSync::missHolder(uint32_t CId) {
  return m_CoreInfos[CId].m_MissIHolder;
}

const InstInfoHolder &SpikeSimObjSync::missHolder(uint32_t CId) const {
  return m_CoreInfos[CId].m_MissIHolder;
}

uint64_t &SpikeSimObjSync::missIdCursor(uint32_t CId) {
  return m_CoreInfos[CId].m_MissIdToAlloc;
}

uint64_t SpikeSimObjSync::backendCurrPc(uint32_t CId) const {
  return m_SimImpl->getCurrPc(CId);
}

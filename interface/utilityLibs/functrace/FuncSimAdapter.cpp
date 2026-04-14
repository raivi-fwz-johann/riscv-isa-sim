/**
 * @file FuncSimAdapter.cpp
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-12-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "FuncSimAdapter.hpp"

#include <sstream>
#include <iostream>

#define insn_length(x) \
  (((x) & 0x03) < 0x03 ? 2 : \
   ((x) & 0x1f) < 0x1f ? 4 : \
   ((x) & 0x3f) < 0x3f ? 6 : \
   8)

FuncSimAdapter &FuncSimAdapter::globalInstance() {
  static FuncSimAdapter SInstance;
  return SInstance;
}

FuncSimAdapter::FuncSimAdapter() {}

FuncSimAdapter::~FuncSimAdapter() {
}

void FuncSimAdapter::setFuncSim(RawSim *&&ptr) {
  m_SimImpl = ptr;
  ptr = nullptr;
}

void FuncSimAdapter::init(const std::string &ArgsStr) {
  m_SimImpl->init(ArgsStr);
  m_CoreInfos = std::vector<CoreInfo>(m_SimImpl->nproc());
  for (size_t i = 0; i < m_SimImpl->nproc(); ++i) {
    m_CoreInfos[i].m_PathHandler.init(this, i);
    m_CoreInfos[i].m_NewInst = std::make_shared<InstTrace>(INVALID_INST_ID);
  }
}

void FuncSimAdapter::init(const std::vector<std::string> &Args) {
  std::string ArgsStr;
  for (const auto &arg : Args) {
    ArgsStr += arg + ' ';
  }
  std::cout << "args: " << ArgsStr << std::endl;
  init(ArgsStr);
}

void FuncSimAdapter::initROICount(int num) {
  m_SimImpl->setupROI(num > 0);
}

void FuncSimAdapter::start() {
  m_SimImpl->start();
}

void FuncSimAdapter::stop() {
  m_SimImpl->stop();
}

bool FuncSimAdapter::done() const {
  return m_SimImpl->done();
}

size_t FuncSimAdapter::step(size_t n, uint32_t CId) {
  if (n > 1) {
    throw std::runtime_error("Only support step 1");
  }
  /* Ignore some step. It mainly to handle the difference between resolve and rollback so as to adapt to timing model usage. */
  auto ignore_step = std::min(n, m_CoreInfos[CId].m_stepToIgnore);
  n -= ignore_step;
  m_CoreInfos[CId].m_stepToIgnore -= ignore_step;
  if (n == 0) {
    // std::cout << "replay" << std::endl;
    return 0;
  }

  std::unique_lock<std::mutex> Lck(m_Mtx);

  if (m_CoreInfos[CId].m_PathHandler.isNewStep()) {
    if (m_CoreInfos[CId].m_PathHandler.isMissPredict()) {
      auto Pc = m_CoreInfos[CId].m_PathHandler.getConfiguredNPc();
      /* Only fetch insn in miss-predict status. */
      // std::cout << "miss alloc id: " << ConvertId(m_CoreInfos[CId].m_MissIdToAlloc) << std::hex << " pc: "<< Pc << std::dec << std::endl;
      *m_CoreInfos[CId].m_NewInst = fetchInstOnly(Pc, CId, m_CoreInfos[CId].m_MissIdToAlloc++);
      m_CoreInfos[CId].m_NewInstValid = true;

      return 1;
    } else {
      /* Do real spike step. */
      size_t steps_done = 0;
      int record_err = 0;
      do {
        steps_done += m_SimImpl->step(n, CId);

        /* Create InstTrace for a step. */
        m_CoreInfos[CId].m_NewInst->reset();
        m_CoreInfos[CId].m_NewInst->m_Id = m_CoreInfos[CId].m_IdToAlloc;
        record_err = m_SimImpl->record(*m_CoreInfos[CId].m_NewInst, CId);
        m_CoreInfos[CId].m_NewInstValid = (record_err == 0);
        if (m_CoreInfos[CId].m_NewInstValid) {
          // std::cout << "alloc id: " << m_CoreInfos[CId].m_IdToAlloc << std::hex << " npc: "<< m_CoreInfos[CId].m_NewInst->getNPc() << std::dec << std::endl;
          m_CoreInfos[CId].m_IdToAlloc += 1;
        }
        // std::cout << "new inst " << m_CoreInfos[CId].m_NewInstValid << std::endl;
        m_CoreInfos[CId].m_NewInst->m_mmuTrace = m_SimImpl->getMmuTrace(CId);
      } while (record_err < 0 and not done()); /* to do. Move loop into m_SimImpl->step */

      return steps_done;
    }
  } else {
    if (m_CoreInfos[CId].m_PathHandler.isMissPredict() and m_CoreInfos[CId].m_PathHandler.inCorrectId()) {
      auto Pc = m_CoreInfos[CId].m_PathHandler.getConfiguredNPc();
      /* Only fetch insn in miss-predict status. */
      // std::cout << "miss alloc id: " << ConvertId(m_CoreInfos[CId].m_MissIdToAlloc) << std::hex << " pc: "<< Pc << std::dec << std::endl;
      *m_CoreInfos[CId].m_NewInst = fetchInstOnly(Pc, CId, m_CoreInfos[CId].m_MissIdToAlloc++);
      m_CoreInfos[CId].m_NewInstValid = true;

      return 1;
    } else {
      /* Step the insn queue. */
      size_t stepped_num = 0;
      auto &holder =
          m_CoreInfos[CId].m_PathHandler.inCorrectId() ? m_CoreInfos[CId].m_IHolder : m_CoreInfos[CId].m_MissIHolder;
      stepped_num = holder.step(n);
      if (holder.getCurrInst()) {
        m_CoreInfos[CId].m_PathHandler.setCurrId(holder.getCurrInst()->getId());
      }
      return stepped_num;
    }
  }
}

void FuncSimAdapter::resetNPc(uint64_t NPc, uint32_t CId) {
  if (m_CoreInfos[CId].m_NewInst and m_CoreInfos[CId].m_NewInstValid) {
    throw std::runtime_error("please reqInst before");
  }
  m_CoreInfos[CId].m_PathHandler.configurePath(NPc);
}

InstUserPtr FuncSimAdapter::reqInst(uint32_t CId) {
  InstUserPtr res = nullptr;
  if (m_CoreInfos[CId].m_NewInst and m_CoreInfos[CId].m_NewInstValid) {
    /* Push inst into queue. */
    auto &holder = m_CoreInfos[CId].m_PathHandler.isMissPredict() ? m_CoreInfos[CId].m_MissIHolder : m_CoreInfos[CId].m_IHolder;
    holder.insertInst(std::move(*m_CoreInfos[CId].m_NewInst));
    m_CoreInfos[CId].m_PathHandler.setCurrId(holder.getCurrInst()->getId());
    m_CoreInfos[CId].m_NewInstValid = false;

    res = holder.getCurrInst();
    holder.setInDummyHead(false); /* After reqInst means a step, to be optimized. */
  } else {
    auto &holder = m_CoreInfos[CId].m_PathHandler.inCorrectId() ? m_CoreInfos[CId].m_IHolder : m_CoreInfos[CId].m_MissIHolder;
    res = holder.getCurrInst();
    holder.setInDummyHead(false); /* After reqInst means a step, to be optimized. */
  }

  if (res && res->m_NextVpc == ERROR_PC_ADDR) {
    throw std::runtime_error("res && res->m_NextVpc == ERROR_PC_ADDR");
  }
  return res;
}

InstUserPtr FuncSimAdapter::requestInst(uint64_t expected_pc, uint32_t CId) {
  auto res = reqInst(CId);
  if (res and expected_pc != res->getPc())
    [[unlikely]] {
      std::cout << "requestInst error: expected pc: 0x" << std::hex << expected_pc << " getting pc: 0x" << res->getPc()
                << " configured npc: 0x" << getConfiguredNPc(CId) << std::dec
                << " correct inst queue size: " << m_CoreInfos[CId].m_IHolder.size()
                << " previous rollback id: " << ConvertId(m_CoreInfos[CId].prev_rollback_id) << std::endl;
      if (m_CoreInfos[CId].m_IHolder.size()) {
        std::cout << "current front inst id: " << m_CoreInfos[CId].m_IHolder.getFrontInst()->getId()
                  << " current last inst id: " << m_CoreInfos[CId].m_IHolder.getLastInst()->getId() << std::endl;
      }
    }
  return res;
}

void FuncSimAdapter::freeInst(InstUserPtr &InstPtr, uint32_t CId) {
  if (InstPtr == nullptr) {
    return;
  }
  // std::cout << "freeInst: " << InstPtr->getId() << " " <<
  // m_CoreInfos[CId].m_PathHandler.correctIIdEnd() << std::endl;
  if (InstPtr->getId() >= m_CoreInfos[CId].m_IdToAlloc) {
    throw std::runtime_error("Can not free miss inst");
  }
  m_CoreInfos[CId].m_IHolder.freeInst(InstPtr);
}

void FuncSimAdapter::freeInst(uint64_t IId, uint32_t CId) {
  if (IId >= m_CoreInfos[CId].m_IdToAlloc) {
    std::cout << "current front id: " << m_CoreInfos[CId].m_IHolder.getFrontInst()->getId() << std::endl;
    throw std::runtime_error("Can not free miss inst, free ID: " + std::to_string(ConvertId(IId)) +
                             " corrent id end at: " + std::to_string(m_CoreInfos[CId].m_IdToAlloc));
  }
  m_CoreInfos[CId].m_IHolder.freeInst(IId);
}

std::shared_ptr<InstTrace> &FuncSimAdapter::takeInst(uint32_t CId) {
  if (not (m_CoreInfos[CId].m_NewInst and m_CoreInfos[CId].m_NewInstValid)) {
    return m_Dummy;
  }
  m_CoreInfos[CId].m_NewInstValid = false;
  return m_CoreInfos[CId].m_NewInst;
}

void FuncSimAdapter::resolve(uint64_t InstUId, uint32_t CId) {
  // std::cout << "resolve id: "<< InstUId << std::endl;
  m_CoreInfos[CId].m_stepToIgnore = 0; /* To adapt to timing model usage. */
  rollback(InstUId, CId);
}

void FuncSimAdapter::replay(uint64_t InstUId, uint32_t CId) {
  // std::cout << "replay id: " << InstUId << std::endl;
  m_CoreInfos[CId].m_stepToIgnore = 1; /* To adapt to timing model usage. */
  rollback(InstUId, CId);
}

InstTrace FuncSimAdapter::fetchInstOnly(uint64_t Pc, uint32_t CId, uint64_t IId) {
  auto res = m_SimImpl->fetchInstOnly(Pc, CId, IId);
  if (not res.perfect()) {
    auto ptr = m_CoreInfos[CId].m_IHolder.getByPc(Pc);
    if (ptr) {
      res.m_InstrRaw = static_cast<uint32_t>(ptr->getBits());
      res.m_Ppc = ptr->getPcPAddr();
      res.m_NextVpc = ptr->getNPc();
    } else {
      res.m_InstrRaw = 0x1;
      res.m_NextVpc = res.m_Vpc + insn_length(res.m_InstrRaw);
    }
  } else {
    res.m_NextVpc = res.m_Vpc + insn_length(res.m_InstrRaw);
  }
  if (res.m_NextVpc == ERROR_PC_ADDR) {
    throw std::runtime_error("res.m_NextVpc == ERROR_PC_ADDR");
  }
  return res;
}

bool FuncSimAdapter::inROI(uint32_t cid) const {
  return m_SimImpl->inROI(cid);
}

uint64_t FuncSimAdapter::getConfiguredNPc(uint32_t cid) const {
  return m_CoreInfos[cid].m_PathHandler.getConfiguredNPc();
}

uint64_t FuncSimAdapter::getCurrPc(uint32_t cid) const {
  bool in_replay = m_CoreInfos[cid].m_stepToIgnore == 1;

  auto &holder = m_CoreInfos[cid].m_PathHandler.inCorrectId() ? m_CoreInfos[cid].m_IHolder : m_CoreInfos[cid].m_MissIHolder;

  auto next_inst = holder.getNextInst();
  if ((holder.size() == 0) or (next_inst == nullptr and not in_replay)) {
    /* Only not misspredict path is meaningful. todo, add +2/+4 for misspredict path. */
    return m_SimImpl->getCurrPc(cid);
  }
  auto curr_inst = holder.getCurrInst();
  if (in_replay) {
    /* When replay, the next req inst is current inst. */
    return curr_inst->getPc();
  } else {
    return next_inst->getPc();
  }
}

void FuncSimAdapter::rollback(uint64_t InstUId, uint32_t CId) {
  if (m_CoreInfos[CId].m_NewInst and m_CoreInfos[CId].m_NewInstValid) {
    throw std::runtime_error("please reqInst before");
  }
  m_CoreInfos[CId].prev_rollback_id = InstUId;
  bool IsCorrectId = InstTrace::isCorrectID(InstUId);
  auto &InstHolder = IsCorrectId ? m_CoreInfos[CId].m_IHolder : m_CoreInfos[CId].m_MissIHolder;

  m_CoreInfos[CId].m_NewInstValid = false;
  if (not InstHolder.size() and IsCorrectId) {
    /* Handle resolve, Only correct id in resolve enter here. */
    m_CoreInfos[CId].m_PathHandler.setCurrId(InstUId);
    m_CoreInfos[CId].m_PathHandler.setConfiguredNPc(m_SimImpl->getCurrPc(CId));
    InstHolder.setInDummyHead(true);
  } else if (InstHolder.has(InstUId)) {
    m_CoreInfos[CId].m_PathHandler.setCurrId(InstUId);
    InstHolder.setCurrInst(InstUId);
    m_CoreInfos[CId].m_PathHandler.setConfiguredNPc(InstHolder.getCurrInst()->getPc());
  } else if (IsCorrectId) {
    /* Handle resolve, Only correct id in resolve enter here, the next id is always exists */
    m_CoreInfos[CId].m_PathHandler.setCurrId(InstUId);
    InstHolder.setCurrInst(InstHolder.getFrontInst()->getId());
    InstHolder.setInDummyHead(true);
  }
  /* When the inst is already clear in out-of-order resolve, do nothing. */
}

bool FuncSimAdapter::getMissPredict(uint32_t CId) const {
  return m_CoreInfos[CId].m_PathHandler.isMissPredict();
}

InstUserPtr FuncSimAdapter::getActiveInst(uint32_t CId) const {
  auto &holder = m_CoreInfos[CId].m_PathHandler.inCorrectId() ? m_CoreInfos[CId].m_IHolder : m_CoreInfos[CId].m_MissIHolder;
  InstUserPtr CurrInst = holder.getCurrInst();
  if (not CurrInst) {
    CurrInst = m_CoreInfos[CId].m_NewInst.get();
  }
  return CurrInst;
}

uint64_t FuncSimAdapter::vaddr2paddr(uint64_t vaddr, uint32_t CId) const { return m_SimImpl->vaddr2paddr(vaddr, CId); }

#include "SpikeSimObjAsync.hpp"

#include <iostream>
#include <utility>

#include "RawSpike.hpp"

SpikeSimObjAsync::SpikeSimObjAsync() {
  m_InstBuf.reserve(INST_BUF_SIZE);
  for (size_t i = 0; i < INST_BUF_SIZE; ++i) {
    m_InstBuf.emplace_back(0);
  }
  m_Taking = std::make_shared<InstTrace>(0);
}

SpikeSimObjAsync::~SpikeSimObjAsync() {
  stop();
  waitStop();
}

void SpikeSimObjAsync::initROICount(int num) {
  m_ROICount = num;
  SpikeSimObjSync::initROICount(num);
}

void SpikeSimObjAsync::start() {
  SpikeSimObjSync::start();
  m_Running = true;
  m_Th = std::make_unique<std::thread>([this] {
    int PassedROI = 0;
    while (not m_SimImpl->done() and m_Running) {
      if (m_ROICount and PassedROI == m_ROICount) {
        break;
      }
      if (not m_ROICount or m_SimImpl->inROI(0)) {
        if (not m_HasEnterROI) {
          m_HasEnterROI = true;
          std::cout << "enter ROI" << std::endl;
        }
        if (full()) {
          continue;
        }
        stepSync(1, 0);
        auto inst = takeProducedInst(0);
        if (inst and inst->perfect()) {
          m_InstBuf[m_PosAdd] = std::move(*inst);
          nextAddPos();
        }
      } else {
        if (m_HasEnterROI) {
          m_HasEnterROI = false;
          ++PassedROI;
          std::cout << "leave ROI" << std::endl;
        }
        stepSync(1, 0);
      }
    }
    m_Running = false;
  });
}

void SpikeSimObjAsync::stop() {
  m_Running = false;
  SpikeSimObjSync::stop();
}

void SpikeSimObjAsync::waitStop() {
  if (m_Th && m_Th->joinable()) {
    m_Th->join();
  }
}

bool SpikeSimObjAsync::done() const {
  return (m_SimImpl->done() or not m_Running) and empty();
}

size_t SpikeSimObjAsync::step(size_t n, [[maybe_unused]]uint32_t CId) {
  (void)n;
  return 0;
}

std::shared_ptr<InstTrace> &SpikeSimObjAsync::takeInst([[maybe_unused]]uint32_t CId) {
  if (not empty()) {
    *m_Taking = std::move(m_InstBuf[m_PosFecth]);
    nextFetchPos();
    return m_Taking;
  }
  return m_Dummy;
}

bool SpikeSimObjAsync::inROI([[maybe_unused]]uint32_t cid) const {
  return m_HasEnterROI;
}

bool SpikeSimObjAsync::empty() const { return m_PosAdd == m_PosFecth; }

bool SpikeSimObjAsync::full() const {
  return (m_PosAdd + 1) % m_InstBuf.size() == m_PosFecth;
}

void SpikeSimObjAsync::nextFetchPos() {
  ++m_PosFecth;
  m_PosFecth %= m_InstBuf.size();
}

void SpikeSimObjAsync::nextAddPos() {
  ++m_PosAdd;
  m_PosAdd %= m_InstBuf.size();
}

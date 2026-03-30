#include "SpikeSimObjAsync.hpp"

#include <iostream>

SpikeSimObjAsync::SpikeSimObjAsync() {
  m_InstBuf.reserve(INST_BUF_SIZE);
  for (size_t i = 0; i < INST_BUF_SIZE; ++i) {
    m_InstBuf.emplace_back(0);
  }
  m_Taking = std::make_shared<InstTrace>(0);
}

SpikeSimObjAsync::~SpikeSimObjAsync() {
  FuncSimAdapter::stop();
}

void SpikeSimObjAsync::initROICount(int num) { m_ROICount = num; }

void SpikeSimObjAsync::start() {
  FuncSimAdapter::start();
  // run
  m_Running = true;
  m_Th = std::make_unique<std::thread>([&] {
    int PassedROI = 0;
    // std::chrono::high_resolution_clock::time_point BegTime;
    size_t ICount = 0;
    while(not FuncSimAdapter::done() and m_Running) {
      if (m_ROICount and PassedROI == m_ROICount) {
        break;
      }
      if (not m_ROICount or FuncSimAdapter::inROI()) {
        if (not m_HasEnterROI) {
          m_HasEnterROI = true;
          // FuncSimAdapter::setLogCommits(true, true);
          std::cout << "enter ROI" << std::endl;
        }
        if (full()) {
          continue;
        }
        FuncSimAdapter::step(1);
        auto Inst = FuncSimAdapter::takeInst();
        if (Inst and Inst->perfect()) {
          // if (not m_InstBuf[m_PosAdd]) {
          //   m_InstBuf[m_PosAdd] = std::make_shared<InstTrace>(0);
          // }
          m_InstBuf[m_PosAdd] = std::move(*Inst);
          nextAddPos();

          // if (ICount == 0) {
          //   BegTime = std::chrono::high_resolution_clock::now();
          // } else if (ICount % INST_COUNT_TO_LOG == 0) {
          //   auto EndTime = std::chrono::high_resolution_clock::now();
          //   auto Dura = EndTime - BegTime;
          //   std::cout << "Complete Insns: " << INST_COUNT_TO_LOG << ", passed time: "
          //             << std::chrono::duration_cast<std::chrono::milliseconds>(Dura).count() << "ms" << std::endl;
          //   BegTime = EndTime;
          // }
          ++ICount;
          // if (ICount == 100000000) {
          //   FuncSimAdapter::stop();
          // }
        }
      } else {
        if (m_HasEnterROI) {
          m_HasEnterROI = false;
          ++PassedROI;
          // FuncSimAdapter::setLogCommits(false, false);
          std::cout << "leave ROI" << std::endl;
        }
        FuncSimAdapter::step(1);
      }
    }
    m_Running = false;
  });
}

void SpikeSimObjAsync::stop() {
  m_Running = false;
}

void SpikeSimObjAsync::waitStop() {
  if (m_Th) {
    m_Th->join();
  }
}

bool SpikeSimObjAsync::done() const {
  return (FuncSimAdapter::done() or not m_Running) and empty();
}

size_t SpikeSimObjAsync::step(size_t n, uint32_t CId) {
  // do nothing
  return 0;
}

std::shared_ptr<InstTrace> &SpikeSimObjAsync::takeInst(uint32_t CId) {
  if (not empty()) {
    *m_Taking = std::move(m_InstBuf[m_PosFecth]);
    nextFetchPos();
    return m_Taking;
  }
  return m_Dummy;
}

bool SpikeSimObjAsync::inROI(uint32_t cid) const {
  return m_HasEnterROI;
}

bool SpikeSimObjAsync::empty() const { return m_PosAdd == m_PosFecth; }

bool SpikeSimObjAsync::full() const { return (m_PosAdd + 1) % m_InstBuf.size() == m_PosFecth; }

void SpikeSimObjAsync::nextFetchPos() {
  ++m_PosFecth;
  m_PosFecth %= m_InstBuf.size();
}

void SpikeSimObjAsync::nextAddPos() {
  ++m_PosAdd;
  m_PosAdd %= m_InstBuf.size();
}
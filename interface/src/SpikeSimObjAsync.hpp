#pragma once

#include <vector>
#include "Thread.hpp"

#include "FuncSimAdapter.hpp"
#include "utility/PerfTimer.hpp"

class SpikeSimObjAsync : public FuncSimAdapter {
public:
  static constexpr size_t INST_BUF_SIZE = 1000;
  SpikeSimObjAsync();
  ~SpikeSimObjAsync();

  void initROICount(int num) override;
  void start() override;
  void stop() override;
  void waitStop() override;
  bool done() const override;
  size_t step(size_t n, uint32_t CId = 0) override;
  std::shared_ptr<InstTrace> &takeInst(uint32_t CId = 0) override;
  bool inROI(uint32_t cid = 0) const override;

private:
  bool empty() const;
  bool full() const;
  void nextFetchPos();
  void nextAddPos();

  // worker data beg
  size_t m_PosAdd = 0;
  int m_ROICount = 0;
  bool m_Running = false;
  volatile bool m_HasEnterROI = false;
  std::vector<InstTrace> m_InstBuf;
  char padding[40];
  // worker data end
  
  // host data beg
  size_t m_PosFecth = 0;
  std::shared_ptr<InstTrace> m_Taking{0};
  // host data end

  std::unique_ptr<std::thread> m_Th;
};
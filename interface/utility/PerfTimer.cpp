/**
 * @file PerfStat.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-02-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "PerfTimer.hpp"

#include <iostream>

namespace util {

TimeSpec nowTime() {
  return std::chrono::high_resolution_clock::now();
}

DurationType toDuration(const TimeSpec &Beg, const TimeSpec &End) {
  return End - Beg;
}

double toMicro(const DurationType &Dura) {
  return Dura.count() * 1e-3;
}

double toSec(const DurationType &Dura) {
  return Dura.count() * 1e-9;
}

double toMili(const DurationType &Dura) {
  return Dura.count() * 1e-6;
}

StatTimes StatTimes::s_Times;
std::mutex StatTimes::s_Mutex;

StatTimes::~StatTimes() {
  print();
}

void StatTimes::print() {
  {
    std::unique_lock<std::mutex> LCK(s_Mutex);
    for (auto &[Name, Dura] : s_Times) {
      std::cout << '[' << Name << "]: " << toSec(Dura) << "s\n";
    }
  }
  std::cout << std::flush;
}

PerfStat::PerfStat(const std::string &Name)
  : m_Name(Name) {}

void PerfStat::logEnd() {
  if (m_IsLog) {
    return;
  }
  std::unique_lock<std::mutex> LCK(StatTimes::s_Mutex);
  StatTimes::s_Times[m_Name] += m_Dura;
  m_Dura = DurationType(0);
  m_IsLog = true;
}

PerfStat::~PerfStat() {
  logEnd();
}

PerfTimer::PerfTimer(PerfStat &Stat)
  : m_Stat(&Stat),
    m_BegTime(nowTime()) {}

PerfTimer::~PerfTimer() {
  if (m_Stat) {
    auto EndTime = nowTime();
    DurationType Dura = toDuration(m_BegTime, EndTime);
    m_Stat->m_Dura += Dura;
    m_Stat->m_IsLog = false;
    // std::cout << m_Stat.m_Name << "## " << m_Stat.m_Dura.count() << std::endl;
  }
}

void PerfTimer::setStat(PerfStat &Stat) {
  m_Stat = &Stat;
  m_BegTime = nowTime();
}

}
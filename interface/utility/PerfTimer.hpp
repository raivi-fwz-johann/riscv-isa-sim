/**
 * @file PerfStat.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-02-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <chrono>
#include <mutex>
#include <string>
#include <unordered_map>
#include <ctime>

namespace util {

using TimeSpec = std::chrono::high_resolution_clock::time_point;
using DurationType = std::chrono::duration<size_t, std::nano>;

TimeSpec nowTime();
DurationType toDuration(const TimeSpec &Beg, const TimeSpec &End);
double toMicro(const DurationType &Dura);
double toSec(const DurationType &Dura);
double toMili(const DurationType &Dura);

class StatTimes : public std::unordered_map<std::string, DurationType> {
public:
  ~StatTimes();
  static void print();

  static StatTimes s_Times;
  static std::mutex s_Mutex;
};

class PerfStat {
public:
  PerfStat(const std::string &Name);
  void logEnd();
  ~PerfStat();

  void reset() {
    m_Dura = DurationType(0);
  }
  DurationType duration() const { return m_Dura; }

private:
  const std::string m_Name;
  DurationType m_Dura = DurationType(0);
  bool m_IsLog = false;

  friend class PerfTimer;
};

class PerfTimer {
public:
  PerfTimer() {}
  PerfTimer(PerfStat &Stat);
  ~PerfTimer();

  void setStat(PerfStat &Stat);

private:
  PerfStat *m_Stat = nullptr;
  TimeSpec m_BegTime;
};

#define TIMER(valname, str) \
  util::PerfStat valname(str); \
  util::PerfTimer valname##Timer(valname);

}
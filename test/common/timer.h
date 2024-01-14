#pragma once

#include <chrono>

namespace test {

struct Timer {
  using Clock = std::chrono::system_clock;
  using DiffType = Clock::time_point::duration::rep;
  std::chrono::system_clock::time_point::duration::rep diff{};

  Timer() = default;

  static DiffType Now();

  void Start();

  void Stop();
};

}// namespace test

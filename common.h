#pragma once
#include <chrono>

namespace AG
{
  template <typename T1, typename T2>
  void swap(T1& lhs, T2& rhs)
  {
    T2 temp = std::move(rhs);
    rhs = std::move(lhs);
    lhs = std::move(temp);
  }
}

namespace Utils
{
  class Timer
  {
  public:
    void Start() { mStart = std::chrono::steady_clock::now(); }
    void Stop()  { mStop = std::chrono::steady_clock::now(); } 
    template <typename CTYP>
    typename std::chrono::duration<double, CTYP>::rep GetDuration() { return std::chrono::duration<double, CTYP>(mStop - mStart).count(); }
  private:
    std::chrono::steady_clock::time_point mStart;
    std::chrono::steady_clock::time_point mStop;
  };

  template <typename CTYP, size_t SZ>
  size_t ArrayLen(CTYP(&)[SZ]) { return SZ; }
}





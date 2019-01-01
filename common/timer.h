#pragma once
#include <chrono>

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
}





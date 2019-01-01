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
  template <typename CTYP, size_t SZ>
  size_t ArrayLen(CTYP(&)[SZ]) { return SZ; }
}





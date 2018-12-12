#pragma once

namespace AG
{
  template <typename T1, typename T2>
  void swap(T1&& lhs, T2&& rhs)
  {
    const T2 temp = rhs;
    rhs = lhs;
    lhs = std::move(temp);
  }
}

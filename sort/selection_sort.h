#pragma once

#include "common.h"

namespace AG
{
  template <typename CTYP>
  class SelectionSort
  {
  public:
    SelectionSort(CTYP& _d) : mData(_d) {}

    void Sort()
    {
      size_t sz = mData.size();
      for (size_t i = 0; i < sz; ++i)
      {
        if (i+1 < sz)
        {
          auto minIdx = FindMinIdx(i+1, sz);
          if (mData[minIdx] < mData[i])
          {
            AG::swap(mData[minIdx], mData[i]);
          }
        }
      }
    }

    private:
      size_t FindMinIdx(const size_t start, const size_t sz)
      {
        auto minIdx = start;
        auto min = mData[start];
        for (size_t i = start + 1; i < sz; ++i)
        {
          if (min > mData[i])
          {
            min = mData[i];
            minIdx = i;
          }
        }
        return minIdx;
      }
      CTYP& mData;
  };
}



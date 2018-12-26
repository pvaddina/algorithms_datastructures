#pragma once

#include "common.h"

namespace AG
{
  template <typename T>
  class InsertionSort
  {
  public:
    InsertionSort(T& _d) : mData(_d) {}

    void Sort()
    {
      size_t sz = mData.size();
      for (size_t i = 0; i < sz; ++i)
      {
        for (size_t j = i; j > 0; --j)
        {
          if (mData[j] < mData[j-1])
          {
            AG::swap(mData[j], mData[j-1]);
          }
          else
          {
            break;
          }
        }
      }
    }

    private:
      T& mData;
  };
}



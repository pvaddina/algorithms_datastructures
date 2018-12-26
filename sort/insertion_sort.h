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
      for (size_t i = 1; i < sz; ++i)
      {
        for (size_t j = 0; j < i; ++j)
        {
          if (mData[i] < mData[j])
          {
            AG::swap(mData[i], mData[j]);
          }
        }
      }
    }

    private:
      T& mData;
  };
}



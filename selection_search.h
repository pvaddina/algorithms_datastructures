#pragma once

#include "common.h"

namespace AG
{
  template <typename T>
  class SelSearch
  {
    public:
      SelSearch(T& _d) : mData(_d) {}

      void Sort()
      {
        size_t sz = mData.size();
        T::value_type ref;
        for (int i=0; i<sz; ++i)
        {
          for (int j=i+1; j<sz; ++j)
          {
            if (mData[j] < mData[0])
            {
              std::swap(mData[j], mData[i]);
            }
        }
      }

    private:
      T& mData;
  };
}



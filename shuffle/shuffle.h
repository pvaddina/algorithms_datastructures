#pragma once

#include "randomgen.h"

namespace AG
{
  template <typename T>
  class Shuffler
  {
    public:
      Shuffler(T& data) : mData(data) {}

      void Shuffle()
      {
        const size_t sz = mData.size();
        Utils::FreeRandomGen r;
        for (size_t i = 1; i < sz; ++i)
        {
          const size_t swapWith = r.Get(0, i - 1);
          std::swap(mData[i], mData[swapWith]);
        }
      }

    private:
      T& mData;
  };
}



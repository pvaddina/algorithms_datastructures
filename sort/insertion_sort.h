#pragma once

#include "common.h"

namespace AG
{
  template <typename CTYP, typename DTYP, size_t H>
  class InsertionSort
  {
  public:
    InsertionSort(CTYP& _d) : mData(_d) {}

    void Sort()
    {
      const size_t sz = GetSize();
      for (size_t i = 0; i < sz; ++i)
      {
        for (size_t j = i; j > 0; --j)
        {
          if (GetItem(j) < GetItem(j-1))
          {
            Swap(j-1, j);
          }
          else
          {
            break;
          }
        }
      }
    }

  private:
    size_t GetSize() const { return mData.size()/H; }
    DTYP& GetItem(const size_t idx) { return mData[idx*H]; }
    void Swap(const size_t lhsIdx, const size_t rhsIdx) { AG::swap(mData[lhsIdx*H], mData[rhsIdx*H]); }

  private:
    CTYP& mData;
  };


  template <typename CTYP, typename DTYP>
  class ShellSort
  {
  public:
    ShellSort(CTYP& _d, const size_t gap) : mData(_d), mGap(gap) {}

    void Sort()
    {
      const size_t sz = GetSize();
      for (size_t i = 0; i < sz; ++i)
      {
        for (size_t j = i; j > 0; --j)
        {
          if (GetItem(j) < GetItem(j - 1))
          {
            Swap(j - 1, j);
          }
          else
          {
            break;
          }
        }
      }
    }

  private:
    size_t GetSize() const { return mData.size() / mGap; }
    DTYP& GetItem(const size_t idx) { return mData[idx*mGap]; }
    void Swap(const size_t lhsIdx, const size_t rhsIdx) { AG::swap(mData[lhsIdx*mGap], mData[rhsIdx*mGap]); }

  private:
    CTYP& mData;
    size_t mGap;
  };

}



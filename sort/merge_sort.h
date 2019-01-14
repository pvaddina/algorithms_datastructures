#pragma once

#include "common.h"

namespace AG
{
  template <typename CTYP>
  class MergeSort
  {
  public:
    //static auto RecursiveSort = [](CTYP& data, const size_t start, const size_t end) {
    //  const auto sz = end - start + 1;
    //  const auto half = sz / 2;
    //  if (half == 1)
    //  {
    //    if (data[start] > data[end])
    //      AG::swap(data[start], data[end]);
    //  }
    //  else
    //  {
    //    RecursiveSort(data, start, half - 1);
    //    RecursiveSort(data, half, end);
    //  }
    //};

    MergeSort(CTYP& _d) : mData(_d) {}

    void Sort()
    {
      // Step-1: Make a copy of the unsorted data first
      auto auxiliaryData = mData;

      // Step-2: Sort the data container now
      const size_t sz = mData.size();
      DoSort(mData, auxiliaryData, 0, sz);
    }

  private:
    void DoSort(CTYP& data, CTYP& auxData, const size_t start, const size_t size)
    {
      const auto half = size / 2;
      if (size > 2)
      {
        DoSort(data, auxData, start, half);
        DoSort(data, auxData, start+half, size-half);
        DoMerge(data, auxData, start, size);
      }
      else if (size == 2)
      {
        if (auxData[start] > auxData[start + 1])
          AG::swap(auxData[start], auxData[start + 1]);
        data[start] = auxData[start];
        data[start + 1] = auxData[start+1];
      }
      else if (size == 1)
      {
        data[start] = auxData[start];
      }
    }

    void DoMerge(CTYP& data, CTYP& auxData, size_t start, size_t size)
    {
      auto i = start;
      auto sz = size;
      auto half = size / 2;
      auto j = i + half;
      auto idxData = start;

      while (sz > 0)
      {
        if (j >= start + size)
        {
          data[idxData] = auxData[i];
          ++i;
        }
        else if (i >= start + half)
        {
          data[idxData] = auxData[j];
          ++j;
        }
        else if (auxData[i] < auxData[j])
        {
          data[idxData] = auxData[i];
          ++i;
        }
        else
        {
          data[idxData] = auxData[j];
          ++j;
        }
        --sz;
        ++idxData;
      }

      for (auto i=start; i<start+size; ++i)
      {
        auxData[i] = data[i];
      }
    }

  private:
    CTYP& mData;
  };

}



#pragma once

#include "common.h"

namespace AG
{
  template <typename CTYP>
  class MergeSort
  {
  public:
    MergeSort(CTYP& _d) : mData(_d) {}

    void Sort()
    {
      // Step-1: Make a copy of the unsorted data first
      auto auxiliaryData = mData;

      // Step-2: Sort the data container now
      const size_t sz = mData.size();
      DoSort(mData, auxiliaryData, 0, sz);
    }

    void Sort(const size_t start, const size_t end)
    {
      // Step-1: Make a copy of the unsorted data first
      auto auxiliaryData = mData;

      // Step-2: Sort the data container now
      size_t ct = end - start + 1;
      DoSort(mData, auxiliaryData, start, ct);
    }

  private:
    void DoSort(CTYP& data, CTYP& auxData, const size_t start, const size_t size)
    {
      const auto half = size / 2;
      if (size > 1)
      {
        DoSort(data, auxData, start, half);
        DoSort(data, auxData, start+half, size-half);
        DoMerge(data, auxData, start, size);
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
        if (j >= start + size) { 
          data[idxData] = auxData[i++];
        }
        else if (i >= start + half) {
          data[idxData] = auxData[j++];
        }
        else if (auxData[i] < auxData[j]) {
          data[idxData] = auxData[i++];
        }
        else {
          data[idxData] = auxData[j++];
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



  template <typename CTYP>
  class BottomUpMergeSort
  {
  public:
    BottomUpMergeSort(CTYP& _d) : mData(_d) {}

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
      bool allMerged = false;
      for (size_t i=0; !allMerged; ++i)
      {
        size_t mergeSize = 1 << (i+1);
        size_t mid = 1 << i;
        const size_t numIter = (size + (mergeSize-1))/ mergeSize;

        for (size_t j=0; j<numIter; ++j)
        {
          const auto lclStart = start + (j*mergeSize);
          const auto lclMergeSz = lclStart + mergeSize > size ? size - lclStart : mergeSize;
          allMerged = lclMergeSz == size;
          DoMerge(data, auxData, start+(j*mergeSize), mid, lclMergeSz);
        }
      }
    }

    void DoMerge(CTYP& data, CTYP& auxData, size_t start, size_t mid, size_t size)
    {
      auto i = start;
      auto sz = size;
      //auto mid = size / 2;
      auto j = i + mid;
      auto idxData = start;

      while (sz > 0)
      {
        if (j >= start + size) {
          data[idxData] = auxData[i++];
        }
        else if (i >= start + mid) {
          data[idxData] = auxData[j++];
        }
        else if (auxData[i] < auxData[j]) {
          data[idxData] = auxData[i++];
        }
        else {
          data[idxData] = auxData[j++];
        }
        --sz;
        ++idxData;
      }

      for (auto i = start; i<start + size; ++i)
      {
        auxData[i] = data[i];
      }
    }

  private:
    CTYP & mData;
  };

}



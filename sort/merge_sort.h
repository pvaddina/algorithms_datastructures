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
      DoSort(mData, auxiliaryData, 0, sz - 1);
    }

  private:
    void DoSort(CTYP& data, CTYP& auxData, const size_t start, const size_t end)
    {
      const auto sz = end - start + 1;
      const auto half = sz / 2;
      if (half == 1)
      {
        if (auxData[start] > auxData[start+1])
          AG::swap(auxData[start], auxData[start+1]);

        if (sz == 3)
          DoMerge(data, auxData, start, start+1, end, end);
      }
      else if (half > 1)
      {
        auto startOne = start;
        auto endOne = start + half - 1;
        auto startTwo = start + half;
        auto endTwo = end;
        DoSort(data, auxData, startOne, endOne);
        DoSort(data, auxData, startTwo, endTwo);
        DoMerge(data, auxData, startOne, endOne, startTwo, endTwo);
      }
    }

    void DoMerge(CTYP& data, CTYP& auxData
               , size_t idxOne, const size_t endOne
               , size_t idxTwo, const size_t endTwo)
    {
      auto idxAuxData = idxOne;
      auto idxData = idxOne;
      size_t sz = (endOne - idxOne + 1) + (endTwo - idxTwo + 1);

      while (sz > 0)
      {
        if (idxTwo > endTwo)
        {
          //asset(idxOne <= endOne);
          data[idxData] = auxData[idxOne];
        }
        else if (idxOne <= endOne && auxData[idxOne] < auxData[idxTwo])
        {
          data[idxData] = auxData[idxOne];
          ++idxOne;
        }
        else if (idxTwo <= endTwo)
        {
          data[idxData] = auxData[idxTwo];
          ++idxTwo;
        }
        ++idxData;
        --sz;
      }
      
      for (auto i=idxAuxData; i<=endTwo; ++i)
      {
        auxData[i] = data[i];
      }
    }


  private:
    CTYP& mData;
  };

}



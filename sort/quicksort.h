#pragma once

#include "common.h"
#include "shuffle.h"
#include "merge_sort.h"

namespace AG
{
  template <typename CTYP>
  class QuickSort
  {
  public:
    QuickSort(CTYP& _d) : mData(_d) {}

    void Sort()
    {
      // Randomly, with no empherical/mathematical proof, disable the 
      // shuffle and partitioning
      constexpr int MIN_ALLOWED_SIZE = 10;
      const auto size = mData.size();
      if (size > MIN_ALLOWED_SIZE)
      {
        // Step-1: Randomly shuffle the data
        AG::Shuffler<CTYP> sh{ mData };
        sh.Shuffle();

        auto partIdx = PartitionDataContainer();

        // Step-3: Sort the left of the partition element
        // Sort the right of the partition element
        AG::MergeSort<CTYP> sorter{ mData };
        if (partIdx > 0)
          sorter.Sort(0, partIdx - 1);
        const size_t lastIdx = size - 1;
        if (partIdx < lastIdx)
          sorter.Sort(partIdx+1, lastIdx);
      }
      else
      {
        AG::MergeSort<CTYP> sorter{ mData };
        sorter.Sort();
      }
    }

  private:
    size_t PartitionDataContainer()
    {
      size_t i = 1;
      size_t j = mData.size() - 1;

      const auto partElem = mData[0];
      while(i < j)
      {
        // Iterate throught the first half until an item is found
        // which is indeed larger than the partition element
        while(i < j) 
        {
          if (mData[i] <= partElem) {
            ++i;
          } else {
            break; // increment as long as no other element 
                 // larger than partition item
          }
        }

        // Iterate throught the second half until an item is found
        // which is indeed smaller than the partition element
        while(i <= j) 
        {
          if (mData[j] >= partElem) {
            --j;
          } else {
            break;
          }
        }

        if (i < j)
          AG::swap(mData[i], mData[j]);
      }
      AG::swap(mData[0], mData[j]);
      return j;
    }

  private:
    CTYP & mData;
  };

}



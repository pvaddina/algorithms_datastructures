#pragma once

#include "common.h"
#include "shuffle.h"

namespace AG
{
  template <typename CTYP>
  class QuickSort
  {
  public:
    QuickSort(CTYP& _d) : mData(_d) {}

    void Sort()
    {
      // Step-1: Randomly shuffle the data
      AG::Shuffler<CTYP> sh{ mData };
      sh.Shuffle();

      std::cout << "\nAfter shuffling: ";
      for (const auto& i : mData)
        std::cout << i << " ";

      // Step-2: Partition the data structure
      PartitionDataContainer();

      std::cout << "\nAfter partitioning: ";
      for (const auto& j : mData)
        std::cout << j << " ";

      // Step-3: Sort the left of the partition element
      // Sort the right of the partition element
      //const size_t sz = mData.size();
      //DoSort(mData, auxiliaryData, 0, sz);
    }

  private:
    void PartitionDataContainer()
    {
      size_t i = 1;
      size_t j = mData.size() - 1;

      const auto partElem = mData[0];
      std::cout << "\nPartition Element is: " << partElem;
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
        else if (i > j)
          AG::swap(mData[0], mData[j]);
      }
    }

  private:
    CTYP & mData;
  };

}



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "timer.h"

#include "quicksort.h"

void RunQuickSortTests()
{
  auto doQuicksortTest = [](std::vector<int>& inData) {
    auto data = inData;
    for (auto& i : data)
      std::cout << i << " ";

    AG::QuickSort<std::vector<int> > sorter{ data };
    sorter.Sort();

    std::cout << "\n";
    for (auto& i : data)
      std::cout << i << " ";
    std::cout << "\n\n";
  };

  //std::vector<int> longAndRepeated{ 3,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9 };
  //doQuicksortTest(longAndRepeated);

  //std::vector<int> dataEven{ 3,5,2,43,2,23};
  //doQuicksortTest(dataEven);

  //std::vector<int> dataOdd{ 3,5,2,43,2,23,99,23,45 };
  //doQuicksortTest(dataOdd);

  //std::vector<int> one{ 3 };
  //doQuicksortTest(one);

  std::vector<int> two{ 6, 3 };
  doQuicksortTest(two);

  //std::vector<int> three{ 9, 2, 3 };
  //doQuicksortTest(three);

  std::cout << "\n\n";
}




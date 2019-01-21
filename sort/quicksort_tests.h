#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "timer.h"

#include "quicksort.h"

void RunQuickSortTests()
{
  auto doNormalMergeTest = [](std::vector<int>& inData) {
    auto data = inData;
    AG::QuickSort<std::vector<int> > sorter{ data };
    sorter.Sort();
  };

  std::vector<int> longAndRepeated{ 3,5,2,43,2,23,99,23,45 };
  //std::vector<int> longAndRepeated{ 3,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9 };
  doNormalMergeTest(longAndRepeated);

#if 0
  std::vector<int> dataEven{ 3,5,2,43,2,23};
  doNormalMergeTest(dataEven);
  doBUMergeTest(dataEven);

  std::vector<int> dataOdd{ 3,5,2,43,2,23,99,23,45 };
  doNormalMergeTest(dataOdd);
  doBUMergeTest(dataOdd);

  std::vector<int> one{ 3 };
  doNormalMergeTest(one);
  doBUMergeTest(one);

  std::vector<int> two{ 6, 3 };
  doNormalMergeTest(two);
  doBUMergeTest(two);

  std::vector<int> three{ 9, 2, 3 };
  doNormalMergeTest(three);
  doBUMergeTest(three);
#endif

  std::cout << "\n\n";
}




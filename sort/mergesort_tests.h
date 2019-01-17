#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "timer.h"

#include "merge_sort.h"

void SimpleMergeSortTesting()
{
  auto doNormalMergeTest = [](std::vector<int>& inData) {
    auto data = inData;
    AG::MergeSort<std::vector<int> > sorter{ data };
    sorter.Sort();
    for (auto& i : data)
      std::cout << i << " ";
    std::cout << "\n";
  };

  auto doBUMergeTest = [](std::vector<int>& inData) {
    auto data = inData;
    AG::BottomUpMergeSort<std::vector<int> > sorter{ data };
    sorter.Sort();
    for (auto& i : data)
      std::cout << i << " ";
    std::cout << "\n";
  };

  std::vector<int> longAndRepeated{ 3,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9,5,2,43,2,23,99,23,1,23,1,6,8,2,3,1,99,9 };
  doNormalMergeTest(longAndRepeated);
  doBUMergeTest(longAndRepeated);

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

  std::cout << "\n\n";
}


void RunMergesortTests()
{
  SimpleMergeSortTesting();
}


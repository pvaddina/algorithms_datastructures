#include <iostream>
#include "common.h"
#include <vector>
#include "data_vec.h"
#include "data_std_array.h"
#include "selection_sort.h"

//extern int data_array[];
extern std::vector<int> data_vec;
constexpr size_t NUM_ITEMS = 10000;
extern std::array<int,NUM_ITEMS> data_std_array;

template <typename T> void TestSort(T& sortFn)
{
  Utils::Timer t;
  t.Start();
  sortFn();
  //AG::SelSearch<T> sort{ data };
  //sort.Sort();
  t.Stop();
  std::cout << "Time for sorting=" << t.GetDuration<std::milli>() << std::endl;
}

template <typename T> struct MySortOp
{
  MySortOp(T& _data) : data{ _data } {}
  T& data;
  void operator()()
  {
    AG::SelectionSort<T> sort{ data };
    sort.Sort();
  }
};

template <typename T> struct StdSortOp
{
  StdSortOp(T& _data) : data{ _data } {}
  T& data;
  void operator()()
  {
    std::sort(data.begin(), data.end());
  }
};

int main()
{
  std::cout << "My selection sort implementation ..." << std::endl;
  TestSort(MySortOp<std::array<int,NUM_ITEMS> >(data_std_array));
  TestSort(MySortOp<std::vector<int> >(data_vec));

  std::cout << "\n\nstd::sort algorithm implementation ..." << std::endl;
  TestSort(StdSortOp<std::array<int, NUM_ITEMS> >(data_std_array));
  TestSort(StdSortOp<std::vector<int> >(data_vec));
  return 0;
}


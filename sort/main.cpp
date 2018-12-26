#include <iostream>
#include <vector>
#include "common.h"
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
  t.Stop();
  std::cout << "Time for sorting=" << t.GetDuration<std::milli>() << "ms" << std::endl;
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
  auto std_array_copy = data_std_array;
  auto vec_data_copy = data_vec;

  std::cout << "My selection sort implementation ..." << std::endl;
  TestSort(MySortOp<std::array<int,NUM_ITEMS> >(data_std_array));
  TestSort(MySortOp<std::vector<int> >(data_vec));

  std::cout << "\n\nstd::sort algorithm implementation ..." << std::endl;
  TestSort(StdSortOp<std::array<int, NUM_ITEMS> >(std_array_copy));
  TestSort(StdSortOp<std::vector<int> >(vec_data_copy));

  if (std_array_copy != data_std_array)
  {
    std::cout << "The sorted std::arrays do not match. There is something wrong in your sort implementation" << std::endl;
  }
  else
  {
    std::cout << "Your sorted algorithm gives the same result as the std implementation" << std::endl;
  }

  if (vec_data_copy != data_vec)
  {
    std::cout << "The sorted vectors do no match. There is something wrong in your sort implementation" << std::endl;
  }
  else
  {
    std::cout << "Your sorted algorithm gives the same result as the std implementation" << std::endl;
  }
  return 0;
}


#include <iostream>
#include <vector>
#include <string>
#include "common.h"
#include "data_vec.h"
#include "data_std_array.h"

#include "selection_sort.h"
#include "insertion_sort.h"

template <typename T> void TestSort(T& sortFn)
{
  Utils::Timer t;
  t.Start();
  sortFn();
  t.Stop();
  std::cout << "Time for sorting=" << t.GetDuration<std::milli>() << "ms" << std::endl;
}

template <template <typename> class STYP, typename T> struct MySortOp
{
  MySortOp(T& _data) : data{ _data } {}
  T& data;
  void operator()()
  {
    typename STYP<T> sort{ data };
    sort.Sort();
  }
};

template <typename T> using SelSortTyp = MySortOp<AG::SelectionSort, T >;
template <typename T> using InsSortTyp = MySortOp<AG::InsertionSort, T>;

template <typename T> struct StdSortOp
{
  StdSortOp(T& _data) : data{ _data } {}
  T& data;
  void operator()()
  {
    std::sort(data.begin(), data.end());
  }
};


template <typename T>
void Validate(const T& myData, const T& stdData, const std::string implName)
{
  if (myData != stdData)
  {
    std::cout << "Error !!! There is something wrong in your " << implName << " sort implementation" << std::endl;
  }
  else
  {
    std::cout << "SUCCESS !!! Your " << implName << " sort algorithm gives the same result as the std implementation" << std::endl;
  }
}


int main()
{
  std::cout << "My selection sort implementation ..." << std::endl;
  TestSort(SelSortTyp<Data::MyStdArray>(Data::data_std_array));
  TestSort(SelSortTyp<std::vector<int> >(Data::data_vec));

  auto stdArrayCopy1 = Data::data_std_array;
  auto stdVecDataCopy1 = Data::data_vec;

  std::cout << "My insertion sort implementation ..." << std::endl;
  TestSort(SelSortTyp<Data::MyStdArray>(stdArrayCopy1));
  TestSort(SelSortTyp<std::vector<int> >(stdVecDataCopy1));

  auto stdArrayCopy_std = Data::data_std_array;
  auto stdVecDataCopy_std = Data::data_vec;

  std::cout << "\n\nstd::sort algorithm implementation ..." << std::endl;
  TestSort(StdSortOp<Data::MyStdArray >(stdArrayCopy_std));
  TestSort(StdSortOp<std::vector<int> >(stdVecDataCopy_std));

  std::cout << std::endl << std::endl;
  Validate(Data::data_std_array, stdArrayCopy_std, "Selection");
  Validate(Data::data_vec, stdVecDataCopy_std, "Selection");

  Validate(stdArrayCopy1, stdArrayCopy_std, "Insertion");
  Validate(stdVecDataCopy1, stdVecDataCopy_std, "Insertion");

  return 0;
}


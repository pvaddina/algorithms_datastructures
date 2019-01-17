#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "timer.h"
#include "data/data_vec_10000.h"
#include "data/data_std_array_10000.h"
#include "mergesort_tests.h"

#include "selection_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"

template <typename CTYP> void TestSort(CTYP&& sortFn)
{
  Utils::Timer t;
  t.Start();
  sortFn();
  t.Stop();
  std::cout << "Time for sorting=" << t.GetDuration<std::milli>() << "ms" << std::endl;
}

template <typename STYP, typename CTYP> struct MySortOp
{
  MySortOp(CTYP& _data) : data{ _data } {}
  CTYP& data;
  void operator()()
  {
    STYP sorter{ data };
    sorter.Sort();
  }
};

template <typename CTYP> using SelSortTyp = MySortOp<AG::SelectionSort<CTYP>, CTYP>;
template <typename CTYP> using MergeSortTyp = MySortOp<AG::MergeSort<CTYP>, CTYP>;
template <typename CTYP> using BUMergeSortTyp = MySortOp<AG::BottomUpMergeSort<CTYP>, CTYP>;
template <typename CTYP, typename DTyp> using InsSortGap1 = MySortOp<AG::InsertionSort<CTYP, DTyp, 1>, CTYP>;

template <typename CTYP> struct StdSortOp
{
  StdSortOp(CTYP& _data) : data{ _data } {}
  CTYP& data;
  void operator()()
  {
    std::sort(data.begin(), data.end());
  }
};

template <typename STYP, typename CTYP> struct ShellSortOp
{
  ShellSortOp(CTYP& _data, std::vector<size_t>&& g) : data{ _data }, gaps{ g } {}
  CTYP& data;
  std::vector<size_t> gaps;
  void operator()()
  {
    for (auto& gap : gaps)
    {
      auto sorter{ STYP{data, gap} };
      sorter.Sort();
    }
  }
};
template <typename CTYP, typename DTyp> using ShellSortTyp = ShellSortOp<AG::ShellSort<CTYP, DTyp>, CTYP>;


template <typename CTYP>
void Validate(const CTYP& myData, const CTYP& stdData, const std::string implName)
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


void TestCompareAllSortAlgos()
{
  auto stdArrayCopy1 = Data::data_std_array_10000;
  auto stdVecDataCopy1 = Data::data_vec_10000;

  auto stdArrayCopy_std = Data::data_std_array_10000;
  auto stdVecDataCopy_std = Data::data_vec_10000;

  auto stdArrayCopy_hibbard = Data::data_std_array_10000;
  auto stdVecDataCopy_hibbard = Data::data_vec_10000;

  auto stdArrayCopy_papernov = Data::data_std_array_10000;
  auto stdVecDataCopy_papernov = Data::data_vec_10000;

  auto stdArrayCopy_pratt1 = Data::data_std_array_10000;
  auto stdVecDataCopy_pratt1 = Data::data_vec_10000;

  auto stdArrayCopy_pratt2 = Data::data_std_array_10000;
  auto stdVecDataCopy_pratt2 = Data::data_vec_10000;

  auto stdArrayCopy_sedgewick1 = Data::data_std_array_10000;
  auto stdVecDataCopy_sedgewick1 = Data::data_vec_10000;

  auto stdArrayCopy_sedgewick2 = Data::data_std_array_10000;
  auto stdVecDataCopy_sedgewick2 = Data::data_vec_10000;

  auto stdArrayCopy_sedgewick3 = Data::data_std_array_10000;
  auto stdVecDataCopy_sedgewick3 = Data::data_vec_10000;

  auto stdArrayCopy_tokuda = Data::data_std_array_10000;
  auto stdVecDataCopy_tokuda = Data::data_vec_10000;

  auto stdArrayCopy_ciura = Data::data_std_array_10000;
  auto stdVecDataCopy_ciura = Data::data_vec_10000;

  auto stdArrayCopy_mergesort = Data::data_std_array_10000;
  auto stdVecDataCopy_mergesort = Data::data_vec_10000;

  auto stdArrayCopy_bumergesort = Data::data_std_array_10000;
  auto stdVecDataCopy_bumergesort = Data::data_vec_10000;

  std::cout << "My selection sort implementation ..." << std::endl;
  TestSort(SelSortTyp<Data::MyStdArray10000>(Data::data_std_array_10000));
  TestSort(SelSortTyp<std::vector<int> >(Data::data_vec_10000));
  std::cout << "Applying the selection sort on already sorted data ..." << std::endl;
  TestSort(SelSortTyp<Data::MyStdArray10000>(Data::data_std_array_10000));
  TestSort(SelSortTyp<std::vector<int> >(Data::data_vec_10000));

  std::cout << "\n\nMy merge sort implementation ..." << std::endl;
  TestSort(MergeSortTyp<Data::MyStdArray10000>(stdArrayCopy_mergesort));
  TestSort(MergeSortTyp<std::vector<int> >(stdVecDataCopy_mergesort));
  std::cout << "Applying the merge sort on already sorted data ..." << std::endl;
  TestSort(MergeSortTyp<Data::MyStdArray10000>(stdArrayCopy_mergesort));
  TestSort(MergeSortTyp<std::vector<int> >(stdVecDataCopy_mergesort));

  std::cout << "\n\nMy bottom up merge sort implementation ..." << std::endl;
  TestSort(BUMergeSortTyp<Data::MyStdArray10000>(stdArrayCopy_bumergesort));
  TestSort(BUMergeSortTyp<std::vector<int> >(stdVecDataCopy_bumergesort));
  std::cout << "Applying the bottom up merge sort on already sorted data ..." << std::endl;
  TestSort(BUMergeSortTyp<Data::MyStdArray10000>(stdArrayCopy_bumergesort));
  TestSort(BUMergeSortTyp<std::vector<int> >(stdVecDataCopy_bumergesort));

  std::cout << "\n\nMy insertion sort implementation ..." << std::endl;
  TestSort(InsSortGap1<Data::MyStdArray10000, int>(stdArrayCopy1));
  TestSort(InsSortGap1<std::vector<int>, int>(stdVecDataCopy1));
  std::cout << "Applying the insertion sort on already sorted data ..." << std::endl;
  TestSort(InsSortGap1<Data::MyStdArray10000, int>(stdArrayCopy1));
  TestSort(InsSortGap1<std::vector<int>, int>(stdVecDataCopy1));


  std::cout << "\n\nShell sorting using Hibbard gaps ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_hibbard, { 63,31,15,7,3,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_hibbard, { 63,31,15,7,3,1 }));

  std::cout << "\n\nShell sorting using Papernov & Stasevich gaps ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_papernov, { 65,33,17,9,5,3,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_papernov, { 65,33,17,9,5,3,1 }));

  std::cout << "\n\nShell sorting using Pratt gaps version-1 ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_pratt1, { 12,9,8,6,4,3,2,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_pratt1, { 12,9,8,6,4,3,2,1 }));

  std::cout << "\n\nShell sorting using Pratt gaps version-2 ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_pratt2, { 121,40,13,4,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_pratt2, { 121,40,13,4,1 }));

  std::cout << "\n\nShell sorting using Sedgewick gaps version-1 ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_sedgewick1, { 112,48,21,7,3,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_sedgewick1, { 112,48,21,7,3,1 }));

  std::cout << "\n\nShell sorting using Sedgewick gaps version-2 ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_sedgewick2, { 281,77,23,8,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_sedgewick2, { 281,77,23,8,1 }));

  std::cout << "\n\nShell sorting using Sedgewick gaps version-3 ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_sedgewick3, { 109,41,19,5,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_sedgewick3, { 109,41,19,5,1 }));

  std::cout << "\n\nShell sorting using Tokuda gaps ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_tokuda, { 103,46,20,9,4,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_tokuda, { 103,46,20,9,4,1 }));

  std::cout << "\n\nShell sorting using Ciura gaps ..." << std::endl;
  TestSort(ShellSortTyp<Data::MyStdArray10000, int >(stdArrayCopy_ciura, { 701,301,132,57,23,10,4,1 }));
  TestSort(ShellSortTyp<std::vector<int>, int >(stdVecDataCopy_ciura, { 701,301,132,57,23,10,4,1 }));

  std::cout << "\n\nstd::sort algorithm implementation ..." << std::endl;
  TestSort(StdSortOp<Data::MyStdArray10000 >(stdArrayCopy_std));
  TestSort(StdSortOp<std::vector<int> >(stdVecDataCopy_std));
  std::cout << "Applying std::sort algorithm on already sorted data ..." << std::endl;
  TestSort(StdSortOp<Data::MyStdArray10000 >(stdArrayCopy_std));
  TestSort(StdSortOp<std::vector<int> >(stdVecDataCopy_std));


  std::cout << std::endl << std::endl;
  Validate(Data::data_std_array_10000, stdArrayCopy_std, "Selection");
  Validate(Data::data_vec_10000, stdVecDataCopy_std, "Selection");
  Validate(stdArrayCopy_mergesort, stdArrayCopy_std, "Merge");
  Validate(stdVecDataCopy_mergesort, stdVecDataCopy_std, "Merge");
  Validate(stdArrayCopy_bumergesort, stdArrayCopy_std, "Bottomup Merge");
  Validate(stdVecDataCopy_bumergesort, stdVecDataCopy_std, "Bottomup Merge");
  Validate(stdArrayCopy1, stdArrayCopy_std, "Insertion");
  Validate(stdVecDataCopy1, stdVecDataCopy_std, "Insertion");
  Validate(stdArrayCopy_hibbard, stdArrayCopy_std, "Shellsort_Hibbard");
  Validate(stdVecDataCopy_hibbard, stdVecDataCopy_std, "Shellsort_Hibbard");
  Validate(stdArrayCopy_papernov, stdArrayCopy_std, "Shellsort_Papernov");
  Validate(stdVecDataCopy_papernov, stdVecDataCopy_std, "Shellsort_Papernov");
  Validate(stdArrayCopy_pratt1, stdArrayCopy_std, "Shellsort_Pratt1");
  Validate(stdVecDataCopy_pratt1, stdVecDataCopy_std, "Shellsort_Pratt1");
  Validate(stdArrayCopy_pratt2, stdArrayCopy_std, "Shellsort_Pratt2");
  Validate(stdVecDataCopy_pratt2, stdVecDataCopy_std, "Shellsort_Pratt2");
  Validate(stdArrayCopy_sedgewick1, stdArrayCopy_std, "Shellsort_Sedgewick1");
  Validate(stdVecDataCopy_sedgewick1, stdVecDataCopy_std, "Shellsort_Sedgewick1");
  Validate(stdArrayCopy_sedgewick2, stdArrayCopy_std, "Shellsort_Sedgewick2");
  Validate(stdVecDataCopy_sedgewick2, stdVecDataCopy_std, "Shellsort_Sedgewick2");
  Validate(stdArrayCopy_sedgewick3, stdArrayCopy_std, "Shellsort_Sedgewick3");
  Validate(stdVecDataCopy_sedgewick3, stdVecDataCopy_std, "Shellsort_Sedgewick3");
  Validate(stdArrayCopy_tokuda, stdArrayCopy_std, "Shellsort_Tokuda");
  Validate(stdVecDataCopy_tokuda, stdVecDataCopy_std, "Shellsort_Tokuda");
  Validate(stdArrayCopy_ciura, stdArrayCopy_std, "Shellsort_Ciura");
  Validate(stdVecDataCopy_ciura, stdVecDataCopy_std, "Shellsort_Ciura");
}

int main()
{
  RunMergesortTests();
  TestCompareAllSortAlgos();
}


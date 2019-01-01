#include <iostream>
#include <string>
#include <vector>
#include "data_std_array_20.h"
#include "data_vec_20.h"
#include "shuffle.h"
#include "randomgen.h"

void RandomGenTest()
{
  std::cout << "Random number generation between 0-10" << std::endl;
  Utils::FreeRandomGen r;
  for (int i=0; i<100; ++i)
    std::cout << r.Get(0,10) << " ";

  std::cout << "\n\nRandom number generation betweeen 437-437" << std::endl;
  for (int i = 0; i<100; ++i)
    std::cout << r.Get(437, 437) << " ";

  std::cout << "\n\nRandom number generation betweeen 0-999" << std::endl;
  Utils::RandomGen r1{ 0,999 };
  for (int i = 0; i<100; ++i)
    std::cout << r1.Get() << " ";

  std::cout << "\n\n\n";
}

extern std::vector<int> Data::data_vec_20;
extern Data::MyStdArray20 Data::data_std_array_20;

template <typename T>
void PrintDS(std::string&& prefix, T& data)
{
  std::cout << prefix;
  for (auto& i : data)
  {
    std::cout << i << " ";
  }
}

void ShuffleTest()
{
  AG::Shuffler<std::vector<int> > sh{ Data::data_vec_20 };
  PrintDS("Vector BEFORE shuffling: ", Data::data_vec_20);
  sh.Shuffle();
  PrintDS("\nVector AFTER shuffling: ", Data::data_vec_20);

  AG::Shuffler<Data::MyStdArray20 > sh1{ Data::data_std_array_20 };
  PrintDS("\n\nstd::array BEFORE shuffling: ", Data::data_std_array_20);
  sh1.Shuffle();
  PrintDS("\nstd::array AFTER shuffling: ", Data::data_std_array_20);
}

int main()
{
  RandomGenTest();
  ShuffleTest();

  std::cout << "\n\n";
  return 0;
}




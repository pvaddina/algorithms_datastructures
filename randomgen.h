#pragma once

#include <memory>
#include <random>

namespace Utils
{
  // Recipe based on the example from:
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

  class RandomGen
  {
    public:
      RandomGen(const int start, const int end) 
        : rgen{ std::random_device()() }
        , distribution{ new std::uniform_int_distribution<int>{start, end} }
      {}

      int Get() { return (*distribution)(rgen); }

    private:
      std::mt19937 rgen; //Standard mersenne_twister_engine seeded with rd()
      std::unique_ptr<std::uniform_int_distribution<int> > distribution;
  };

  class FreeRandomGen
  {
  public:
    FreeRandomGen()
      : rgen{ std::random_device()() }
      , distribution{ nullptr }
    {}

    int Get(const int start, const int end)
    {
      distribution.reset(new std::uniform_int_distribution<int>{ start, end });
      return (*distribution)(rgen);
    }

  private:
    std::mt19937 rgen; //Standard mersenne_twister_engine seeded with rd()
    std::unique_ptr<std::uniform_int_distribution<int> > distribution;
  };
}





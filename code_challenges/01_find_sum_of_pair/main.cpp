#include <iostream>
#include <vector>
#include <unordered_set>

//
// Sample (integer and unordered) data, potentially with negative values.
// 
std::vector<int> a{ 3, 4, 89, 3, 54, 2, -45, 7 };
std::vector<int> b{ 89, -343, 23, 5456, 2, 45, 0, 1, 234, 331, 9 };

// 
// A function that returns on finding a pair whose sum is equal to a specific value
// 
bool ContainsPairWithSum(const std::vector<int>& data, int sum)
{
  std::unordered_set<int> comp;
  for (auto value : data)
  {
    if(comp.find(sum - value) != comp.end()) 
    {
      return true;
    }
    comp.insert(value);
  }
  return false;
}

// 
// A function that returns all the pairs whose sum is equal to a specific value
// 
std::vector<std::pair<int, int> > FindPairs(const std::vector<int>& data, const int sum)
{
  std::vector<std::pair<int, int> > fPairs;
  std::unordered_set<int> comp;
  
  for (auto value : data)
  {
    auto it = comp.find(sum - value);
    if (it != comp.end())
    {
      fPairs.push_back(std::pair<int, int>(*it, value));
    }
    comp.insert(value);
  }
  return fPairs;
}

int main()
{
  std::cout << ContainsPairWithSum(a, 9) << std::endl;
  std::vector<std::pair<int, int> > pairs = FindPairs(a, 9);
  for (auto i : pairs)
  {
    std::cout << i.first << " " << i.second << std::endl;
  }

  std::vector<std::pair<int, int> > pairs1 = FindPairs(b, 33);
  for (auto i : pairs1)
  {
    std::cout << i.first << " " << i.second << std::endl;
  }

  return 0;
}





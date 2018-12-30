#include <iostream>
#include <vector>
#include <string>
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

void PrintDs(const std::string& str, std::vector<int>& v)
{
  std::cout << str << " = {";
  auto sz = v.size();
  auto i = 0;
  for (auto& item : v)
  {
    if ( i+1 == sz )
      std::cout << item;
    else
      std::cout << item << ", ";
    ++i;
  }
  std::cout << "};\n";
}

int main()
{
  PrintDs("a", a);
  PrintDs("b", b);
  std::cout << std::endl;

  constexpr auto a_sumpair = 9;
  constexpr auto b_sumpair = 33;

  while (true)
  {
    std::string dstyp;
    std::string strSum;
    std::cout << "Enter the DS type: ";
    std::getline(std::cin, dstyp);
    auto ds = a;
    if (dstyp == "b") { ds = b; }

    std::cout << "Enter the value you are looking for: ";
    std::getline(std::cin, strSum);
    auto sum = std::stoi(strSum);

    std::cout << "Does the container has a pair whose sum is:" << sum << "? " << ContainsPairWithSum(ds, sum) << std::endl;
    std::cout << "The pairs whose sum is " << sum << " are given below:" << std::endl;
    std::vector<std::pair<int, int> > pairs = FindPairs(ds, sum);
    for (auto i : pairs)
    {
      std::cout << "      " << i.first << " " << i.second << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}





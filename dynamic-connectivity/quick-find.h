#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace AG
{
  // Data representation
  //
  // Index:0  1  2  3  4  5  6  7  8
  // mIds :0  1  2  3  4  5  6  7  8
  //
  // The indices indicates the items
  // Where as the array, mIds indicate the item to which the item at a particular index
  // is connected. In the example above at the beginning of the algorithm, each item is 
  // connected to itself. 
  //
  // Index:0  1  2  3  4  5  6  7  8
  // mIds :0  3  2  3  4  3  6  3  8
  //
  // Here the items with indices, 1, 3n 5 and 7 are all connected to 3. Meaning they all form a component
  class QuickFind
  {
    public:
      QuickFind(const int N)
      {
        for (auto i = 0; i < N; ++i)
        {
          mIds.push_back(i);
        }
      }

      bool Connected(const int p, const int q)
      {
        return mIds[p] == mIds[q];
      }

      // A linear algorith to union
      void Union(const int p, const int q)
      {
        const int id2Change = mIds[p];
        const int targetId = mIds[q];
        const int N = mIds.size();
        mIds[p] = targetId;
        for (auto i = 0; i<N; ++i)
        {
          if (mIds[i] == id2Change)
          {
            mIds[i] = targetId;
          }
        }
      }

      void Print(const std::string& s)
      {
        const int N = mIds.size();
        std::cout << s;
        for (auto i = 0; i<N; ++i)
        {
          std::cout << mIds[i] << " ";
        }
        std::cout << std::endl;
      }

    private:
      std::vector<int> mIds;
  };
}

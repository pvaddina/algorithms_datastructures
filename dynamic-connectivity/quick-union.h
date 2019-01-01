#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace AG
{
  class QuickUnion
  {
    public:
      QuickUnion(const int N)
      {
        for (auto i = 0; i < N; ++i)
        {
          mIds.push_back(i);
        }
      }

      int Root(const int p)
      {
        int i = p;
        // Keep going as long as the id of a particular index is its index itself
        // When both are equal it indicates a root item and we cannot traverse further up
        while(mIds[i] != i)                             
        {
          i = mIds[i];
        }
        return i;
      }

      bool Connected(const int p, const int q)
      {
        // If the root of p, is the same as q, then both are connected
        return Root(p) == Root(q);
      }

      void Union(const int p, const int q)
      {
        // Make a connection from the root of p, to the root of q
        // A Merge operation of two trees
        mIds[Root(p)] = Root(q);
      }

      void Print(const std::string& s)
      {
        const size_t N = mIds.size();
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

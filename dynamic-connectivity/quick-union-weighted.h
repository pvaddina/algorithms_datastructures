#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace AG
{
  class QuickUnionWeighted
  {
    public:
      QuickUnionWeighted(const int N)
      {
        for (auto i = 0; i < N; ++i)
        {
          mIds.push_back(i);
          mWeights.push_back(1); // At the beginning all the weights are just 1
        }
      }

      int Root(const int p)
      {
        // Keep going as long as the id of a particular index is its index itself
        // When both are equal it indicates a root item and we cannot traverse further up
        int i = p;
        while(mIds[i] != i)
        {
          i = mIds[i];
        }
        return i;
      }

      bool Connected(const int p, const int q)
      {
        return Root(p) == Root(q);
      }

      void Union(const int p, const int q)
      {
        auto rootP = Root(p);
        auto rootQ = Root(q);

        // This function will perform a union of P, with Q.
        // Meaning after this operation, the tree with P as root
        // will go under/connect to the tree with Q as root. 
        // Therefore, the new weight of P will will be 0, 
        // and the weight of Q will increase by the weight of P.
        auto unionP2Q = [&](const int p, const int q) {
          mIds[p] = mIds[q];
          mWeights[q] += mWeights[p];
          mWeights[p] = 0;
        };

        if (mWeights[rootP] >= mWeights[rootQ])
        {
          unionP2Q(rootQ, rootP);
        }
        else
        {
          unionP2Q(rootP, rootQ);
        }
      }

      void Print(const std::string& s)
      {
        const size_t N = mIds.size();
        std::cout << s;
        for (auto i = 0; i<N; ++i)
        {
          std::cout << mIds[i] << " ";
        }
        std::cout << "; Weights= ";
        for (auto i = 0; i<N; ++i)
        {
          std::cout << mWeights[i] << " ";
        }
        std::cout << std::endl;
      }

    private:
      std::vector<int> mIds;
      std::vector<int> mWeights; // Weights of all items, where a weight indicates 
                                 // the number of items under it as children. At 
                                 // the very beginning there is just one item at 
                                 // each index. Therefore, each item contains a value 1
  };
}

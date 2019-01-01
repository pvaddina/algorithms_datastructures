#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace AG
{
  class QuickUnionWtPathComp
  {
    public:
      QuickUnionWtPathComp(const int N)
      {
        for (auto i = 0; i < N; ++i)
        {
          mIds.push_back(i); // At the beginning, each item is connected to itself
          mWeights.push_back(1); // At the beginning all the weights are just 1
          mComponentLargest.push_back(i); // At the beginning, since an item is connected
                                          // to itself, the largest item of the component
                                          // is also itself
        }
      }

      // Get the parent of the current parent, and set it as the new parent
      // Over time this will result in a shorter tree.
      //                2
      //              /   \
      //             4     7
      //            /
      //           5
      //          / \
      //         9   3 
      // In the figure above when p = 3;
      // Loop-1: i = 3; mIds[3] = 5; Inside the loop, mIds[3] = mIds[mIds[3]] = mIds[5] = 4; 
      //         After the end of loop-1, '4' will be the root of the item, '3'
      //                2
      //              /   \
      //             4     7
      //            / \
      //           5   3
      //          / 
      //         9   
      // Loop-2: i = 4; mIds[4] = 2; Again, mIds[4] = mIds[mIds[4]] = mIds[2] = 2; 
      //         After this loop the value of root of '4' does not change. But if there were something
      //         else as the root of 2, then it could be have been the new root. 
      size_t Root(const size_t p)
      {
        size_t i = p;
        while(mIds[i] != i)
        {
          mIds[i] = mIds[mIds[i]];
          i = mIds[i];
        }
        return i;
      }

      bool Connected(const size_t p, const size_t q)
      {
        return Root(p) == Root(q);
      }

      bool SystemPercolates()
      {
        return Connected(0, mIds.size()-1);
      }

      void Union(const int p, const int q)
      {
        auto rootP = Root(p);
        auto rootQ = Root(q);
        auto largest = p > q ? p : q;

        // This function will perform a union of P, with Q.
        // Meaning after this operation, the tree with P as root
        // will go under/connect to the tree with Q as root. 
        // Therefore, the new weight of P will will be 0, 
        // and the weight of Q will increase by the weight of P.
        //
        // This will also find if the largest among p and q, who shall
        // be part of the same component this point on, is largest or smallest
        // to the current value set at the root of this component. Accordingly
        // the value at the root will be reset. Note that the rest of the items 
        // in the sub tree still contain the older largest values. Since 
        // we always see the value stored in the root, it shall contain the 
        // correct value always.
        auto unionP2Q = [&](const size_t p, const size_t q) {
          mIds[p] = mIds[q];
          mWeights[q] += mWeights[p];
          mWeights[p] = 0;
          mComponentLargest[q] = mComponentLargest[q] > largest ? mComponentLargest[q] : largest;
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

      int find(const int p)
      {
        return mComponentLargest[Root(p)];
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
      std::vector<int> mComponentLargest;
  };
}

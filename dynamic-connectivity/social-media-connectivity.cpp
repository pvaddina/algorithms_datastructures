// Social network connectivity. Given a social network containing n members and a 
// log file containing m timestamps at which times pairs of members formed friendships, 
// design an algorithm to determine the earliest time at which all members are connected 
// (i.e., every member is a friend of a friend of a friend ... of a friend). Assume 
// that the log file is sorted by timestamp and that friendship is an equivalence relation. 
// The running time of your algorithm should be mlogn or better and use extra 
// space proportional to n.

#include <iostream>
#include "quick-union-wt-pcomp.h"

class SocialMediaAlgos
{
  public:
    int GetEarliestFriendshipTime()
    {
      int time = 0;
      auto it = mLogEntries.begin();
      while(it != mLogEntries.end() )
      {
        mSocialNw.Union(it->first, it->second);
        ++it;
        ++time;
        if (mSocialNw.SystemPercolates())
        {
          break;
        }
      }
      return time;
    }
  private:
    std::unique<QuickUnionWtPathComp> mSocialNw;
    std::vector<std::pair<int,int> > mLogEntries;
};



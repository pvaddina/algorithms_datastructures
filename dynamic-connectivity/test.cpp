#include "quick-find.h"
#include "quick-union.h"
#include "quick-union-weighted.h"
#include "quick-union-wt-pcomp.h"


template <typename T>
void test_quick_find()
{
  std::cout << "#######################################################\n";
  T qf{10};

  qf.Union(4,3);
  qf.Print("qf.Union(4,3): ");

  qf.Union(3,8);
  qf.Print("qf.Union(3,8): ");

  qf.Union(6,5);
  qf.Print("qf.Union(6,5): ");

  qf.Union(9,4);
  qf.Print("qf.Union(9,4): ");

  qf.Union(2,1);
  qf.Print("qf.Union(2,1): ");

  std::cout << "qf.Connected(8, 9) = " << qf.Connected(8, 9) << std::endl;
  std::cout << "qf.Connected(5, 0) = " << qf.Connected(5, 0) << std::endl;

  qf.Union(5, 0);
  qf.Print("qf.Union(5,0): ");

  std::cout << "qf.Connected(5, 0) = " << qf.Connected(5, 0) << std::endl;

  qf.Union(7, 2);
  qf.Print("qf.Union(7,2): ");

  qf.Union(6, 1);
  qf.Print("qf.Union(6,1): ");

  qf.Union(7, 3);
  qf.Print("qf.Union(7,3): ");
}


int main()
{
  test_quick_find<AG::QuickFind>();
  test_quick_find<AG::QuickUnion>();
  test_quick_find<AG::QuickUnionWeighted>();
  test_quick_find<AG::QuickUnionWtPathComp>();

  return 0;
}
#include <iostream>
#include "stack.h"

int main()
{
  AG::Stack<int> st;

  for (int i=0; i<100; ++i)
    st.Push(i);

  auto sz = st.Size();
  for (int i = 0; i < sz; ++i)
  {
    std::cout << st.Top() << std::endl;
    st.Pop();
  }

  return 0;
}



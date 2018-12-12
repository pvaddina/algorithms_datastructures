#pragma once

namespace AG
{
  template <typename T>
  class Stack
  {
    public:
      Stack();
      void Push(T& item);
      T& Top();
      void Pop();
      size_t Size() const;
#if 0
      bool IsEmpty() const;
#endif
    private:
      void Resize();
    private:
      T * mArray = nullptr;
      size_t mN = 0;
      size_t mMaxSize = 0;
  };

  template <typename T>
  void Stack<T>::Resize()
  {
    if (mN == mMaxSize)
    {
      auto oldArray = mArray;
      auto oldSz = mMaxSize;
      mMaxSize = oldSz * 2;
      mArray = new T[mMaxSize];

      for (size_t i = 0; i < oldSz; ++i)
        mArray[i] = oldArray[i];
    }
   }

  template <typename T>
  Stack<T>::Stack()
  {
    auto sz = 1;
    mArray = new T[sz];
    mMaxSize = sz;
  }

  template <typename T>
  void Stack<T>::Push(T& item)
  {
    mArray[mN++] = item;
    Resize();
  }

  template<typename T>
  T& Stack<T>::Top()
  {
    return mArray[mN-1];
  }

  template<typename T>
  void Stack<T>::Pop()
  {
    if (mN > 0)
    {
      --mN;
    }
  }

  template<typename T>
  size_t Stack<T>::Size() const
  {
    return mN;
  }

}



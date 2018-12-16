#pragma once
#include <memory>

namespace AG
{
  ///
  /// \brief Stack class
  /// A stack implementation with a resizing array. Meaning the stack is
  /// initialized with a size of 1. And after every push the size of the array
  /// is checked and if it is equal to the size of the array, then a new
  /// array with double the size is created and existing items are copied
  /// in the new array.
  /// Similarly when an item is popped, and if the size if 1/4th the size 
  /// of the array, then a new array with 1/2 the size of the actual array
  /// is created and used
  template <typename T>
  class Stack
  {
    public:
      Stack() { Resize(1); }

      void push(T& item)
      {
        // Copy assignment operation
        //std::cout << "Copy pushing ....\n";
        mArray[mLen++] = item;
        if (mLen == mMaxSize)
        {
          Resize(mMaxSize * 2);
        }
      }
      void push(T&& item)
      {
        // Move assignment operation
        //std::cout << "Move pushing ....\n";
        mArray[mLen++] = std::move(item);
        if (mLen == mMaxSize)
        {
          Resize(mMaxSize * 2);
        }
      }
      template <typename... Ts>
      void emplace(Ts&&... args)
      {
        mArray[mLen++] = std::move(T(std::forward<Ts>(args)...));
        if (mLen == mMaxSize)
        {
          Resize(mMaxSize * 2);
        }
      }
      T& top()
      {
        return mArray[mLen - 1];
      }
      void pop()
      {
        if (mLen > 0)
        {
          --mLen;
          if (mLen > 0 && mLen == mMaxSize / 4)
          {
            Resize(mMaxSize / 2);
          }
        }
      }
      size_t size() const { return mLen; }
      bool empty() const { return mLen == 0; }
  private:
      void Resize(const size_t newSz)
      {
        auto oldArray = mArray;
        mMaxSize = newSz;
        // Call to default constructor
        mArray = new T[mMaxSize];
        for (size_t i = 0; i < mLen; ++i)
        {
          // Move assignment operation
          mArray[i] = std::move(oldArray[i]);
        }
      }

    private:
      T * mArray = nullptr;
      size_t mLen = 0;
      size_t mMaxSize = 0;
  };

  ///
  /// \brief LLStack class
  /// A stack implementation with a linked list. Here a simple node structure
  /// represents each item that is pushed on the stack.
  /// The node holds a link to the last item in the list. The first item
  /// of the stack does not point to anything else.
  template <typename T>
  class LLStack
  {
  public:
    LLStack() {}
    void push(T& item)
    {
      auto lastNode = mLast;
      mLast = new Node<T>{};
      mLast->item = item;
      mLast->pPrevItem = lastNode;
      ++mLen;
    }
    void push(T&& item)
    {
      auto lastNode = mLast;
      mLast = new Node<T>{};
      mLast->item = std::move(item);
      mLast->pPrevItem = lastNode;
      ++mLen;
    }
    template <typename... Ts>
    void emplace(Ts&&... args)
    {
      push(T{ std::forward<Ts>(args)... });
    }
    T& top() { return mLast->item; }
    void pop()
    {
      if (mLen > 0)
      {
        auto node2Del = mLast;
        mLast = mLast->pPrevItem;
        delete node2Del;
        --mLen;
      }
    }
    size_t size() const { return mLen; }
    bool empty() const { return mLen == 0; }
  private:
    template <typename U> struct Node
    {
      U item;
      Node<U>* pPrevItem;
    };
    Node<T>* mLast = nullptr;
    size_t mLen = 0;
  };
}



#pragma once
#include <memory>

namespace DS
{
  ///
  /// \brief Queue class
  /// A Queue implementation with a resizing array. Meaning the Queue is
  /// initialized with a size of 1. And after every push the size of the Queue
  /// is checked and if it is equal to the size of the array, then a new
  /// array with double the size is created and existing items are copied
  /// in the new array.
  /// Similarly when an item is popped, and if the size of the queue is 1/4th the size 
  /// of the array, then a new array with 1/2 the size of the actual array
  /// is created and used
  /// Cases when not to access the front/back items:
  ///    1. Immediately after creating the queue
  ///    2. When size of the queue is 0, say by popping all the elements enqueued in it
  template <typename T>
  class Queue
  {
    public:
      Queue() { Resize(1); }
      ~Queue() 
      {
        for (size_t i = 0; i < mLen; ++i)
        {
          pop();
        }
      }

      void push(T& item)
      {
        mArray[mLen++] = item;
        if (mLen == mMaxSize)
        {
          Resize(mMaxSize * 2);
        }
      }
      void push(T&& item)
      {
        mArray[mLen++] = std::move(item);
        if (mLen == mMaxSize)
        {
          Resize(mMaxSize * 2);
        }
      }
      template <typename... Ts>
      void emplace(Ts&&... args)
      {
        push(T(std::forward<Ts>(args)...));
      }
      T& front() { return mArray[mFront]; }  // Get the first item of the stack
      T& back() { return mArray[mLen-1]; }   // To be called at least after the first push
      void pop()
      {
        if (mLen > 0)
        {
          --mLen;
          if (mLen > 0)
          {
            ++mFront;
            if (mLen == mMaxSize / 4)
            {
              Resize(mMaxSize / 2);
            }
          }
          else
          {
            mFront = 0;
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
        for (size_t i = mFront; i < mLen; ++i)
        {
          mArray[i] = std::move(oldArray[i]);
        }
        mFront = 0;
      }

    private:
      T * mArray = nullptr;
      size_t mLen = 0;
      size_t mMaxSize = 0;
      size_t mFront = 0;
  };

  ///
  /// \brief LLQueue class
  /// A Queue implementation with a linked list. Here a simple node structure
  /// represents each item that is pushed on the stack.
  /// The node holds a link to the last item in the list. The first item
  /// of the stack does not point to anything else.
  template <typename T>
  class LLQueue
  {
  public:
    LLQueue() {}
    ~LLQueue()
    {
      for (size_t i = 0; i < mLen; ++i)
      {
        pop();
      }
    }
    void push(T& item)
    {
      auto lastNode = mLast;
      mLast = new Node<T>{};
      mLast->item = item; // Copy the item
      mLast->pNextItem = nullptr;
      if (lastNode) { lastNode->pNextItem = mLast; }
      if (!mFirst) { mFirst = mLast; }
      ++mLen;
    }
    void push(T&& item)
    {
      auto lastNode = mLast;
      mLast = new Node<T>{};
      mLast->item = std::move(item); // Move the item
      mLast->pNextItem = nullptr;
      if (lastNode) { lastNode->pNextItem = mLast; }
      if (!mFirst) { mFirst = mLast; }
      ++mLen;
    }
    template <typename... Ts>
    void emplace(Ts&&... args)
    {
      push(T{ std::forward<Ts>(args)... });
    }
    T& front() { return mFirst->item; }
    T& back() { return mLast->item; }
    void pop()
    {
      if (mLen > 0)
      {
        auto node2Del = mFirst;
        mFirst = node2Del->pNextItem;
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
      Node<U>* pNextItem;
    };
    Node<T>* mFirst = nullptr;
    Node<T>* mLast = nullptr;
    size_t mLen = 0;
  };
}



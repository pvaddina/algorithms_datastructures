#pragma once
#include <memory>

namespace DS
{
  ///
  /// \brief LLQueue class
  /// A Queue implementation with a linked list. Here a simple node structure
  /// represents each item that is pushed on the stack.
  /// The node holds a link to the last item in the list. The first item
  /// of the stack does not point to anything else.
  template <typename T>
  class LLDeque
  {
  public:
    LLDeque() {}
    ~LLDeque()
    {
      for (size_t i = 0; i < mLen; ++i)
      {
        pop_back();
      }
    }
    void push_back(const T& item)
    {
      auto lastNode = mLast;
      mLast = new Node<T>{};
      mLast->item = item; // Copy the item
      OnPushBack(lastNode);
    }

    void push_back(T&& item)
    {
      auto lastNode = mLast;
      mLast = new Node<T>{};
      mLast->item = std::move(item); // Move the item
      OnPushBack(lastNode);
    }
    void push_front(const T& item)
    {
      auto frontNode = mFirst;
      mFirst = new Node<T>{};
      mFirst->item = item; // Copy the item
      OnPushFront(frontNode);
    }
    void push_front(T&& item)
    {
      auto frontNode = mFirst;
      mFirst = new Node<T>{};
      mFirst->item = std::move(item); // move the item
      OnPushFront(frontNode);
    }

    template <typename... Ts>
    void emplace(Ts&&... args)
    {
      push(T{ std::forward<Ts>(args)... });
    }
    T& front() { return mFirst->item; }
    T& back() { return mLast->item; }
    void pop_front()
    {
      if (mLen > 0)
      {
        auto node2Del = mFirst;
        mFirst = node2Del->pNextItem;
        delete node2Del;
        --mLen;
      }
    }
    void pop_back()
    {
      if (mLen > 0)
      {
        auto node2Del = mLast;
        mLast = node2Del->pPrevItem;
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
      Node<U>* pNextItem;
    };

    void OnPushBack(Node<T>* oldLastNode)
    {
      mLast->pPrevItem = oldLastNode;
      mLast->pNextItem = nullptr;
      if (oldLastNode) { oldLastNode->pNextItem = mLast; } // Establish a link between the last known 'last node' and the newly created 'last node'
      if (!mFirst) { mFirst = mLast; } // Until something is pushed onto the queue, 'mFirst' is uninitialized. Initialize 
                                       // it now. Unfortunately it is done once but the check if the pointer is initialized
                                       // need to be done always. Is there a better way ?
      ++mLen;
    }

    void OnPushFront(Node<T>* oldFrontNode)
    {
      mFirst->pPrevItem = nullptr;
      mFirst->pNextItem = oldFrontNode;
      if (oldFrontNode) { oldFrontNode->pPrevItem = mFirst; }
      if (!mLast) { mLast = mFirst; } // Check if mLast is not initialized, and if it is not, then initialize it here. 
      ++mLen;
    }

    Node<T>* mFirst = nullptr;
    Node<T>* mLast = nullptr;
    size_t mLen = 0;
  };
}



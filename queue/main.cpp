#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <queue>
#include "queue.h"

namespace T1
{
  template <typename T>
  void POD_Test(const std::string&& dtype)
  {
    auto start = std::chrono::steady_clock::now();
    T st;
    constexpr auto testSz = 1000000;

    //std::cout << "pushing: ";
    for (int i = 0; i < testSz; ++i)
    {
      //std::cout << i << " ";
      st.push(i);
    }
    //std::cout << "\n";

    auto sz = st.size();
    //std::cout << "Popping: ";
    for (size_t i = 0; i < sz; ++i)
    {
      auto& a = st.back();
      st.pop();
    }
    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Pusing/Popping " << testSz << " integers to the queue type:=" << dtype << ", took: " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
  }
}

namespace T2
{
  struct NoCopyData
  {
    NoCopyData() : name{}, ids{} {}
    NoCopyData(std::string&& n, std::vector<int>&& _ids) : name{ std::move(n) }, ids{ std::move(_ids) } {}

    // Copy construction and assignment are deleted
    NoCopyData(const NoCopyData&) = delete;
    NoCopyData& operator=(const NoCopyData&) = delete;

    // Move construction and assignment are enabled
    NoCopyData(NoCopyData&& data)
    {
      name = std::move(data.name);
      ids = std::move(data.ids);
    }
    NoCopyData& operator=(NoCopyData&& data)
    {
      name = std::move(data.name);
      ids = std::move(data.ids);
      return *this;
    }
  private:
    std::string name;
    std::vector<int> ids;
  };

  template <typename T>
  void TestComplexTyp(const std::string&& dtype)
  {
    auto start = std::chrono::steady_clock::now();
    T st;
    constexpr auto testSz = 900000;
    //std::cout << "Pusing objects constructed with rvalue refs, and finally being moved into the stack";
    for (int i = 0; i < testSz; ++i)
    {
      st.push(NoCopyData("name", { i, i + 1, i + 2, i + 3}));
    }
    //std::cout << "\n";

    NoCopyData data{ "Same item",{ 437, 438, 439, 440 } };
    //std::cout << "Pusing one single object using copy assignment into the stack";
    for (int i = 0; i < 50; ++i)
    {
      // Note without the move, the following operation will fail to compile
      // since the NoCopyData type does not support copying. 
      // And without the move, push of the stack will try to make a copy of the
      // passed object
      // Theoretically at the end of the move operation the data object should
      // be practically a zombie object with no data inside but for simplicity
      // it is not implemented here
      st.push(std::move(data));
    }

    auto sz = st.size();
    for (size_t i = 0; i < sz; ++i)
    {
      auto& a = st.back();
      st.pop();
    }

    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Pusing/Popping " << testSz << " complex('NoCopyData' type) to the queue type:=" << dtype << ", took: " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
  }

  template <typename T>
  void ComplexTypeEmplaceTest(const std::string&& dtype)
  {
    auto start = std::chrono::steady_clock::now();
    T st;

    constexpr auto testSz = 500000;
    for (int i = 0; i < testSz; ++i)
    {
      // Note without the move, the following operation will fail to compile
      // since the NoCopyData type does not support copying. 
      // And without the move, push of the stack will try to make a copy of the
      // passed object
      // Theoretically at the end of the move operation the data object should
      // be practically a zombie object with no data inside but for simplicity
      // it is not implemented here
      //st.emplace("Same item",{ 437, 438, 439, 440 });
      st.emplace("Same item",std::vector<int>{ 437, 438, 439, 440 });
    }

    auto sz = st.size();
    for (size_t i = 0; i < sz; ++i)
    {
      auto& a = st.back();
      st.pop();
    }

    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Pusing/Popping " << testSz << " complex('NoCopyData' type) to the queue type:=" << dtype << " using emplace, took: " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
  }

  template <typename T>
  void MultiplePushPop(const std::string&& dtype)
  {
    auto start = std::chrono::steady_clock::now();
    T st;

    auto push_pop = [&st](const int npush, const int npop) {
      for (int i = 0; i < npush; ++i)
      {
        st.push(NoCopyData("name", { i, i + 1, i + 2, i + 3 }));
      }
      std::cout << "Size after " << npush << " pushes is: " << st.size() << std::endl;
      for (int i = 0; i < npop; ++i)
      {
        st.pop();
      }
      std::cout << "Size after " << npop << " pops is: " << st.size() << std::endl;
    };

    push_pop(1000000, 500000);
    push_pop(1000000, 500000);
    push_pop(1000000, 2000000);
    std::cout << "Final size of the queue=" << st.size() << std::endl;

    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Pusing/Popping large amounts of data at the same time took " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
  }

  template <typename T>
  void MultiplePushPop_SmallIterations(const std::string&& dtype)
  {
    auto start = std::chrono::steady_clock::now();
    T st;

    auto push_pop = [&st](const int npush, const int npop) {
      for (int i = 0; i < npush; ++i)
      {
        st.push(NoCopyData("name", { i, i + 1, i + 2, i + 3 }));
      }
      //std::cout << "Size after " << npush << " pushes is: " << st.size() << std::endl;
      for (int i = 0; i < npop; ++i)
      {
        st.pop();
      }
      //std::cout << "Size after " << npop << " pops is: " << st.size() << std::endl;
    };

    push_pop(100, 1);
    push_pop(200, 1);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 10);
    push_pop(10, 50);
    push_pop(10, 50);
    push_pop(10, 50);
    for (int i = 0; i < 500000; ++i)
    {
      push_pop(100, 100);
    }
    std::cout << "Final size of the queue=" << st.size() << std::endl;

    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Pusing/Popping small amounts of items took " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
  }

}

namespace T3
{
  // A simple Data type that implements default copying and moving semantics
  struct SimpleData
  {
    std::string name;
  };

  template <typename T>
  void TestSimpleData(const std::string&& dtype)
  {
    auto start = std::chrono::steady_clock::now();
    T st;

    //std::cout << "Pusing objects that are default constructed and finally being moved to the stack";
    constexpr auto testSz = 1000000;
    for (int i = 0; i < testSz; ++i)
    {
      // This will invoke the push with move semantics. Since SimpleData implements/supports
      // default copying and moving this is fine
      st.push(SimpleData{});
    }
    //std::cout << "\n";

    SimpleData data{"Some text"};
    //std::cout << "Pusing one single object using copy assignment into the stack";
    for (int i = 0; i < testSz; ++i)
    {
      st.push(data);
    }

    auto sz = st.size();
    for (size_t i = 0; i < sz; ++i)
    {
      auto& a = st.back();
      st.pop();
    }

    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Pushing " << testSz << "items of type 'SimpleDataType' ";
    std::cout << "Pushing another " << testSz << "items of a single object by copy to the queue type : = " << dtype << ", took : " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
  }
}

int main()
{
  // Plain old data tests with DS::Queue and std::queue
  T1::POD_Test<DS::Queue<int> >(std::string("DS::Queue<int>"));
  T1::POD_Test<DS::LLQueue<int> >(std::string("DS::LLQueue<int>"));
  T1::POD_Test<std::queue<int> >(std::string("std::queue<int>"));
  std::cout << "\n";

  // A complex data type
  T2::TestComplexTyp<DS::Queue<T2::NoCopyData> >(std::string("DS::Queue<T2::NoCopyData>"));
  T2::TestComplexTyp<DS::LLQueue<T2::NoCopyData> >(std::string("DS::LLQueue<T2::NoCopyData>"));
  T2::TestComplexTyp<std::queue<T2::NoCopyData> >(std::string("std::queue<T2::NoCopyData>"));
  std::cout << "\n";

  // Use complex data type and push objects via emplace
  T2::ComplexTypeEmplaceTest<DS::Queue<T2::NoCopyData> >(std::string("DS::Queue<T2::NoCopyData>"));
  T2::ComplexTypeEmplaceTest<DS::LLQueue<T2::NoCopyData> >(std::string("DS::LLQueue<T2::NoCopyData>"));
  T2::ComplexTypeEmplaceTest<std::queue<T2::NoCopyData> >(std::string("std::queue<T2::NoCopyData>"));
  std::cout << "\n";

  // A simple data type 
  T3::TestSimpleData<DS::Queue<T3::SimpleData> >(std::string("DS::Queue<T3::SimpleData>"));
  T3::TestSimpleData<DS::LLQueue<T3::SimpleData> >(std::string("DS::LLQueue<T3::SimpleData>"));
  T3::TestSimpleData<std::queue<T3::SimpleData> >(std::string("std::queue<T3::SimpleData>"));
  std::cout << "\n";

  T2::MultiplePushPop<DS::Queue<T2::NoCopyData> >(std::string("DS::Queue<T2::NoCopyData>"));
  T2::MultiplePushPop<DS::LLQueue<T2::NoCopyData> >(std::string("DS::LLQueue<T2::NoCopyData>"));
  T2::MultiplePushPop<std::queue<T2::NoCopyData> >(std::string("std::queue<T2::NoCopyData>"));
  std::cout << "\n";

  T2::MultiplePushPop_SmallIterations<DS::Queue<T2::NoCopyData> >(std::string("DS::Queue<T2::NoCopyData>"));
  T2::MultiplePushPop_SmallIterations<DS::LLQueue<T2::NoCopyData> >(std::string("DS::LLQueue<T2::NoCopyData>"));
  T2::MultiplePushPop_SmallIterations<std::queue<T2::NoCopyData> >(std::string("std::queue<T2::NoCopyData>"));
  std::cout << "\n";

  return 0;
}




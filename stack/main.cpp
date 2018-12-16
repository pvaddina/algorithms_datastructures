#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <stack>
#include "stack.h"

namespace T1
{
  template <typename T>
  void POD_Test(const std::string&& dtype)
  {
    auto start = std::chrono::steady_clock::now();
    T st;

    //std::cout << "pushing: ";
    for (int i = 0; i < 1000000; ++i)
    {
      //std::cout << i << " ";
      st.push(i);
    }
    //std::cout << "\n";

    auto sz = st.size();
    //std::cout << "Popping: ";
    for (size_t i = 0; i < sz; ++i)
    {
      auto& a = st.top();
      st.pop();
    }
    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "POD_Test with T=" << dtype << ", took: " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
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
    //std::cout << "Pusing objects constructed with rvalue refs, and finally being moved into the stack";
    for (int i = 0; i < 900000; ++i)
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
      auto& a = st.top();
      st.pop();
    }

    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "TestComplextyp with T=" << dtype << ", took: " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
  }

  template <typename T>
  void ComplexTypeEmplaceTest(const std::string&& dtype)
  {
    auto start = std::chrono::steady_clock::now();
    T st;

    for (int i = 0; i < 500000; ++i)
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
      auto& a = st.top();
      st.pop();
    }

    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "TestComplextyp with T=" << dtype << ", took: " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
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
    for (int i = 0; i < 1000000; ++i)
    {
      // This will invoke the push with move semantics. Since SimpleData implements/supports
      // default copying and moving this is fine
      st.push(SimpleData{});
    }
    //std::cout << "\n";

    SimpleData data{};
    //std::cout << "Pusing one single object using copy assignment into the stack";
    for (int i = 0; i < 1000000; ++i)
    {
      st.push(data);
    }

    auto sz = st.size();
    for (size_t i = 0; i < sz; ++i)
    {
      auto& a = st.top();
      st.pop();
    }

    //std::cout << "\n";
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "TestSimpleData with T=" << dtype << ", took: " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
  }
}

int main()
{
  // Plain old data tests with AG::Stack and std::stack
  T1::POD_Test<AG::Stack<int> >(std::string("AG::Stack<int>"));
  T1::POD_Test<AG::LLStack<int> >(std::string("AG::LLStack<int>"));
  T1::POD_Test<std::stack<int> >(std::string("std::stack<int>"));

  // A complex data type
  T2::TestComplexTyp<AG::Stack<T2::NoCopyData> >(std::string("AG::Stack<T2::NoCopyData>"));
  T2::TestComplexTyp<AG::LLStack<T2::NoCopyData> >(std::string("AG::LLStack<T2::NoCopyData>"));
  T2::TestComplexTyp<std::stack<T2::NoCopyData> >(std::string("std::stack<T2::NoCopyData>"));

  // Use complex data type and push objects via emplace
  T2::ComplexTypeEmplaceTest<AG::Stack<T2::NoCopyData> >(std::string("AG::Stack<T2::NoCopyData>"));
  T2::ComplexTypeEmplaceTest<AG::LLStack<T2::NoCopyData> >(std::string("AG::LLStack<T2::NoCopyData>"));
  T2::ComplexTypeEmplaceTest<std::stack<T2::NoCopyData> >(std::string("std::stack<T2::NoCopyData>"));

  // A simple data type 
  T3::TestSimpleData<AG::Stack<T3::SimpleData> >(std::string("AG::Stack<T3::SimpleData>"));
  T3::TestSimpleData<AG::LLStack<T3::SimpleData> >(std::string("AG::LLStack<T3::SimpleData>"));
  T3::TestSimpleData<std::stack<T3::SimpleData> >(std::string("std::stack<T3::SimpleData>"));

  return 0;
}




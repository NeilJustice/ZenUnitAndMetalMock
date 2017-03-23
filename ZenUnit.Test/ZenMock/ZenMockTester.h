#pragma once

struct ZenMockTester
{
   template<typename Callable>
   static void call_n_times(size_t n, Callable&& callable)
   {
      for (size_t i = 0; i < n; ++i)
      {
         std::forward<Callable>(callable)();
      }
   }

   static string ExpectedCallCountMismatchWhat(
      const string& expectedSignature, size_t expectedCallCount, size_t actualCallCount)
   {
      string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature)
Expected: )", expectedCallCount, R"(
  Actual: )", actualCallCount, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
      return expectedWhat;
   }
};

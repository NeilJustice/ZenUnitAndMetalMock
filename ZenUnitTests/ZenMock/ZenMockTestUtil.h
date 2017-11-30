#pragma once

struct ZenMockTestUtil
{
   template<typename Callable>
   static void CallNTimes(size_t n, Callable&& callable)
   {
      for (size_t i = 0; i < n; ++i)
      {
         forward<Callable>(callable)();
      }
   }

   static string ExpectedCallCountMismatchWhat(
      const string& expectedSignature, size_t expectedCallCount, size_t actualCallCount)
   {
      const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: )", expectedCallCount, R"(
  Actual: )", actualCallCount, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
      return expectedWhat;
   }
};

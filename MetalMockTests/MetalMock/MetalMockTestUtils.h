#pragma once

struct MetalMockTestUtil
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
      const string expectedWhat = String::ConcatValues(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, actualNumberOfCalls, this->metalMockedFunctionSignature)
Expected: )", expectedCallCount, R"(
  Actual: )", actualCallCount, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
      return expectedWhat;
   }
};

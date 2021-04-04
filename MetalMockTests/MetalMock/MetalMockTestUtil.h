#pragma once

struct MetalMockTestUtils
{
   template<typename Callable>
   static void CallNTimes(size_t n, Callable&& callable)
   {
      for (size_t i = 0; i < n; ++i)
      {
         forward<Callable>(callable)();
      }
   }

   static string MakeExpectedExceptionMessageForCallCountMismatch0Args(
      const string& expectedFunctionSignature, size_t expectedCallCount, size_t actualCallCount)
   {
      const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->numberOfCallsToMetalMockedFunction, this->MetalMockedFunctionSignature)
Expected: )", expectedCallCount, R"(
  Actual: )", actualCallCount, R"(
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1))");
      return expectedExceptionMessage;
   }

   static string MakeExpectedExceptionMessageForCallCountMismatch(
      const string& expectedFunctionSignature, size_t expectedCallCount, size_t actualCallCount)
   {
      const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)
Expected: )", expectedCallCount, R"(
  Actual: )", actualCallCount, R"(
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1))");
      return expectedExceptionMessage;
   }
};

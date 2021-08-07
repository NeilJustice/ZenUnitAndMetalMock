#include "pch.h"

namespace MetalMock
{
   TESTS(ReturnValueMustBeSpecifiedExceptionTests)
   AFACT(DefaultConstructor_SetsWhatText)
   EVIDENCE

   static_assert(is_base_of_v<MetalMockException, ReturnValueMustBeSpecifiedException>);

   TEST(DefaultConstructor_SetsWhatText)
   {
      const ReturnValueMustBeSpecifiedException ex("MetalMockedFunctionSignature");
      //
      const string expectedExceptionMessage = R"(For MetalMocked function "MetalMockedFunctionSignature":
MetalMocked functions with non-void return types must have their return value or values set explicitly by calling:
[FunctionName]Mock.[Return|ReturnValues]())";
      const string exceptionMessage = ex.what();
      ARE_EQUAL(expectedExceptionMessage, exceptionMessage);
   }

   RUN_TESTS(ReturnValueMustBeSpecifiedExceptionTests)
}

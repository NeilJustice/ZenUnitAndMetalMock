#include "pch.h"

namespace MetalMock
{
   TESTS(ReturnValueMustBeSpecifiedExceptionTests)
   AFACT(DefaultConstructor_SetsWhatText_ClassIsSubclassOfMetalMockException)
   EVIDENCE

   TEST(DefaultConstructor_SetsWhatText_ClassIsSubclassOfMetalMockException)
   {
      ReturnValueMustBeSpecifiedException ex("MetalMockedFunctionSignature");
      //
      const string expectedExceptionMessage = R"(For MetalMocked function "MetalMockedFunctionSignature":
MetalMocked functions with non-void return types must have their return value or values set explicitly by calling:
[FunctionName]Mock.[Return|ReturnValues]())";
      ARE_EQUAL(expectedExceptionMessage, ex.what());

      IS_TRUE((is_base_of<MetalMockException, ReturnValueMustBeSpecifiedException>::value));
   }

   RUN_TESTS(ReturnValueMustBeSpecifiedExceptionTests)
}

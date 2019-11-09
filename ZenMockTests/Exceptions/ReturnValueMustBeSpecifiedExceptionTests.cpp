#include "pch.h"

namespace ZenMock
{
   TESTS(ReturnValueMustBeSpecifiedExceptionTests)
   AFACT(DefaultConstructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   EVIDENCE

   TEST(DefaultConstructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   {
      ReturnValueMustBeSpecifiedException ex("ZenMockedFunctionSignature");
      //
      const string expectedExceptionMessage = R"(For ZenMocked function "ZenMockedFunctionSignature":
ZenMocked functions with non-void return types must have their return value or values set explicitly by calling:
[FunctionName]Mock.[Return|ReturnValues]())";
      ARE_EQUAL(expectedExceptionMessage, ex.what());

      IS_TRUE((is_base_of<ZenMockException, ReturnValueMustBeSpecifiedException>::value));
   }

   RUN_TESTS(ReturnValueMustBeSpecifiedExceptionTests)
}

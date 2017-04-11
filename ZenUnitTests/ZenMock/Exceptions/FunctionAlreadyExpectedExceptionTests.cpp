#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/FunctionAlreadyExpectedException.h"

namespace ZenMock
{
   TESTS(FunctionAlreadyExpectedExceptionTests)
   SPEC(Constructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   SPECEND

   TEST(Constructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   {
      const string ZenMockedFunctionSignature = "void ClassName::FunctionName(int) const";
      //
      FunctionAlreadyExpectedException e(ZenMockedFunctionSignature);
      //
      const string expectedWhat = "For ZenMocked function \"" + ZenMockedFunctionSignature + R"(":
[ZenMockObjectName].Expect[AndReturn or AndReturnValues or AndThrow]() already called.)";
      ARE_EQUAL(expectedWhat, e.what());
      IS_TRUE((is_base_of<ZenMockException, FunctionAlreadyExpectedException>::value));
   }

   }; RUN(FunctionAlreadyExpectedExceptionTests)
}

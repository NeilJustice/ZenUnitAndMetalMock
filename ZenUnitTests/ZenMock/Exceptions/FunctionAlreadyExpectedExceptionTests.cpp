#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/FunctionAlreadyExpectedException.h"

namespace ZenMock
{
   TESTS(FunctionAlreadyExpectedExceptionTests)
   FACT(Constructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   EVIDENCE

   TEST(Constructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   {
      const string ZenMockedFunctionSignature = "void ClassName::FunctionName(int) const";
      //
      FunctionAlreadyExpectedException e(ZenMockedFunctionSignature);
      //
      const string expectedWhat = "For ZenMocked function \"" + ZenMockedFunctionSignature + R"(":
Already called [ZenMockedFunctionName]Mock.Expect[AndReturn|AndReturnValues|AndThrow]().)";
      ARE_EQUAL(expectedWhat, e.what());
      IS_TRUE((is_base_of<ZenMockException, FunctionAlreadyExpectedException>::value));
   }

   }; RUNTESTS(FunctionAlreadyExpectedExceptionTests)
}

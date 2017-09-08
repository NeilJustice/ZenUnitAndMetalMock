#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/ReturnValueMustBeSpecifiedException.h"

namespace ZenMock
{
   TESTS(ReturnValueMustBeSpecifiedExceptionTests)
   AFACT(DefaultConstructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   EVIDENCE

   TEST(DefaultConstructor_SetsWhatText_ClassIsSubclassOfZenMockException)
   {
      const string ZenMockedFunctionSignature = "ZenMockedFunctionSignature";
      //
      ReturnValueMustBeSpecifiedException e(ZenMockedFunctionSignature);
      //
      const string ExpectedWhat = R"(For ZenMocked function "ZenMockedFunctionSignature":
 ZenMocked functions with non-default-constructible return types
 must have their return value set explicitly by calling
 [ZenMockedFunctionName]Mock.[ExpectAndReturn|ExpectAndReturnValues]())";
      ARE_EQUAL(ExpectedWhat, e.what());
      IS_TRUE((is_base_of<ZenMockException, ReturnValueMustBeSpecifiedException>::value));
   }

   }; RUNTESTS(ReturnValueMustBeSpecifiedExceptionTests)
}

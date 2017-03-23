#include "pch.h"
#include "ReturnValueMustBeSpecifiedException.h"

namespace ZenMock
{
   ReturnValueMustBeSpecifiedException::ReturnValueMustBeSpecifiedException(
      const string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   const char* ReturnValueMustBeSpecifiedException::what() const noexcept
   {
      return _what.c_str();
   }

   string ReturnValueMustBeSpecifiedException::MakeWhat(
      const string& zenMockedFunctionSignature)
   {
      string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
 ZenMocked functions with non-default-constructible return types
 must have their return value set explicitly by calling
 [ZenMockObjectName].[ExpectAndReturn or ExpectAndReturnValues]())";
      return what;
   }
}

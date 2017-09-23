#include "pch.h"
#include "ReturnValueMustBeSpecifiedException.h"

namespace ZenMock
{
   ReturnValueMustBeSpecifiedException::ReturnValueMustBeSpecifiedException(
      const std::string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   const char* ReturnValueMustBeSpecifiedException::what() const noexcept
   {
      return _what.c_str();
   }

   std::string ReturnValueMustBeSpecifiedException::MakeWhat(
      const std::string& zenMockedFunctionSignature)
   {
      const std::string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
 ZenMocked functions with non-default-constructible return types
 must have their return value set explicitly by calling
 [ZenMockedFunctionName]Mock.[ExpectAndReturn|ExpectAndReturnValues]())";
      return what;
   }
}

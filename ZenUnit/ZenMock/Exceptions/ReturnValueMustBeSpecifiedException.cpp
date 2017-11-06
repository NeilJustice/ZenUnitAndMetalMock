#include "pch.h"
#include "ReturnValueMustBeSpecifiedException.h"

namespace ZenMock
{
   inline ReturnValueMustBeSpecifiedException::ReturnValueMustBeSpecifiedException(
      const std::string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   inline const char* ReturnValueMustBeSpecifiedException::what() const noexcept
   {
      return _what.c_str();
   }

   inline std::string ReturnValueMustBeSpecifiedException::MakeWhat(
      const std::string& zenMockedFunctionSignature)
   {
      const std::string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
 ZenMocked functions with non-default-constructible return types
 must have their return value set explicitly by calling
 [ZenMockedFunctionName]Mock.[ExpectAndReturn|ExpectAndReturnValues]())";
      return what;
   }
}

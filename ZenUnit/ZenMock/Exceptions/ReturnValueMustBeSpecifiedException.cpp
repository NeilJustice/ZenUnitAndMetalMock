#include "pch.h"
#include "ReturnValueMustBeSpecifiedException.h"

namespace ZenMock
{
   INLINE ReturnValueMustBeSpecifiedException::ReturnValueMustBeSpecifiedException(
      const std::string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   INLINE const char* ReturnValueMustBeSpecifiedException::what() const noexcept
   {
      return _what.c_str();
   }

   INLINE std::string ReturnValueMustBeSpecifiedException::MakeWhat(
      const std::string& zenMockedFunctionSignature)
   {
      const std::string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
  ZenMocked functions with non-void return types
  must have their return value or values set explicitly by calling
  [FunctionName]Mock.[ExpectAndReturn|ExpectAndReturnValues]())";
      return what;
   }
}

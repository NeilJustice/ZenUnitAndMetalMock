#include "pch.h"
#include "FunctionAlreadyExpectedException.h"

namespace ZenMock
{
   inline FunctionAlreadyExpectedException::FunctionAlreadyExpectedException(
      const std::string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   inline std::string FunctionAlreadyExpectedException::MakeWhat(const std::string& zenMockedFunctionSignature)
   {
      const std::string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
Already called [ZenMockedFunctionName]Mock.Expect[AndReturn|AndReturnValues|AndThrow]().)";
      return what;
   }

   inline const char* FunctionAlreadyExpectedException::what() const noexcept
   {
      return _what.c_str();
   }
}

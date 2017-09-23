#include "pch.h"
#include "FunctionAlreadyExpectedException.h"

namespace ZenMock
{
   FunctionAlreadyExpectedException::FunctionAlreadyExpectedException(
      const std::string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   std::string FunctionAlreadyExpectedException::MakeWhat(const std::string& zenMockedFunctionSignature)
   {
      const std::string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
Already called [ZenMockedFunctionName]Mock.Expect[AndReturn|AndReturnValues|AndThrow]().)";
      return what;
   }

   const char* FunctionAlreadyExpectedException::what() const noexcept
   {
      return _what.c_str();
   }
}

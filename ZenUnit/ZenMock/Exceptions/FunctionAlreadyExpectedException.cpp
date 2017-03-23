#include "pch.h"
#include "FunctionAlreadyExpectedException.h"

namespace ZenMock
{
   FunctionAlreadyExpectedException::FunctionAlreadyExpectedException(const std::string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   string FunctionAlreadyExpectedException::MakeWhat(const std::string& zenMockedFunctionSignature)
   {
      string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
[ZenMockObjectName].Expect[AndReturn or AndReturnValues or AndThrow]() already called.)";
      return what;
   }

   const char* FunctionAlreadyExpectedException::what() const noexcept
   {
      return _what.c_str();
   }
}

#include "pch.h"
#include "FunctionAlreadyExpectedException.h"

namespace ZenMock
{
   INLINE FunctionAlreadyExpectedException::FunctionAlreadyExpectedException(
      const std::string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   INLINE std::string FunctionAlreadyExpectedException::MakeWhat(const std::string& zenMockedFunctionSignature)
   {
      const std::string what = "For ZenMocked function \"" + zenMockedFunctionSignature + R"(":
Already called [FunctionName]Mock.Expect[AndReturn|AndReturnValues|AndThrow]().)";
      return what;
   }

   INLINE const char* FunctionAlreadyExpectedException::what() const noexcept
   {
      return _what.c_str();
   }
}

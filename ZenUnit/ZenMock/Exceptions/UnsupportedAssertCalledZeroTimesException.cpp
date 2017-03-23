#include "pch.h"
#include "UnsupportedAssertCalledZeroTimesException.h"
#include "Utils/StringUtil.h"

namespace ZenMock
{
   UnsupportedAssertCalledZeroTimesException::
      UnsupportedAssertCalledZeroTimesException(const string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   string UnsupportedAssertCalledZeroTimesException::MakeWhat(const string& zenMockedFunctionSignature)
   {
      string what = ZenUnit::String::Concat(
"For ZenMocked function \"", zenMockedFunctionSignature, R"(":
 ZenMock objects by design do not support the operation of asserting that
 their corresponding ZenMocked function was called zero times.
 To confirm that a ZenMocked function was called zero times,
 simply do not call any of the Expect() functions on a ZenMock object.)");
      return what;
   }

   const char* UnsupportedAssertCalledZeroTimesException::what() const noexcept
   {
      return _what.c_str();
   }
}

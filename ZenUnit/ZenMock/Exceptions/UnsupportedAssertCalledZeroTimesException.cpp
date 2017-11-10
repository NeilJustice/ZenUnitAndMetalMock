#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "UnsupportedAssertCalledZeroTimesException.h"
#include "ZenUnit/Utils/StringUtil.h"

namespace ZenMock
{
   INLINE UnsupportedAssertCalledZeroTimesException::
      UnsupportedAssertCalledZeroTimesException(const std::string& zenMockedFunctionSignature)
      : _what(MakeWhat(zenMockedFunctionSignature))
   {
   }

   INLINE std::string UnsupportedAssertCalledZeroTimesException::MakeWhat(const std::string& zenMockedFunctionSignature)
   {
      const std::string what = ZenUnit::String::Concat(
"For ZenMocked function \"", zenMockedFunctionSignature, R"(":
 ZenMock objects by design do not support the operation of asserting that
 their corresponding ZenMocked function was called zero times.
 To confirm that a ZenMocked function was called zero times,
 simply do not call any of the Expect() functions on a ZenMock object.)");
      return what;
   }

   INLINE const char* UnsupportedAssertCalledZeroTimesException::what() const noexcept
   {
      return _what.c_str();
   }
}

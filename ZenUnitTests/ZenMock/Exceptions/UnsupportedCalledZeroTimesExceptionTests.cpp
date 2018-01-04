#include "pch.h"

namespace ZenMock
{
   TESTS(UnsupportedCalledZeroTimesExceptionTests)
   AFACT(Constructor_SetsWhat_ClassIsSubclassOfZenMockException)
   EVIDENCE

   TEST(Constructor_SetsWhat_ClassIsSubclassOfZenMockException)
   {
      const string ZenMockedFunctionSignature = "virtual void ClassName::FunctionName(int, int) const";
      //
      const UnsupportedCalledZeroTimesException e(ZenMockedFunctionSignature);
      //
      const string ExpectedWhat = ZenUnit::String::Concat(
"For ZenMocked function \"", ZenMockedFunctionSignature, R"(":
 ZenMock objects by design do not support the operation of asserting that
 their corresponding ZenMocked function was called zero times.
 To confirm that a ZenMocked function was called zero times,
 simply do not call any of the Expect() functions on a ZenMock object.)");
      const string actualWhat = e.what();
      ARE_EQUAL(ExpectedWhat, actualWhat);
      IS_TRUE((is_base_of<ZenMockException, UnsupportedCalledZeroTimesException>::value));
   }

   }; RUNTESTS(UnsupportedCalledZeroTimesExceptionTests)
}

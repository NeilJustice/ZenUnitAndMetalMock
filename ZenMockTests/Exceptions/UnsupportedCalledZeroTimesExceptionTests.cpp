#include "pch.h"

namespace ZenMock
{
   TESTS(UnsupportedCalledZeroTimesExceptionTests)
   AFACT(Constructor_SetsWhat_ClassIsSubclassOfZenMockException)
   EVIDENCE

   TEST(Constructor_SetsWhat_ClassIsSubclassOfZenMockException)
   {
      // Example ZenMocked function signature: "virtual void ClassName::FunctionName(int, int) const"
      const string zenMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const UnsupportedCalledZeroTimesException ex(zenMockedFunctionSignature);
      //
      const std::string expectedWhat = ZenUnit::String::Concat(
         "For ZenMocked function \"", zenMockedFunctionSignature, R"(":

Due to ZenMock being a strict mocking library,
ZenMock objects by design do not support asserting that
their corresponding ZenMocked functions were called zero times.
To state the intention that a ZenMocked function
is expected to be called zero times, simply do not call Expect(),
Return(), ReturnValues(), ReturnRandom(), or ThrowException<T>() on a ZenMock object.)");
      const string actualWhat = ex.what();
      ARE_EQUAL(expectedWhat, actualWhat);
      IS_TRUE((is_base_of<ZenMockException, UnsupportedCalledZeroTimesException>::value));
   }

   RUN_TESTS(UnsupportedCalledZeroTimesExceptionTests)
}

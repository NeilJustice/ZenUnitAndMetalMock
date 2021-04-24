#include "pch.h"

namespace MetalMock
{
   TESTS(UnsupportedCalledZeroTimesExceptionTests)
   AFACT(OneArgConstructor_SetsExceptionMessage__ClassIsASubclassOfMetalMockException)
   EVIDENCE

   TEST(OneArgConstructor_SetsExceptionMessage__ClassIsASubclassOfMetalMockException)
   {
      // Example MetalMocked function signature: "virtual void ClassName::FunctionName(int, int) const"
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const UnsupportedCalledZeroTimesException ex(metalMockedFunctionSignature);
      //
      const std::string expectedExceptionMessage = ZenUnit::String::ConcatStrings(
         "For MetalMocked function \"", metalMockedFunctionSignature, R"(":

Because MetalMock is a strict mocking framework,
by design MetalMock objects do not support asserting that
their corresponding MetalMocked functions were called zero times.
To effectively assert that a MetalMocked function is expected to be called zero times,
simply do not call any of the expectation functions:
MetalMockObject.Expect()
MetalMockObject.Return()
MetalMockObject.ReturnValues()
MetalMockObject.ReturnRandom() or
MetalMockObject.ThrowExceptionWhenCalled<T>())");
      const string actualExceptionMessage = ex.what();
      ARE_EQUAL(expectedExceptionMessage, actualExceptionMessage);
      IS_TRUE((is_base_of<MetalMockException, UnsupportedCalledZeroTimesException>::value));
   }

   RUN_TESTS(UnsupportedCalledZeroTimesExceptionTests)
}

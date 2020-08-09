#include "pch.h"

namespace MetalMock
{
   TESTS(UnsupportedCalledZeroTimesExceptionTests)
   AFACT(Constructor_SetsWhat_ClassIsSubclassOfMetalMockException)
   EVIDENCE

   TEST(Constructor_SetsWhat_ClassIsSubclassOfMetalMockException)
   {
      // Example MetalMocked function signature: "virtual void ClassName::FunctionName(int, int) const"
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const UnsupportedCalledZeroTimesException ex(metalMockedFunctionSignature);
      //
      const std::string expectedWhat = ZenUnit::String::Concat(
         "For MetalMocked function \"", metalMockedFunctionSignature, R"(":

Due to MetalMock being a strict mocking library,
MetalMock objects by design do not support asserting that
their corresponding MetalMocked functions were called zero times.
To state the intention that a MetalMocked function
is expected to be called zero times, simply do not call Expect(),
Return(), ReturnValues(), ReturnRandom(), or ThrowException<T>() on a MetalMock object.)");
      const string actualWhat = ex.what();
      ARE_EQUAL(expectedWhat, actualWhat);
      IS_TRUE((is_base_of<MetalMockException, UnsupportedCalledZeroTimesException>::value));
   }

   RUN_TESTS(UnsupportedCalledZeroTimesExceptionTests)
}

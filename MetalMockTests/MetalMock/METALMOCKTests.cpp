#include "pch.h"

class METALMOCKTestingClass
{
public:
   virtual ~METALMOCKTestingClass() = default;
   virtual void Function(string_view) const {}
};

class METALMOCKTestingClassMock : public Metal::Mock<METALMOCKTestingClass>
{
public:
   METALMOCK_VOID1_CONST(Function, string_view)
};

namespace MetalMock
{
   TESTS(METALMOCKTests)
   AFACT(METALMOCKWrappedAssertionDoesNotThrow_NothingHappens)
   AFACT(METALMOCKWrappedAssertionThrows_RethrowsMETALMOCKWrappedAnomaly)
   EVIDENCE

   TEST(METALMOCKWrappedAssertionDoesNotThrow_NothingHappens)
   {
      METALMOCKTestingClassMock mock;
      mock.FunctionMock.Expect();
      const string message = ZenUnit::Random<string>();
      //
      mock.Function(message);
      //
      METALMOCK(mock.FunctionMock.CalledOnceWith(message));
   }

   TEST(METALMOCKWrappedAssertionThrows_RethrowsMETALMOCKWrappedAnomaly)
   {
      METALMOCKTestingClassMock mock;
      mock.FunctionMock.Expect();
      mock.Function("message");
      const string message = "Message";

      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: METALMOCK(mock.FunctionMock.CalledOnceWith(message))",
"Because of this ZenUnit::Anomaly:",
"  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->metalMockedFunctionSignature)",
"Expected: \"Message\"",
"  Actual: \"message\"",
" Message: \"virtual void METALMOCKTestingClass::Function(string_view) const\"",
"File.cpp(1)",
"File.cpp(1)");
      THROWS_EXCEPTION(
         METALMOCK(mock.FunctionMock.CalledOnceWith(message)),
         Anomaly, expectedExceptionMessage);
   }

   RUN_TESTS(METALMOCKTests)
}

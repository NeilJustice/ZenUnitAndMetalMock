#include "pch.h"

class METALMOCKTHENTestingClass
{
public:
   METALMOCKTHENTestingClass() {}
   virtual ~METALMOCKTHENTestingClass() = default;
   virtual void FunctionA(string_view) const {}
   virtual void FunctionB(string_view) const {}
};

class METALMOCKTHENTestingClassMock : public Metal::Mock<METALMOCKTHENTestingClass>
{
public:
   METALMOCK_VOID1_CONST(FunctionA, string_view)
   METALMOCK_VOID1_CONST(FunctionB, string_view)
};

namespace MetalMock
{
   TESTS(METALMOCKTHENTests)
   AFACT(METALMOCKTHENWrappedAssertionDoesNotThrow_DoesNotThrowException)
   AFACT(METALMOCKTHENWrappedAssertionThrowsAnomaly_RethrowsMETALMOCKTHENWrappedAnomaly)
   AFACT(METALMOCKTHENWrappedAssertionDotThenThrowsFunctionCallOrderingAnomaly_ThrowsIS_LESS_THANAnomaly)
   AFACT(METALMOCKTHENTestingClass_FunctionA_FunctionB_CodeCoverage)
   EVIDENCE

   METALMOCKTHENTestingClassMock _classMock;

   TEST(METALMOCKTHENWrappedAssertionDoesNotThrow_DoesNotThrowException)
   {
      _classMock.FunctionAMock.Expect();
      _classMock.FunctionBMock.Expect();
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      //
      _classMock.FunctionA(messageA);
      _classMock.FunctionB(messageB);
      //
      METALMOCK(_classMock.FunctionAMock.CalledOnceWith(messageA));
      METALMOCK(_classMock.FunctionBMock.CalledOnceWith(messageB));
   }

   TEST(METALMOCKTHENWrappedAssertionThrowsAnomaly_RethrowsMETALMOCKTHENWrappedAnomaly)
   {
      _classMock.FunctionAMock.Expect();
      //
      _classMock.FunctionA("message");
      //
      const string expectedMessage = "mismatching_message";
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: METALMOCKTHEN(_classMock.FunctionAMock.CalledOnceWith(expectedMessage))",
"Because of this ZenUnit::Anomaly:",
"  Failed: ARE_EQUAL(expectedArgument, _metalMockedFunctionCallHistory[0].argument.value, this->metalMockedFunctionSignature)",
"Expected: \"mismatching_message\"",
"  Actual: \"message\"",
" Message: \"virtual void METALMOCKTHENTestingClass::FunctionA(string_view) const\"",
"File.cpp(1)",
"File.cpp(1)");
      THROWS_EXCEPTION(METALMOCKTHEN(_classMock.FunctionAMock.CalledOnceWith(expectedMessage)),
         Anomaly, expectedExceptionMessage);
   }

   TEST(METALMOCKTHENWrappedAssertionDotThenThrowsFunctionCallOrderingAnomaly_ThrowsIS_LESS_THANAnomaly)
   {
      _classMock.FunctionAMock.Expect();
      _classMock.FunctionBMock.Expect();
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      //
      const unsigned long long expectedSequenceNumberA = MetalMock::_globalMetalMockedFunctionCallSequenceNumber;
      const unsigned long long expectedSequenceNumberB = MetalMock::_globalMetalMockedFunctionCallSequenceNumber + 1;
      _classMock.FunctionA(messageA);
      _classMock.FunctionB(messageB);
      //
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LESS_THAN(expectedFirstFunctionCallSequenceNumber, expectedNextFunctionCallSequenceNumber, unexpectedFunctionCallOrderingErrorMessage)",
"Expected: " + to_string(expectedSequenceNumberB),
"  Actual: " + to_string(expectedSequenceNumberA),
" Message: \"Unexpected MetalMocked function call ordering:",
"Expected function called first: virtual void METALMOCKTHENTestingClass::FunctionB(string_view) const",
"  Actual function called first: virtual void METALMOCKTHENTestingClass::FunctionA(string_view) const\"",
"File.cpp(1)");
      THROWS_EXCEPTION(
         METALMOCKTHEN(_classMock.FunctionBMock.CalledOnceWith(messageB)).Then(
         METALMOCKTHEN(_classMock.FunctionAMock.CalledOnceWith(messageA))),
         Anomaly, expectedExceptionMessage);
   }

   TEST(METALMOCKTHENTestingClass_FunctionA_FunctionB_CodeCoverage)
   {
      METALMOCKTHENTestingClass classInstance{};
      classInstance.FunctionA(ZenUnit::Random<string>());
      classInstance.FunctionB(ZenUnit::Random<string>());
   }

   RUN_TESTS(METALMOCKTHENTests)
}

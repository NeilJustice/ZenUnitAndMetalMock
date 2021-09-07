#include "pch.h"

class METALMOCKTestingClass
{
public:
   METALMOCKTestingClass() {}
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
   AFACT(METALMOCKTestingClass_Function_CodeCoverage)
   EVIDENCE

   TEST(METALMOCKWrappedAssertionDoesNotThrow_NothingHappens)
   {
      METALMOCKTestingClassMock classMock;
      classMock.FunctionMock.Expect();
      const string message = ZenUnit::Random<string>();
      //
      classMock.Function(message);
      //
      METALMOCK(classMock.FunctionMock.CalledOnceWith(message));
   }

   TEST(METALMOCKWrappedAssertionThrows_RethrowsMETALMOCKWrappedAnomaly)
   {
      METALMOCKTestingClassMock classMock;
      classMock.FunctionMock.Expect();
      //
      classMock.Function("message");
      //
      const string expectedMessage = "mismatching_message";
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: METALMOCK(classMock.FunctionMock.CalledOnceWith(expectedMessage))",
"Because of this ZenUnit::Anomaly:",
"  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->metalMockedFunctionSignature)",
"Expected: \"mismatching_message\"",
"  Actual: \"message\"",
" Message: \"virtual void METALMOCKTestingClass::Function(string_view) const\"",
"File.cpp(1)",
"File.cpp(1)");
      THROWS_EXCEPTION(
         METALMOCK(classMock.FunctionMock.CalledOnceWith(expectedMessage)),
         Anomaly, expectedExceptionMessage);
   }

   TEST(METALMOCKTestingClass_Function_CodeCoverage)
   {
      METALMOCKTestingClass classInstance{};
      classInstance.Function(ZenUnit::Random<string>());
   }

   RUN_TESTS(METALMOCKTests)
}

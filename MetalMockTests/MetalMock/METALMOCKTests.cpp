#include "pch.h"
#include "MetalMockTests/MetalMock/ConsoleMock.h"

namespace MetalMock
{
   TESTS(METALMOCKTests)
   AFACT(METALMOCKWrappedAssertionDoesNotThrow_NothingHappens)
   AFACT(METALMOCKWrappedAssertionThrows_RethrowsMETALMOCKWrappedAnomaly)
   EVIDENCE

   TEST(METALMOCKWrappedAssertionDoesNotThrow_NothingHappens)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      const string message = ZenUnit::Random<string>();
      //
      consoleMock.WriteLine(message);
      //
      METALMOCK(consoleMock.WriteLineMock.CalledOnceWith(message));
   }

   TEST(METALMOCKWrappedAssertionThrows_RethrowsMETALMOCKWrappedAnomaly)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      consoleMock.WriteLine("message");
      const string expectedMessage = "Message";

      const string expectedWhat = TestUtil::NewlineConcat("",
"  Failed: METALMOCK(consoleMock.WriteLineMock.CalledOnceWith(expectedMessage))",
"Because of this ZenUnit::Anomaly:",
"  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->metalMockedFunctionSignature)",
"Expected: \"Message\"",
"  Actual: \"message\"",
" Message: \"virtual void ZenUnit::Console::WriteLine(string_view) const\"",
"File.cpp(1)",
"File.cpp(1)");
      THROWS_EXCEPTION(
         METALMOCK(consoleMock.WriteLineMock.CalledOnceWith(expectedMessage)),
         Anomaly, expectedWhat);
   }

   RUN_TESTS(METALMOCKTests)
}

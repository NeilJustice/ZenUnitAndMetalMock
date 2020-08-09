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
      consoleMock.WriteLine("message");
      METALMOCK(consoleMock.WriteLineMock.CalledOnceWith("message"));
   }

   TEST(METALMOCKWrappedAssertionThrows_RethrowsMETALMOCKWrappedAnomaly)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      consoleMock.WriteLine("message");
      const string expectedMessage = "Message";
      const string expectedWhat = "\n"
"  Failed: METALMOCK(consoleMock.WriteLineMock.CalledOnceWith(expectedMessage))\n"
" Because: ARE_EQUAL(expectedArgument, metalMockedFunctionCallHistory[0].argument.value, this->MetalMockedFunctionSignature) failed\n"
"Expected: \"Message\"\n"
"  Actual: \"message\"\n"
" Message: \"virtual void ZenUnit::Console::WriteLine(string_view) const\"\n"
"File.cpp(1)";
      THROWS_EXCEPTION(METALMOCK(consoleMock.WriteLineMock.CalledOnceWith(expectedMessage)), Anomaly, expectedWhat);
   }

   RUN_TESTS(METALMOCKTests)
}

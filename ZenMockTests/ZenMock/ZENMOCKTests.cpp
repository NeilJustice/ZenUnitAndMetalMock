#include "pch.h"
#include "ZenMockTests/Mock/ConsoleMock.h"

namespace ZenMock
{
   TESTS(ZENMOCKTests)
   AFACT(ZENMOCKWrappedAssertionDoesNotThrow_NothingHappens)
   AFACT(ZENMOCKWrappedAssertionThrows_RethrowsZENMOCKWrappedAnomaly)
   EVIDENCE

   TEST(ZENMOCKWrappedAssertionDoesNotThrow_NothingHappens)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      consoleMock.WriteLine("message");
      ZENMOCK(consoleMock.WriteLineMock.CalledOnceWith("message"));
   }

   TEST(ZENMOCKWrappedAssertionThrows_RethrowsZENMOCKWrappedAnomaly)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      consoleMock.WriteLine("message");
      const string expectedMessage = "Message";
      const string expectedWhat = "\n"
"  Failed: ZENMOCK(consoleMock.WriteLineMock.CalledOnceWith(expectedMessage))\n"
" Because: ARE_EQUAL(expectedArgument, zenMockObjectCallHistory[0].argument.value, this->ZenMockedFunctionSignature) failed\n"
"Expected: \"Message\"\n"
"  Actual: \"message\"\n"
" Message: \"virtual void ZenUnit::Console::WriteLine(string_view) const\"\n"
"File.cpp(1)";
      THROWS(ZENMOCK(consoleMock.WriteLineMock.CalledOnceWith(expectedMessage)), Anomaly, expectedWhat);
   }

   RUN_TESTS(ZENMOCKTests)
}

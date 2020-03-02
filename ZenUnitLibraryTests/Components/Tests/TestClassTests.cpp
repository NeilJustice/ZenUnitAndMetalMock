#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/ZenMock/ConsoleColorerMock.h"
#include "ZenUnitLibraryTests/Components/Console/ZenMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Components/Misc/ZenMock/ExitCallerMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/ZenUnitTestRunnerMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"

namespace ZenUnit
{
   TESTS(TestClassTests)
   AFACT(DefaultConstructor_DoesNotThrow)
   AFACT(Startup_DoesNotThrow)
   AFACT(Cleanup_DoesNotThrow)
   AFACT(TestFromTestNXNPmfToken_NotFound_Exits0IfExitZeroIsTrueOtherwiseExits1_ReturnsNullptr)
   EVIDENCE

   TestClass _testClass;

   TEST(DefaultConstructor_DoesNotThrow)
   {
      const TestClass testClass{};
   }

   TEST(Startup_DoesNotThrow)
   {
      _testClass.Startup();
   }

   TEST(Cleanup_DoesNotThrow)
   {
      _testClass.Cleanup();
   }

   TEST(TestFromTestNXNPmfToken_NotFound_Exits0IfExitZeroIsTrueOtherwiseExits1_ReturnsNullptr)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineColorMock.Expect();

      ZenUnitTestRunnerMock zenUnitTestRunnerMock;
      const ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitTestRunnerMock.VirtualGetZenUnitArgsMock.Return(zenUnitArgs);

      ExitCallerMock exitCallerMock;
      exitCallerMock.CallExitMock.Expect();
      //
      const std::unique_ptr<ZenUnit::Test>* test = TestClass::TestFromTestNXNPmfToken(nullptr, &consoleMock, &zenUnitTestRunnerMock, &exitCallerMock);
      //
      ZENMOCK(zenUnitTestRunnerMock.VirtualGetZenUnitArgsMock.CalledOnce());

      const int expectedExitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
      const string expectedMessage = R"(The above test name was declared using FACTS(TestName).

Therefore a TESTNXN(TestName, ...) definition was expected to be found in the EVIDENCE section of the test class.

Unexpectedly a TEST(TestName) definition was found in the EVIDENCE section of the test class.

The fix for this error is to change FACTS(TestName) to AFACT(TestName)

or change TEST(TestName) to TESTNXN(TestName, ...), where N can be 1 through 10.

Exiting with code )" + std::to_string(expectedExitCode) + ".\n";
      ZENMOCK(consoleMock.WriteLineColorMock.CalledAsFollows(
         {
            { "====================================\nZenUnit Test Definition Syntax Error\n====================================\n", Color::Red },
            { expectedMessage, Color::Red }
         }));
      ZENMOCK(exitCallerMock.CallExitMock.CalledOnceWith(expectedExitCode));
      POINTER_IS_NULL(test);
   }

   RUN_TESTS(TestClassTests)
}

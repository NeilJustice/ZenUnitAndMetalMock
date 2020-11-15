#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleColorerMock.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Components/Misc/MetalMock/ExitCallerMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/ZenUnitTestRunnerMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(TestClassTests)
   AFACT(DefaultConstructor_DoesNotThrowException)
   AFACT(Startup_DoesNotThrowException)
   AFACT(Cleanup_DoesNotThrowException)
   FACTS(GetTestPointerForTestNXNPmfToken_PMFTokenIsNotFoundInPmfTokenToTestPointerMap_ExitsWithCode1OrWithCode0IfAlwaysExit0IsTrue)
   EVIDENCE

   TestClass _testClass;

   TEST(DefaultConstructor_DoesNotThrowException)
   {
      const TestClass testClass{};
   }

   TEST(Startup_DoesNotThrowException)
   {
      _testClass.Startup();
   }

   TEST(Cleanup_DoesNotThrowException)
   {
      _testClass.Cleanup();
   }

   TEST3X3(GetTestPointerForTestNXNPmfToken_PMFTokenIsNotFoundInPmfTokenToTestPointerMap_ExitsWithCode1OrWithCode0IfAlwaysExit0IsTrue,
      bool alwaysExit0, int expectedExitCode, Color expectedExitCodeLineColor,
      true, 0, Color::Green,
      false, 1, Color::Red)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      consoleMock.WriteLineColorMock.Expect();

      ZenUnitTestRunnerMock zenUnitTestRunnerMock;
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.alwaysExit0 = alwaysExit0;
      zenUnitTestRunnerMock.VirtualGetZenUnitArgsMock.Return(zenUnitArgs);

      ExitCallerMock exitCallerMock;
      exitCallerMock.CallExitMock.Expect();
      //
      const std::unique_ptr<ZenUnit::Test>* testPointer =
         TestClass::GetTestPointerForTestNXNPmfToken(nullptr, &consoleMock, &zenUnitTestRunnerMock, &exitCallerMock);
      //
      METALMOCK(zenUnitTestRunnerMock.VirtualGetZenUnitArgsMock.CalledOnce());
      const string expectedExitCodeMessage = String::Concat("[ZenUnit] ExitCode: ", expectedExitCode);
      METALMOCK(consoleMock.WriteLineColorMock.CalledAsFollows(
      {
         { "=======================================================\nZenUnit Test Declaration Test Definition Mismatch Error\n=======================================================", Color::Red },
         { expectedExitCodeMessage, expectedExitCodeLineColor }
      }));
      const string expectedErrorMessage = ZenUnit::String::Concat(R"(The above test name was declared using FACTS(TestName).

Unexpectedly, a corresponding TESTNXN(TestName, ...) test definition was not found in the EVIDENCE section of this test class.

To fix this mismatch, either change FACTS(TestName) to AFACT(TestName) in the test declaration section of this test class,

or change TEST(TestName) to TESTNXN(TestName, ...), where N can be 1 through 10, in the EVIDENCE section of this test class.
)");
      METALMOCK(consoleMock.WriteLineMock.CalledOnceWith(expectedErrorMessage));
      METALMOCK(exitCallerMock.CallExitMock.CalledOnceWith(expectedExitCode));
      IS_NULLPTR(testPointer);
   }

   RUN_TESTS(TestClassTests)
}

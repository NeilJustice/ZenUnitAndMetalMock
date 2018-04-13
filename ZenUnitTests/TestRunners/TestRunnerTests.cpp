#include "pch.h"
#if defined __linux__
#include <unistd.h>
#endif

#include "ZenUnitTests/Args/Mock/ArgsParserMock.h"
#include "ZenUnitTests/Args/Mock/RunFilterMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"
#include "ZenUnitTests/Random/RandomTestResult.h"
#include "ZenUnitTests/Random/RandomZenUnitArgs.h"
#include "ZenUnitTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitTests/Results/Mock/TestRunResultMock.h"
#include "ZenUnitTests/TestRunners/Mock/PreamblePrinterMock.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerRunnerMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/Utils/Function/Mock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TwoArgAnyerMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TwoArgMemberAnyerMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TwoArgMemberForEacherMock.h"
#include "ZenUnitTests/Utils/Mock/MachineNameGetterMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"

namespace ZenUnit
{

TESTS(TestRunnerTests)
AFACT(Constructor_NewsComponents)
AFACT(AddTestClassRunner_EmplacesBackTestClassRunner)
AFACT(SkipTest_CallsTestRunResultAddSkippedFullTestName)
AFACT(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
FACTS(ParseArgsRunTestClassesPrintResults_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1)
AFACT(WaitForAnyKeyIfPauseMode_PauseModeFalse_DoesNothing_ReturnsFalse)
AFACT(WaitForAnyKeyIfPauseMode_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
AFACT(WaitForAnyKeyIfPauseMode_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
FACTS(PrintPreambleRunTestClassesPrintConclusion_RunsTestsAndPrintsResults_UsingBackgroundThreadIfMaxTotalSecondsGT0_Returns0IfAllTestsPassedOtherwiseReturns1)
AFACT(RunTestClasses_RunsTestClasses)
//FACTS(RunTestClassesWithWaitableRunnerThread_SpawnsThreadToCallRunTestClasses_PrintsResultsAndExits1IfThreadTimesOut)
EVIDENCE

TestRunner _testRunner;
ConsoleMock* _consoleMock = nullptr;
PreamblePrinterMock* _preamblePrinterMock = nullptr;
ArgsParserMock* _argsParserMock = nullptr;

using NonVoidOneArgMemberFunctionCallerMockType = NonVoidOneArgMemberFunctionCallerMock<int, TestRunner, const ZenUnitArgs&>;
NonVoidOneArgMemberFunctionCallerMockType* _nonVoidOneArgMemberFunctionCallerMock;

using VoidOneArgMemberFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<TestRunner, unsigned>;
VoidOneArgMemberFunctionCallerMockType* _voidOneArgMemberFunctionCallerMock;

using NonVoidTwoArgMemberFunctionCallerMockType = NonVoidTwoArgMemberFunctionCallerMock<bool, TestRunner, bool, bool >;
NonVoidTwoArgMemberFunctionCallerMockType* _nonVoidTwoArgMemberFunctionCallerMock = nullptr;

VoidZeroArgMemberFunctionCallerMock<TestRunner>* _voidZeroArgMemberFunctionCallerMock = nullptr;

//FuturistMock<TestRunner>* _futuristMock;
TestClassRunnerRunnerMock* _testClassRunnerRunnerMock = nullptr;
TestRunResultMock* _testRunResultMock = nullptr;
StopwatchMock* _testRunStopwatchMock = nullptr;

class TestingTestClass
{
public:
   static vector<unique_ptr<Test>> GetTests(const char*)
   {
      return {};
   }
};

STARTUP
{
   _testRunner._console.reset(_consoleMock = new ConsoleMock);
   _testRunner._preamblePrinter.reset(_preamblePrinterMock = new PreamblePrinterMock);
   _testRunner._argsParser.reset(_argsParserMock = new ArgsParserMock);
   _testRunner._testRunResult.reset(_testRunResultMock = new TestRunResultMock);
   _testRunner._nonVoidOneArgMemberFunctionCaller.reset(_nonVoidOneArgMemberFunctionCallerMock = new NonVoidOneArgMemberFunctionCallerMockType);
   _testRunner._voidOneArgMemberFunctionCaller.reset(_voidOneArgMemberFunctionCallerMock = new VoidOneArgMemberFunctionCallerMockType);
   _testRunner._nonVoidTwoArgMemberFunctionCaller.reset(_nonVoidTwoArgMemberFunctionCallerMock = new NonVoidTwoArgMemberFunctionCallerMockType);
   _testRunner._voidZeroArgMemberFunctionCaller.reset(_voidZeroArgMemberFunctionCallerMock = new VoidZeroArgMemberFunctionCallerMock<TestRunner>);
   //_testRunner._futurist.reset(_futuristMock = new FuturistMock<TestRunner>);
   _testRunner._testClassRunnerRunner.reset(_testClassRunnerRunnerMock = new TestClassRunnerRunnerMock);
   _testRunner._testRunStopwatch.reset(_testRunStopwatchMock = new StopwatchMock);
}

TEST(Constructor_NewsComponents)
{
   TestRunner testRunner;
   POINTER_WAS_NEWED(testRunner._console);
   POINTER_WAS_NEWED(testRunner._preamblePrinter);
   POINTER_WAS_NEWED(testRunner._argsParser);
   POINTER_WAS_NEWED(testRunner._nonVoidOneArgMemberFunctionCaller);
   POINTER_WAS_NEWED(testRunner._voidOneArgMemberFunctionCaller);
   POINTER_WAS_NEWED(testRunner._nonVoidTwoArgMemberFunctionCaller);
   POINTER_WAS_NEWED(testRunner._voidZeroArgMemberFunctionCaller);
   //POINTER_WAS_NEWED(testRunner._futurist);
   POINTER_WAS_NEWED(testRunner._testClassRunnerRunner);
   POINTER_WAS_NEWED(testRunner._testRunResult);
   POINTER_WAS_NEWED(testRunner._testRunStopwatch);
   ARE_EQUAL(ZenUnitArgs(), testRunner._zenUnitArgs);
   IS_FALSE(testRunner._havePaused);
}

TEST(AddTestClassRunner_EmplacesBackTestClassRunner)
{
   _testClassRunnerRunnerMock->AddTestClassRunnerMock.Expect();
   SpecificTestClassRunner<TestingTestClass> testClassRunner("TestClassName");
   //
   _testRunner.AddTestClassRunner(&testClassRunner);
   //
   ZEN(_testClassRunnerRunnerMock->AddTestClassRunnerMock.CalledOnceWith(&testClassRunner));
}

TEST4X4(ParseArgsRunTestClassesPrintResults_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1,
   int expectedOverallExitCode, unsigned testrunsArgs, int firstTestRunExitCode, int secondTestRunExitCode,
   0, 1, 0, NA<int>(),
   1, 2, 1, 0,
   1, 2, 0, 1,
   1, 2, 1, 1)
{
   ZenUnitArgs parsedZenUnitArgs;
   parsedZenUnitArgs.runFilters = { Random<RunFilter>(), Random<RunFilter>() };
   parsedZenUnitArgs.wait = ZenUnit::Random<bool>();
   parsedZenUnitArgs.testruns = testrunsArgs;
   _argsParserMock->ParseMock.Return(parsedZenUnitArgs);

   _testClassRunnerRunnerMock->ApplyRunFiltersIfAnyMock.Expect();

   _nonVoidOneArgMemberFunctionCallerMock->NonConstCallMock.ReturnValues(firstTestRunExitCode, secondTestRunExitCode);

   _testRunResultMock->ResetStateExceptForSkipsMock.Expect();

   _consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.Expect();

   const vector<string> commandLineArgs{ Random<string>() };
   //
   const int overallExitCode = _testRunner.ParseArgsRunTestClassesPrintResults(commandLineArgs);
   //
   ZEN(_argsParserMock->ParseMock.CalledOnceWith(commandLineArgs));
   ZEN(_testClassRunnerRunnerMock->ApplyRunFiltersIfAnyMock.CalledOnceWith(parsedZenUnitArgs.runFilters));
   ZEN(_nonVoidOneArgMemberFunctionCallerMock->NonConstCallMock.CalledNTimesWith(
      testrunsArgs, &_testRunner, &TestRunner::PrintPreambleRunTestClassesPrintConclusion, parsedZenUnitArgs));
   ZEN(_testRunResultMock->ResetStateExceptForSkipsMock.CalledNTimes(testrunsArgs));
   ZEN(_consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.CalledOnceWith(parsedZenUnitArgs.wait));
   ARE_EQUAL(expectedOverallExitCode, overallExitCode);
}

TEST3X3(PrintPreambleRunTestClassesPrintConclusion_RunsTestsAndPrintsResults_UsingBackgroundThreadIfMaxTotalSecondsGT0_Returns0IfAllTestsPassedOtherwiseReturns1,
   unsigned maxtotalseconds,
   bool expectRunTestClassesWithWaitableRunnerThread,
   int determineExitCodeReturnValueAndExpectedExitCode,
   0u, false, 0,
   0u, false, 1,
   1u, true, 0,
   1u, true, 1,
   2u, true, 0,
   2u, true, 1)
{
   bool waitForAnyKeyIfPauseModeReturnValue = ZenUnit::Random<bool>();
   _nonVoidTwoArgMemberFunctionCallerMock->ConstCallMock.Return(waitForAnyKeyIfPauseModeReturnValue);
   bool havePausedInitialValue = ZenUnit::Random<bool>();
   _testRunner._havePaused = havePausedInitialValue;

   _testRunStopwatchMock->StartMock.Expect();

   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.commandLine = Random<string>();
   zenUnitArgs.maxtotalseconds = maxtotalseconds;
   _preamblePrinterMock->PrintOpeningThreeLinesMock.Expect();
   if (expectRunTestClassesWithWaitableRunnerThread)
   {
      _voidOneArgMemberFunctionCallerMock->NonConstCallMock.Expect();
   }
   else
   {
      _voidZeroArgMemberFunctionCallerMock->NonConstCallMock.Expect();
   }
   _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
   _testRunResultMock->PrintClosingLinesMock.Expect();

   const size_t TotalNumberOfTestCases = Random<size_t>();
   _testClassRunnerRunnerMock->NumberOfTestCasesMock.Return(TotalNumberOfTestCases);

   const unsigned testRunMicroseconds = _testRunStopwatchMock->StopMock.ReturnRandom();

   _testRunResultMock->DetermineExitCodeMock.Return(determineExitCodeReturnValueAndExpectedExitCode);
   //
   const int exitCode = _testRunner.PrintPreambleRunTestClassesPrintConclusion(zenUnitArgs);
   //
   ZEN(_nonVoidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
       &_testRunner, &TestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPaused, zenUnitArgs.pause, havePausedInitialValue));
   ARE_EQUAL(waitForAnyKeyIfPauseModeReturnValue, _testRunner._havePaused);
   ZEN(_testRunStopwatchMock->StartMock.CalledOnce());
   ZEN(_preamblePrinterMock->PrintOpeningThreeLinesMock.CalledOnceWith(
       zenUnitArgs, _testRunner._testClassRunnerRunner.get()));
   if (expectRunTestClassesWithWaitableRunnerThread)
   {
      ZEN(_voidOneArgMemberFunctionCallerMock->NonConstCallMock.CalledOnceWith(
         &_testRunner, &TestRunner::RunTestClassesWithWaitableRunnerThread, zenUnitArgs.maxtotalseconds));
   }
   else
   {
      ZEN(_voidZeroArgMemberFunctionCallerMock->NonConstCallMock.CalledOnceWith(
          &_testRunner, &TestRunner::RunTestClasses));
   }
   const unsigned expectedTestRunMilliseconds = testRunMicroseconds / 1000;
   ZEN(_testRunResultMock->PrintTestFailuresAndSkipsMock.CalledOnce());
   ZEN(_testClassRunnerRunnerMock->NumberOfTestCasesMock.CalledOnce());
   ZEN(_testRunStopwatchMock->StopMock.CalledOnce());
   ZEN(_testRunResultMock->PrintClosingLinesMock.CalledOnceWith(
       TotalNumberOfTestCases, expectedTestRunMilliseconds, zenUnitArgs));
   ZEN(_testRunResultMock->DetermineExitCodeMock.CalledOnceWith(zenUnitArgs));
   ARE_EQUAL(determineExitCodeReturnValueAndExpectedExitCode, exitCode);
}

TEST(WaitForAnyKeyIfPauseMode_PauseModeFalse_DoesNothing_ReturnsFalse)
{
   bool newValueForHavePaused = _testRunner.
      WaitForAnyKeyIfPauseModeAndHaveNotPaused(false, ZenUnit::Random<bool>());
   IS_FALSE(newValueForHavePaused);
}

TEST(WaitForAnyKeyIfPauseMode_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
{
   bool newValueForHavePaused = _testRunner.
      WaitForAnyKeyIfPauseModeAndHaveNotPaused(true, true);
   IS_TRUE(newValueForHavePaused);
}

TEST(WaitForAnyKeyIfPauseMode_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
{
   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WaitForAnyKeyMock.Expect();
   //
   bool newValueForHavePaused = _testRunner.
      WaitForAnyKeyIfPauseModeAndHaveNotPaused(true, false);
   //
   ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
      "ZenUnit test runner paused. Press any key to run tests."));
   ZEN(_consoleMock->WaitForAnyKeyMock.CalledOnce());
   IS_TRUE(newValueForHavePaused);
}

TEST(SkipTest_CallsTestRunResultAddSkippedFullTestName)
{
   _testRunResultMock->AddSkippedTestMock.Expect();
   const string TestClassName = Random<string>();
   const string TestName = Random<string>();
   const string Reason = Random<string>();
   //
   _testRunner.SkipTest(TestClassName.c_str(), TestName.c_str(), Reason.c_str());
   //
   ZEN(_testRunResultMock->AddSkippedTestMock.
      CalledOnceWith(TestClassName.c_str(), TestName.c_str(), Reason.c_str()));
}

TEST(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
{
   _testRunResultMock->AddSkippedTestClassNameAndReasonMock.Expect();
   const string SkippedTestClassName = Random<string>();
   const string Reason = Random<string>();
   //
   _testRunner.SkipTestClass(SkippedTestClassName.c_str(), Reason.c_str());
   //
   ZEN(_testRunResultMock->AddSkippedTestClassNameAndReasonMock.
      CalledOnceWith(SkippedTestClassName.c_str(), Reason.c_str()));
}

TEST(RunTestClasses_RunsTestClasses)
{
   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.commandLine = Random<string>();
   _testRunner._zenUnitArgs = zenUnitArgs;

   vector<TestClassResult> testClassResults(1);
   _testClassRunnerRunnerMock->RunTestClassesMock.Return(testClassResults);
   _testRunResultMock->SetTestClassResultsMock.Expect();
   //
   _testRunner.RunTestClasses();
   //
   ZEN(_testClassRunnerRunnerMock->RunTestClassesMock.CalledOnceWith(_testRunner._zenUnitArgs));
   ZEN(_testRunResultMock->SetTestClassResultsMock.CalledOnceWith(testClassResults));
}

//TEST2X2(RunTestClassesWithWaitableRunnerThread_SpawnsThreadToCallRunTestClasses_PrintsResultsAndExits1IfThreadTimesOut,
//   future_status runnerThreadWaitResult, bool expectTimeoutHandling,
//   future_status::ready, false,
//   future_status::timeout, true)
//{
//   const shared_ptr<VoidFutureMock> testClassRunnerDoneFutureMock(new VoidFutureMock);
//   testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.Return(runnerThreadWaitResult);
//   _futuristMock->AsyncMock.Return(testClassRunnerDoneFutureMock);
//   if (expectTimeoutHandling)
//   {
//      _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
//      _consoleMock->WriteLineAndExitMock.Expect();
//   }
//   const unsigned MaxTotalSeconds = Random<unsigned>();
//   //
//   _testRunner.RunTestClassesWithWaitableRunnerThread(MaxTotalSeconds);
//   //
//   ZEN(_futuristMock->AsyncMock.CalledOnceWith(&TestRunner::RunTestClasses, &_testRunner));
//   ZEN(testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.CalledOnceWith(MaxTotalSeconds));
//   if (expectTimeoutHandling)
//   {
//      ZEN(_testRunResultMock->PrintTestFailuresAndSkipsMock.CalledOnce());
//      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(
//         "[ZenUnit] Total run time exceeded maximum run time of " + to_string(MaxTotalSeconds) + " seconds.", 1));
//   }
//}

RUN_TESTS(TestRunnerTests)

}

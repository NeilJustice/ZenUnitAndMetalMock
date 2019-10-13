#include "pch.h"
#if defined __linux__ || defined __APPLE__
#include <unistd.h>
#endif

#include "ZenUnitLibraryTests/Components/Args/ZenMock/ArgsParserMock.h"
#include "ZenUnitLibraryTests/Components/Console/ZenMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomRunFilter.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/ZenMock/TestRunResultMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/PreamblePrinterMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/TestClassRunnerRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/ZenMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/ZenMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/ZenMock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/ZenMock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/ZenMock/StopwatchMock.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"

namespace ZenUnit
{
   TESTS(ZenUnitTestRunnerTests)
   AFACT(Constructor_NewsComponents)
   AFACT(AddTestClassRunner_EmplacesBackTestClassRunner)
   AFACT(SkipTest_CallsTestRunResultAddSkippedFullTestName)
   AFACT(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
   FACTS(RunTests_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeFalse_DoesNothing_ReturnsFalse)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
   FACTS(PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines_RunsTestsAndPrintsResults_UsingBackgroundThreadIfMaxTotalSecondsGT0_Returns0IfAllTestsPassedOtherwiseReturns1)
   AFACT(RunTestClasses_RunsTestClasses)
   EVIDENCE

   ZenUnitTestRunner _testRunner;
   ConsoleMock* _consoleMock = nullptr;
   PreamblePrinterMock* _preamblePrinterMock = nullptr;
   ArgsParserMock* _argsParserMock = nullptr;

   using NonVoidOneArgMemberFunctionCallerMockType = NonVoidOneArgMemberFunctionCallerMock<int, ZenUnitTestRunner, const ZenUnitArgs&>;
   NonVoidOneArgMemberFunctionCallerMockType* _nonVoidOneArgMemberFunctionCallerMock = nullptr;

   using VoidOneArgMemberFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<ZenUnitTestRunner, unsigned>;
   VoidOneArgMemberFunctionCallerMockType* _voidOneArgMemberFunctionCallerMock = nullptr;

   using NonVoidTwoArgMemberFunctionCallerMockType = NonVoidTwoArgMemberFunctionCallerMock<bool, ZenUnitTestRunner, bool, bool >;
   NonVoidTwoArgMemberFunctionCallerMockType* _nonVoidTwoArgMemberFunctionCallerMock = nullptr;

   VoidZeroArgMemberFunctionCallerMock<ZenUnitTestRunner>* _voidZeroArgMemberFunctionCallerMock = nullptr;

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
      _testRunner._voidZeroArgMemberFunctionCaller.reset(_voidZeroArgMemberFunctionCallerMock = new VoidZeroArgMemberFunctionCallerMock<ZenUnitTestRunner>);
      //_testRunner._futurist.reset(_futuristMock = new FuturistMock<TestRunner>);
      _testRunner._testClassRunnerRunner.reset(_testClassRunnerRunnerMock = new TestClassRunnerRunnerMock);
      _testRunner._testRunStopwatch.reset(_testRunStopwatchMock = new StopwatchMock);
   }

   TEST(Constructor_NewsComponents)
   {
      ZenUnitTestRunner testRunner;
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
      ARE_EQUAL(ZenUnitArgs(), testRunner._args);
      IS_FALSE(testRunner._havePaused);
   }

   TEST(AddTestClassRunner_EmplacesBackTestClassRunner)
   {
      _testClassRunnerRunnerMock->AddTestClassRunnerMock.Expect();
      SpecificTestClassRunner<TestingTestClass> testClassRunner("TestClassName");
      //
      _testRunner.AddTestClassRunner(&testClassRunner);
      //
      ZENMOCK(_testClassRunnerRunnerMock->AddTestClassRunnerMock.CalledOnceWith(&testClassRunner));
   }

   TEST4X4(RunTests_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1,
      int testrunsArg, int firstTestRunExitCode, int secondTestRunExitCode, int expectedOverallExitCode,
      1, 0, ZenUnit::Random<int>(), 0,
      2, 1, 0, 1,
      2, 0, 1, 1,
      2, 1, 1, 1)
   {
      ZenUnitArgs parsedZenUnitArgs;
      parsedZenUnitArgs.runFilters = { Random<RunFilter>(), Random<RunFilter>() };
      parsedZenUnitArgs.wait = ZenUnit::Random<bool>();
      parsedZenUnitArgs.testRuns = testrunsArg;
      _argsParserMock->ParseMock.Return(parsedZenUnitArgs);

      _testClassRunnerRunnerMock->ApplyRunFiltersIfAnyMock.Expect();

      _nonVoidOneArgMemberFunctionCallerMock->NonConstCallMock.ReturnValues(firstTestRunExitCode, secondTestRunExitCode);

      _testRunResultMock->ResetStateExceptForSkipsMock.Expect();

      _consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.Expect();

      const vector<string> commandLineArgs = ZenUnit::RandomVector<string>();
      //
      const int overallExitCode = _testRunner.RunTests(commandLineArgs);
      //
      ZENMOCK(_argsParserMock->ParseMock.CalledOnceWith(commandLineArgs));
      ZENMOCK(_testClassRunnerRunnerMock->ApplyRunFiltersIfAnyMock.CalledOnceWith(parsedZenUnitArgs.runFilters));
      ZENMOCK(_nonVoidOneArgMemberFunctionCallerMock->NonConstCallMock.CalledNTimesWith(
         testrunsArg, &_testRunner, &ZenUnitTestRunner::PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines, parsedZenUnitArgs));
      ZENMOCK(_testRunResultMock->ResetStateExceptForSkipsMock.CalledNTimes(testrunsArg));
      ZENMOCK(_consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.CalledOnceWith(parsedZenUnitArgs.wait));
      ARE_EQUAL(expectedOverallExitCode, overallExitCode);
   }

   TEST3X3(PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines_RunsTestsAndPrintsResults_UsingBackgroundThreadIfMaxTotalSecondsGT0_Returns0IfAllTestsPassedOtherwiseReturns1,
      unsigned maxTotalSeconds,
      bool expectRunTestClassesWithWaitableRunnerThread,
      int determineExitCodeReturnValueAndExpectedExitCode,
      0u, false, 0,
      0u, false, 1,
      1u, true, 0,
      1u, true, 1,
      2u, true, 0,
      2u, true, 1)
   {
      const bool waitForAnyKeyIfPauseModeReturnValue = ZenUnit::Random<bool>();
      _nonVoidTwoArgMemberFunctionCallerMock->ConstCallMock.Return(waitForAnyKeyIfPauseModeReturnValue);
      const bool havePausedInitialValue = ZenUnit::Random<bool>();
      _testRunner._havePaused = havePausedInitialValue;

      _testRunStopwatchMock->StartMock.Expect();

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      zenUnitArgs.maxTotalSeconds = maxTotalSeconds;
      const string startDateTime = _preamblePrinterMock->PrintPreambleLinesAndGetStartTimeMock.ReturnRandom();
      if (expectRunTestClassesWithWaitableRunnerThread)
      {
         _voidOneArgMemberFunctionCallerMock->NonConstCallMock.Expect();
      }
      else
      {
         _voidZeroArgMemberFunctionCallerMock->NonConstCallMock.Expect();
      }
      _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
      _testRunResultMock->PrintConclusionLinesMock.Expect();

      const size_t totalNumberOfTestCases = Random<size_t>();
      _testClassRunnerRunnerMock->NumberOfTestCasesMock.Return(totalNumberOfTestCases);

      const string testRunElapsedSeconds = _testRunStopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

      _testRunResultMock->DetermineExitCodeMock.Return(determineExitCodeReturnValueAndExpectedExitCode);
      //
      const int exitCode = _testRunner.PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines(zenUnitArgs);
      //
      ZENMOCK(_nonVoidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         &_testRunner, &ZenUnitTestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused,
         zenUnitArgs.pause, havePausedInitialValue));
      ARE_EQUAL(waitForAnyKeyIfPauseModeReturnValue, _testRunner._havePaused);
      ZENMOCK(_testRunStopwatchMock->StartMock.CalledOnce());
      ZENMOCK(_preamblePrinterMock->PrintPreambleLinesAndGetStartTimeMock.CalledOnceWith(
         zenUnitArgs, _testRunner._testClassRunnerRunner.get()));
      if (expectRunTestClassesWithWaitableRunnerThread)
      {
         ZENMOCK(_voidOneArgMemberFunctionCallerMock->NonConstCallMock.CalledOnceWith(
            &_testRunner, &ZenUnitTestRunner::RunTestClassesWithWaitableRunnerThread, zenUnitArgs.maxTotalSeconds));
      }
      else
      {
         ZENMOCK(_voidZeroArgMemberFunctionCallerMock->NonConstCallMock.CalledOnceWith(
            &_testRunner, &ZenUnitTestRunner::RunTestClasses));
      }
      ZENMOCK(_testRunResultMock->PrintTestFailuresAndSkipsMock.CalledOnce());
      ZENMOCK(_testClassRunnerRunnerMock->NumberOfTestCasesMock.CalledOnce());
      ZENMOCK(_testRunStopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
      ZENMOCK(_testRunResultMock->PrintConclusionLinesMock.CalledOnceWith(startDateTime, totalNumberOfTestCases, testRunElapsedSeconds, zenUnitArgs));
      ZENMOCK(_testRunResultMock->DetermineExitCodeMock.CalledOnceWith(zenUnitArgs));
      ARE_EQUAL(determineExitCodeReturnValueAndExpectedExitCode, exitCode);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeFalse_DoesNothing_ReturnsFalse)
   {
      const bool newValueForHavePaused = _testRunner.
         WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(false, ZenUnit::Random<bool>());
      IS_FALSE(newValueForHavePaused);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
   {
      const bool newValueForHavePaused = _testRunner.
         WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(true, true);
      IS_TRUE(newValueForHavePaused);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WaitForAnyKeyMock.Expect();
      //
      const bool newValueForHavePaused = _testRunner.
         WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(true, false);
      //
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit test runner paused. Press any key to run tests."));
      ZENMOCK(_consoleMock->WaitForAnyKeyMock.CalledOnce());
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
      ZENMOCK(_testRunResultMock->AddSkippedTestMock.
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
      ZENMOCK(_testRunResultMock->AddSkippedTestClassNameAndReasonMock.
         CalledOnceWith(SkippedTestClassName.c_str(), Reason.c_str()));
   }

   TEST(RunTestClasses_RunsTestClasses)
   {
      ZenUnitArgs args;
      args.commandLine = Random<string>();
      _testRunner._args = args;

      vector<TestClassResult> testClassResults(1);
      _testClassRunnerRunnerMock->RunTestClassesMock.Return(testClassResults);
      _testRunResultMock->SetTestClassResultsMock.Expect();
      //
      _testRunner.RunTestClasses();
      //
      ZENMOCK(_testClassRunnerRunnerMock->RunTestClassesMock.CalledOnceWith(_testRunner._args));
      ZENMOCK(_testRunResultMock->SetTestClassResultsMock.CalledOnceWith(testClassResults));
   }

   RUN_TESTS(ZenUnitTestRunnerTests)
}

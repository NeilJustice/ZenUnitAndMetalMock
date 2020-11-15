#include "pch.h"
#if defined __linux__ || defined __APPLE__
#include <unistd.h>
#endif

#include "ZenUnitLibraryTests/Components/Args/MetalMock/ArgsParserMock.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestRunResultMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/PreamblePrinterMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestClassRunnerRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/StopwatchMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(ZenUnitTestRunnerTests)
   AFACT(Constructor_NewsComponents)
   AFACT(GetZenUnitArgs_ReturnsConstReferenceToZenUnitArgsFieldOnStaticInstanceOfZenUnitTestRunner)
   AFACT(VirtualGetZenUnitArgs_ReturnsConstReferenceToZenUnitArgsField)
   AFACT(AddTestClassRunner_EmplacesBackTestClassRunner_ReturnsNullptr)
   AFACT(SkipTest_CallsTestRunResultAddSkippedFullTestName)
   AFACT(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
   FACTS(RunTests_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeFalse_DoesNothing_ReturnsFalse)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
   AFACT(PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines_RunsTestsAndPrintsResults_Returns0IfAllTestsPassedOtherwiseReturns1)
   AFACT(RunTestClasses_RunsTestClasses)
   EVIDENCE

   ZenUnitTestRunner _zenUnitTestRunner;
   ConsoleMock* _consoleMock = nullptr;
   PreamblePrinterMock* _preamblePrinterMock = nullptr;
   ArgsParserMock* _argsParserMock = nullptr;

   using NonVoidOneArgMemberFunctionCallerMockType = NonVoidOneArgMemberFunctionCallerMock<int, ZenUnitTestRunner, const ZenUnitArgs&>;
   NonVoidOneArgMemberFunctionCallerMockType* _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLinesMock = nullptr;

   using NonVoidTwoArgMemberFunctionCallerMockType = NonVoidTwoArgMemberFunctionCallerMock<bool, ZenUnitTestRunner, bool, bool >;
   NonVoidTwoArgMemberFunctionCallerMockType* _caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPausedMock = nullptr;

   VoidZeroArgMemberFunctionCallerMock<ZenUnitTestRunner>* _caller_RunTestClassesMock = nullptr;

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
      _zenUnitTestRunner._console.reset(_consoleMock = new ConsoleMock);
      _zenUnitTestRunner._preamblePrinter.reset(_preamblePrinterMock = new PreamblePrinterMock);
      _zenUnitTestRunner._argsParser.reset(_argsParserMock = new ArgsParserMock);
      _zenUnitTestRunner._testRunResult.reset(_testRunResultMock = new TestRunResultMock);
      _zenUnitTestRunner._caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines.reset(_caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLinesMock = new NonVoidOneArgMemberFunctionCallerMockType);
      _zenUnitTestRunner._caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused.reset(_caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPausedMock = new NonVoidTwoArgMemberFunctionCallerMockType);
      _zenUnitTestRunner._caller_RunTestClasses.reset(_caller_RunTestClassesMock = new VoidZeroArgMemberFunctionCallerMock<ZenUnitTestRunner>);
      _zenUnitTestRunner._testClassRunnerRunner.reset(_testClassRunnerRunnerMock = new TestClassRunnerRunnerMock);
      _zenUnitTestRunner._testRunStopwatch.reset(_testRunStopwatchMock = new StopwatchMock);
   }

   TEST(Constructor_NewsComponents)
   {
      ZenUnitTestRunner zenUnitTestRunner;
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._console);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._preamblePrinter);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._argsParser);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._caller_RunTestClasses);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._testClassRunnerRunner);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._testRunResult);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._testRunStopwatch);
      ARE_EQUAL(ZenUnitArgs(), zenUnitTestRunner._zenUnitArgs);
      IS_FALSE(zenUnitTestRunner._havePaused);
   }

   TEST(GetZenUnitArgs_ReturnsConstReferenceToZenUnitArgsFieldOnStaticInstanceOfZenUnitTestRunner)
   {
      const ZenUnitArgs& zenUnitArgs = ZenUnitTestRunner::GetZenUnitArgs();
      ARE_SAME(ZenUnitTestRunner::Instance()->_zenUnitArgs, zenUnitArgs);
   }

   TEST(VirtualGetZenUnitArgs_ReturnsConstReferenceToZenUnitArgsField)
   {
      const ZenUnitArgs& zenUnitArgs = _zenUnitTestRunner.VirtualGetZenUnitArgs();
      ARE_SAME(_zenUnitTestRunner._zenUnitArgs, zenUnitArgs);
   }

   TEST(AddTestClassRunner_EmplacesBackTestClassRunner_ReturnsNullptr)
   {
      _testClassRunnerRunnerMock->AddTestClassRunnerMock.Expect();
      unique_ptr<SpecificTestClassRunner<TestingTestClass>> specificTestClassRunner = make_unique<SpecificTestClassRunner<TestingTestClass>>("TestClassName");
      //
      const std::nullptr_t returnValue = _zenUnitTestRunner.AddTestClassRunner(std::move(specificTestClassRunner));
      //
      METALMOCK(_testClassRunnerRunnerMock->AddTestClassRunnerMock.CalledOnceWithAny());
      IS_NULLPTR(returnValue);
   }

   TEST4X4(RunTests_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1,
      int testrunsArg, int firstTestRunExitCode, int secondTestRunExitCode, int expectedOverallExitCode,
      1, 0, ZenUnit::Random<int>(), 0,
      2, 1, 0, 1,
      2, 0, 1, 1,
      2, 1, 1, 1)
   {
      ZenUnitArgs parsedZenUnitArgs;
      parsedZenUnitArgs.testNameFilters = { Random<TestNameFilter>(), Random<TestNameFilter>() };
      parsedZenUnitArgs.pauseAfter = ZenUnit::Random<bool>();
      parsedZenUnitArgs.testRuns = testrunsArg;
      _argsParserMock->ParseMock.Return(parsedZenUnitArgs);

      _testClassRunnerRunnerMock->ApplyTestNameFiltersIfAnyMock.Expect();

      _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLinesMock->
         NonConstCallMock.ReturnValues(firstTestRunExitCode, secondTestRunExitCode);

      _testRunResultMock->ResetStateExceptForSkipsMock.Expect();

      _consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.Expect();

      const vector<string> commandLineArgs = ZenUnit::RandomVector<string>();
      //
      const int overallExitCode = _zenUnitTestRunner.RunTests(commandLineArgs);
      //
      METALMOCK(_argsParserMock->ParseMock.CalledOnceWith(commandLineArgs));
      METALMOCK(_testClassRunnerRunnerMock->ApplyTestNameFiltersIfAnyMock.CalledOnceWith(parsedZenUnitArgs.testNameFilters));
      METALMOCK(_caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLinesMock->NonConstCallMock.CalledNTimesWith(
         testrunsArg, &_zenUnitTestRunner, &ZenUnitTestRunner::PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines, parsedZenUnitArgs));
      METALMOCK(_testRunResultMock->ResetStateExceptForSkipsMock.CalledNTimes(testrunsArg));
      METALMOCK(_consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.CalledOnceWith(parsedZenUnitArgs.pauseAfter));
      ARE_EQUAL(expectedOverallExitCode, overallExitCode);
   }

   TEST(PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines_RunsTestsAndPrintsResults_Returns0IfAllTestsPassedOtherwiseReturns1)
   {
      const bool waitForAnyKeyIfPauseModeReturnValue = ZenUnit::Random<bool>();
      _caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPausedMock->ConstCallMock.Return(waitForAnyKeyIfPauseModeReturnValue);
      const bool havePausedInitialValue = ZenUnit::Random<bool>();
      _zenUnitTestRunner._havePaused = havePausedInitialValue;

      _testRunStopwatchMock->StartMock.Expect();

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      const string startDateTime = _preamblePrinterMock->PrintPreambleLinesAndGetStartDateTimeMock.ReturnRandom();
      _caller_RunTestClassesMock->NonConstCallMock.Expect();
      _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
      _testRunResultMock->PrintConclusionLinesMock.Expect();

      const size_t totalNumberOfTestCases = Random<size_t>();
      _testClassRunnerRunnerMock->NumberOfTestCasesMock.Return(totalNumberOfTestCases);

      const string testRunElapsedSeconds = _testRunStopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

      const int determineZenUnitExitCodeReturnValue = _testRunResultMock->DetermineZenUnitExitCodeMock.ReturnRandom();
      //
      const int exitCode = _zenUnitTestRunner.PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines(zenUnitArgs);
      //
      METALMOCK(_caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPausedMock->ConstCallMock.CalledOnceWith(
         &_zenUnitTestRunner, &ZenUnitTestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused,
         zenUnitArgs.pauseBefore, havePausedInitialValue));
      ARE_EQUAL(waitForAnyKeyIfPauseModeReturnValue, _zenUnitTestRunner._havePaused);
      METALMOCK(_testRunStopwatchMock->StartMock.CalledOnce());
      METALMOCK(_preamblePrinterMock->PrintPreambleLinesAndGetStartDateTimeMock.CalledOnceWith(
         zenUnitArgs, _zenUnitTestRunner._testClassRunnerRunner.get()));
      METALMOCK(_caller_RunTestClassesMock->NonConstCallMock.CalledOnceWith(&_zenUnitTestRunner, &ZenUnitTestRunner::RunTestClasses));
      METALMOCK(_testRunResultMock->PrintTestFailuresAndSkipsMock.CalledOnce());
      METALMOCK(_testClassRunnerRunnerMock->NumberOfTestCasesMock.CalledOnce());
      METALMOCK(_testRunStopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
      METALMOCK(_testRunResultMock->PrintConclusionLinesMock.CalledOnceWith(startDateTime, totalNumberOfTestCases, testRunElapsedSeconds, zenUnitArgs));
      METALMOCK(_testRunResultMock->DetermineZenUnitExitCodeMock.CalledOnceWith(zenUnitArgs));
      ARE_EQUAL(determineZenUnitExitCodeReturnValue, exitCode);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeFalse_DoesNothing_ReturnsFalse)
   {
      const bool newValueForHavePaused = _zenUnitTestRunner.
         WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(false, ZenUnit::Random<bool>());
      IS_FALSE(newValueForHavePaused);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
   {
      const bool newValueForHavePaused = _zenUnitTestRunner.
         WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(true, true);
      IS_TRUE(newValueForHavePaused);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WaitForAnyKeyMock.Expect();
      //
      const bool newValueForHavePaused = _zenUnitTestRunner.
         WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(true, false);
      //
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit test runner paused. Press any key to run tests."));
      METALMOCK(_consoleMock->WaitForAnyKeyMock.CalledOnce());
      IS_TRUE(newValueForHavePaused);
   }

   TEST(SkipTest_CallsTestRunResultAddSkippedFullTestName)
   {
      _testRunResultMock->AddSkippedTestMock.Expect();
      const string TestClassName = Random<string>();
      const string TestName = Random<string>();
      const string Reason = Random<string>();
      //
      _zenUnitTestRunner.SkipTest(TestClassName.c_str(), TestName.c_str(), Reason.c_str());
      //
      METALMOCK(_testRunResultMock->AddSkippedTestMock.
         CalledOnceWith(TestClassName.c_str(), TestName.c_str(), Reason.c_str()));
   }

   TEST(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
   {
      _testRunResultMock->AddSkippedTestClassNameAndReasonMock.Expect();
      const string SkippedTestClassName = Random<string>();
      const string Reason = Random<string>();
      //
      _zenUnitTestRunner.SkipTestClass(SkippedTestClassName.c_str(), Reason.c_str());
      //
      METALMOCK(_testRunResultMock->AddSkippedTestClassNameAndReasonMock.
         CalledOnceWith(SkippedTestClassName.c_str(), Reason.c_str()));
   }

   TEST(RunTestClasses_RunsTestClasses)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      _zenUnitTestRunner._zenUnitArgs = zenUnitArgs;

      vector<TestClassResult> testClassResults(1);
      _testClassRunnerRunnerMock->RunTestClassesMock.Return(testClassResults);
      _testRunResultMock->SetTestClassResultsMock.Expect();
      //
      _zenUnitTestRunner.RunTestClasses();
      //
      METALMOCK(_testClassRunnerRunnerMock->RunTestClassesMock.CalledOnceWith(_zenUnitTestRunner._zenUnitArgs));
      METALMOCK(_testRunResultMock->SetTestClassResultsMock.CalledOnceWith(testClassResults));
   }

   RUN_TESTS(ZenUnitTestRunnerTests)
}

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
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NTimesMemberFunctionAccumulatorMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/StopwatchMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/WatchMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(ZenUnitTestRunnerTests)
   AFACT(DefaultConstructor_NewsComponents)
   AFACT(GetZenUnitArgs_ReturnsConstReferenceToZenUnitArgsFieldOnStaticInstanceOfZenUnitTestRunner)
   AFACT(VirtualGetZenUnitArgs_ReturnsConstReferenceToZenUnitArgsField)
   AFACT(AddTestClassRunner_EmplacesBackTestClassRunner_ReturnsNullptr)
   AFACT(SkipTest_CallsTestRunResultAddSkippedFullTestName)
   AFACT(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
   FACTS(RunTestsNumberOfTestRunsTimes_SetsCrtAssertionFailureHandlerOnWindows_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1)
   // Private Functions
   AFACT(PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines_RunsTestsAndPrintsResults_Returns0IfAllTestsPassedOtherwiseReturns1)
   AFACT(RunTestClasses_CallsRunTestClassesOnTestClassRunnerRunner_CallsTestRunResultSetsTestClassResults)
   AFACT(SetNextGlobalZenUnitModeRandomSeed_RandomSeedSetByUserIsFalse_SetsGlobalZenUnitModeRandomSeedToSecondsSince1970)
   AFACT(SetNextGlobalZenUnitModeRandomSeed_RandomSeedSetByUserIsTrue_DoesNothing)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeFalse_DoesNothing_ReturnsFalse)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
   AFACT(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
   EVIDENCE

   ZenUnitTestRunner _zenUnitTestRunner;
   // Function Callers
   using NonVoidOneArgMemberFunctionCallerMockType = NonVoidOneArgMemberFunctionCallerMock<int, ZenUnitTestRunner, const ZenUnitArgs&>;
   NonVoidOneArgMemberFunctionCallerMockType* _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLinesMock = nullptr;

   VoidZeroArgMemberFunctionCallerMock<ZenUnitTestRunner>* _caller_RunTestClassesMock = nullptr;

   using VoidOneArgMemberFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<ZenUnitTestRunner, bool>;
   VoidOneArgMemberFunctionCallerMockType* _caller_SetNextGlobalZenUnitModeRandomSeedMock = nullptr;

   using NonVoidTwoArgMemberFunctionCallerMockType = NonVoidTwoArgMemberFunctionCallerMock<bool, ZenUnitTestRunner, bool, bool>;
   NonVoidTwoArgMemberFunctionCallerMockType* _caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPausedMock = nullptr;

   NTimesMemberFunctionAccumulatorMock<int, ZenUnitTestRunner>* _nTimesMemberFunctionAccumulator_RunTestsMock = nullptr;
   // Function Pointers
#if defined _WIN32 && defined _DEBUG
   using CRT_REPORT_HOOK_FunctionType = int(*)(int, char*, int*);
   METALMOCK_NONVOID1_FREE(CRT_REPORT_HOOK_FunctionType, _CrtSetReportHook, CRT_REPORT_HOOK_FunctionType)
#endif
   // Constant Components
   ArgsParserMock* _argsParserMock = nullptr;
   ConsoleMock* _consoleMock = nullptr;
   PreamblePrinterMock* _preamblePrinterMock = nullptr;
   WatchMock* _watchMock = nullptr;
   // Mutable Components
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
      // Function Callers
      _zenUnitTestRunner._caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines.reset(
         _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLinesMock = new NonVoidOneArgMemberFunctionCallerMockType);
      _zenUnitTestRunner._caller_RunTestClasses.reset(
         _caller_RunTestClassesMock = new VoidZeroArgMemberFunctionCallerMock<ZenUnitTestRunner>);
      _zenUnitTestRunner._caller_SetNextGlobalZenUnitModeRandomSeed.reset(
         _caller_SetNextGlobalZenUnitModeRandomSeedMock = new VoidOneArgMemberFunctionCallerMockType);
      _zenUnitTestRunner._caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused.reset(
         _caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPausedMock = new NonVoidTwoArgMemberFunctionCallerMockType);
      _zenUnitTestRunner._nTimesMemberFunctionAccumulator_RunTests.reset(
         _nTimesMemberFunctionAccumulator_RunTestsMock = new NTimesMemberFunctionAccumulatorMock<int, ZenUnitTestRunner>);
      // Function Pointers
#if defined _WIN32 && defined _DEBUG
      _zenUnitTestRunner._call_CrtSetReportHook = BIND_1ARG_METALMOCK_OBJECT(_CrtSetReportHookMock);
#endif
      // Constant Components
      _zenUnitTestRunner._argsParser.reset(_argsParserMock = new ArgsParserMock);
      _zenUnitTestRunner._console.reset(_consoleMock = new ConsoleMock);
      _zenUnitTestRunner._preamblePrinter.reset(_preamblePrinterMock = new PreamblePrinterMock);
      _zenUnitTestRunner._watch.reset(_watchMock = new WatchMock);
      // Mutable Components
      _zenUnitTestRunner._testClassRunnerRunner.reset(_testClassRunnerRunnerMock = new TestClassRunnerRunnerMock);
      _zenUnitTestRunner._testRunResult.reset(_testRunResultMock = new TestRunResultMock);
      _zenUnitTestRunner._testRunStopwatch.reset(_testRunStopwatchMock = new StopwatchMock);
   }

   TEST(DefaultConstructor_NewsComponents)
   {
      ZenUnitTestRunner zenUnitTestRunner;
      // Function Callers
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._caller_RunTestClasses);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._caller_SetNextGlobalZenUnitModeRandomSeed);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._nTimesMemberFunctionAccumulator_RunTests);
      // Function Pointers
#if defined _WIN32 && defined _DEBUG
      STD_FUNCTION_TARGETS(_CrtSetReportHook, zenUnitTestRunner._call_CrtSetReportHook);
#endif
      // Constant Components
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._argsParser);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._console);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._preamblePrinter);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._watch);
      // Mutable Components
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._testClassRunnerRunner);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._testRunResult);
      DELETE_TO_ASSERT_NEWED(zenUnitTestRunner._testRunStopwatch);
      // Mutable Fields
      IS_DEFAULT_VALUE(zenUnitTestRunner._zenUnitArgs);
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
      SpecificTestClassRunner<TestingTestClass> specificTestClassRunner(ZenUnit::Random<const char*>());
      //
      const std::nullptr_t returnValue = _zenUnitTestRunner.AddTestClassRunner(&specificTestClassRunner);
      //
      METALMOCK(_testClassRunnerRunnerMock->AddTestClassRunnerMock.CalledOnceWithAny());
      IS_NULLPTR(returnValue);
   }

   TEST2X2(RunTestsNumberOfTestRunsTimes_SetsCrtAssertionFailureHandlerOnWindows_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1,
      int zenUnitArgsTestRuns, size_t expectedNumberOfTestRuns,
      -2, numeric_limits<size_t>::max(),
      -1, numeric_limits<size_t>::max(),
      0, size_t(0),
      1, size_t(1),
      2, size_t(2))
   {
#if defined _WIN32 && defined _DEBUG
      _CrtSetReportHookMock.Return(nullptr);
#endif
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.testRuns = zenUnitArgsTestRuns;
      _argsParserMock->ParseMock.Return(zenUnitArgs);

      _testClassRunnerRunnerMock->ApplyTestNameFiltersIfAnyMock.Expect();

      const int numberOfFailedTestRuns =
         _nTimesMemberFunctionAccumulator_RunTestsMock->AccumulateNonConstMemberFunctionNTimesMock.ReturnRandom();

      _consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.Expect();

      const vector<string> commandLineArgs = ZenUnit::RandomVector<string>();
      //
      const int returnedNumberOfFailedTestRuns = _zenUnitTestRunner.RunTestsNumberOfTestRunsTimes(commandLineArgs);
      //
#if defined _WIN32 && defined _DEBUG
      METALMOCK(_CrtSetReportHookMock.CalledOnceWith(ZenUnitTestRunner::FailFastInResponseToWindowsCrtAssertionFailure));
#endif
      METALMOCK(_argsParserMock->ParseMock.CalledOnceWith(commandLineArgs));
      METALMOCK(_testClassRunnerRunnerMock->ApplyTestNameFiltersIfAnyMock.CalledOnceWith(zenUnitArgs.testNameFilters));
      METALMOCK(_nTimesMemberFunctionAccumulator_RunTestsMock->AccumulateNonConstMemberFunctionNTimesMock.CalledOnceWith(
         expectedNumberOfTestRuns, &_zenUnitTestRunner, &ZenUnitTestRunner::RunTests));
      METALMOCK(_consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.CalledOnceWith(zenUnitArgs.pauseAfter));
      ARE_EQUAL(numberOfFailedTestRuns, returnedNumberOfFailedTestRuns);
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
      METALMOCK(_testRunResultMock->AddSkippedTestMock.CalledOnceWith(TestClassName.c_str(), TestName.c_str(), Reason.c_str()));
   }

   TEST(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
   {
      _testRunResultMock->AddSkippedTestClassNameAndReasonMock.Expect();
      const string SkippedTestClassName = Random<string>();
      const string Reason = Random<string>();
      //
      _zenUnitTestRunner.SkipTestClass(SkippedTestClassName.c_str(), Reason.c_str());
      //
      METALMOCK(_testRunResultMock->AddSkippedTestClassNameAndReasonMock.CalledOnceWith(SkippedTestClassName.c_str(), Reason.c_str()));
   }

   // Private Functions

   TEST(PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines_RunsTestsAndPrintsResults_Returns0IfAllTestsPassedOtherwiseReturns1)
   {
      const bool waitForAnyKeyIfPauseModeReturnValue = ZenUnit::Random<bool>();
      _caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPausedMock->CallConstMemberFunctionMock.Return(waitForAnyKeyIfPauseModeReturnValue);
      const bool havePausedInitialValue = ZenUnit::Random<bool>();
      _zenUnitTestRunner._havePaused = havePausedInitialValue;

      _testRunStopwatchMock->StartMock.Expect();

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      const string startDateTime = _preamblePrinterMock->PrintPreambleLinesAndGetStartDateTimeMock.ReturnRandom();
      _caller_RunTestClassesMock->CallNonConstMemberFunctionMock.Expect();
      _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
      _testRunResultMock->PrintConclusionLinesMock.Expect();

      const size_t totalNumberOfTestCases = Random<size_t>();
      _testClassRunnerRunnerMock->NumberOfTestCasesMock.Return(totalNumberOfTestCases);

      const string testRunElapsedSeconds = _testRunStopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

      const int determineZenUnitExitCodeReturnValue = _testRunResultMock->DetermineZenUnitExitCodeMock.ReturnRandom();
      //
      const int exitCode = _zenUnitTestRunner.PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines(zenUnitArgs);
      //
      METALMOCK(_caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPausedMock->CallConstMemberFunctionMock.CalledOnceWith(
         &_zenUnitTestRunner, &ZenUnitTestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused,
         zenUnitArgs.pauseBefore, havePausedInitialValue));
      ARE_EQUAL(waitForAnyKeyIfPauseModeReturnValue, _zenUnitTestRunner._havePaused);
      METALMOCK(_testRunStopwatchMock->StartMock.CalledOnce());
      METALMOCK(_preamblePrinterMock->PrintPreambleLinesAndGetStartDateTimeMock.CalledOnceWith(
         zenUnitArgs, _zenUnitTestRunner._testClassRunnerRunner.get()));
      METALMOCK(_caller_RunTestClassesMock->CallNonConstMemberFunctionMock.CalledOnceWith(
         &_zenUnitTestRunner, &ZenUnitTestRunner::RunTestClasses));
      METALMOCK(_testRunResultMock->PrintTestFailuresAndSkipsMock.CalledOnce());
      METALMOCK(_testClassRunnerRunnerMock->NumberOfTestCasesMock.CalledOnce());
      METALMOCK(_testRunStopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
      METALMOCK(_testRunResultMock->PrintConclusionLinesMock.CalledOnceWith(
         startDateTime, totalNumberOfTestCases, testRunElapsedSeconds, zenUnitArgs));
      METALMOCK(_testRunResultMock->DetermineZenUnitExitCodeMock.CalledOnceWith(zenUnitArgs));
      ARE_EQUAL(determineZenUnitExitCodeReturnValue, exitCode);
   }

   TEST(RunTestClasses_CallsRunTestClassesOnTestClassRunnerRunner_CallsTestRunResultSetsTestClassResults)
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

   TEST(SetNextGlobalZenUnitModeRandomSeed_RandomSeedSetByUserIsFalse_SetsGlobalZenUnitModeRandomSeedToSecondsSince1970)
   {
      const unsigned secondSince1970 = _watchMock->SecondsSince1970Mock.ReturnRandom();
      //
      _zenUnitTestRunner.SetNextGlobalZenUnitModeRandomSeed(false);
      //
      METALMOCK(_watchMock->SecondsSince1970Mock.CalledOnce());
      ARE_EQUAL(secondSince1970, globalZenUnitMode.randomSeed);
   }

   TEST(SetNextGlobalZenUnitModeRandomSeed_RandomSeedSetByUserIsTrue_DoesNothing)
   {
      _zenUnitTestRunner.SetNextGlobalZenUnitModeRandomSeed(true);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeFalse_DoesNothing_ReturnsFalse)
   {
      const bool newValueForHavePaused = _zenUnitTestRunner.WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(false, ZenUnit::Random<bool>());
      IS_FALSE(newValueForHavePaused);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
   {
      const bool newValueForHavePaused = _zenUnitTestRunner.WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(true, true);
      IS_TRUE(newValueForHavePaused);
   }

   TEST(WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WaitForAnyKeyMock.Expect();
      //
      const bool newValueForHavePaused =
         _zenUnitTestRunner.WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(true, false);
      //
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit test runner paused before running tests. Press any key to run tests..."));
      METALMOCK(_consoleMock->WaitForAnyKeyMock.CalledOnce());
      IS_TRUE(newValueForHavePaused);
   }

   RUN_TESTS(ZenUnitTestRunnerTests)
}

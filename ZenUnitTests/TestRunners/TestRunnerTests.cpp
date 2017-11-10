#include "pch.h"
#include "ZenUnitTests/Args/Mock/ArgsParserMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestRunResultMock.h"
#include "ZenUnitTests/TestRunners/Mock/PreamblePrinterMock.h"
#include "ZenUnitTests/TestRunners/Mock/MultiTestClassRunnerMock.h"
//#include "ZenUnitTests/Utils/Concurrency/Mock/FuturistMock.h"
#include "ZenUnitTests/Utils/Concurrency/Mock/VoidFutureMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"

namespace ZenUnit
{
   TESTS(TestRunnerTests)
   AFACT(Constructor_NewsComponents)
   AFACT(AddTestClassRunner_EmplacesBackTestClassRunner)
   AFACT(SkipTest_CallsTestRunResultAddSkippedFullTestName)
   AFACT(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
   FACTS(ParseArgsRunTestClassesPrintResults_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1)
   AFACT(WaitForEnterKeyIfPauseMode_PauseModeFalse_DoesNothing_ReturnsFalse)
   AFACT(WaitForEnterKeyIfPauseMode_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
   AFACT(WaitForEnterKeyIfPauseMode_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForEnterKey_ReturnsTrue)
   //FACTS(RunTestClassesAndPrintResults_RunsTestsAndPrintsResults_Returns0IfAllTestsPassedOtherwiseReturns1)
   AFACT(RunTestClasses_RunsTestClasses)
   //FACTS(RunTestClassesWithWaitableRunnerThread_SpawnsThreadToCallRunTestClasses_PrintsResultsAndExits1IfThreadTimesOut)
   EVIDENCE

   TestRunner _testRunner;
   ConsoleMock* _consoleMock;
   PreamblePrinterMock* _preamblePrinterMock;
   //FuturistMock<TestRunner>* _futuristMock;
   MultiTestClassRunnerMock* _multiTestClassRunnerMock;
   TestRunResultMock* _testRunResultMock;

   class TestingTestClass
   {
   public:
      static vector<unique_ptr<Test>> GetTests(const char*) { return {}; }
   };

   class TestRunnerSelfMockedA : public Zen::Mock<TestRunner>
   {
   public:
      ZENMOCK_NONVOID1(int, RunTestClassesAndPrintResults, const ZenUnitArgs&)
      ArgsParserMock* argsParserMock;
      PreamblePrinterMock* preamblePrinterMock;
      MultiTestClassRunnerMock* multiTestClassRunnerMock;
      TestRunResultMock* testRunResultMock;
      ConsoleMock* consoleMock;
      StopwatchMock* testRunStopwatchMock;
      TestRunnerSelfMockedA()
      {
         _argsParser.reset(argsParserMock = new ArgsParserMock);
         _preamblePrinter.reset(preamblePrinterMock = new PreamblePrinterMock);
         _multiTestClassRunner.reset(multiTestClassRunnerMock = new MultiTestClassRunnerMock);
         _testRunResult.reset(testRunResultMock = new TestRunResultMock);
         _console.reset(consoleMock = new ConsoleMock);
         _testRunStopwatch.reset(testRunStopwatchMock = new StopwatchMock);
      }
   } _testRunnerSelfMockedA;

   class TestRunnerSelfMockedB : public Zen::Mock<TestRunner>
   {
   public:
      ZENMOCK_NONVOID2_CONST(bool, WaitForEnterKeyIfPauseModeAndHaveNotPaused, bool, bool)
      ZENMOCK_VOID0(RunTestClasses)
      ZENMOCK_VOID1(RunTestClassesWithWaitableRunnerThread, unsigned)
      PreamblePrinterMock* preamblePrinterMock;
      MultiTestClassRunnerMock* multiTestClassRunnerMock;
      TestRunResultMock* testRunResultMock;
      StopwatchMock* testRunStopwatchMock;
      TestRunnerSelfMockedB()
      {
         _preamblePrinter.reset(preamblePrinterMock = new PreamblePrinterMock);
         _multiTestClassRunner.reset(multiTestClassRunnerMock = new MultiTestClassRunnerMock);
         _testRunResult.reset(testRunResultMock = new TestRunResultMock);
         _testRunStopwatch.reset(testRunStopwatchMock = new StopwatchMock);
      }
   } _testRunnerSelfMockedB;

   STARTUP
   {
      _testRunner._console.reset(_consoleMock = new ConsoleMock);
      _testRunner._testRunResult.reset(_testRunResultMock = new TestRunResultMock);
      //_testRunner._futurist.reset(_futuristMock = new FuturistMock<TestRunner>);
      _testRunner._multiTestClassRunner.reset(_multiTestClassRunnerMock = new MultiTestClassRunnerMock);
   }

   TEST(Constructor_NewsComponents)
   {
      TestRunner testRunner;
      POINTER_WAS_NEWED(testRunner._console);
      POINTER_WAS_NEWED(testRunner._preamblePrinter);
      POINTER_WAS_NEWED(testRunner._argsParser);
      //POINTER_WAS_NEWED(testRunner._futurist);
      POINTER_WAS_NEWED(testRunner._multiTestClassRunner);
      POINTER_WAS_NEWED(testRunner._testRunResult);
      POINTER_WAS_NEWED(testRunner._testRunStopwatch);
      ARE_EQUAL(ZenUnitArgs(), testRunner._zenUnitArgs);
      IS_FALSE(testRunner._havePaused);
   }

   TEST(AddTestClassRunner_EmplacesBackTestClassRunner)
   {
      _multiTestClassRunnerMock->AddTestClassRunnerMock.Expect();
      SpecificTestClassRunner<TestingTestClass> testClassRunner("TestClassNamePossiblyTemplatized");
      //
      _testRunner.AddTestClassRunner(&testClassRunner);
      //
      ZEN(_multiTestClassRunnerMock->AddTestClassRunnerMock.AssertCalledOnceWith(&testClassRunner));
   }

   TEST4X4(ParseArgsRunTestClassesPrintResults_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1,
      int expectedOverallExitCode, unsigned testrunsArgs, int firstTestRunExitCode, int secondTestRunExitCode,
      0, 1, 0, NA<int>(),
      1, 2, 1, 0,
      1, 2, 0, 1,
      1, 2, 1, 1)
   {
      ZenUnitArgs parsedZenUnitArgs;
      parsedZenUnitArgs.runFilters = { ZenUnit::Random<RunFilter>(), ZenUnit::Random<RunFilter>() };
      parsedZenUnitArgs.wait = ZenUnit::Random<bool>();
      parsedZenUnitArgs.testruns = testrunsArgs;
      _testRunnerSelfMockedA.argsParserMock->ParseMock.ExpectAndReturn(parsedZenUnitArgs);

      _testRunnerSelfMockedA.multiTestClassRunnerMock->ApplyRunFiltersIfAnyMock.Expect();

      _testRunnerSelfMockedA.RunTestClassesAndPrintResultsMock.
         ExpectAndReturnValues(firstTestRunExitCode, secondTestRunExitCode);

      _testRunnerSelfMockedA.testRunResultMock->ResetStateExceptForSkipsMock.Expect();

      _testRunnerSelfMockedA.consoleMock->WaitForEnterKeyIfDebuggerPresentOrValueTrueMock.Expect();

      const vector<string> commandLineArgs{ Random<string>() };
      //
      const int overallExitCode = _testRunnerSelfMockedA.ParseArgsRunTestClassesPrintResults(commandLineArgs);
      //
      ZEN(_testRunnerSelfMockedA.argsParserMock->ParseMock.AssertCalledOnceWith(commandLineArgs));
      ZEN(_testRunnerSelfMockedA.multiTestClassRunnerMock->
         ApplyRunFiltersIfAnyMock.AssertCalledOnceWith(parsedZenUnitArgs.runFilters));
      ZEN(_testRunnerSelfMockedA.RunTestClassesAndPrintResultsMock.AssertCalledNTimesWith(testrunsArgs, parsedZenUnitArgs));
      ZEN(_testRunnerSelfMockedA.testRunResultMock->ResetStateExceptForSkipsMock.AssertCalledNTimes(testrunsArgs));
      ZEN(_testRunnerSelfMockedA.consoleMock->
         WaitForEnterKeyIfDebuggerPresentOrValueTrueMock.AssertCalledOnceWith(parsedZenUnitArgs.wait));
      ARE_EQUAL(expectedOverallExitCode, overallExitCode);
   }

   // TEST3X3(RunTestClassesAndPrintResults_RunsTestsAndPrintsResults_Returns0IfAllTestsPassedOtherwiseReturns1,
   //    unsigned maxtotalseconds,
   //    bool expectRunTestClassesWithWaitableRunnerThread,
   //    int determineExitCodeReturnValueAndExpectedExitCode,
   //    0u, false, 0,
   //    0u, false, 1,
   //    1u, true, 0,
   //    1u, true, 1,
   //    2u, true, 0,
   //    2u, true, 1)
   // {
   //    bool waitForEnterKeyIfPauseModeReturnValue = ZenUnit::Random<bool>();
   //    _testRunnerSelfMockedB.WaitForEnterKeyIfPauseModeAndHaveNotPausedMock.ExpectAndReturn(waitForEnterKeyIfPauseModeReturnValue);
   //    bool havePausedInitialValue = ZenUnit::Random<bool>();
   //    _testRunnerSelfMockedB._havePaused = havePausedInitialValue;

   //    _testRunnerSelfMockedB.testRunStopwatchMock->StartMock.Expect();

   //    ZenUnitArgs zenUnitArgs;
   //    zenUnitArgs.commandLine = Random<string>();
   //    zenUnitArgs.maxtotalseconds = maxtotalseconds;
   //    _testRunnerSelfMockedB.preamblePrinterMock->PrintOpeningThreeLinesMock.Expect();
   //    if (expectRunTestClassesWithWaitableRunnerThread)
   //    {
   //       _testRunnerSelfMockedB.RunTestClassesWithWaitableRunnerThreadMock.Expect();
   //    }
   //    else
   //    {
   //       _testRunnerSelfMockedB.RunTestClassesMock.Expect();
   //    }
   //    _testRunnerSelfMockedB.testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
   //    _testRunnerSelfMockedB.testRunResultMock->PrintClosingLinesMock.Expect();

   //    const size_t TotalNumberOfTestCases = Random<size_t>();
   //    _testRunnerSelfMockedB.multiTestClassRunnerMock->NumberOfTestCasesMock.ExpectAndReturn(TotalNumberOfTestCases);

   //    const unsigned TestRunMilliseconds = Random<unsigned>();
   //    _testRunnerSelfMockedB.testRunStopwatchMock->StopMock.ExpectAndReturn(TestRunMilliseconds);

   //    _testRunnerSelfMockedB.testRunResultMock->
   //       DetermineExitCodeMock.ExpectAndReturn(determineExitCodeReturnValueAndExpectedExitCode);
   //    //
   //    const int exitCode = _testRunnerSelfMockedB.RunTestClassesAndPrintResults(zenUnitArgs);
   //    //
   //    ZEN(_testRunnerSelfMockedB.WaitForEnterKeyIfPauseModeAndHaveNotPausedMock.
   //       AssertCalledOnceWith(zenUnitArgs.pause, havePausedInitialValue));
   //    ARE_EQUAL(waitForEnterKeyIfPauseModeReturnValue, _testRunnerSelfMockedB._havePaused);
   //    ZEN(_testRunnerSelfMockedB.testRunStopwatchMock->StartMock.AssertCalledOnce());
   //    ZEN(_testRunnerSelfMockedB.preamblePrinterMock->PrintOpeningThreeLinesMock.AssertCalledOnceWith(
   //       zenUnitArgs, _testRunnerSelfMockedB._multiTestClassRunner.get()));
   //    if (expectRunTestClassesWithWaitableRunnerThread)
   //    {
   //       ZEN(_testRunnerSelfMockedB.RunTestClassesWithWaitableRunnerThreadMock.
   //          AssertCalledOnceWith(zenUnitArgs.maxtotalseconds));
   //    }
   //    else
   //    {
   //       ZEN(_testRunnerSelfMockedB.RunTestClassesMock.AssertCalledOnce());
   //    }
   //    ZEN(_testRunnerSelfMockedB.testRunResultMock->PrintTestFailuresAndSkipsMock.AssertCalledOnce());
   //    ZEN(_testRunnerSelfMockedB.multiTestClassRunnerMock->NumberOfTestCasesMock.AssertCalledOnce());
   //    ZEN(_testRunnerSelfMockedB.testRunStopwatchMock->StopMock.AssertCalledOnce());
   //    ZEN(_testRunnerSelfMockedB.testRunResultMock->PrintClosingLinesMock.AssertCalledOnceWith(
   //       TotalNumberOfTestCases, TestRunMilliseconds, zenUnitArgs));
   //    ZEN(_testRunnerSelfMockedB.testRunResultMock->DetermineExitCodeMock.AssertCalledOnceWith(zenUnitArgs));
   //    ARE_EQUAL(determineExitCodeReturnValueAndExpectedExitCode, exitCode);
   // }

   TEST(WaitForEnterKeyIfPauseMode_PauseModeFalse_DoesNothing_ReturnsFalse)
   {
      bool newValueForHavePaused = _testRunner.
         WaitForEnterKeyIfPauseModeAndHaveNotPaused(false, ZenUnit::Random<bool>());
      IS_FALSE(newValueForHavePaused);
   }

   TEST(WaitForEnterKeyIfPauseMode_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
   {
      bool newValueForHavePaused = _testRunner.
         WaitForEnterKeyIfPauseModeAndHaveNotPaused(true, true);
      IS_TRUE(newValueForHavePaused);
   }

   TEST(WaitForEnterKeyIfPauseMode_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForEnterKey_ReturnsTrue)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WaitForEnterKeyMock.Expect();
      //
      bool newValueForHavePaused = _testRunner.
         WaitForEnterKeyIfPauseModeAndHaveNotPaused(true, false);
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit test runner paused. Press Enter to run tests."));
      ZEN(_consoleMock->WaitForEnterKeyMock.AssertCalledOnce());
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
         AssertCalledOnceWith(TestClassName.c_str(), TestName.c_str(), Reason.c_str()));
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
         AssertCalledOnceWith(SkippedTestClassName.c_str(), Reason.c_str()));
   }

   TEST(RunTestClasses_RunsTestClasses)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      _testRunner._zenUnitArgs = zenUnitArgs;

      vector<TestClassResult> testClassResults(1);
      _multiTestClassRunnerMock->RunTestClassesMock.ExpectAndReturn(testClassResults);
      _testRunResultMock->SetTestClassResultsMock.Expect();
      //
      _testRunner.RunTestClasses();
      //
      ZEN(_multiTestClassRunnerMock->RunTestClassesMock.AssertCalledOnceWith(_testRunner._zenUnitArgs));
      ZEN(_testRunResultMock->SetTestClassResultsMock.AssertCalledOnceWith(testClassResults));
   }

   // TEST2X2(RunTestClassesWithWaitableRunnerThread_SpawnsThreadToCallRunTestClasses_PrintsResultsAndExits1IfThreadTimesOut,
   //    future_status runnerThreadWaitResult, bool expectTimeoutHandling,
   //    future_status::ready, false,
   //    future_status::timeout, true)
   // {
   //    const shared_ptr<VoidFutureMock> testClassRunnerDoneFutureMock(new VoidFutureMock);
   //    testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.ExpectAndReturn(runnerThreadWaitResult);
   //    _futuristMock->AsyncMock.ExpectAndReturn(testClassRunnerDoneFutureMock);
   //    if (expectTimeoutHandling)
   //    {
   //       _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
   //       _consoleMock->WriteLineAndExitMock.Expect();
   //    }
   //    const unsigned MaxTotalSeconds = Random<unsigned>();
   //    //
   //    _testRunner.RunTestClassesWithWaitableRunnerThread(MaxTotalSeconds);
   //    //
   //    ZEN(_futuristMock->AsyncMock.AssertCalledOnceWith(&TestRunner::RunTestClasses, &_testRunner));
   //    ZEN(testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.AssertCalledOnceWith(MaxTotalSeconds));
   //    if (expectTimeoutHandling)
   //    {
   //       ZEN(_testRunResultMock->PrintTestFailuresAndSkipsMock.AssertCalledOnce());
   //       ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(
   //          "[ZenUnit] Total run time exceeded maximum run time of " + to_string(MaxTotalSeconds) + " seconds.", 1));
   //    }
   // }

   }; RUNTESTS(TestRunnerTests)
}

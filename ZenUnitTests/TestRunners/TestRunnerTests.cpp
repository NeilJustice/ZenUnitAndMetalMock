#include "pch.h"
#include "ZenUnitTests/Args/Mock/ArgsParserMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestRunResultMock.h"
#include "ZenUnitTests/TestRunners/Mock/PreamblePrinterMock.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassMultiRunnerMock.h"
#include "ZenUnitTests/Utils/Concurrency/Mock/FuturistMock.h"
#include "ZenUnitTests/Utils/Concurrency/Mock/VoidFutureMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"

namespace ZenUnit
{
   TESTS(TestRunnerTests)
   SPEC(Constructor_NewsComponents)
   SPEC(RegisterTestClassRunner_EmplacesBackTestClassRunner)
   SPEC(SkipTest_CallsTestRunResultAddSkippedFullTestName)
   SPEC(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
   SPECX(ParseArgsRunTestsPrintResults_ParsesArgs_RunsTests_PrintsResults_Returns0IfAllTestsPassedOrExit0_OtherwiseReturns1)
   SPEC(RunTests_RunsTestClasses)
   SPECX(RunTestsWithWaitableRunnerThread_SpawnsThreadToCallRunTests_PrintsResultsAndExits1IfThreadTimesOut)
   SPECEND

   TestRunner _testRunner;
   ConsoleMock* _consoleMock;
   PreamblePrinterMock* _preamblePrinterMock;
   FuturistMock<TestRunner>* _futuristMock;
   TestClassMultiRunnerMock* _multiTestClassRunnerMock;
   TestRunResultMock* _testRunResultMock;

   class TestingTestClass
   {
   public:
      static vector<unique_ptr<Test>> GetTests(const char*) { return {}; }
   };

   class TestRunnerRunTestsMocked : public Zen::Mock<TestRunner>
   {
   public:
      ArgsParserMock* argsParserMock;
      PreamblePrinterMock* preamblePrinterMock;
      TestClassMultiRunnerMock* multiTestClassRunnerMock;
      TestRunResultMock* testRunResultMock;
      ConsoleMock* consoleMock;
      StopwatchMock* testRunStopwatchMock;

      TestRunnerRunTestsMocked()
      {
         _argsParser.reset(argsParserMock = new ArgsParserMock);
         _preamblePrinter.reset(preamblePrinterMock = new PreamblePrinterMock);
         _multiTestClassRunner.reset(multiTestClassRunnerMock = new TestClassMultiRunnerMock);
         _testRunResult.reset(testRunResultMock = new TestRunResultMock);
         _console.reset(consoleMock = new ConsoleMock);
         _testRunStopwatch.reset(testRunStopwatchMock = new StopwatchMock);
      }

      ZENMOCK_VOID0(RunTests)
      ZENMOCK_VOID1(RunTestsWithWaitableRunnerThread, unsigned)
   } _testRunnerRunTestsMocked;

   STARTUP
   {
      _testRunner._console.reset(_consoleMock = new ConsoleMock);
      _testRunner._testRunResult.reset(_testRunResultMock = new TestRunResultMock);
      _testRunner._futurist.reset(_futuristMock = new FuturistMock<TestRunner>);
      _testRunner._multiTestClassRunner.reset(_multiTestClassRunnerMock = new TestClassMultiRunnerMock);
   }

   TEST(Constructor_NewsComponents)
   {
      TestRunner testRunner;
      WAS_NEWED(testRunner._console);
      WAS_NEWED(testRunner._preamblePrinter);
      WAS_NEWED(testRunner._argsParser);
      WAS_NEWED(testRunner._futurist);
      WAS_NEWED(testRunner._multiTestClassRunner);
      WAS_NEWED(testRunner._testRunResult);
      WAS_NEWED(testRunner._testRunStopwatch);
      ARE_EQUAL(ZenUnitArgs(), testRunner._args);
   }

   TEST(RegisterTestClassRunner_EmplacesBackTestClassRunner)
   {
      _multiTestClassRunnerMock->AddTestClassRunnerMock.Expect();
      SpecificTestClassRunner<TestingTestClass> testClassRunner("TestClassNamePossiblyTemplatized");
      //
      _testRunner.RegisterTestClassRunner(&testClassRunner);
      //
      ZEN(_multiTestClassRunnerMock->AddTestClassRunnerMock.AssertCalledOnceWith(&testClassRunner));
   }

   TEST4X4(ParseArgsRunTestsPrintResults_ParsesArgs_RunsTests_PrintsResults_Returns0IfAllTestsPassedOrExit0_OtherwiseReturns1,
      unsigned maxtotalseconds, bool expectBackgroundThread, int determineExitCodeReturnValue, int expectedExitCode,
      0U, false, 0, 0,
      0U, false, 1, 1,
      1U, true, 0, 0,
      1U, true, 1, 1,
      2U, true, 0, 0,
      2U, true, 1, 1)
   {
      _testRunnerRunTestsMocked.testRunStopwatchMock->StartMock.Expect();
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = "Folder//Tests -exit0";
      zenUnitArgs.maxtotalseconds = maxtotalseconds;
      _testRunnerRunTestsMocked.argsParserMock->ParseMock.ExpectAndReturn(zenUnitArgs);
      _testRunnerRunTestsMocked.preamblePrinterMock->PrintOpeningThreeLinesMock.Expect();
      if (expectBackgroundThread)
      {
         _testRunnerRunTestsMocked.RunTestsWithWaitableRunnerThreadMock.Expect();
      }
      else
      {
         _testRunnerRunTestsMocked.RunTestsMock.Expect();
      }
      _testRunnerRunTestsMocked.testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
      _testRunnerRunTestsMocked.testRunResultMock->PrintClosingLinesMock.Expect();
      _testRunnerRunTestsMocked.consoleMock->PauseForAnyKeyIfDebuggerIsPresentMock.Expect();

      const size_t TotalNumberOfTestCases = 10;
      _testRunnerRunTestsMocked.multiTestClassRunnerMock->TotalNumberOfTestCasesMock.
         ExpectAndReturn(TotalNumberOfTestCases);

      const unsigned TestRunMilliseconds = 20;
      _testRunnerRunTestsMocked.testRunStopwatchMock->StopMock.ExpectAndReturn(TestRunMilliseconds);

      _testRunnerRunTestsMocked.testRunResultMock->
         DetermineExitCodeMock.ExpectAndReturn(determineExitCodeReturnValue);

      _testRunnerRunTestsMocked._args.commandLine = "CommandLine";
      const vector<string> Args = { "NonEmpty" };
      //
      const int exitCode = _testRunnerRunTestsMocked.ParseArgsRunTestsPrintResults(Args);
      //
      ZEN(_testRunnerRunTestsMocked.testRunStopwatchMock->StartMock.AssertCalledOnce());
      ZEN(_testRunnerRunTestsMocked.argsParserMock->ParseMock.AssertCalledOnceWith(Args));
      ZEN(_testRunnerRunTestsMocked.preamblePrinterMock->
         PrintOpeningThreeLinesMock.AssertCalledOnceWith(
         _testRunnerRunTestsMocked._multiTestClassRunner.get(), zenUnitArgs.commandLine));
      if (expectBackgroundThread)
      {
         ZEN(_testRunnerRunTestsMocked.
            RunTestsWithWaitableRunnerThreadMock.AssertCalledOnceWith(zenUnitArgs.maxtotalseconds));
      }
      else
      {
         ZEN(_testRunnerRunTestsMocked.RunTestsMock.AssertCalledOnce());
      }
      ZEN(_testRunnerRunTestsMocked.testRunResultMock->PrintTestFailuresAndSkipsMock.AssertCalledOnce());
      ZEN(_testRunnerRunTestsMocked.multiTestClassRunnerMock->
         TotalNumberOfTestCasesMock.AssertCalledOnce());
      ZEN(_testRunnerRunTestsMocked.testRunStopwatchMock->StopMock.AssertCalledOnce());
      ZEN(_testRunnerRunTestsMocked.testRunResultMock->PrintClosingLinesMock.AssertCalledOnceWith(
         TotalNumberOfTestCases, TestRunMilliseconds, zenUnitArgs.commandLine));
      ZEN(_testRunnerRunTestsMocked.consoleMock->
         PauseForAnyKeyIfDebuggerIsPresentMock.AssertCalledOnce());
      ZEN(_testRunnerRunTestsMocked.testRunResultMock->
         DetermineExitCodeMock.AssertCalledOnceWith(zenUnitArgs));
      ARE_EQUAL(expectedExitCode, exitCode);
   }

   TEST(SkipTest_CallsTestRunResultAddSkippedFullTestName)
   {
      _testRunResultMock->AddSkippedTestMock.Expect();
      const char* const TestClassName = "TestClassName";
      const char* const TestName = "TestName";
      const char* const Reason = "Reason";
      //
      _testRunner.SkipTest(TestClassName, TestName, Reason);
      //
      ZEN(_testRunResultMock->AddSkippedTestMock.
         AssertCalledOnceWith(TestClassName, TestName, Reason));
   }

   TEST(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
   {
      _testRunResultMock->AddSkippedTestClassNameAndReasonMock.Expect();
      const char* const SkippedTestClassName = "SkippedTestClassName";
      const char* const Reason = "Reason";
      //
      _testRunner.SkipTestClass(SkippedTestClassName, Reason);
      //
      ZEN(_testRunResultMock->AddSkippedTestClassNameAndReasonMock.
         AssertCalledOnceWith(SkippedTestClassName, Reason));
   }

   TEST(RunTests_RunsTestClasses)
   {
      ZenUnitArgs args;
      args.commandLine = "commandLine";
      _testRunner._args = args;

      vector<TestClassResult> testClassResults(1);
      _multiTestClassRunnerMock->RunTestClassesMock.ExpectAndReturn(testClassResults);
      _testRunResultMock->SetTestClassResultsMock.Expect();
      //
      _testRunner.RunTests();
      //
      ZEN(_multiTestClassRunnerMock->RunTestClassesMock.AssertCalledOnce());
      ZEN(_testRunResultMock->SetTestClassResultsMock.AssertCalledOnceWith(testClassResults));
   }

   TEST2X2(RunTestsWithWaitableRunnerThread_SpawnsThreadToCallRunTests_PrintsResultsAndExits1IfThreadTimesOut,
      future_status runnerThreadWaitResult, bool expectTimeoutHandling,
      future_status::ready, false,
      future_status::timeout, true)
   {
      const shared_ptr<VoidFutureMock> testClassRunnerDoneFutureMock(new VoidFutureMock);
      testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.ExpectAndReturn(runnerThreadWaitResult);
      _futuristMock->AsyncMock.ExpectAndReturn(testClassRunnerDoneFutureMock);
      if (expectTimeoutHandling)
      {
         _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
         _consoleMock->WriteLineAndExitMock.Expect();
      }
      const unsigned MaxTotalSeconds = 2;
      //
      _testRunner.RunTestsWithWaitableRunnerThread(MaxTotalSeconds);
      //
      ZEN(_futuristMock->AsyncMock.AssertCalledOnceWith(&TestRunner::RunTests, &_testRunner));
      ZEN(testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.AssertCalledOnceWith(MaxTotalSeconds));
      if (expectTimeoutHandling)
      {
         ZEN(_testRunResultMock->PrintTestFailuresAndSkipsMock.AssertCalledOnce());
         ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(
            "[ZenUnit] Total run time exceeded maximum of " +
            to_string(MaxTotalSeconds) + " seconds.", 1));
      }
   }

   }; RUN(TestRunnerTests)
}

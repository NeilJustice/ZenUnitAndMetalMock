#include "pch.h"
#include "ZenUnit/Utils/Random.h"
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
   SPECX(ParseArgsRunTestsPrintResults_ParsesArgs_RunsTestsTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1)
   SPECX(RunTestsAndPrintResults_RunsTestsAndPrintsResults_Returns0IfAllTestsPassedOtherwiseReturns1)
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

   class TestRunnerSelfMocked : public Zen::Mock<TestRunner>
   {
   public:
      ZENMOCK_NONVOID0(int, RunTestsAndPrintResults)
      ArgsParserMock* argsParserMock;
      PreamblePrinterMock* preamblePrinterMock;
      TestClassMultiRunnerMock* multiTestClassRunnerMock;
      TestRunResultMock* testRunResultMock;
      ConsoleMock* consoleMock;
      StopwatchMock* testRunStopwatchMock;
      TestRunnerSelfMocked()
      {
         _argsParser.reset(argsParserMock = new ArgsParserMock);
         _preamblePrinter.reset(preamblePrinterMock = new PreamblePrinterMock);
         _multiTestClassRunner.reset(multiTestClassRunnerMock = new TestClassMultiRunnerMock);
         _testRunResult.reset(testRunResultMock = new TestRunResultMock);
         _console.reset(consoleMock = new ConsoleMock);
         _testRunStopwatch.reset(testRunStopwatchMock = new StopwatchMock);
      }
   } _testRunnerSelfMocked;

   class TestRunnerSelfMocked2 : public Zen::Mock<TestRunner>
   {
   public:
      ZENMOCK_VOID0(RunTests)
      ZENMOCK_VOID1(RunTestsWithWaitableRunnerThread, unsigned)
      PreamblePrinterMock* preamblePrinterMock;
      TestClassMultiRunnerMock* multiTestClassRunnerMock;
      TestRunResultMock* testRunResultMock;
      StopwatchMock* testRunStopwatchMock;
      TestRunnerSelfMocked2()
      {
         _preamblePrinter.reset(preamblePrinterMock = new PreamblePrinterMock);
         _multiTestClassRunner.reset(multiTestClassRunnerMock = new TestClassMultiRunnerMock);
         _testRunResult.reset(testRunResultMock = new TestRunResultMock);
         _testRunStopwatch.reset(testRunStopwatchMock = new StopwatchMock);
      }
   } _testRunnerSelfMocked2;

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
      POINTER_WAS_NEWED(testRunner._console);
      POINTER_WAS_NEWED(testRunner._preamblePrinter);
      POINTER_WAS_NEWED(testRunner._argsParser);
      POINTER_WAS_NEWED(testRunner._futurist);
      POINTER_WAS_NEWED(testRunner._multiTestClassRunner);
      POINTER_WAS_NEWED(testRunner._testRunResult);
      POINTER_WAS_NEWED(testRunner._testRunStopwatch);
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

   TEST4X4(ParseArgsRunTestsPrintResults_ParsesArgs_RunsTestsTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1,
      int expectedOverallExitCode, unsigned testrunsArgs, int firstTestRunExitCode, int secondTestRunExitCode,
      0, 1, 0, NA<int>(),
      1, 2, 1, 0,
      1, 2, 0, 1,
      1, 2, 1, 1)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.testruns = testrunsArgs;
      _testRunnerSelfMocked.argsParserMock->ParseMock.ExpectAndReturn(zenUnitArgs);
      _testRunnerSelfMocked.RunTestsAndPrintResultsMock.ExpectAndReturnValues(firstTestRunExitCode, secondTestRunExitCode);
      _testRunnerSelfMocked.testRunResultMock->ResetStateExceptForSkipsMock.Expect();
      _testRunnerSelfMocked.consoleMock->PauseForAnyKeyIfDebuggerIsPresentMock.Expect();
      const vector<string> CommandLineArgs{ Random<string>() };
      //
      const int overallExitCode = _testRunnerSelfMocked.ParseArgsRunTestsPrintResults(CommandLineArgs);
      //
      ZEN(_testRunnerSelfMocked.argsParserMock->ParseMock.AssertCalledOnceWith(CommandLineArgs));
      ZEN(_testRunnerSelfMocked.RunTestsAndPrintResultsMock.AssertCalledNTimes(testrunsArgs));
      ZEN(_testRunnerSelfMocked.testRunResultMock->ResetStateExceptForSkipsMock.AssertCalledNTimes(testrunsArgs));
      ZEN(_testRunnerSelfMocked.consoleMock->PauseForAnyKeyIfDebuggerIsPresentMock.AssertCalledOnce());
      ARE_EQUAL(expectedOverallExitCode, overallExitCode);
   }

   TEST3X3(RunTestsAndPrintResults_RunsTestsAndPrintsResults_Returns0IfAllTestsPassedOtherwiseReturns1,
      unsigned maxtotalseconds, bool expectRunTestsWithWaitableRunnerThread, int determineExitCodeReturnValueAndExpectedExitCode,
      0u, false, 0,
      0u, false, 1,
      1u, true, 0,
      1u, true, 1,
      2u, true, 0,
      2u, true, 1)
   {
      _testRunnerSelfMocked2.testRunStopwatchMock->StartMock.Expect();
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.commandLine = Random<string>();
      zenUnitArgs.maxtotalseconds = maxtotalseconds;
      _testRunnerSelfMocked2._args = zenUnitArgs;
      _testRunnerSelfMocked2.preamblePrinterMock->PrintOpeningThreeLinesMock.Expect();
      if (expectRunTestsWithWaitableRunnerThread)
      {
         _testRunnerSelfMocked2.RunTestsWithWaitableRunnerThreadMock.Expect();
      }
      else
      {
         _testRunnerSelfMocked2.RunTestsMock.Expect();
      }
      _testRunnerSelfMocked2.testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
      _testRunnerSelfMocked2.testRunResultMock->PrintClosingLinesMock.Expect();

      const size_t TotalNumberOfTestCases = Random<size_t>();
      _testRunnerSelfMocked2.multiTestClassRunnerMock->NumberOfTestCasesMock.ExpectAndReturn(TotalNumberOfTestCases);

      const unsigned TestRunMilliseconds = Random<unsigned>();
      _testRunnerSelfMocked2.testRunStopwatchMock->StopMock.ExpectAndReturn(TestRunMilliseconds);

      _testRunnerSelfMocked2.testRunResultMock->
         DetermineExitCodeMock.ExpectAndReturn(determineExitCodeReturnValueAndExpectedExitCode);
      //
      const int exitCode = _testRunnerSelfMocked2.RunTestsAndPrintResults();
      //
      ZEN(_testRunnerSelfMocked2.testRunStopwatchMock->StartMock.AssertCalledOnce());
      ZEN(_testRunnerSelfMocked2.preamblePrinterMock->PrintOpeningThreeLinesMock.AssertCalledOnceWith(
         _testRunnerSelfMocked2._args.commandLine, _testRunnerSelfMocked2._multiTestClassRunner.get()));
      if (expectRunTestsWithWaitableRunnerThread)
      {
         ZEN(_testRunnerSelfMocked2.RunTestsWithWaitableRunnerThreadMock.
            AssertCalledOnceWith(zenUnitArgs.maxtotalseconds));
      }
      else
      {
         ZEN(_testRunnerSelfMocked2.RunTestsMock.AssertCalledOnce());
      }
      ZEN(_testRunnerSelfMocked2.testRunResultMock->PrintTestFailuresAndSkipsMock.AssertCalledOnce());
      ZEN(_testRunnerSelfMocked2.multiTestClassRunnerMock->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(_testRunnerSelfMocked2.testRunStopwatchMock->StopMock.AssertCalledOnce());
      ZEN(_testRunnerSelfMocked2.testRunResultMock->PrintClosingLinesMock.AssertCalledOnceWith(
         TotalNumberOfTestCases, TestRunMilliseconds, _testRunnerSelfMocked2._args.commandLine));
      ZEN(_testRunnerSelfMocked2.testRunResultMock->DetermineExitCodeMock.AssertCalledOnceWith(zenUnitArgs));
      ARE_EQUAL(determineExitCodeReturnValueAndExpectedExitCode, exitCode);
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

   TEST(RunTests_RunsTestClasses)
   {
      ZenUnitArgs args;
      args.commandLine = Random<string>();
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
      const unsigned MaxTotalSeconds = Random<unsigned>();
      //
      _testRunner.RunTestsWithWaitableRunnerThread(MaxTotalSeconds);
      //
      ZEN(_futuristMock->AsyncMock.AssertCalledOnceWith(&TestRunner::RunTests, &_testRunner));
      ZEN(testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.AssertCalledOnceWith(MaxTotalSeconds));
      if (expectTimeoutHandling)
      {
         ZEN(_testRunResultMock->PrintTestFailuresAndSkipsMock.AssertCalledOnce());
         ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(
            "[ZenUnit] Total run time exceeded maximum run time of " + to_string(MaxTotalSeconds) + " seconds.", 1));
      }
   }

   }; RUN(TestRunnerTests)
}

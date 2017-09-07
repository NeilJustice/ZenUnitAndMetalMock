#include "pch.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Results/TestRunResult.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "ZenUnit/TestRunners/PreamblePrinter.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Utils/AssertTrue.h"
#include "ZenUnit/Utils/Concurrency/Futurist.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Time/Stopwatch.h"

namespace ZenUnit
{
   TestRunner::TestRunner()
      : _console(new Console)
      , _preamblePrinter(new PreamblePrinter)
      , _argsParser(new ArgsParser)
      , _futurist(new Futurist<TestRunner>)
      , _testRunStopwatch(new Stopwatch)
      , _multiTestClassRunner(new MultiTestClassRunner)
      , _testRunResult(new TestRunResult)
   {
   }

   TestRunner::~TestRunner() = default;

   TestRunner& TestRunner::Instance()
   {
      static TestRunner testRunner;
      return testRunner;
   }

   const ZenUnitArgs& TestRunner::GetArgs()
   {
      const TestRunner& testRunner = Instance();
      return testRunner._zenUnitArgs;
   }

   std::nullptr_t TestRunner::RegisterTestClassRunner(TestClassRunner* testClassRunner)
   {
      _multiTestClassRunner->AddTestClassRunner(testClassRunner);
      return nullptr;
   }

   std::nullptr_t TestRunner::SkipTest(const char* testClassName, const char* testName, const char* reason)
   {
      _testRunResult->AddSkippedTest(testClassName, testName, reason);
      return nullptr;
   }

   std::nullptr_t TestRunner::SkipTestClass(const char* skippedTestClassName, const char* reason)
   {
      _testRunResult->AddSkippedTestClassNameAndReason(skippedTestClassName, reason);
      return nullptr;
   }

   int TestRunner::ParseArgsRunTestsPrintResults(const vector<string>& commandLineArgs)
   {
      _zenUnitArgs = _argsParser->Parse(commandLineArgs);
      int overallExitCode = 0;
      for (unsigned testRunIndex = 0; testRunIndex < _zenUnitArgs.testruns; ++testRunIndex)
      {
         const int testRunExitCode = RunTestsAndPrintResults();
         assert_true(testRunExitCode == 0 || testRunExitCode == 1);
         overallExitCode |= testRunExitCode;
         _testRunResult->ResetStateExceptForSkips();
      }
      _console->PauseForAnyKeyIfDebuggerIsPresent();
      return overallExitCode;
   }

   int TestRunner::RunTestsAndPrintResults()
   {
      _testRunStopwatch->Start();
      _preamblePrinter->PrintOpeningThreeLines(_zenUnitArgs, _multiTestClassRunner.get());
      if (_zenUnitArgs.maxtotalseconds > 0)
      {
         RunTestsWithWaitableRunnerThread(_zenUnitArgs.maxtotalseconds);
      }
      else
      {
         RunTests();
      }
      _testRunResult->PrintTestFailuresAndSkips();
      const size_t numberOfTestCases = _multiTestClassRunner->NumberOfTestCases();
      const unsigned testRunMilliseconds = _testRunStopwatch->Stop();
      _testRunResult->PrintClosingLines(numberOfTestCases, testRunMilliseconds, _zenUnitArgs);
      const int testRunExitCode = _testRunResult->DetermineExitCode(_zenUnitArgs);
      return testRunExitCode;
   }

   void TestRunner::RunTestsWithWaitableRunnerThread(unsigned maxtTotalSeconds)
   {
      const shared_ptr<const VoidFuture> testClassRunnerDoneFuture = _futurist->Async(&TestRunner::RunTests, this);
      const future_status waitResult = testClassRunnerDoneFuture->WaitAtMostSeconds(maxtTotalSeconds);
      if (waitResult == future_status::timeout)
      {
         _testRunResult->PrintTestFailuresAndSkips();
         _console->WriteLineAndExit(String::Concat(
            "[ZenUnit] Total run time exceeded maximum run time of ", maxtTotalSeconds, " seconds."), 1);
      }
   }

   void TestRunner::RunTests()
   {
      vector<TestClassResult> testClassResults = _multiTestClassRunner->RunTestClasses(_zenUnitArgs);
      _testRunResult->SetTestClassResults(std::move(testClassResults));
   }
}

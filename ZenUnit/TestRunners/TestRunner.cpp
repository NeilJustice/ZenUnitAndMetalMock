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
      , _havePaused(false)
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

   int TestRunner::ParseArgsRunTestClassesPrintResults(const std::vector<std::string>& commandLineArgs)
   {
      _zenUnitArgs = _argsParser->Parse(commandLineArgs);
      int overallExitCode = 0;
      for (unsigned testRunIndex = 0; testRunIndex < _zenUnitArgs.testruns; ++testRunIndex)
      {
         const int testRunExitCode = RunTestClassesAndPrintResults();
         assert_true(testRunExitCode == 0 || testRunExitCode == 1);
         overallExitCode |= testRunExitCode;
         _testRunResult->ResetStateExceptForSkips();
      }
      _console->WaitForAnyKeyIfDebuggerPresentOrValueTrue(_zenUnitArgs.wait);
      return overallExitCode;
   }

   int TestRunner::RunTestClassesAndPrintResults()
   {
      _preamblePrinter->PrintOpeningThreeLines(_zenUnitArgs, _multiTestClassRunner.get());
      _havePaused = WaitForAnyKeyIfPauseModeAndHaveNotPaused(_zenUnitArgs.pause, _havePaused);
      _testRunStopwatch->Start();
      //_zenUnitArgs.randomseed = _randomSeedGenerator->GenerateRandomSeed();
      if (_zenUnitArgs.maxtotalseconds > 0)
      {
         RunTestClassesWithWaitableRunnerThread(_zenUnitArgs.maxtotalseconds);
      }
      else
      {
         RunTestClasses();
      }
      _testRunResult->PrintTestFailuresAndSkips();
      const size_t numberOfTestCases = _multiTestClassRunner->NumberOfTestCases();
      const unsigned testRunMilliseconds = _testRunStopwatch->Stop();
      _testRunResult->PrintClosingLines(numberOfTestCases, testRunMilliseconds, _zenUnitArgs);
      const int testRunExitCode = _testRunResult->DetermineExitCode(_zenUnitArgs);
      return testRunExitCode;
   }

   bool TestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPaused(bool pauseMode, bool havePaused) const
   {
      if (!pauseMode)
      {
         return false;
      }
      if (havePaused)
      {
         return true;
      }
      _console->WriteLine("ZenUnit test runner paused. Press any key to run.");
      _console->WaitForAnyKey();
      return true;
   }

   void TestRunner::RunTestClassesWithWaitableRunnerThread(unsigned maxtTotalSeconds)
   {
      const std::shared_ptr<const VoidFuture> testClassRunnerDoneFuture = _futurist->Async(&TestRunner::RunTestClasses, this);
      const std::future_status waitResult = testClassRunnerDoneFuture->WaitAtMostSeconds(maxtTotalSeconds);
      if (waitResult == std::future_status::timeout)
      {
         _testRunResult->PrintTestFailuresAndSkips();
         _console->WriteLineAndExit(String::Concat(
            "[ZenUnit] Total run time exceeded maximum run time of ", maxtTotalSeconds, " seconds."), 1);
      }
   }

   void TestRunner::RunTestClasses()
   {
      std::vector<TestClassResult> testClassResults = _multiTestClassRunner->RunTestClasses(_zenUnitArgs);
      _testRunResult->SetTestClassResults(std::move(testClassResults));
   }
}

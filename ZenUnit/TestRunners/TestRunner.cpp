#include "pch.h"
#include "TestRunner.h"
#include "Args/ArgsParser.h"
#include "Results/TestRunResult.h"
#include "TestRunners/PreamblePrinter.h"
#include "TestRunners/MultiTestClassRunner.h"
#include "Utils/Concurrency/Futurist.h"
#include "Utils/Time/Stopwatch.h"
#include "Console/Console.h"

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

   TestRunner::~TestRunner()
   {
   }

   TestRunner& TestRunner::Instance()
   {
      static TestRunner testRunner;
      return testRunner;
   }

   ZenUnitArgs TestRunner::GetArgs()
   {
      const TestRunner& testRunner = Instance();
      return testRunner._args;
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
      _testRunStopwatch->Start();
      _args = _argsParser->Parse(commandLineArgs);
      _preamblePrinter->PrintOpeningThreeLines(_multiTestClassRunner.get(), _args.commandLine);
      if (_args.maxtotalseconds > 0)
      {
         RunTestsWithWaitableRunnerThread(_args.maxtotalseconds);
      }
      else
      {
         RunTests();
      }
      _testRunResult->PrintTestFailuresAndSkips();
      const size_t totalNumberOfTestCases = _multiTestClassRunner->TotalNumberOfTestCases();
      const long long testRunMilliseconds = _testRunStopwatch->StopMilliseconds();
      _testRunResult->PrintClosingLines(totalNumberOfTestCases, testRunMilliseconds, _args.commandLine);
      _console->PauseForAnyKeyIfDebuggerIsPresent();
      const int exitCode = _testRunResult->DetermineExitCode(_args);
      return exitCode;
   }

   void TestRunner::RunTestsWithWaitableRunnerThread(unsigned maxtotalseconds)
   {
      const shared_ptr<const VoidFuture> testClassRunnerDoneFuture = _futurist->Async(&TestRunner::RunTests, this);
      const future_status waitResult = testClassRunnerDoneFuture->WaitAtMostSeconds(maxtotalseconds);
      if (waitResult == future_status::timeout)
      {
         _testRunResult->PrintTestFailuresAndSkips();
         _console->WriteLineAndExit(String::Concat(
            "[ZenUnit] Total run time exceeded maximum of ", maxtotalseconds, " seconds."), 151);
      }
   }

   void TestRunner::RunTests()
   {
      vector<TestClassResult> testClassResults = _multiTestClassRunner->RunTestClasses();
      _testRunResult->SetTestClassResults(testClassResults);
   }
}

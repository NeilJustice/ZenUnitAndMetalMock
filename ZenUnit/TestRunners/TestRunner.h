#pragma once
#include <memory>
#include "ZenUnit/Args/ZenUnitArgs.h"

namespace ZenUnit
{
   class Console;
   class PreamblePrinter;
   class ArgsParser;
   class TestClassRunner;
   class MultiTestClassRunner;
   class TestRunResult;
   class Stopwatch;
   template<typename> class TestClass;
   template<typename> class Futurist;

   class TestRunner
   {
      friend class TestRunnerTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const PreamblePrinter> _preamblePrinter;
      std::unique_ptr<const ArgsParser> _argsParser;
      std::unique_ptr<const Futurist<TestRunner>> _futurist;
      std::unique_ptr<Stopwatch> _testRunStopwatch;
      std::unique_ptr<MultiTestClassRunner> _multiTestClassRunner;
      std::unique_ptr<TestRunResult> _testRunResult;
      ZenUnitArgs _args;
   public:
      TestRunner();
      virtual ~TestRunner();
      static TestRunner& Instance();
      static ZenUnitArgs GetArgs();
      std::nullptr_t RegisterTestClassRunner(TestClassRunner* testClassRunner);
      std::nullptr_t SkipTest(const char* testClassName, const char* testName, const char* reason);
      std::nullptr_t SkipTestClass(const char* skippedTestClassName, const char* reason);
      int ParseArgsRunTestsPrintResults(const std::vector<std::string>& commandLineArgs);
   private:
      virtual void RunTests();
      virtual void RunTestsWithWaitableRunnerThread(unsigned maxtotalseconds);
   };
}

#include "pch.h"
#include "TestRunResult.h"
#include "Utils/Iteration/MemberForEacher.h"
#include "Console/Console.h"
#include "TestFailureNumberer.h"
#include "Args/ZenUnitArgs.h"
#include "Macros/VECTORS_EQUAL.h"

namespace ZenUnit
{
   TestRunResult::TestRunResult()
      : _console(new Console)
      , _memberForEacherTestClassResults(new MemberForEacherTestClassResultsType)
      , _memberForEacherSkippedTests(new MemberForEacherSkippedTestsType)
      , _testFailureNumberer(new TestFailureNumberer)
      , _numberOfFailedTestCases(0)
   {
   }

   TestRunResult::~TestRunResult()
   {
   }

   void TestRunResult::AddSkippedTest(
      const char* testClassName, const char* testName, const char* reason)
   {
      string fullTestNameAndReason = String::Concat(testClassName, ".", testName, " because: ", reason);
      _skippedFullTestNamesAndReasons.push_back(fullTestNameAndReason);
   }

   void TestRunResult::AddSkippedTestClassNameAndReason(
      const char* testClassName, const char* reason)
   {
      string testClassNameAndReason = String::Concat(testClassName, " because: ", reason);
      _skippedTestClassNamesAndReasons.push_back(testClassNameAndReason);
   }

   void TestRunResult::SetTestClassResults(vector<TestClassResult>& testClassResults)
   {
      _numberOfFailedTestCases = NumberOfFailedTestCases(testClassResults);
      _testClassResults = std::move(testClassResults);
   }

   size_t TestRunResult::NumberOfFailedTestCases(const vector<TestClassResult>& testClassResults) const
   {
      size_t numberOfFailedTestCases = std::accumulate(
         testClassResults.cbegin(), testClassResults.cend(), size_t(),
         [](size_t cumulativeNumberOfFailedTestCases, const TestClassResult& testClassResult)
      {
         return cumulativeNumberOfFailedTestCases + testClassResult.NumberOfFailedTestCases();
      });
      return numberOfFailedTestCases;
   }

   void TestRunResult::PrintTestFailuresAndSkips() const
   {
      if (_numberOfFailedTestCases > 0)
      {
         string numberOfTestFailuresLine = String::Concat(
            _numberOfFailedTestCases, " test ", _numberOfFailedTestCases == 1 ? "failure" : "failures", ":\n");
         _console->WriteLineColor(numberOfTestFailuresLine, Color::Red);
         _memberForEacherTestClassResults->ForEach(
            &_testClassResults, this, &TestRunResult::PrintTestClassResultFailures);
      }
      _memberForEacherSkippedTests->ForEach(
         &_skippedTestClassNamesAndReasons, this, &TestRunResult::PrintSkippedTestClassReminder);
      _memberForEacherSkippedTests->ForEach(
         &_skippedFullTestNamesAndReasons, this, &TestRunResult::PrintSkippedTestReminder);
   }

   void TestRunResult::PrintTestClassResultFailures(const TestClassResult& testClassResult) const
   {
      testClassResult.PrintTestFailures(_console.get(), _testFailureNumberer.get());
   }

   void TestRunResult::PrintClosingLines(
      size_t totalNumberOfTestCases,
      long long testRunMilliseconds,
      const string& comamndLine) const
   {
      assert_true(_numberOfFailedTestCases <= totalNumberOfTestCases);
      Color prefixColor = _numberOfFailedTestCases == 0 ? Color::Green : Color::Red;
      if (totalNumberOfTestCases == 0)
      {
         _console->WriteColor("[ZenUnit] ", Color::Green);
         _console->WriteLine("Zero test classes (TESTS or TEMPLATETESTS) are registered to run (RUN or RUNTEMPLATE).");
      }
      else
      {
         string testOrTests = totalNumberOfTestCases == 1 ? "test" : "tests";
         string millisecondOrMilliseconds = testRunMilliseconds == 1 ? "millisecond" : "milliseconds";
         string inMillisecondsPart = String::Concat("in ", testRunMilliseconds, ' ', millisecondOrMilliseconds);
         string closingLineBody;
         string prefixAsciiArt;
         if (_numberOfFailedTestCases == 0)
         {
            _console->WriteColor(" SUCCESS  ", prefixColor);
            closingLineBody = String::Concat(totalNumberOfTestCases,
            ' ', testOrTests, " passed ", inMillisecondsPart);
            prefixAsciiArt = "+===+===+ ";
         }
         else
         {
            _console->WriteColor(">>-FAIL-> ", prefixColor);
            closingLineBody = String::Concat(
               _numberOfFailedTestCases, '/', totalNumberOfTestCases,
               ' ', testOrTests, " failed ", inMillisecondsPart);
            prefixAsciiArt = ">>------> ";
         }
         _console->WriteLine(closingLineBody);
         _console->WriteColor(prefixAsciiArt, prefixColor);
         _console->WriteLine(comamndLine);
      }
   }

   int TestRunResult::DetermineExitCode(const ZenUnitArgs& args) const
   {
      if (args.exit0)
      {
         return 0;
      }
      bool haveSkippedTestsOrTestClasses =
         !_skippedFullTestNamesAndReasons.empty() ||
         !_skippedTestClassNamesAndReasons.empty();
      if (args.noskips && haveSkippedTestsOrTestClasses)
      {
         return 1;
      }
      int exitCode = _numberOfFailedTestCases > 0 ? 1 : 0;
      return exitCode;
   }

   void TestRunResult::PrintSkippedTestReminder(const string& skippedFullTestNameAndReason) const
   {
      _console->WriteLine(String::Concat("[Warning] Skipped test ", skippedFullTestNameAndReason));
   }

   void TestRunResult::PrintSkippedTestClassReminder(const string& skippedTestClassNameAndReason) const
   {
      _console->WriteLine(String::Concat("[Warning] Skipped test class ", skippedTestClassNameAndReason));
   }

   void TestRunResult::AssertEqual(
      const ZenUnit::TestRunResult& expectedTestRunResult,
      const ZenUnit::TestRunResult& actualTestRunResult)
   {
      VECTORS_EQUAL(expectedTestRunResult._testClassResults, actualTestRunResult._testClassResults);
      VECTORS_EQUAL(expectedTestRunResult._skippedTestClassNamesAndReasons, actualTestRunResult._skippedTestClassNamesAndReasons);
      VECTORS_EQUAL(expectedTestRunResult._skippedFullTestNamesAndReasons, actualTestRunResult._skippedFullTestNamesAndReasons);
   }
}

void ZenUnitEqualizer<ZenUnit::TestRunResult>::
AssertEqual(
   const ZenUnit::TestRunResult& expectedTestRunResult,
   const ZenUnit::TestRunResult& actualTestRunResult)
{
   ZenUnit::TestRunResult::AssertEqual(expectedTestRunResult, actualTestRunResult);
}

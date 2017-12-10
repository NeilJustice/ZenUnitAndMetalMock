#include "pch.h"
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/Results/TestClassResult.h"
#include "ZenUnit/Results/TestFailureNumberer.h"
#include "ZenUnit/Results/TestRunResult.h"
#include "ZenUnit/Utils/Iteration/MemberForEacher.h"

namespace ZenUnit
{
   INLINE TestRunResult::TestRunResult()
      : _console(std::make_unique<Console>())
      , _memberForEacherTestClassResults(std::make_unique<MemberForEacherTestClassResultsType>())
      , _memberForEacherSkippedTests(std::make_unique<MemberForEacherSkippedTestsType>())
      , _twoExtraArgsForEacher(std::make_unique<TwoExtraArgsForEacherType>())
      , _testFailureNumberer(std::make_unique<TestFailureNumberer>())
      , _numberOfFailedTestCases(0)
   {
   }

   INLINE TestRunResult::~TestRunResult() = default;

   INLINE void TestRunResult::AddSkippedTest(
      const char* testClassName, const char* testName, const char* reason)
   {
      const std::string fullTestNameAndReason = String::Concat(
         testClassName, ".", testName, " because: ", reason);
      _skippedFullTestNamesAndReasons.push_back(fullTestNameAndReason);
   }

   INLINE void TestRunResult::AddSkippedTestClassNameAndReason(
      const char* testClassName, const char* reason)
   {
      const std::string testClassNameAndReason = String::Concat(
         testClassName, " because: ", reason);
      _skippedTestClassNamesAndReasons.push_back(testClassNameAndReason);
   }

   INLINE void TestRunResult::SetTestClassResults(std::vector<TestClassResult>&& testClassResults)
   {
      _numberOfFailedTestCases = NumberOfFailedTestCases(testClassResults);
      _testClassResults = std::move(testClassResults);
   }

   INLINE size_t TestRunResult::NumberOfFailedTestCases(const std::vector<TestClassResult>& testClassResults) const
   {
      const size_t numberOfFailedTestCases = std::accumulate(
         testClassResults.cbegin(), testClassResults.cend(), size_t(),
         [](size_t cumulativeNumberOfFailedTestCases, const TestClassResult& testClassResult)
      {
         return cumulativeNumberOfFailedTestCases + testClassResult.NumberOfFailedTestCases();
      });
      return numberOfFailedTestCases;
   }

   INLINE void TestRunResult::PrintTestFailuresAndSkips() const
   {
      if (_numberOfFailedTestCases > 0)
      {
         const std::string numberOfTestFailuresLine = String::Concat(
            _numberOfFailedTestCases, " test failure", _numberOfFailedTestCases > 1 ? "s" : "", ":\n");
         _console->WriteLineColor(numberOfTestFailuresLine, Color::Red);
         _memberForEacherTestClassResults->MemberForEach(
            &_testClassResults, this, &TestRunResult::PrintTestClassResultFailures);
      }
      _memberForEacherSkippedTests->MemberForEach(
         &_skippedTestClassNamesAndReasons, this, &TestRunResult::PrintSkippedTestClassReminder);
      _memberForEacherSkippedTests->MemberForEach(
         &_skippedFullTestNamesAndReasons, this, &TestRunResult::PrintSkippedTestReminder);
   }

   INLINE void TestRunResult::PrintTestClassResultFailures(const TestClassResult& testClassResult) const
   {
      testClassResult.PrintTestFailures(
         _twoExtraArgsForEacher.get(), _console.get(), _testFailureNumberer.get());
   }

   INLINE void TestRunResult::PrintClosingLines(
      size_t totalNumberOfTestCases,
      unsigned testRunMilliseconds,
      const ZenUnitArgs& zenUnitArgs) const
   {
      assert_true(_numberOfFailedTestCases <= totalNumberOfTestCases);
      const Color prefixColor = _numberOfFailedTestCases == 0 ? Color::Green : Color::Red;
      if (totalNumberOfTestCases == 0)
      {
         _console->WriteColor("[ZenUnit] ", Color::Green);
         _console->WriteLine("Zero test classes run.");
      }
      else
      {
         const std::string testOrTests = totalNumberOfTestCases == 1 ? "test" : "tests";
         const std::string millisecondOrMilliseconds = testRunMilliseconds == 1 ? "millisecond" : "milliseconds";
         const std::string inMillisecondsPart = String::Concat("in ", testRunMilliseconds, ' ', millisecondOrMilliseconds);
         std::string closingLineBody;
         std::string prefixAsciiArt;
         if (_numberOfFailedTestCases == 0)
         {
            _console->WriteColor("[VICTORY] ", prefixColor);
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
         _console->Write(zenUnitArgs.commandLine);
         const std::string randomSeedWriteLine =
            (zenUnitArgs.random && !zenUnitArgs.randomseedsetbyuser) ?
            " (seed " + std::to_string(zenUnitArgs.randomseed) + ")" : "";
         _console->WriteLine(randomSeedWriteLine);
      }
   }

   INLINE int TestRunResult::DetermineExitCode(const ZenUnitArgs& args) const
   {
      if (args.exit0)
      {
         return 0;
      }
      const bool haveSkippedTestsOrTestClasses =
         !_skippedFullTestNamesAndReasons.empty() ||
         !_skippedTestClassNamesAndReasons.empty();
      if (args.failskips && haveSkippedTestsOrTestClasses)
      {
         return 1;
      }
      const int exitCode = _numberOfFailedTestCases > 0 ? 1 : 0;
      return exitCode;
   }

   INLINE void TestRunResult::PrintSkippedTestClassReminder(const std::string& skippedTestClassNameAndReason) const
   {
      _console->WriteLine("[SKIPPED] Test class " + skippedTestClassNameAndReason);
   }

   INLINE void TestRunResult::PrintSkippedTestReminder(const std::string& skippedFullTestNameAndReason) const
   {
      _console->WriteLine("[SKIPPED] Test " + skippedFullTestNameAndReason);
   }

   INLINE void TestRunResult::ResetStateExceptForSkips()
   {
      _testFailureNumberer->Reset();
      _testClassResults.clear();
      _numberOfFailedTestCases = 0;
   }

   INLINE void TestRunResult::AssertEqual(
      const ZenUnit::TestRunResult& expectedTestRunResult,
      const ZenUnit::TestRunResult& actualTestRunResult)
   {
      VECTORS_EQUAL(
         expectedTestRunResult._testClassResults,
         actualTestRunResult._testClassResults);
      VECTORS_EQUAL(
         expectedTestRunResult._skippedTestClassNamesAndReasons,
         actualTestRunResult._skippedTestClassNamesAndReasons);
      VECTORS_EQUAL(
         expectedTestRunResult._skippedFullTestNamesAndReasons,
         actualTestRunResult._skippedFullTestNamesAndReasons);
   }

   INLINE void Equalizer<ZenUnit::TestRunResult>::
   AssertEqual(
      const ZenUnit::TestRunResult& expectedTestRunResult,
      const ZenUnit::TestRunResult& actualTestRunResult)
   {
      ZenUnit::TestRunResult::AssertEqual(expectedTestRunResult, actualTestRunResult);
   }
}

#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/Results/TestClassResult.h"
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/Utils/Iteration/TwoExtraArgsForEacher.h"

namespace ZenUnit
{
   INLINE TestClassResult::TestClassResult()
   {
   }

   INLINE TestClassResult::TestClassResult(const TestClassResult& testClassResult)
   {
      *this = testClassResult;
   }

   INLINE TestClassResult& TestClassResult::operator=(const TestClassResult& testClassResult)
   {
      if (this != &testClassResult)
      {
         _testResults = testClassResult._testResults;
      }
      return *this;
   }

   INLINE TestClassResult::TestClassResult(TestClassResult&& testClassResult) noexcept
   {
      *this = std::move(testClassResult);
   }

   INLINE TestClassResult& TestClassResult::operator=(TestClassResult&& testClassResult) noexcept
   {
      _testResults = std::exchange(testClassResult._testResults, std::vector<TestResult>());
      return *this;
   }

   INLINE TestClassResult::~TestClassResult() = default;

   INLINE void TestClassResult::AddTestResults(const std::vector<TestResult>& testResults)
   {
      _testResults.insert(_testResults.end(), testResults.cbegin(), testResults.cend());
   }

   INLINE unsigned TestClassResult::Milliseconds() const
   {
      const unsigned milliseconds = std::accumulate(_testResults.cbegin(), _testResults.cend(), 0u,
         [](unsigned cumulativeMilliseconds, const TestResult& testResult)
         {
            return cumulativeMilliseconds + testResult.milliseconds;
         });
      return milliseconds;
   }

   INLINE void TestClassResult::NonMinimalPrintResultLine(const Console* console, PrintMode printMode) const
   {
      const size_t numberOfFailedTestCases = NumberOfFailedTestCases();
      if (numberOfFailedTestCases == 0)
      {
         console->NonMinimalWriteColor("[  OK  ]", Color::Green, printMode);
      }
      else
      {
         console->NonMinimalWriteColor("[TestClass Failed]", Color::Red, printMode);
      }
      console->NonMinimalWriteNewLine(printMode);
   }

   INLINE size_t TestClassResult::NumberOfFailedTestCases() const
   {
      const ptrdiff_t numberOfFailedTestCases = std::count_if(
         _testResults.cbegin(), _testResults.cend(), [](const TestResult& testResult)
         {
            return testResult.testOutcome != TestOutcome::Success;
         });
      return static_cast<size_t>(numberOfFailedTestCases);
   }

   INLINE void TestClassResult::PrintTestFailures(
      const TwoExtraArgsForEacherType* forEacherTwoExtraArgs,
      const Console* console,
      TestFailureNumberer* testFailureNumberer) const
   {
      forEacherTwoExtraArgs->TwoExtraArgsForEach(
         &_testResults, PrintTestResultIfFailure, console, testFailureNumberer);
   }

   INLINE void TestClassResult::PrintTestResultIfFailure(
      const TestResult& testResult, const Console* console, TestFailureNumberer* testFailureNumberer)
   {
      testResult.PrintIfFailure(console, testFailureNumberer);
   }

   INLINE void TestClassResult::AssertEqual(
      const ZenUnit::TestClassResult& expectedTestClassResult,
      const ZenUnit::TestClassResult& actualTestClassResult)
   {
      VECTORS_EQUAL(expectedTestClassResult._testResults, actualTestClassResult._testResults);
   }

   INLINE TestClassResult TestClassResult::TestingNonDefault()
   {
      TestClassResult testClassResult;
      testClassResult._testResults.resize(1);
      return testClassResult;
   }
}

INLINE void ZenUnitEqualizer<ZenUnit::TestClassResult>::
AssertEqual(
   const ZenUnit::TestClassResult& expectedTestClassResult,
   const ZenUnit::TestClassResult& actualTestClassResult)
{
   ZenUnit::TestClassResult::AssertEqual(expectedTestClassResult, actualTestClassResult);
}

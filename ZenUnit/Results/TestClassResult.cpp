#include "pch.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/Results/TestClassResult.h"
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/Utils/Iteration/ForEacherTwoExtraArgs.h"

namespace ZenUnit
{
   TestClassResult::TestClassResult()
      : _forEacherTwoExtraArgs(new ForEacherTwoExtraArgsType)
   {
   }

   TestClassResult::TestClassResult(const TestClassResult& testClassResult)
   {
      *this = testClassResult;
   }

   TestClassResult& TestClassResult::operator=(const TestClassResult& testClassResult)
   {
      if (this != &testClassResult)
      {
         _forEacherTwoExtraArgs = testClassResult._forEacherTwoExtraArgs;
         _testResults = testClassResult._testResults;
      }
      return *this;
   }

   TestClassResult::TestClassResult(TestClassResult&& testClassResult)
   {
      *this = std::move(testClassResult);
   }

   TestClassResult& TestClassResult::operator=(TestClassResult&& testClassResult)
   {
      _forEacherTwoExtraArgs = std::exchange(testClassResult._forEacherTwoExtraArgs, nullptr);
      _testResults = std::exchange(testClassResult._testResults, std::vector<TestResult>());
      return *this;
   }

   TestClassResult::~TestClassResult() = default;

   void TestClassResult::AddTestResults(const vector<TestResult>& testResults)
   {
      _testResults.insert(_testResults.end(), testResults.cbegin(), testResults.cend());
   }

   unsigned TestClassResult::Milliseconds() const
   {
      const unsigned milliseconds = std::accumulate(_testResults.cbegin(), _testResults.cend(), 0u,
         [](unsigned cumulativeMilliseconds, const TestResult& testResult)
         {
            return cumulativeMilliseconds + testResult.milliseconds;
         });
      return milliseconds;
   }

   void TestClassResult::PrintResultLine(const Console* console) const
   {
      const size_t numberOfFailedTestCases = NumberOfFailedTestCases();
      if (numberOfFailedTestCases == 0)
      {
         console->WriteColor("[  OK  ]", Color::Green);
      }
      else
      {
         console->WriteColor("[FAILED]", Color::Red);
      }
      console->WriteNewline();
   }

   size_t TestClassResult::NumberOfFailedTestCases() const
   {
      const ptrdiff_t numberOfFailedTestCases = std::count_if(
         _testResults.cbegin(), _testResults.cend(), [](const TestResult& testResult)
         {
            return testResult.testOutcome != TestOutcome::Success;
         });
      return static_cast<size_t>(numberOfFailedTestCases);
   }

   void TestClassResult::PrintTestFailures(
      const Console* console, TestFailureNumberer* testFailureNumberer) const
   {
      _forEacherTwoExtraArgs->ForEach(&_testResults, PrintTestResultIfFailure, console, testFailureNumberer);
   }

   void TestClassResult::PrintTestResultIfFailure(
      const TestResult& testResult, const Console* console, TestFailureNumberer* testFailureNumberer)
   {
      testResult.PrintIfFailure(console, testFailureNumberer);
   }

   void TestClassResult::AssertEqual(
      const ZenUnit::TestClassResult& expectedTestClassResult,
      const ZenUnit::TestClassResult& actualTestClassResult)
   {
      VECTORS_EQUAL(expectedTestClassResult._testResults, actualTestClassResult._testResults);
   }

   TestClassResult TestClassResult::TestingNonDefault()
   {
      TestClassResult testClassResult;
      testClassResult._forEacherTwoExtraArgs.reset(new ForEacherTwoExtraArgsType);
      testClassResult._testResults.resize(1);
      return testClassResult;
   }
}

void ZenUnitEqualizer<ZenUnit::TestClassResult>::
AssertEqual(
   const ZenUnit::TestClassResult& expectedTestClassResult,
   const ZenUnit::TestClassResult& actualTestClassResult)
{
   ZenUnit::TestClassResult::AssertEqual(expectedTestClassResult, actualTestClassResult);
}

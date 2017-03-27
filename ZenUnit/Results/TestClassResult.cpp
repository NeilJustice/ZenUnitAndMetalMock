#include "pch.h"
#include "TestClassResult.h"
#include "Utils/Iteration/ForEacherTwoExtraArgs.h"
#include "Console/Console.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

namespace ZenUnit
{
   TestClassResult::TestClassResult()
      : _forEacherTwoExtraArgs(new ForEacherTwoExtraArgsType)
   {
   }

   TestClassResult::~TestClassResult()
   {
   }

   void TestClassResult::Assign(const TestClassResult& testClassResult)
   {
      _testResults = testClassResult._testResults;
   }

   void TestClassResult::AddTestResults(const vector<TestResult>& newTestResults)
   {
      _testResults.insert(end(_testResults), newTestResults.cbegin(), newTestResults.cend());
   }

   long long TestClassResult::Milliseconds() const
   {
      const long long milliseconds = std::accumulate(_testResults.cbegin(), _testResults.cend(), 0ll,
         [](long long cumulativeMilliseconds, const TestResult& testResult)
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
         console->WriteColor("[ OK ]", Color::Green);
      }
      else
      {
         console->WriteColor("[FAIL]", Color::Red);
      }
      console->WriteNewline();
   }

   size_t TestClassResult::NumberOfFailedTestCases() const
   {
      const long long numberOfFailedTestCases = std::count_if(
         _testResults.cbegin(), _testResults.cend(), [](const TestResult& testResult)
         {
            return testResult.testOutcome != TestOutcome::Success;
         });
      return static_cast<size_t>(numberOfFailedTestCases);
   }

   void TestClassResult::PrintTestFailures(
      const Console* console, TestFailureNumberer* testFailureNumberer) const
   {
      _forEacherTwoExtraArgs->ForEach(&_testResults, 
         PrintTestResultIfFailure, console, testFailureNumberer);
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
      testClassResult._testResults = { TestResult() };
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

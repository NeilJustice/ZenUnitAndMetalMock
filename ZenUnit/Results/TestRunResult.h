#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Utils/Iteration/ForEacherTwoExtraArgs.h"

namespace ZenUnit
{
   class Console;
   template<typename DataStructureType, typename ClassType, typename FunctionType>
   class MemberForEacher;
   template<typename IterableType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
   class ForEacherTwoExtraArgs;
   class TestFailureNumberer;
   struct ZenUnitArgs;
   struct TestClassResult;
   struct TestResult;

   using ForEacherTwoExtraArgsType = const ForEacherTwoExtraArgs<
      std::vector<TestResult>, void (*)(const TestResult&, const Console*, TestFailureNumberer*),
      const Console*, TestFailureNumberer*>;

   class TestRunResult
   {
      friend class TestRunResultTests;
      using MemberForEacherTestClassResultsType = MemberForEacher<vector<TestClassResult>,
         TestRunResult, void(TestRunResult::*)(const TestClassResult&) const>;
      using MemberForEacherSkippedTestsType = MemberForEacher<std::vector<std::string>,
         TestRunResult, void(TestRunResult::*)(const std::string&) const>;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const MemberForEacherTestClassResultsType> _memberForEacherTestClassResults;
      std::unique_ptr<const MemberForEacherSkippedTestsType> _memberForEacherSkippedTests;
      std::unique_ptr<const ForEacherTwoExtraArgsType> _forEacherTwoExtraArgs;
      std::unique_ptr<TestFailureNumberer> _testFailureNumberer;
      std::vector<std::string> _skippedTestClassNamesAndReasons;
      std::vector<std::string> _skippedFullTestNamesAndReasons;
      std::vector<TestClassResult> _testClassResults;
      size_t _numberOfFailedTestCases;
   public:
      TestRunResult();
      virtual ~TestRunResult();
      virtual void AddSkippedTest(
         const char* testClassName, const char* testName, const char* reason);
      virtual void AddSkippedTestClassNameAndReason(
         const char* testClassName, const char* reason);
      virtual void SetTestClassResults(std::vector<TestClassResult>&& testClassResults);
      virtual void PrintTestFailuresAndSkips() const;
      virtual void PrintClosingLines(
         size_t totalNumberOfTestCases,
         unsigned testRunMilliseconds,
         const ZenUnitArgs& zenUnitArgs) const;
      virtual int DetermineExitCode(const ZenUnitArgs& args) const;
      virtual void ResetStateExceptForSkips();

      static void AssertEqual(
         const ZenUnit::TestRunResult& expectedTestRunResult,
         const ZenUnit::TestRunResult& actualTestRunResult);
   private:
      virtual size_t NumberOfFailedTestCases(const vector<TestClassResult>& testClassResults) const;
      void PrintTestClassResultFailures(const TestClassResult& testClassResult) const;
      void PrintSkippedTestClassReminder(const std::string& skippedTestClassNameAndReason) const;
      void PrintSkippedTestReminder(const std::string& skippedFullTestNameAndReason) const;
   };
}

template<>
struct ZenUnitEqualizer<ZenUnit::TestRunResult>
{
   static void AssertEqual(
      const ZenUnit::TestRunResult& expectedTestRunResult,
      const ZenUnit::TestRunResult& actualTestRunResult);
};

#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Results/TestResult.h"

namespace ZenUnit
{
   template<typename IterableType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
   class ForEacherTwoExtraArgs;
   class Console;
   class TestFailureNumberer;

   struct TestClassResult
   {
      friend class TestClassResultTests;
   private:
      using ForEacherTwoExtraArgsType = const ForEacherTwoExtraArgs<
         std::vector<TestResult>, void (*)(const TestResult&, const Console*, TestFailureNumberer*),
         const Console*, TestFailureNumberer*>;
      std::shared_ptr<ForEacherTwoExtraArgsType> _forEacherTwoExtraArgs;
      std::vector<TestResult> _testResults;
   public:
      TestClassResult();
      virtual ~TestClassResult();
      virtual void Assign(const TestClassResult& testClassResult);
      virtual void AddTestResults(const std::vector<TestResult>& testResults);
      virtual long long Milliseconds() const;
      virtual void PrintResultLine(const Console* console) const;
      virtual size_t NumberOfFailedTestCases() const;
      virtual void PrintTestFailures(
         const Console* console, TestFailureNumberer* testFailureNumberer) const;
      static void AssertEqual(
         const TestClassResult& expectedTestClassResult,
         const TestClassResult& actualTestClassResult);
      static TestClassResult TestingNonDefault();
   private:
      static void PrintTestResultIfFailure(
         const TestResult& testResult, const Console* console, TestFailureNumberer* testFailureNumberer);
   };

   #ifdef __linux__
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(TestClassResult) == 56, "Debug sizeof(TestClassResult) != 56");
      #elif NDEBUG
         static_assert(sizeof(TestClassResult) == 48, "Release sizeof(TestClassResult) != 48");
      #endif
   #endif
}

template<>
struct ZenUnitEqualizer<ZenUnit::TestClassResult>
{
   static void AssertEqual(
      const ZenUnit::TestClassResult& expectedTestClassResult,
      const ZenUnit::TestClassResult& actualTestClassResult);
};

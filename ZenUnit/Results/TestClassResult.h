#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Results/TestResult.h"

namespace ZenUnit
{
   template<typename IterableType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
   class ForEacherTwoExtraArgs;
   class Console;
   class TestFailureNumberer;

   using ForEacherTwoExtraArgsType = const ForEacherTwoExtraArgs<
      std::vector<TestResult>, void (*)(const TestResult&, const Console*, TestFailureNumberer*),
      const Console*, TestFailureNumberer*>;

   struct TestClassResult
   {
      friend class TestClassResultTests;
   private:
      std::vector<TestResult> _testResults;
   public:
      TestClassResult();
      TestClassResult(const TestClassResult&);
      TestClassResult& operator=(const TestClassResult&);
      TestClassResult(TestClassResult&& testClassResult) noexcept;
      TestClassResult& operator=(TestClassResult&& testClassResult) noexcept;
      virtual ~TestClassResult();
      virtual void AddTestResults(const std::vector<TestResult>& testResults);
      virtual unsigned Milliseconds() const;
      virtual void PrintResultLine(const Console* console) const;
      virtual size_t NumberOfFailedTestCases() const;
      virtual void PrintTestFailures(
         const ForEacherTwoExtraArgsType* forEacherTwoExtraArgs,
         const Console* console,
         TestFailureNumberer* testFailureNumberer) const;
      static void AssertEqual(
         const TestClassResult& expectedTestClassResult,
         const TestClassResult& actualTestClassResult);
      static TestClassResult TestingNonDefault();
   private:
      static void PrintTestResultIfFailure(
         const TestResult& testResult, const Console* console, TestFailureNumberer* testFailureNumberer);
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(TestClassResult) == 32, "Release sizeof(TestClassResult) != 32");
      #endif
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(TestClassResult) == 40, "Debug sizeof(TestClassResult) != 40");
      #elif NDEBUG
         static_assert(sizeof(TestClassResult) == 32, "Release sizeof(TestClassResult) != 32");
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

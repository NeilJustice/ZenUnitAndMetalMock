#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Results/TestResult.h"

namespace ZenUnit
{
   template<typename CollectionType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
   class TwoExtraArgsForEacher;
   class Console;
   class TestFailureNumberer;
   enum class PrintMode : unsigned char;

   using TwoExtraArgsForEacherType = const TwoExtraArgsForEacher<
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
      virtual void NonMinimalPrintResultLine(const Console* console, PrintMode printMode) const;
      virtual size_t NumberOfFailedTestCases() const;
      virtual void PrintTestFailures(
         const TwoExtraArgsForEacherType* forEacherTwoExtraArgs,
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
         static_assert(sizeof(TestClassResult) == 32);
      #endif
   #elif _MSC_FULL_VER == VS2017Update4 && defined(_WIN64)
      #ifdef _DEBUG
         static_assert(sizeof(TestClassResult) == 40);
      #elif NDEBUG
         static_assert(sizeof(TestClassResult) == 32);
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

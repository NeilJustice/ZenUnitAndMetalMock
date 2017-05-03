#pragma once
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Results/CallResult.h"
#include "ZenUnit/Tests/FullTestName.h"
#include <functional>

namespace ZenUnit
{
   class Console;
   struct ZenUnitArgs;
   class TestFailureNumberer;

   struct TestResult
   {
      FullTestName fullTestName;
      CallResult constructorCallResult;
      CallResult startupCallResult;
      CallResult testBodyCallResult;
      CallResult cleanupCallResult;
      CallResult destructorCallResult;
      CallResult TestResult::* responsibleCallResultField;
      TestOutcome testOutcome;
      unsigned milliseconds;
      unsigned short testCaseIndex;

      TestResult();
      virtual ~TestResult() = default;

      static TestResult ConstructorFail(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult);

      static TestResult StartupFail(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& destructorCallResult);

      static TestResult CtorDtorSuccess(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& destructorCallResult);

      TestResult(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& testBodyCallResult,
         const CallResult& cleanupCallResult,
         const CallResult& destructorCallResult,
         const std::function<ZenUnitArgs()>& getArgs);

      virtual void PrintOKIfTestPassed(const Console* console) const;
      virtual void PrintIfFailure(const Console* console, TestFailureNumberer* testFailureNumberer) const;
      virtual void WriteTestCaseNumberIfAny(const Console* console, unsigned short testCaseIndexArgument) const;
      static const TestResult TestingNonDefault;
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(TestResult) == 168, "sizeof(TestResult) != 168");
      #endif
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(TestResult) == 168, "Debug sizeof(TestResult) != 168");
      #elif NDEBUG
         static_assert(sizeof(TestResult) == 168, "Release sizeof(TestResult) != 168");
      #endif
   #endif

   static_assert(std::is_move_constructible<TestResult>::value, "!std::is_move_constructible<TestResult>::value");
   static_assert(std::is_move_assignable<TestResult>::value, "!std::is_move_assignable<TestResult>::value");
}

template<>
struct ZenUnitEqualizer<ZenUnit::TestResult>
{
   static void AssertEqual(
      const ZenUnit::TestResult& expectedTestResult,
      const ZenUnit::TestResult& actualTestResult);
};

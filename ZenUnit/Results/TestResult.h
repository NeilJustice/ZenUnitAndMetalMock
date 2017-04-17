#pragma once
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Results/CallResult.h"
#include "ZenUnit/Tests/FullName.h"
#include <functional>

namespace ZenUnit
{
   class Console;
   struct ZenUnitArgs;
   class TestFailureNumberer;

   struct TestResult
   {
      FullName fullName;
      int testCaseIndex;
      CallResult constructorCallResult;
      CallResult startupCallResult;
      CallResult testBodyCallResult;
      CallResult cleanupCallResult;
      CallResult destructorCallResult;
      CallResult TestResult::* responsibleCallResultField;
      TestOutcome testOutcome;
      long long milliseconds;

      TestResult();
      virtual ~TestResult() = default;

      static TestResult ConstructorFail(
         FullName fullName,
         const CallResult& constructorCallResult);

      static TestResult StartupFail(
         FullName fullName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& destructorCallResult);

      static TestResult CtorDtorSuccess(
         FullName fullName,
         const CallResult& constructorCallResult,
         const CallResult& destructorCallResult);

      TestResult(
         FullName fullName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& testBodyCallResult,
         const CallResult& cleanupCallResult,
         const CallResult& destructorCallResult,
         const std::function<ZenUnitArgs()>& getArgs);

      virtual void PrintTestOutcome(const Console* console) const;
      virtual void PrintIfFailure(const Console* console, TestFailureNumberer* testFailureNumberer) const;
      virtual void WriteTestCaseNumberIfAny(const Console* console, int testCaseIndexArgument) const;
      static const TestResult TestingNonDefault;
   };

   #ifdef __linux__
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(TestResult) == 1608, "Debug sizeof(TestResult) != 1608");
      #elif NDEBUG
         static_assert(sizeof(TestResult) == 1368, "Release sizeof(TestResult) != 1368");
      #endif
   #endif
}

template<>
struct ZenUnitEqualizer<ZenUnit::TestResult>
{
   static void AssertEqual(
      const ZenUnit::TestResult& expectedTestResult,
      const ZenUnit::TestResult& actualTestResult);
};

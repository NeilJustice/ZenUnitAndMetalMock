#pragma once
#include "ZenUnit/Tests/FullName.h"
#include "ZenUnit/Results/CallResult.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
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
         const FullName& fullName,
         const CallResult& constructorCallResult);

      static TestResult StartupFail(
         const FullName& fullName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& destructorCallResult);

      static TestResult CtorDtorSuccess(
         const FullName& fullName,
         const CallResult& constructorCallResult,
         const CallResult& destructorCallResult);

      TestResult(
         const FullName& fullName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& testBodyCallResult,
         const CallResult& cleanupCallResult,
         const CallResult& destructorCallResult,
         std::function<ZenUnitArgs()> getArgs);

      virtual void PrintTestOutcome(const Console* console) const;
      virtual void PrintIfFailure(const Console* console, TestFailureNumberer* testFailureNumberer) const;
      virtual void WriteTestCaseNumberIfAny(const Console* console, int testCaseIndexArgument) const;
      static const TestResult TestingNonDefault;
   };
}

template<>
struct ZenUnitEqualizer<ZenUnit::TestResult>
{
   static void AssertEqual(
      const ZenUnit::TestResult& expectedTestResult,
      const ZenUnit::TestResult& actualTestResult);
};

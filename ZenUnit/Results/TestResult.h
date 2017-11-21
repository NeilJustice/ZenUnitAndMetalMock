#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Results/CallResult.h"
#include "ZenUnit/Tests/FullTestName.h"

namespace ZenUnit
{
   class Console;
   struct ZenUnitArgs;
   class TestFailureNumberer;
   enum class PrintMode : unsigned char;

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
         const std::function<const ZenUnitArgs&()>& getArgs);

      virtual void NonMinimalWriteLineOKIfSuccess(const Console* console, PrintMode printMode) const;
      virtual void PrintIfFailure(const Console* console, TestFailureNumberer* testFailureNumberer) const;
      virtual void WriteTestCaseNumberIfAny(const Console* console, unsigned short testCaseIndexArgument) const;
      static const TestResult TestingNonDefault();
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(TestResult) == 176);
      #endif
   #elif defined(_WIN64)
      #ifdef _DEBUG
         static_assert(sizeof(TestResult) == 168);
      #elif NDEBUG
         static_assert(sizeof(TestResult) == 168);
      #endif
   #endif

   template<>
   struct Equalizer<ZenUnit::TestResult>
   {
      static void AssertEqual(
         const ZenUnit::TestResult& expectedTestResult,
         const ZenUnit::TestResult& actualTestResult);
   };
}

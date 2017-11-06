#include "pch.h"
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/Results/TestResultFactory.h"
#include "ZenUnit/TestRunners/TestRunner.h"

namespace ZenUnit
{
   inline TestResult TestResultFactory::ConstructorFail(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult) const
   {
      return TestResult::ConstructorFail(fullTestName, constructorCallResult);
   }

   inline TestResult TestResultFactory::StartupFail(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::StartupFail(
         fullTestName, constructorCallResult, startupCallResult, destructorCallResult);
   }

   inline TestResult TestResultFactory::CtorDtorSuccess(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::CtorDtorSuccess(
         fullTestName, constructorCallResult, destructorCallResult);
   }

   inline TestResult TestResultFactory::FullCtor(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& testBodyCallResult,
      const CallResult& cleanupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult(
         fullTestName,
         constructorCallResult,
         startupCallResult,
         testBodyCallResult,
         cleanupCallResult,
         destructorCallResult,
         TestRunner::GetArgs);
   }
}

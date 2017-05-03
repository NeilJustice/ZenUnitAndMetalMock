#include "pch.h"
#include "TestResultFactory.h"
#include "ZenUnit/Results/TestResult.h"

namespace ZenUnit
{
   TestResult TestResultFactory::ConstructorFail(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult) const
   {
      return TestResult::ConstructorFail(fullTestName, constructorCallResult);
   }

   TestResult TestResultFactory::StartupFail(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::StartupFail(
         fullTestName, constructorCallResult, startupCallResult, destructorCallResult);
   }

   TestResult TestResultFactory::CtorDtorSuccess(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::CtorDtorSuccess(
         fullTestName, constructorCallResult, destructorCallResult);
   }

   TestResult TestResultFactory::FullCtor(
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

#include "pch.h"
#include "TestResultFactory.h"
#include "ZenUnit/Results/TestResult.h"

namespace ZenUnit
{
   TestResult TestResultFactory::ConstructorFail(
      const ClassNameTestName& classNameTestName,
      const CallResult& constructorCallResult) const
   {
      return TestResult::ConstructorFail(classNameTestName, constructorCallResult);
   }

   TestResult TestResultFactory::StartupFail(
      const ClassNameTestName& classNameTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::StartupFail(
         classNameTestName, constructorCallResult, startupCallResult, destructorCallResult);
   }

   TestResult TestResultFactory::CtorDtorSuccess(
      const ClassNameTestName& classNameTestName,
      const CallResult& constructorCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::CtorDtorSuccess(
         classNameTestName, constructorCallResult, destructorCallResult);
   }

   TestResult TestResultFactory::FullCtor(
      const ClassNameTestName& classNameTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& testBodyCallResult,
      const CallResult& cleanupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult(
         classNameTestName,
         constructorCallResult,
         startupCallResult,
         testBodyCallResult,
         cleanupCallResult,
         destructorCallResult,
         TestRunner::GetArgs);
   }
}

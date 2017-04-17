#include "pch.h"
#include "TestResultFactory.h"
#include "ZenUnit/Results/TestResult.h"

namespace ZenUnit
{
   TestResult TestResultFactory::ConstructorFail(
      const FullName& fullName,
      const CallResult& constructorCallResult) const
   {
      return TestResult::ConstructorFail(fullName, constructorCallResult);
   }

   TestResult TestResultFactory::StartupFail(
      const FullName& fullName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::StartupFail(
         fullName, constructorCallResult, startupCallResult, destructorCallResult);
   }

   TestResult TestResultFactory::CtorDtorSuccess(
      const FullName& fullName,
      const CallResult& constructorCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::CtorDtorSuccess(
         fullName, constructorCallResult, destructorCallResult);
   }

   TestResult TestResultFactory::FullCtor(
      const FullName& fullName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& testBodyCallResult,
      const CallResult& cleanupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult(
         fullName,
         constructorCallResult,
         startupCallResult,
         testBodyCallResult,
         cleanupCallResult,
         destructorCallResult,
         TestRunner::GetArgs);
   }
}

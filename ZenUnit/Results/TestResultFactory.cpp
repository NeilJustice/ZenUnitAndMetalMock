#include "pch.h"
#include "TestResultFactory.h"
#include "ZenUnit/Results/TestResult.h"

namespace ZenUnit
{
   TestResult TestResultFactory::ConstructorFail(
      FullName fullName,
      const CallResult& constructorCallResult) const
   {
      return TestResult::ConstructorFail(std::move(fullName), constructorCallResult);
   }

   TestResult TestResultFactory::StartupFail(
      FullName fullName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::StartupFail(
         std::move(fullName), constructorCallResult, startupCallResult, destructorCallResult);
   }

   TestResult TestResultFactory::CtorDtorSuccess(
      FullName fullName,
      const CallResult& constructorCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult::CtorDtorSuccess(
         std::move(fullName), constructorCallResult, destructorCallResult);
   }

   TestResult TestResultFactory::FullCtor(
      FullName fullName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& testBodyCallResult,
      const CallResult& cleanupCallResult,
      const CallResult& destructorCallResult) const
   {
      return TestResult(
         std::move(fullName),
         constructorCallResult,
         startupCallResult,
         testBodyCallResult,
         cleanupCallResult,
         destructorCallResult,
         TestRunner::GetArgs);
   }
}

#pragma once
#include "ZenUnit/TestRunners/TestRunner.h"

namespace ZenUnit
{
   struct TestResult;
   struct FullName;
   struct CallResult;
   struct ZenUnitArgs;

   class TestResultFactory
   {
   public:
      virtual TestResult ConstructorFail(
         FullName fullName,
         const CallResult& constructorCallResult) const;

      virtual TestResult StartupFail(
         FullName fullName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& destructorCallResult) const;

      virtual TestResult CtorDtorSuccess(
         FullName fullName,
         const CallResult& constructorCallResult,
         const CallResult& destructorCallResult) const;

      virtual TestResult FullCtor(
         FullName fullName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& testBodyCallResult,
         const CallResult& cleanupCallResult,
         const CallResult& destructorCallResult) const;

      virtual ~TestResultFactory() = default;
   };
}

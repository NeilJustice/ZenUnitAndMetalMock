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
         const FullName& fullName,
         const CallResult& constructorCallResult) const;

      virtual TestResult StartupFail(
         const FullName& fullName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& destructorCallResult) const;

      virtual TestResult CtorDtorSuccess(
         const FullName& fullName,
         const CallResult& constructorCallResult,
         const CallResult& destructorCallResult) const;

      virtual TestResult FullCtor(
         const FullName& fullName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& testBodyCallResult,
         const CallResult& cleanupCallResult,
         const CallResult& destructorCallResult) const;

      virtual ~TestResultFactory() = default;
   };
}

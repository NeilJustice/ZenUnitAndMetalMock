#pragma once

namespace ZenUnit
{
   struct TestResult;
   struct FullTestName;
   struct CallResult;
   struct ZenUnitArgs;

   class TestResultFactory
   {
   public:
      virtual TestResult ConstructorFail(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult) const;

      virtual TestResult StartupFail(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& destructorCallResult) const;

      virtual TestResult CtorDtorSuccess(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& destructorCallResult) const;

      virtual TestResult FullCtor(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& testBodyCallResult,
         const CallResult& cleanupCallResult,
         const CallResult& destructorCallResult) const;

      virtual ~TestResultFactory() = default;
   };
}

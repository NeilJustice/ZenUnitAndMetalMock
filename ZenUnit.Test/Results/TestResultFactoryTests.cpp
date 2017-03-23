#include "pch.h"
#include "ZenUnit/Results/TestResultFactory.h"

namespace ZenUnit
{
   TESTS(TestResultFactoryTests)
   SPEC(ConstructorFail_ReturnsTestResultConstructorFail)
   SPEC(StartupFail_ReturnsTestResultStartupFail)
   SPEC(CtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
   SPEC(FullConstructor_ReturnsTestResultSixArgCtor)
   SPECEND

   TestResultFactory _testResultFactory;
   const FullName FullNameValue = FullName("TestClass", "Test");
   CallResult ConstructorCallResult;
   CallResult StartupCallResult;
   CallResult DestructorCallResult;
   CallResult TestBodyCallResult;
   CallResult CleanupCallResult;
   STARTUP
   {
      ConstructorCallResult.testPhase = TestPhase::Constructor;
      StartupCallResult.testPhase = TestPhase::Startup;
      TestBodyCallResult.testPhase = TestPhase::TestBody;
      CleanupCallResult.testPhase = TestPhase::Cleanup;
      DestructorCallResult.testPhase = TestPhase::Destructor;
   }

   TEST(ConstructorFail_ReturnsTestResultConstructorFail)
   {
      TestResult constructorFailTestResult = _testResultFactory.ConstructorFail(FullNameValue, ConstructorCallResult);
      //
      TestResult expectedTestResult = TestResult::ConstructorFail(FullNameValue, ConstructorCallResult);
      ARE_EQUAL(expectedTestResult, constructorFailTestResult);
   }

   TEST(StartupFail_ReturnsTestResultStartupFail)
   {
      TestResult startupFailTestResult = _testResultFactory.StartupFail(
         FullNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      //
      TestResult expectedTestResult = TestResult::StartupFail(
         FullNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(CtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
   {
      TestResult ctorDtorSuccessResult = _testResultFactory.CtorDtorSuccess(
         FullNameValue, ConstructorCallResult, DestructorCallResult);
      //
      TestResult expectedTestResult = TestResult::CtorDtorSuccess(
         FullNameValue, ConstructorCallResult, DestructorCallResult);
      ARE_EQUAL(expectedTestResult, ctorDtorSuccessResult);
   }

   TEST(FullConstructor_ReturnsTestResultSixArgCtor)
   {
      TestResult testResult = _testResultFactory.FullCtor(
         FullNameValue, ConstructorCallResult, StartupCallResult,
         TestBodyCallResult, CleanupCallResult, DestructorCallResult);
      //
      TestResult expectedTestResult(
         FullNameValue, ConstructorCallResult, StartupCallResult,
         TestBodyCallResult, CleanupCallResult, DestructorCallResult, TestRunner::GetArgs);
      ARE_EQUAL(expectedTestResult, testResult);
   }

   }; RUN(TestResultFactoryTests)
}

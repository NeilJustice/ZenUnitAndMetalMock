#include "pch.h"
#include "ZenUnit/Results/TestResultFactory.h"

namespace ZenUnit
{
   TESTS(TestResultFactoryTests)
   FACT(ConstructorFail_ReturnsTestResultConstructorFail)
   FACT(StartupFail_ReturnsTestResultStartupFail)
   FACT(CtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
   FACT(FullConstructor_ReturnsTestResultSixArgCtor)
   EVIDENCE

   TestResultFactory _testResultFactory;
   const FullTestName FullTestNameValue = FullTestName("TestClass", "Test", 0);
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
      const TestResult constructorFailTestResult = 
         _testResultFactory.ConstructorFail(FullTestNameValue, ConstructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::ConstructorFail(FullTestNameValue, ConstructorCallResult);
      ARE_EQUAL(expectedTestResult, constructorFailTestResult);
   }

   TEST(StartupFail_ReturnsTestResultStartupFail)
   {
      const TestResult startupFailTestResult = _testResultFactory.StartupFail(
         FullTestNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::StartupFail(
         FullTestNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(CtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
   {
      const TestResult ctorDtorSuccessResult = _testResultFactory.CtorDtorSuccess(
         FullTestNameValue, ConstructorCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::CtorDtorSuccess(
         FullTestNameValue, ConstructorCallResult, DestructorCallResult);
      ARE_EQUAL(expectedTestResult, ctorDtorSuccessResult);
   }

   TEST(FullConstructor_ReturnsTestResultSixArgCtor)
   {
      const TestResult testResult = _testResultFactory.FullCtor(
         FullTestNameValue, ConstructorCallResult, StartupCallResult,
         TestBodyCallResult, CleanupCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult(
         FullTestNameValue, ConstructorCallResult, StartupCallResult,
         TestBodyCallResult, CleanupCallResult, DestructorCallResult, TestRunner::GetArgs);
      ARE_EQUAL(expectedTestResult, testResult);
   }

   }; RUNTESTS(TestResultFactoryTests)
}

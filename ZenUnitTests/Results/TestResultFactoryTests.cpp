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
   const ClassNameTestName FullNameValue = ClassNameTestName("TestClass", "Test");
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
         _testResultFactory.ConstructorFail(FullNameValue, ConstructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::ConstructorFail(FullNameValue, ConstructorCallResult);
      ARE_EQUAL(expectedTestResult, constructorFailTestResult);
   }

   TEST(StartupFail_ReturnsTestResultStartupFail)
   {
      const TestResult startupFailTestResult = _testResultFactory.StartupFail(
         FullNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::StartupFail(
         FullNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(CtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
   {
      const TestResult ctorDtorSuccessResult = _testResultFactory.CtorDtorSuccess(
         FullNameValue, ConstructorCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::CtorDtorSuccess(
         FullNameValue, ConstructorCallResult, DestructorCallResult);
      ARE_EQUAL(expectedTestResult, ctorDtorSuccessResult);
   }

   TEST(FullConstructor_ReturnsTestResultSixArgCtor)
   {
      const TestResult testResult = _testResultFactory.FullCtor(
         FullNameValue, ConstructorCallResult, StartupCallResult,
         TestBodyCallResult, CleanupCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult(
         FullNameValue, ConstructorCallResult, StartupCallResult,
         TestBodyCallResult, CleanupCallResult, DestructorCallResult, TestRunner::GetArgs);
      ARE_EQUAL(expectedTestResult, testResult);
   }

   }; RUN(TestResultFactoryTests)
}

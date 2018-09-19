#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"

namespace ZenUnit
{
   TESTS(TestResultFactoryTests)
   AFACT(MakeConstructorFail_ReturnsTestResultConstructorFail)
   AFACT(MakeStartupFail_ReturnsTestResultStartupFail)
   AFACT(MakeCtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
   AFACT(MakeFullTestResult_ReturnsTestResultSixArgCtor)
   EVIDENCE

   TestResultFactory _testResultFactory;
   const string testClassName = ZenUnit::Random<string>();
   const string testName = ZenUnit::Random<string>();
   const FullTestName FullTestNameValue = FullTestName(testClassName.c_str(), testName.c_str(), ZenUnit::Random<char>());
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

   TEST(MakeConstructorFail_ReturnsTestResultConstructorFail)
   {
      const TestResult constructorFailTestResult =
         _testResultFactory.MakeConstructorFail(FullTestNameValue, ConstructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::ConstructorFail(FullTestNameValue, ConstructorCallResult);
      ARE_EQUAL(expectedTestResult, constructorFailTestResult);
   }

   TEST(MakeStartupFail_ReturnsTestResultStartupFail)
   {
      const TestResult startupFailTestResult = _testResultFactory.MakeStartupFail(
         FullTestNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::StartupFail(
         FullTestNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(MakeCtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
   {
      const TestResult ctorDtorSuccessResult = _testResultFactory.MakeCtorDtorSuccess(
         FullTestNameValue, ConstructorCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult = TestResult::CtorDtorSuccess(
         FullTestNameValue, ConstructorCallResult, DestructorCallResult);
      ARE_EQUAL(expectedTestResult, ctorDtorSuccessResult);
   }

   TEST(MakeFullTestResult_ReturnsTestResultSixArgCtor)
   {
      const TestResult testResult = _testResultFactory.MakeFullTestResult(
         FullTestNameValue, ConstructorCallResult, StartupCallResult,
         TestBodyCallResult, CleanupCallResult, DestructorCallResult);
      //
      const TestResult expectedTestResult(
         FullTestNameValue, ConstructorCallResult, StartupCallResult,
         TestBodyCallResult, CleanupCallResult, DestructorCallResult, TestRunner::GetArgs);
      ARE_EQUAL(expectedTestResult, testResult);
   }

   RUN_TESTS(TestResultFactoryTests)
}

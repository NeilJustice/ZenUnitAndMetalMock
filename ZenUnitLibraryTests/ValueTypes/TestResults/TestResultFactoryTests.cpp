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
   TestPhaseResult ConstructorTestPhaseResult;
   TestPhaseResult StartupTestPhaseResult;
   TestPhaseResult DestructorTestPhaseResult;
   TestPhaseResult TestBodyTestPhaseResult;
   TestPhaseResult CleanupTestPhaseResult;
   STARTUP
   {
      ConstructorTestPhaseResult.testPhase = TestPhase::Constructor;
      StartupTestPhaseResult.testPhase = TestPhase::Startup;
      TestBodyTestPhaseResult.testPhase = TestPhase::TestBody;
      CleanupTestPhaseResult.testPhase = TestPhase::Cleanup;
      DestructorTestPhaseResult.testPhase = TestPhase::Destructor;
   }

   TEST(MakeConstructorFail_ReturnsTestResultConstructorFail)
   {
      const TestResult constructorFailTestResult =
         _testResultFactory.MakeConstructorFail(FullTestNameValue, ConstructorTestPhaseResult);
      //
      const TestResult expectedTestResult = TestResult::ConstructorFail(FullTestNameValue, ConstructorTestPhaseResult);
      ARE_EQUAL(expectedTestResult, constructorFailTestResult);
   }

   TEST(MakeStartupFail_ReturnsTestResultStartupFail)
   {
      const TestResult startupFailTestResult = _testResultFactory.MakeStartupFail(
         FullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult, DestructorTestPhaseResult);
      //
      const TestResult expectedTestResult = TestResult::StartupFail(
         FullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult, DestructorTestPhaseResult);
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(MakeCtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
   {
      const TestResult ctorDtorSuccessResult = _testResultFactory.MakeCtorDtorSuccess(
         FullTestNameValue, ConstructorTestPhaseResult, DestructorTestPhaseResult);
      //
      const TestResult expectedTestResult = TestResult::CtorDtorSuccess(
         FullTestNameValue, ConstructorTestPhaseResult, DestructorTestPhaseResult);
      ARE_EQUAL(expectedTestResult, ctorDtorSuccessResult);
   }

   TEST(MakeFullTestResult_ReturnsTestResultSixArgCtor)
   {
      const TestResult testResult = _testResultFactory.MakeFullTestResult(
         FullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult,
         TestBodyTestPhaseResult, CleanupTestPhaseResult, DestructorTestPhaseResult);
      //
      const TestResult expectedTestResult(
         FullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult,
         TestBodyTestPhaseResult, CleanupTestPhaseResult, DestructorTestPhaseResult, ZenUnitTestRunner::GetZenUnitArgs);
      ARE_EQUAL(expectedTestResult, testResult);
   }

   RUN_TESTS(TestResultFactoryTests)
}

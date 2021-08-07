#include "pch.h"

namespace ZenUnit
{
   TESTS(TestResultFactoryTests)
   AFACT(MakeConstructorFail_ReturnsTestResultConstructorFail)
   AFACT(MakeStartupFail_ReturnsTestResultStartupFail)
   AFACT(MakeConstructorDestructorSuccess_ReturnsTestResultConstructorDestructorSuccess)
   AFACT(MakeFullTestResult_ReturnsTestResultSixArgCtor)
   EVIDENCE

   TestResultFactory _testResultFactory;
   const string testClassName = ZenUnit::Random<string>();
   const string testName = ZenUnit::Random<string>();
   FullTestName _fullTestNameValue;
   TestPhaseResult ConstructorTestPhaseResult;
   TestPhaseResult StartupTestPhaseResult;
   TestPhaseResult DestructorTestPhaseResult;
   TestPhaseResult TestBodyTestPhaseResult;
   TestPhaseResult CleanupTestPhaseResult;

   STARTUP
   {
      _fullTestNameValue = FullTestName(testClassName.c_str(), testName.c_str(), ZenUnit::Random<unsigned char>());
      ConstructorTestPhaseResult.testPhase = TestPhase::Constructor;
      StartupTestPhaseResult.testPhase = TestPhase::Startup;
      TestBodyTestPhaseResult.testPhase = TestPhase::TestBody;
      CleanupTestPhaseResult.testPhase = TestPhase::Cleanup;
      DestructorTestPhaseResult.testPhase = TestPhase::Destructor;
   }

   TEST(MakeConstructorFail_ReturnsTestResultConstructorFail)
   {
      const TestResult constructorFailTestResult =
         _testResultFactory.MakeConstructorFail(_fullTestNameValue, ConstructorTestPhaseResult);
      //
      const TestResult expectedTestResult = TestResult::ConstructorFail(_fullTestNameValue, ConstructorTestPhaseResult);
      ARE_EQUAL(expectedTestResult, constructorFailTestResult);
   }

   TEST(MakeStartupFail_ReturnsTestResultStartupFail)
   {
      const TestResult startupFailTestResult = _testResultFactory.MakeStartupFail(
         _fullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult, DestructorTestPhaseResult);
      //
      const TestResult expectedTestResult = TestResult::StartupFail(
         _fullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult, DestructorTestPhaseResult);
      ARE_EQUAL(expectedTestResult, startupFailTestResult);
   }

   TEST(MakeConstructorDestructorSuccess_ReturnsTestResultConstructorDestructorSuccess)
   {
      const TestResult ctorDtorSuccessResult = _testResultFactory.MakeConstructorDestructorSuccess(
         _fullTestNameValue, ConstructorTestPhaseResult, DestructorTestPhaseResult);
      //
      const TestResult expectedTestResult = TestResult::ConstructorDestructorSuccess(
         _fullTestNameValue, ConstructorTestPhaseResult, DestructorTestPhaseResult);
      ARE_EQUAL(expectedTestResult, ctorDtorSuccessResult);
   }

   TEST(MakeFullTestResult_ReturnsTestResultSixArgCtor)
   {
      const TestResult testResult = _testResultFactory.MakeFullTestResult(
         _fullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult,
         TestBodyTestPhaseResult, CleanupTestPhaseResult, DestructorTestPhaseResult);
      //
      const TestResult expectedTestResult(
         _fullTestNameValue, ConstructorTestPhaseResult, StartupTestPhaseResult,
         TestBodyTestPhaseResult, CleanupTestPhaseResult, DestructorTestPhaseResult, ZenUnitTestRunner::GetZenUnitArgs);
      ARE_EQUAL(expectedTestResult, testResult);
   }

   RUN_TESTS(TestResultFactoryTests)
}

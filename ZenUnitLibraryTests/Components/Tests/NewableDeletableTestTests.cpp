#include "pch.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultFactoryMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestPhaseRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/StopwatchMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(NewableDeletableTestTests)
   AFACT(Constructor_NewsComponents)
   AFACT(NumberOfTestCases_Returns1)
   FACTS(RunTest_StartsStopWatch_CallsNewTestClassWhichFails_DoesNotCallDeleteTestClass_StopsStopwatch_ReturnsConstructorFailTestResult)
   AFACT(RunTest_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsConstructorDestructorSuccessTestResult)
   AFACT(NewAndDeleteTestClass_NewsThenDeletesTestClass)
   EVIDENCE

   class TestingTestClass {};
   unique_ptr<NewableDeletableTest<TestingTestClass>> _newableDeletableTest;
   TestPhaseRunnerMock* _tryCatchCallerMock = nullptr;
   TestResultFactoryMock* _testResultFactoryMock = nullptr;
   const string TestClassName = Random<string>();

   STARTUP
   {
      _newableDeletableTest = make_unique<NewableDeletableTest<TestingTestClass>>(TestClassName.c_str());
      _newableDeletableTest->_testPhaseRunner.reset(_tryCatchCallerMock = new TestPhaseRunnerMock);
      _newableDeletableTest->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(Constructor_NewsComponents)
   {
      NewableDeletableTest<TestingTestClass> newableDeletableTest(TestClassName.c_str());
      ARE_EQUAL("TestClassIsNewableAndDeletable", newableDeletableTest.Name());
      DELETE_TO_ASSERT_NEWED(newableDeletableTest._testResultFactory);
      DELETE_TO_ASSERT_NEWED(newableDeletableTest._testPhaseRunner);
      IS_NULLPTR(newableDeletableTest._instanceOfTestClass);
   }

   TEST(NumberOfTestCases_Returns1)
   {
      ARE_EQUAL(1, _newableDeletableTest->NumberOfTestCases());
   }

   TEST1X1(RunTest_StartsStopWatch_CallsNewTestClassWhichFails_DoesNotCallDeleteTestClass_StopsStopwatch_ReturnsConstructorFailTestResult,
      TestOutcome nonSuccessOutcome,
      TestOutcome::Anomaly,
      TestOutcome::Exception)
   {
      TestPhaseResult failedConstructorTestPhaseResult;
      failedConstructorTestPhaseResult.testOutcome = nonSuccessOutcome;
      _tryCatchCallerMock->RunTestPhaseMock.Return(failedConstructorTestPhaseResult);

      const unsigned short elapsedMilliseconds = 0;

      TestResult constructorFailTestResult = TestingNonDefaultTestResult();
      _testResultFactoryMock->MakeConstructorFailMock.Return(constructorFailTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledOnceWith(
         &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor));

      METALMOCKTHEN(_testResultFactoryMock->MakeConstructorFailMock.CalledOnceWith(
         _newableDeletableTest->p_fullTestName,
         failedConstructorTestPhaseResult,
         elapsedMilliseconds));

      const vector<TestResult> expectedTestResults{ constructorFailTestResult };
      VECTORS_ARE_EQUAL(expectedTestResults, testResults);
   }

   TEST(RunTest_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsConstructorDestructorSuccessTestResult)
   {
      TestPhaseResult successConstructorTestPhaseResult;
      successConstructorTestPhaseResult.testOutcome = TestOutcome::Success;

      TestPhaseResult destructorTestPhaseResult;
      _tryCatchCallerMock->RunTestPhaseMock.ReturnValues(
         successConstructorTestPhaseResult,
         destructorTestPhaseResult);

      const unsigned short elapsedMilliseconds = 0;

      TestResult sixArgCtorTestResult = TestingNonDefaultTestResult();
      _testResultFactoryMock->MakeConstructorDestructorSuccessMock.Return(sixArgCtorTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledNTimes(2));

      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(
         &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor)).Then(

      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(
         &Test::CallDeleteTestClass, _newableDeletableTest.get(), TestPhase::Destructor))).Then(

      METALMOCKTHEN(_testResultFactoryMock->MakeConstructorDestructorSuccessMock.CalledOnceWith(
         _newableDeletableTest->p_fullTestName,
         successConstructorTestPhaseResult,
         destructorTestPhaseResult,
         elapsedMilliseconds)));

      const vector<TestResult> expectedTestResults{ sixArgCtorTestResult };
      VECTORS_ARE_EQUAL(expectedTestResults, testResults);
   }

   TEST(NewAndDeleteTestClass_NewsThenDeletesTestClass)
   {
      IS_NULLPTR(_newableDeletableTest->_instanceOfTestClass);
      //
      _newableDeletableTest->NewTestClass();
      //
      IS_NOT_NULLPTR(_newableDeletableTest->_instanceOfTestClass);
      //
      _newableDeletableTest->DeleteTestClass();
      //
      IS_NULLPTR(_newableDeletableTest->_instanceOfTestClass);
   }

   RUN_TESTS(NewableDeletableTestTests)
}

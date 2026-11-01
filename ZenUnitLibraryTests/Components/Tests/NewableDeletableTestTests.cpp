#include "pch.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestPhaseRunnerMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultFactoryMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/StopwatchMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/StopwatchMock.h"

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
   // Base Mutable Components
   StopwatchMock* p_stopwatchMock = nullptr;
   // Constant Components
   TestPhaseRunnerMock* _testPhaseRunnerMock = nullptr;
   TestResultFactoryMock* _testResultFactoryMock = nullptr;
   const string TestClassName = Random<string>();

   STARTUP
   {
      _newableDeletableTest = make_unique<NewableDeletableTest<TestingTestClass>>(TestClassName.c_str());
      // Base Mutable Components
      _newableDeletableTest->p_stopwatch.reset(p_stopwatchMock = new StopwatchMock);
      // Constant Components
      _newableDeletableTest->_testPhaseRunner.reset(_testPhaseRunnerMock = new TestPhaseRunnerMock);
      _newableDeletableTest->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(Constructor_NewsComponents)
   {
      NewableDeletableTest<TestingTestClass> newableDeletableTest(TestClassName.c_str());
      // Constant Components
      DELETE_TO_ASSERT_NEWED(newableDeletableTest._testResultFactory);
      DELETE_TO_ASSERT_NEWED(newableDeletableTest._testPhaseRunner);
      // Mutable Components
      IS_NULLPTR(newableDeletableTest._instanceOfTestClass);
      ARE_EQUAL("TestClassIsNewableAndDeletable", newableDeletableTest.Name());
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
      p_stopwatchMock->StartMock.Expect();

      TestPhaseResult failedConstructorTestPhaseResult;
      failedConstructorTestPhaseResult.testOutcome = nonSuccessOutcome;
      _testPhaseRunnerMock->RunTestPhaseMock.Return(failedConstructorTestPhaseResult);

      const unsigned short elapsedTestMilliseconds = p_stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();

      TestResult constructorFailTestResult = TestingNonDefaultTestResult();
      _testResultFactoryMock->MakeConstructorFailMock.Return(constructorFailTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      METALMOCKTHEN(p_stopwatchMock->StartMock.CalledOnce()).Then(

      METALMOCKTHEN(_testPhaseRunnerMock->RunTestPhaseMock.CalledOnceWith(
         &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor))).Then(

      METALMOCKTHEN(p_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(

      METALMOCKTHEN(_testResultFactoryMock->MakeConstructorFailMock.CalledOnceWith(
         _newableDeletableTest->p_fullTestName,
         failedConstructorTestPhaseResult,
         elapsedTestMilliseconds)));

      const vector<TestResult> expectedTestResults{ constructorFailTestResult };
      VECTORS_ARE_EQUAL(expectedTestResults, testResults);
   }

   TEST(RunTest_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsConstructorDestructorSuccessTestResult)
   {
      p_stopwatchMock->StartMock.Expect();

      TestPhaseResult successConstructorTestPhaseResult;
      successConstructorTestPhaseResult.testOutcome = TestOutcome::Success;

      TestPhaseResult destructorTestPhaseResult;
      _testPhaseRunnerMock->RunTestPhaseMock.ReturnValues(
         successConstructorTestPhaseResult,
         destructorTestPhaseResult);

      const unsigned short elapsedTestMilliseconds = p_stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();

      TestResult sixArgCtorTestResult = TestingNonDefaultTestResult();
      _testResultFactoryMock->MakeConstructorDestructorSuccessMock.Return(sixArgCtorTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      METALMOCK(_testPhaseRunnerMock->RunTestPhaseMock.CalledNTimes(2));

      METALMOCKTHEN(p_stopwatchMock->StartMock.CalledOnce()).Then(

      METALMOCKTHEN(_testPhaseRunnerMock->RunTestPhaseMock.CalledWith(
         &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor))).Then(

      METALMOCKTHEN(_testPhaseRunnerMock->RunTestPhaseMock.CalledWith(
         &Test::CallDeleteTestClass, _newableDeletableTest.get(), TestPhase::Destructor))).Then(

      METALMOCKTHEN(p_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(

      METALMOCKTHEN(_testResultFactoryMock->MakeConstructorDestructorSuccessMock.CalledOnceWith(
         _newableDeletableTest->p_fullTestName,
         successConstructorTestPhaseResult,
         destructorTestPhaseResult,
         elapsedTestMilliseconds)));

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

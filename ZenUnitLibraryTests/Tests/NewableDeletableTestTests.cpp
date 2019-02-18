#include "pch.h"
#include "ZenUnitLibraryTests/Results/Mock/TestResultFactoryMock.h"
#include "ZenUnitLibraryTests/TestRunners/Mock/TestPhaseRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Time/Mock/StopwatchMock.h"
#include "ZenUnitTestUtils/Equalizers/TestPhaseResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/FullTestNameEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"

namespace ZenUnit
{
   TESTS(NewableDeletableTestTests)
   AFACT(Constructor_NewsComponents)
   AFACT(NumberOfTestCases_Returns1)
   FACTS(RunTest_StartsStopWatch_CallsNewTestClassWhichFails_DoesNotCallDeleteTestClass_StopsStopwatch_ReturnsConstructorFailTestResult)
   AFACT(RunTest_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsCtorDtorSuccessTestResult)
   AFACT(NewAndDeleteTestClass_NewsAndDeleteFirstInstanceOfTestClass)
   EVIDENCE

   class TestingTestClass {};
   unique_ptr<NewableDeletableTest<TestingTestClass>> _newableDeletableTest;
   TestPhaseRunnerMock* _tryCatchCallerMock = nullptr;
   TestResultFactoryMock* _testResultFactoryMock = nullptr;
   StopwatchMock* _stopwatchMock = nullptr;
   const string TestClassName = Random<string>();

   STARTUP
   {
      _newableDeletableTest = make_unique<NewableDeletableTest<TestingTestClass>>(TestClassName.c_str());
      _newableDeletableTest->_testPhaseRunner.reset(_tryCatchCallerMock = new TestPhaseRunnerMock);
      _newableDeletableTest->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
      _newableDeletableTest->_stopwatch.reset(_stopwatchMock = new StopwatchMock);
   }

   TEST(Constructor_NewsComponents)
   {
      NewableDeletableTest<TestingTestClass> newableDeletableTest(TestClassName.c_str());
      ARE_EQUAL("TestClassIsNewableAndDeletable", newableDeletableTest.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST(TestClassIsNewableAndDeletable)", newableDeletableTest.FullTestNameValue());
      ARE_EQUAL("(0)", newableDeletableTest.FileLineString());
      POINTER_WAS_NEWED(newableDeletableTest._testResultFactory);
      POINTER_WAS_NEWED(newableDeletableTest._testPhaseRunner);
      POINTER_WAS_NEWED(newableDeletableTest._stopwatch);
      POINTER_IS_NULL(newableDeletableTest._firstInstanceOfTestClass);
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
      _stopwatchMock->StartMock.Expect();

      TestPhaseResult failedConstructorTestPhaseResult;
      failedConstructorTestPhaseResult.testOutcome = nonSuccessOutcome;
      _tryCatchCallerMock->RunTestPhaseMock.Return(failedConstructorTestPhaseResult);

      const unsigned microseconds = _stopwatchMock->StopMock.ReturnRandom();

      TestResult constructorFailTestResult = TestResult::TestingNonDefault();
      constructorFailTestResult.microseconds = microseconds;
      _testResultFactoryMock->MakeConstructorFailMock.Return(constructorFailTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      ZENMOCK(_stopwatchMock->StartMock.CalledOnce());
      ZENMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledOnceWith(
         &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor));
      ZENMOCK(_testResultFactoryMock->MakeConstructorFailMock.CalledOnceWith(
         _newableDeletableTest->p_fullTestName, failedConstructorTestPhaseResult));
      const vector<TestResult> expectedTestResults{ constructorFailTestResult };
      ZENMOCK(_stopwatchMock->StopMock.CalledOnce());
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(RunTest_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsCtorDtorSuccessTestResult)
   {
      _stopwatchMock->StartMock.Expect();

      TestPhaseResult successConstructorTestPhaseResult;
      successConstructorTestPhaseResult.testOutcome = TestOutcome::Success;

      TestPhaseResult destructorTestPhaseResult;
      _tryCatchCallerMock->RunTestPhaseMock.ReturnValues(successConstructorTestPhaseResult, destructorTestPhaseResult);

      const unsigned microseconds = _stopwatchMock->StopMock.ReturnRandom();

      TestResult sixArgCtorTestResult = TestResult::TestingNonDefault();
      sixArgCtorTestResult.microseconds = microseconds;
      _testResultFactoryMock->MakeCtorDtorSuccessMock.Return(sixArgCtorTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      ZENMOCK(_stopwatchMock->StartMock.CalledOnce());
      ZENMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledAsFollows(
      {
         { &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor },
         { &Test::CallDeleteTestClass, _newableDeletableTest.get(), TestPhase::Destructor }
      }));
      ZENMOCK(_testResultFactoryMock->MakeCtorDtorSuccessMock.CalledOnceWith(
         _newableDeletableTest->p_fullTestName, successConstructorTestPhaseResult, destructorTestPhaseResult));
      ZENMOCK(_stopwatchMock->StopMock.CalledOnce());
      const vector<TestResult> expectedTestResults{ sixArgCtorTestResult };
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(NewAndDeleteTestClass_NewsAndDeleteFirstInstanceOfTestClass)
   {
      POINTER_IS_NULL(_newableDeletableTest->_firstInstanceOfTestClass);
      //
      _newableDeletableTest->NewTestClass();
      //
      POINTER_IS_NOT_NULL(_newableDeletableTest->_firstInstanceOfTestClass);
      //
      _newableDeletableTest->DeleteTestClass();
      //
      POINTER_IS_NULL(_newableDeletableTest->_firstInstanceOfTestClass);
   }

   RUN_TESTS(NewableDeletableTestTests)
}

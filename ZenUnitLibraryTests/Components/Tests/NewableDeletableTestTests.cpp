#include "pch.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultFactoryMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestPhaseRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/StopwatchMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/TestingNonDefaultTestResult.h"

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
   StopwatchMock* _stopwatchMock = nullptr;
   const string TestClassName = Random<string>();

   STARTUP
   {
      _newableDeletableTest = make_unique<NewableDeletableTest<TestingTestClass>>(TestClassName.c_str());
      _newableDeletableTest->_testPhaseRunner.reset(_tryCatchCallerMock = new TestPhaseRunnerMock);
      _newableDeletableTest->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
      _newableDeletableTest->_testPhaseStopwatch.reset(_stopwatchMock = new StopwatchMock);
   }

   TEST(Constructor_NewsComponents)
   {
      NewableDeletableTest<TestingTestClass> newableDeletableTest(TestClassName.c_str());
      ARE_EQUAL("TestClassIsNewableAndDeletable", newableDeletableTest.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST(TestClassIsNewableAndDeletable)", newableDeletableTest.FullName());
      ARE_EQUAL("(0)", newableDeletableTest.FilePathLineNumberString());
      DELETE_TO_ASSERT_NEWED(newableDeletableTest._testResultFactory);
      DELETE_TO_ASSERT_NEWED(newableDeletableTest._testPhaseRunner);
      DELETE_TO_ASSERT_NEWED(newableDeletableTest._testPhaseStopwatch);
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
      _stopwatchMock->StartMock.Expect();

      TestPhaseResult failedConstructorTestPhaseResult;
      failedConstructorTestPhaseResult.testOutcome = nonSuccessOutcome;
      _tryCatchCallerMock->RunTestPhaseMock.Return(failedConstructorTestPhaseResult);

      const long long microseconds = _stopwatchMock->GetElapsedMicrosecondsThenResetStopwatchMock.ReturnRandom();

      TestResult constructorFailTestResult = TestingNonDefaultTestResult();
      constructorFailTestResult.microseconds = microseconds;
      _testResultFactoryMock->MakeConstructorFailMock.Return(constructorFailTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      METALMOCK(_stopwatchMock->StartMock.CalledOnce());
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledOnceWith(
         &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor));
      METALMOCK(_testResultFactoryMock->MakeConstructorFailMock.CalledOnceWith(
         _newableDeletableTest->_protected_fullTestName, failedConstructorTestPhaseResult));
      const vector<TestResult> expectedTestResults{ constructorFailTestResult };
      METALMOCK(_stopwatchMock->GetElapsedMicrosecondsThenResetStopwatchMock.CalledOnce());
      VECTORS_ARE_EQUAL(expectedTestResults, testResults);
   }

   TEST(RunTest_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsConstructorDestructorSuccessTestResult)
   {
      _stopwatchMock->StartMock.Expect();

      TestPhaseResult successConstructorTestPhaseResult;
      successConstructorTestPhaseResult.testOutcome = TestOutcome::Success;

      TestPhaseResult destructorTestPhaseResult;
      _tryCatchCallerMock->RunTestPhaseMock.ReturnValues(successConstructorTestPhaseResult, destructorTestPhaseResult);

      const long long microseconds = _stopwatchMock->GetElapsedMicrosecondsThenResetStopwatchMock.ReturnRandom();

      TestResult sixArgCtorTestResult = TestingNonDefaultTestResult();
      sixArgCtorTestResult.microseconds = microseconds;
      _testResultFactoryMock->MakeConstructorDestructorSuccessMock.Return(sixArgCtorTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      METALMOCK(_stopwatchMock->StartMock.CalledOnce());
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledAsFollows(
      {
         { &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor },
         { &Test::CallDeleteTestClass, _newableDeletableTest.get(), TestPhase::Destructor }
      }));
      METALMOCK(_testResultFactoryMock->MakeConstructorDestructorSuccessMock.CalledOnceWith(
         _newableDeletableTest->_protected_fullTestName, successConstructorTestPhaseResult, destructorTestPhaseResult));
      METALMOCK(_stopwatchMock->GetElapsedMicrosecondsThenResetStopwatchMock.CalledOnce());
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

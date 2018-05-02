#include "pch.h"
#include "ZenUnitTests/TestRunners/Mock/TryCatchCallerMock.h"
#include "ZenUnitTests/Results/Mock/TestResultFactoryMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"

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
   TryCatchCallerMock* _tryCatchCallerMock = nullptr;
   TestResultFactoryMock* _testResultFactoryMock = nullptr;
   StopwatchMock* _stopwatchMock = nullptr;
   const string TestClassName = Random<string>();

   STARTUP
   {
      _newableDeletableTest = make_unique<NewableDeletableTest<TestingTestClass>>(TestClassName.c_str());
      _newableDeletableTest->_tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock);
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
      POINTER_WAS_NEWED(newableDeletableTest._tryCatchCaller);
      POINTER_WAS_NEWED(newableDeletableTest._stopwatch);
      IS_NULL(newableDeletableTest._firstInstanceOfTestClass);
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

      CallResult failedConstructorCallResult;
      failedConstructorCallResult.testOutcome = nonSuccessOutcome;
      _tryCatchCallerMock->CallMock.Return(failedConstructorCallResult);

      const unsigned microseconds = _stopwatchMock->StopMock.ReturnRandom();

      TestResult constructorFailTestResult = TestResult::TestingNonDefault();
      constructorFailTestResult.microseconds = microseconds;
      _testResultFactoryMock->ConstructorFailMock.Return(constructorFailTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      ZEN(_stopwatchMock->StartMock.CalledOnce());
      ZEN(_tryCatchCallerMock->CallMock.CalledOnceWith(
         &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor));
      ZEN(_testResultFactoryMock->ConstructorFailMock.CalledOnceWith(
         _newableDeletableTest->p_fullTestName, failedConstructorCallResult));
      const vector<TestResult> expectedTestResults{ constructorFailTestResult };
      ZEN(_stopwatchMock->StopMock.CalledOnce());
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(RunTest_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsCtorDtorSuccessTestResult)
   {
      _stopwatchMock->StartMock.Expect();

      CallResult successConstructorCallResult;
      successConstructorCallResult.testOutcome = TestOutcome::Success;

      CallResult destructorCallResult;
      _tryCatchCallerMock->CallMock.ReturnValues(successConstructorCallResult, destructorCallResult);

      const unsigned microseconds = _stopwatchMock->StopMock.ReturnRandom();

      TestResult sixArgCtorTestResult = TestResult::TestingNonDefault();
      sixArgCtorTestResult.microseconds = microseconds;
      _testResultFactoryMock->CtorDtorSuccessMock.Return(sixArgCtorTestResult);
      //
      const vector<TestResult> testResults = _newableDeletableTest->RunTest();
      //
      ZEN(_stopwatchMock->StartMock.CalledOnce());
      ZEN(_tryCatchCallerMock->CallMock.CalledAsFollows(
      {
         { &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor },
         { &Test::CallDeleteTestClass, _newableDeletableTest.get(), TestPhase::Destructor }
      }));
      ZEN(_testResultFactoryMock->CtorDtorSuccessMock.CalledOnceWith(
         _newableDeletableTest->p_fullTestName, successConstructorCallResult, destructorCallResult));
      ZEN(_stopwatchMock->StopMock.CalledOnce());
      const vector<TestResult> expectedTestResults{ sixArgCtorTestResult };
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(NewAndDeleteTestClass_NewsAndDeleteFirstInstanceOfTestClass)
   {
      IS_NULL(_newableDeletableTest->_firstInstanceOfTestClass);
      //
      _newableDeletableTest->NewTestClass();
      //
      IS_NOT_NULL(_newableDeletableTest->_firstInstanceOfTestClass);
      //
      _newableDeletableTest->DeleteTestClass();
      //
      IS_NULL(_newableDeletableTest->_firstInstanceOfTestClass);
   }

   RUN_TESTS(NewableDeletableTestTests)
}

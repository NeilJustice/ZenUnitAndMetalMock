#include "pch.h"
#include "ZenUnitTests/Results/Mock/TestResultFactoryMock.h"
#include "ZenUnitTests/TestRunners/Mock/TryCatchCallerMock.h"

namespace ZenUnit
{
   TESTS(NewDeleteTestTests)
   AFACT(Constructor_NewsComponents)
   AFACT(NumberOfTestCases_Returns1)
   FACTS(Run_CallsNewTestClassWhichFails_DoesNotCallDeleteTestClass_ReturnsConstructorFailTestResult)
   AFACT(Run_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_ReturnsCtorDtorSuccessTestResult)
   AFACT(NewAndDeleteTestClass_NewsAndDeleteFirstInstanceOfTestClass)
   EVIDENCE

   class TestingTestClass {};
   unique_ptr<NewDeleteTest<TestingTestClass>> _newDeleteTest;
   TryCatchCallerMock* _tryCatchCallerMock;
   TestResultFactoryMock* _testResultFactoryMock;
   const string TestClassName = Random<string>();

   STARTUP
   {
      _newDeleteTest = make_unique<NewDeleteTest<TestingTestClass>>(TestClassName.c_str());
      _newDeleteTest->_tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock);
      _newDeleteTest->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(Constructor_NewsComponents)
   {
      NewDeleteTest<TestingTestClass> newDeleteTest(TestClassName.c_str());
      ARE_EQUAL("TestClassIsNewableAndDeletable", newDeleteTest.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST(TestClassIsNewableAndDeletable)", newDeleteTest.FullTestNameValue());
      ARE_EQUAL("(0)", newDeleteTest.FileLineString());
      POINTER_WAS_NEWED(newDeleteTest._testResultFactory);
      POINTER_WAS_NEWED(newDeleteTest._tryCatchCaller);
      IS_NULL(newDeleteTest._firstInstanceOfTestClass);
   }

   TEST(NumberOfTestCases_Returns1)
   {
      ARE_EQUAL(1, _newDeleteTest->NumberOfTestCases());
   }

   TEST1X1(Run_CallsNewTestClassWhichFails_DoesNotCallDeleteTestClass_ReturnsConstructorFailTestResult,
      TestOutcome nonSuccessOutcome,
      TestOutcome::Anomaly,
      TestOutcome::Exception)
   {
      CallResult failedConstructorCallResult;
      failedConstructorCallResult.testOutcome = nonSuccessOutcome;
      _tryCatchCallerMock->CallMock.ExpectAndReturn(failedConstructorCallResult);

      const TestResult constructorFailTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->ConstructorFailMock.ExpectAndReturn(constructorFailTestResult);
      //
      const vector<TestResult> testResults = _newDeleteTest->Run();
      //
      ZEN(_tryCatchCallerMock->CallMock.AssertCalledOnceWith(
         &Test::CallNewTestClass, _newDeleteTest.get(), TestPhase::Constructor));
      ZEN(_testResultFactoryMock->ConstructorFailMock.AssertCalledOnceWith(
         _newDeleteTest->_fullTestName, failedConstructorCallResult));
      const vector<TestResult> expectedTestResults { constructorFailTestResult };
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(Run_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_ReturnsCtorDtorSuccessTestResult)
   {
      CallResult successConstructorCallResult;
      successConstructorCallResult.testOutcome = TestOutcome::Success;

      CallResult destructorCallResult;
      _tryCatchCallerMock->CallMock.ExpectAndReturnValues(successConstructorCallResult, destructorCallResult);

      const TestResult sixArgCtorTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->CtorDtorSuccessMock.ExpectAndReturn(sixArgCtorTestResult);
      //
      const vector<TestResult> testResults = _newDeleteTest->Run();
      //
      ZEN(_tryCatchCallerMock->CallMock.AssertCalls(
      {
         { &Test::CallNewTestClass, _newDeleteTest.get(), TestPhase::Constructor },
         { &Test::CallDeleteTestClass, _newDeleteTest.get(), TestPhase::Destructor }
      }));
      ZEN(_testResultFactoryMock->CtorDtorSuccessMock.AssertCalledOnceWith(
         _newDeleteTest->_fullTestName, successConstructorCallResult, destructorCallResult));
      const vector<TestResult> expectedTestResults { sixArgCtorTestResult };
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(NewAndDeleteTestClass_NewsAndDeleteFirstInstanceOfTestClass)
   {
      IS_NULL(_newDeleteTest->_firstInstanceOfTestClass);
      //
      _newDeleteTest->NewTestClass();
      //
      IS_NOT_NULL(_newDeleteTest->_firstInstanceOfTestClass);
      //
      _newDeleteTest->DeleteTestClass();
      //
      IS_NULL(_newDeleteTest->_firstInstanceOfTestClass);
   }

   }; RUNTESTS(NewDeleteTestTests)
}

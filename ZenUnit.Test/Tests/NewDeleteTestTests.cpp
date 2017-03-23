#include "pch.h"
#include "ZenUnit/Tests/NewDeleteTest.h"
#include "TestRunners/Mock/TryCatchCallerMock.h"
#include "Results/Mock/TestResultFactoryMock.h"

namespace ZenUnit
{
   TESTS(NewDeleteTestTests)
   SPEC(Constructor_NewsComponents)
   SPEC(NumberOfTestCases_Returns1)
   SPECX(Run_CallsNewTestClassWhichFails_DoesNotCallDeleteTestClass_ReturnsConstructorFailTestResult)
   SPEC(Run_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_ReturnsCtorDtorSuccessTestResult)
   SPEC(NewAndDeleteTestClass_NewsAndDeleteFirstInstanceOfTestClass)
   SPEC(StartupTestBodyCleanup_EachDoNothing)
   SPECEND

   class TestingTestClass {};
   unique_ptr<NewDeleteTest<TestingTestClass>> _newDeleteTest;
   TryCatchCallerMock* _tryCatchCallerMock;
   TestResultFactoryMock* _testResultFactoryMock;
   const char* TestClassName = "TestClassName";

   STARTUP
   {
      _newDeleteTest.reset(new NewDeleteTest<TestingTestClass>(TestClassName));
      _newDeleteTest->_tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock);
      _newDeleteTest->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(Constructor_NewsComponents)
   {
      NewDeleteTest<TestingTestClass> newDeleteTest(TestClassName);
      ARE_EQUAL("ImplicitFirstTestForNewabilityAndDeletability", newDeleteTest.Name());
      ARE_EQUAL("TESTS(TestClassName)\nTEST(ImplicitFirstTestForNewabilityAndDeletability)", newDeleteTest.TestClassTestNameLines());
      ARE_EQUAL("(0)", newDeleteTest.FileLineString());
      WAS_NEWED(newDeleteTest._testResultFactory);
      WAS_NEWED(newDeleteTest._tryCatchCaller);
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

      TestResult constructorFailTestResult;
      _testResultFactoryMock->ConstructorFailMock.ExpectAndReturn(constructorFailTestResult);
      //
      vector<TestResult> testResults = _newDeleteTest->Run();
      //
      ZEN(_tryCatchCallerMock->CallMock.AssertCalledOnceWith(
         &Test::CallNewTestClass, _newDeleteTest.get(), TestPhase::Constructor));
      ZEN(_testResultFactoryMock->ConstructorFailMock.AssertCalledOnceWith(
         _newDeleteTest->_fullName, failedConstructorCallResult));
      vector<TestResult> expectedTestResults = { constructorFailTestResult };
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(Run_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_ReturnsCtorDtorSuccessTestResult)
   {
      CallResult successConstructorCallResult;
      successConstructorCallResult.testOutcome = TestOutcome::Success;

      CallResult destructorCallResult;
      _tryCatchCallerMock->CallMock.ExpectAndReturnValues(successConstructorCallResult, destructorCallResult);

      TestResult sixArgCtorTestResult = TestResult::TestingNonDefault;
      _testResultFactoryMock->CtorDtorSuccessMock.ExpectAndReturn(sixArgCtorTestResult);
      //
      vector<TestResult> testResults = _newDeleteTest->Run();
      //
      ZEN(_tryCatchCallerMock->CallMock.AssertCalls(
      {
         { &Test::CallNewTestClass, _newDeleteTest.get(), TestPhase::Constructor },
         { &Test::CallDeleteTestClass, _newDeleteTest.get(), TestPhase::Destructor }
      }));
      ZEN(_testResultFactoryMock->CtorDtorSuccessMock.AssertCalledOnceWith(
         _newDeleteTest->_fullName, successConstructorCallResult, destructorCallResult));
      vector<TestResult> expectedTestResults = { sixArgCtorTestResult };
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

   TEST(StartupTestBodyCleanup_EachDoNothing)
   {
      _newDeleteTest->Startup();
      _newDeleteTest->TestBody();
      _newDeleteTest->Cleanup();
   }

   }; RUN(NewDeleteTestTests)
}

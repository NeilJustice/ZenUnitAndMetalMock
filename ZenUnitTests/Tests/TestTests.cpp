#include "pch.h"
#include "ZenUnit/Tests/FullTestName.h"
#include "ZenUnit/Tests/Test.h"
#include "ZenUnit/Utils/Random.h"
#include "ZenUnitTests/Results/Mock/TestResultFactoryMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/TestRunners/Mock/TryCatchCallerMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"

namespace ZenUnit
{
   TESTS(TestTests)
   FACT(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   FACTS(RunTestCase_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail)
   FACTS(RunTestCase_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail)
   FACT(RunTestCase_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   FACT(NonMinimalWritePostTestNameMessage_DoesNothing)
   FACT(PrintPostTestCompletionMessage_DoesNothing)
   FACT(StaticCallNewTestClass_CallsNewTestClass)
   FACT(StaticCallStartup_CallsStartup)
   FACT(StaticTestBody_CallsTestBody)
   FACT(StaticCallCleanup_CallsCleanup)
   FACT(StaticCallDeleteTestClass_CallsDeleteTestClass)
   FACT(PseudoAbstractFunctions_DoNothingOrReturn0)
   EVIDENCE

   unique_ptr<Test> _test;
   TryCatchCallerMock* _tryCatchCallerMock;
   TestResultFactoryMock* _testResultFactoryMock;
   TestMock _testMock;

   STARTUP
   {
      _test = make_unique<Test>("", "", static_cast<unsigned char>(0));
      _test->_tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock);
      _test->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   {
      const string TestClassName = Random<string>();
      const string TestName = Random<string>();
      //
      Test test(TestClassName.c_str(), TestName.c_str(), 0);
      POINTER_WAS_NEWED(test._tryCatchCaller);
      POINTER_WAS_NEWED(test._testResultFactory);
      ARE_EQUAL(FileLine(), test._fileLine);

      const char* const testName = test.Name();
      ARE_EQUAL(TestName.c_str(), testName);

      const string fullTestName = test.FullTestNameValue();
      ARE_EQUAL(fullTestName, test._fullTestName.Value());

      test._fileLine = FileLine("FilePath", 1);
      ARE_EQUAL(test._fileLine.ToString(), test.FileLineString());
   }

   TEST(NonMinimalWritePostTestNameMessage_DoesNothing)
   {
      _test->NonMinimalWritePostTestNameMessage(nullptr, PrintMode::Minimalist);
      _test->NonMinimalWritePostTestNameMessage(nullptr, PrintMode::Normal);
      _test->NonMinimalWritePostTestNameMessage(nullptr, PrintMode::Detailed);
   }

   TEST(PrintPostTestCompletionMessage_DoesNothing)
   {
      TestResultMock testResultMock;
      _test->NonMinimalWritePostTestCompletionMessage(nullptr, testResultMock, PrintMode::Minimalist);
      _test->NonMinimalWritePostTestCompletionMessage(nullptr, testResultMock, PrintMode::Normal);
      _test->NonMinimalWritePostTestCompletionMessage(nullptr, testResultMock, PrintMode::Detailed);
   }

   static CallResult CallResultWithOutcome(TestOutcome testOutcome)
   {
      CallResult callResult;
      callResult.testOutcome = testOutcome;
      return callResult;
   }

   TEST1X1(RunTestCase_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail,
      TestOutcome constructorOutcome, TestOutcome::Anomaly, TestOutcome::Exception)
   {
      const CallResult constructorFailCallResult = CallResultWithOutcome(constructorOutcome);
      _tryCatchCallerMock->CallMock.ExpectAndReturn(constructorFailCallResult);

      const TestResult constructorFailTestResult = TestResult::TestingNonDefault;
      _testResultFactoryMock->ConstructorFailMock.ExpectAndReturn(constructorFailTestResult);
      //
      const TestResult testResult = _test->RunTestCase();
      //
      ZEN(_tryCatchCallerMock->CallMock.AssertCalledOnceWith(
         &Test::CallNewTestClass, _test.get(), TestPhase::Constructor));
      ZEN(_testResultFactoryMock->ConstructorFailMock.AssertCalledOnceWith(
         _test->_fullTestName, constructorFailCallResult));
      ARE_EQUAL(constructorFailTestResult, testResult);
   }

   TEST1X1(RunTestCase_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail,
      TestOutcome startupOutcome,
      TestOutcome::Anomaly,
      TestOutcome::Exception)
   {
      const CallResult constructorSuccessCallResult = CallResultWithOutcome(TestOutcome::Success);
      const CallResult startupFailCallResult = CallResultWithOutcome(startupOutcome);
      const CallResult destructorCallResult = CallResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->CallMock.ExpectAndReturnValues(constructorSuccessCallResult, startupFailCallResult, destructorCallResult);

      const TestResult startupFailTestResult = TestResult::TestingNonDefault;
      _testResultFactoryMock->StartupFailMock.ExpectAndReturn(startupFailTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->RunTestCase();
      //
      ZEN(_tryCatchCallerMock->CallMock.AssertCalls(
      {
         { &Test::CallNewTestClass, _test.get(), TestPhase::Constructor },
         { &Test::CallStartup, _test.get(), TestPhase::Startup },
         { &Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor }
      }));
      ZEN(_testResultFactoryMock->StartupFailMock.AssertCalledOnceWith(
         _test->_fullTestName, constructorSuccessCallResult, startupFailCallResult, destructorCallResult));
      ARE_EQUAL(startupFailTestResult, testResult);
   }

   TEST(RunTestCase_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   {
      const CallResult successCallResult = CallResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->CallMock.ExpectAndReturn(successCallResult);

      const TestResult sixArgTestResult = TestResult::TestingNonDefault;
      _testResultFactoryMock->FullCtorMock.ExpectAndReturn(sixArgTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->RunTestCase();
      //
      ZEN(_tryCatchCallerMock->CallMock.AssertCalls(
      {
         { &Test::CallNewTestClass, _test.get(), TestPhase::Constructor },
         { &Test::CallStartup, _test.get(), TestPhase::Startup },
         { &Test::CallTestBody, _test.get(), TestPhase::TestBody },
         { &Test::CallCleanup, _test.get(), TestPhase::Cleanup },
         { &Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor }
      }));
      ZEN(_testResultFactoryMock->FullCtorMock.AssertCalledOnceWith(
         _test->_fullTestName,
         CallResultWithOutcome(TestOutcome::Success),
         CallResultWithOutcome(TestOutcome::Success),
         CallResultWithOutcome(TestOutcome::Success),
         CallResultWithOutcome(TestOutcome::Success),
         CallResultWithOutcome(TestOutcome::Success)));
      ARE_EQUAL(testResult, sixArgTestResult);
   }

   TEST(StaticCallNewTestClass_CallsNewTestClass)
   {
      _testMock.NewTestClassMock.Expect();
      //
      Test::CallNewTestClass(&_testMock);
      //
      ZEN(_testMock.NewTestClassMock.AssertCalledOnce());
   }

   TEST(StaticCallStartup_CallsStartup)
   {
      _testMock.StartupMock.Expect();
      //
      Test::CallStartup(&_testMock);
      //
      ZEN(_testMock.StartupMock.AssertCalledOnce());
   }

   TEST(StaticTestBody_CallsTestBody)
   {
      _testMock.TestBodyMock.Expect();
      //
      Test::CallTestBody(&_testMock);
      //
      ZEN(_testMock.TestBodyMock.AssertCalledOnce());
   }

   TEST(StaticCallCleanup_CallsCleanup)
   {
      _testMock.CleanupMock.Expect();
      //
      Test::CallCleanup(&_testMock);
      //
      ZEN(_testMock.CleanupMock.AssertCalledOnce());
   }

   TEST(StaticCallDeleteTestClass_CallsDeleteTestClass)
   {
      _testMock.DeleteTestClassMock.Expect();
      //
      Test::CallDeleteTestClass(&_testMock);
      //
      ZEN(_testMock.DeleteTestClassMock.AssertCalledOnce());
   }

   TEST(PseudoAbstractFunctions_DoNothingOrReturn0)
   {
      Test test("", "", 0);
      ARE_EQUAL(0, test.NumberOfTestCases());
      IS_EMPTY(test.Run());
      test.NewTestClass();
      test.Startup();
      test.TestBody();
      test.Cleanup();
      test.DeleteTestClass();
   }

   RUNTESTS(TestTests)
}

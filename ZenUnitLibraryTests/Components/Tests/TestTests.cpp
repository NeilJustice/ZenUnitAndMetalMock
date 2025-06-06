#include "pch.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultFactoryMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestPhaseRunnerMock.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/TestMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(TestTests)
   AFACT(TwoArgConstructor_NewsComponents_NameFunctionReturnsTestName)
   FACTS(BaseRunTest_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail)
   FACTS(BaseRunTest_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail)
   AFACT(BaseRunTest_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   AFACT(WritePostTestNameMessage_DoesNotThrowException)
   AFACT(PrintPostTestCompletionMessage_DoesNotThrowException)
   AFACT(StaticCallNewTestClass_CallsNewTestClass)
   AFACT(StaticCallStartup_CallsStartup)
   AFACT(StaticTestBody_CallsTestBody)
   AFACT(StaticCallCleanup_CallsCleanup)
   AFACT(StaticCallDeleteTestClass_CallsDeleteTestClass)
   AFACT(PseudoAbstractFunctions_DoNothingOrReturn0)
   EVIDENCE

   unique_ptr<Test> _test;
   TestPhaseRunnerMock* _tryCatchCallerMock = nullptr;
   TestResultFactoryMock* _testResultFactoryMock = nullptr;
   TestMock _testMock;

   STARTUP
   {
      _test = make_unique<Test>("", "", static_cast<unsigned char>(0));
      _test->_testPhaseRunner.reset(_tryCatchCallerMock = new TestPhaseRunnerMock);
      _test->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(TwoArgConstructor_NewsComponents_NameFunctionReturnsTestName)
   {
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      //
      Test test(testClassName.c_str(), testName.c_str(), 0);
      DELETE_TO_ASSERT_NEWED(test._testPhaseRunner);
      DELETE_TO_ASSERT_NEWED(test._testResultFactory);
      ARE_EQUAL(FilePathLineNumber(), test.p_fileLine);

      const char* const testNameValue = test.Name();
      ARE_EQUAL(testName.c_str(), testNameValue);
   }

   TEST(WritePostTestNameMessage_DoesNotThrowException)
   {
      _test->WritePostTestNameMessage(nullptr);
      _test->WritePostTestNameMessage(nullptr);
   }

   TEST(PrintPostTestCompletionMessage_DoesNotThrowException)
   {
      TestResultMock testResultMock;
      _test->WritePostTestCompletionMessage(nullptr, testResultMock);
      _test->WritePostTestCompletionMessage(nullptr, testResultMock);
   }

   static TestPhaseResult TestPhaseResultWithOutcome(TestOutcome testOutcome)
   {
      TestPhaseResult testPhaseResult;
      testPhaseResult.testOutcome = testOutcome;
      return testPhaseResult;
   }

   TEST1X1(BaseRunTest_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail,
      TestOutcome constructorOutcome, TestOutcome::Anomaly, TestOutcome::Exception)
   {
      const TestPhaseResult constructorFailTestPhaseResult = TestPhaseResultWithOutcome(constructorOutcome);
      _tryCatchCallerMock->RunTestPhaseMock.Return(constructorFailTestPhaseResult);

      const TestResult constructorFailTestResult = TestingNonDefaultTestResult();
      _testResultFactoryMock->MakeConstructorFailMock.Return(constructorFailTestResult);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledOnceWith(&Test::CallNewTestClass, _test.get(), TestPhase::Constructor));
      METALMOCK(_testResultFactoryMock->MakeConstructorFailMock.CalledOnceWith(_test->p_fullTestName, constructorFailTestPhaseResult));
      ARE_EQUAL(constructorFailTestResult, testResult);
   }

   TEST1X1(BaseRunTest_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail,
      TestOutcome startupOutcome,
      TestOutcome::Anomaly,
      TestOutcome::Exception)
   {
      const TestPhaseResult constructorSuccessTestPhaseResult = TestPhaseResultWithOutcome(TestOutcome::Success);
      const TestPhaseResult startupFailTestPhaseResult = TestPhaseResultWithOutcome(startupOutcome);
      const TestPhaseResult destructorTestPhaseResult = TestPhaseResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->RunTestPhaseMock.ReturnValues(constructorSuccessTestPhaseResult, startupFailTestPhaseResult, destructorTestPhaseResult);

      const TestResult startupFailTestResult = TestingNonDefaultTestResult();
      _testResultFactoryMock->MakeStartupFailMock.Return(startupFailTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->p_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledNTimes(3));
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(&Test::CallNewTestClass, _test.get(), TestPhase::Constructor)).Then(
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(&Test::CallStartup, _test.get(), TestPhase::Startup))).Then(
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(&Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor))).Then(
      METALMOCKTHEN(_testResultFactoryMock->MakeStartupFailMock.CalledOnceWith(
         _test->p_fullTestName, constructorSuccessTestPhaseResult, startupFailTestPhaseResult, destructorTestPhaseResult)));
      ARE_EQUAL(startupFailTestResult, testResult);
   }

   TEST(BaseRunTest_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   {
      const TestPhaseResult successTestPhaseResult = TestPhaseResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->RunTestPhaseMock.Return(successTestPhaseResult);

      const TestResult sixArgTestResult = TestingNonDefaultTestResult();
      _testResultFactoryMock->MakeFullTestResultMock.Return(sixArgTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->p_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledNTimes(5));
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(&Test::CallNewTestClass, _test.get(), TestPhase::Constructor)).Then(
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(&Test::CallStartup, _test.get(), TestPhase::Startup))).Then(
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(&Test::CallTestBody, _test.get(), TestPhase::TestBody))).Then(
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(&Test::CallCleanup, _test.get(), TestPhase::Cleanup))).Then(
      METALMOCKTHEN(_tryCatchCallerMock->RunTestPhaseMock.CalledWith(&Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor))).Then(
      METALMOCKTHEN(_testResultFactoryMock->MakeFullTestResultMock.CalledOnceWith(
         _test->p_fullTestName,
         TestPhaseResultWithOutcome(TestOutcome::Success),
         TestPhaseResultWithOutcome(TestOutcome::Success),
         TestPhaseResultWithOutcome(TestOutcome::Success),
         TestPhaseResultWithOutcome(TestOutcome::Success),
         TestPhaseResultWithOutcome(TestOutcome::Success))));
      ARE_EQUAL(testResult, sixArgTestResult);
   }

   TEST(StaticCallNewTestClass_CallsNewTestClass)
   {
      _testMock.NewTestClassMock.Expect();
      //
      Test::CallNewTestClass(&_testMock);
      //
      METALMOCK(_testMock.NewTestClassMock.CalledOnce());
   }

   TEST(StaticCallStartup_CallsStartup)
   {
      _testMock.StartupMock.Expect();
      //
      Test::CallStartup(&_testMock);
      //
      METALMOCK(_testMock.StartupMock.CalledOnce());
   }

   TEST(StaticTestBody_CallsTestBody)
   {
      _testMock.TestBodyMock.Expect();
      //
      Test::CallTestBody(&_testMock);
      //
      METALMOCK(_testMock.TestBodyMock.CalledOnce());
   }

   TEST(StaticCallCleanup_CallsCleanup)
   {
      _testMock.CleanupMock.Expect();
      //
      Test::CallCleanup(&_testMock);
      //
      METALMOCK(_testMock.CleanupMock.CalledOnce());
   }

   TEST(StaticCallDeleteTestClass_CallsDeleteTestClass)
   {
      _testMock.DeleteTestClassMock.Expect();
      //
      Test::CallDeleteTestClass(&_testMock);
      //
      METALMOCK(_testMock.DeleteTestClassMock.CalledOnce());
   }

   TEST(PseudoAbstractFunctions_DoNothingOrReturn0)
   {
      Test test("", "", 0);
      IS_ZERO(test.NumberOfTestCases());
      IS_EMPTY(test.RunTest());
      test.NewTestClass();
      test.Startup();
      test.TestBody();
      test.Cleanup();
      test.DeleteTestClass();
   }

   RUN_TESTS(TestTests)
}

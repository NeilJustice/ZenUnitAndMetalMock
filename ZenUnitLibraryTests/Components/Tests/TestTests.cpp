#include "pch.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultFactoryMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultMock.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestPhaseRunnerMock.h"
#include "ZenUnitLibraryTests/Components/Tests/MetalMock/TestMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizer.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(TestTests)
   AFACT(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   FACTS(BaseRunTest_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail)
   FACTS(BaseRunTest_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail)
   AFACT(BaseRunTest_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   AFACT(WritePostTestNameMessage_DoesNothing)
   AFACT(PrintPostTestCompletionMessage_DoesNothing)
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

   TEST(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   {
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      //
      Test test(testClassName.c_str(), testName.c_str(), 0);
      DELETE_TO_ASSERT_NEWED(test._testPhaseRunner);
      DELETE_TO_ASSERT_NEWED(test._testResultFactory);
      ARE_EQUAL(FilePathLineNumber(), test._protected_fileLine);

      const char* const testNameValue = test.Name();
      ARE_EQUAL(testName.c_str(), testNameValue);

      const string fullTestName = test.FullName();
      ARE_EQUAL(fullTestName, test._protected_fullTestName.Value());

      test._protected_fileLine = FilePathLineNumber("FilePath", 1);
      ARE_EQUAL(test._protected_fileLine.ToString(), test.FilePathLineNumberString());
   }

   TEST(WritePostTestNameMessage_DoesNothing)
   {
      _test->WritePostTestNameMessage(nullptr);
      _test->WritePostTestNameMessage(nullptr);
   }

   TEST(PrintPostTestCompletionMessage_DoesNothing)
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

      const TestResult constructorFailTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->MakeConstructorFailMock.Return(constructorFailTestResult);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledOnceWith(&Test::CallNewTestClass, _test.get(), TestPhase::Constructor));
      METALMOCK(_testResultFactoryMock->MakeConstructorFailMock.CalledOnceWith(_test->_protected_fullTestName, constructorFailTestPhaseResult));
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

      const TestResult startupFailTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->MakeStartupFailMock.Return(startupFailTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->_protected_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledAsFollows(
      {
         { &Test::CallNewTestClass, _test.get(), TestPhase::Constructor },
         { &Test::CallStartup, _test.get(), TestPhase::Startup },
         { &Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor }
      }));
      METALMOCK(_testResultFactoryMock->MakeStartupFailMock.CalledOnceWith(
         _test->_protected_fullTestName, constructorSuccessTestPhaseResult, startupFailTestPhaseResult, destructorTestPhaseResult));
      ARE_EQUAL(startupFailTestResult, testResult);
   }

   TEST(BaseRunTest_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   {
      const TestPhaseResult successTestPhaseResult = TestPhaseResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->RunTestPhaseMock.Return(successTestPhaseResult);

      const TestResult sixArgTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->MakeFullTestResultMock.Return(sixArgTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->_protected_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->BaseRunTest();
      //
      METALMOCK(_tryCatchCallerMock->RunTestPhaseMock.CalledAsFollows(
      {
         { &Test::CallNewTestClass, _test.get(), TestPhase::Constructor },
         { &Test::CallStartup, _test.get(), TestPhase::Startup },
         { &Test::CallTestBody, _test.get(), TestPhase::TestBody },
         { &Test::CallCleanup, _test.get(), TestPhase::Cleanup },
         { &Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor }
      }));
      METALMOCK(_testResultFactoryMock->MakeFullTestResultMock.CalledOnceWith(
         _test->_protected_fullTestName,
         TestPhaseResultWithOutcome(TestOutcome::Success),
         TestPhaseResultWithOutcome(TestOutcome::Success),
         TestPhaseResultWithOutcome(TestOutcome::Success),
         TestPhaseResultWithOutcome(TestOutcome::Success),
         TestPhaseResultWithOutcome(TestOutcome::Success)));
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
      ARE_EQUAL(0, test.NumberOfTestCases());
      IS_EMPTY(test.RunTest());
      test.NewTestClass();
      test.Startup();
      test.TestBody();
      test.Cleanup();
      test.DeleteTestClass();
   }

   RUN_TESTS(TestTests)
}

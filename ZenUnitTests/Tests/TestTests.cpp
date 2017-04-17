#include "pch.h"
#include "Mock/TestMock.h"
#include "Results/Mock/TestResultFactoryMock.h"
#include "Results/Mock/TestResultMock.h"
#include "TestRunners/Mock/TryCatchCallerMock.h"
#include "ZenUnit/Tests/FullName.h"
#include "ZenUnit/Tests/Test.h"

class TestingTest : public Test
{
public:
   TestingTest(const char* testClassName, const char* testName)
      : Test(testClassName, testName) {}

   size_t NumberOfTestCases() const override { return 0; }
   std::vector<TestResult> Run() override { return std::vector<TestResult>(); }
   void NewTestClass() override {}
   void Startup() override {}
   void TestBody() override {}
   void Cleanup() override {}
   void DeleteTestClass() override {}
};

namespace ZenUnit
{
   TESTS(TestTests)
   SPEC(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   SPECX(RunTestCase_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail)
   SPECX(RunTestCase_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail)
   SPEC(RunTestCase_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   SPEC(PrintPostTestNameMessage_DoesNothing)
   SPEC(PrintPostTestCompletionMessage_DoesNothing)
   SPEC(StaticCallNewTestClass_CallsNewTestClass)
   SPEC(StaticCallStartup_CallsStartup)
   SPEC(StaticTestBody_CallsTestBody)
   SPEC(StaticCallCleanup_CallsCleanup)
   SPEC(StaticCallDeleteTestClass_CallsDeleteTestClass)
   SPEC(TestingTestAbstractFunctions_CodeCoverage)
   SPECEND

   unique_ptr<TestingTest> _test;
   TryCatchCallerMock* _tryCatchCallerMock;
   TestResultFactoryMock* _testResultFactoryMock;
   TestMock _testMock;

   STARTUP
   {
      _test = make_unique<TestingTest>("", "");
      _test->_tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock);
      _test->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   {
      TestingTest testingTest("TestClass", "TestName");
      WAS_NEWED(testingTest._tryCatchCaller);
      WAS_NEWED(testingTest._testResultFactory);
      ARE_EQUAL(FileLine(), testingTest._fileLine);

      const char* const testName = testingTest.Name();
      ARE_EQUAL(testName, testingTest._fullName.testName);

      const string testsAndTestLines = testingTest.TestsAndTestLines();
      ARE_EQUAL(testsAndTestLines, testingTest._fullName.TestsAndTestLines());

      testingTest._fileLine = FileLine("FilePath", 1);
      ARE_EQUAL(testingTest._fileLine.ToString(), testingTest.FileLineString());
   }

   TEST(PrintPostTestNameMessage_DoesNothing)
   {
      _test->PrintPostTestNameMessage(nullptr);
   }

   TEST(PrintPostTestCompletionMessage_DoesNothing)
   {
      TestResultMock testResultMock;
      _test->PrintPostTestCompletionMessage(nullptr, testResultMock);
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
         _test->_fullName, constructorFailCallResult));
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
      _test->_fullName = FullName("Non", "Default");
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
         _test->_fullName, constructorSuccessCallResult, startupFailCallResult, destructorCallResult));
      ARE_EQUAL(startupFailTestResult, testResult);
   }

   TEST(RunTestCase_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   {
      const CallResult successCallResult = CallResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->CallMock.ExpectAndReturn(successCallResult);

      const TestResult sixArgTestResult = TestResult::TestingNonDefault;
      _testResultFactoryMock->FullCtorMock.ExpectAndReturn(sixArgTestResult);
      _test->_fullName = FullName("Non", "Default");
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
         _test->_fullName,
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

   TEST(TestingTestAbstractFunctions_CodeCoverage)
   {
      TestingTest testingTest("", "");
      ARE_EQUAL(0, testingTest.NumberOfTestCases());
      IS_EMPTY(testingTest.Run());
      testingTest.NewTestClass();
      testingTest.Startup();
      testingTest.TestBody();
      testingTest.Cleanup();
      testingTest.DeleteTestClass();
   }

   }; RUN(TestTests)
}

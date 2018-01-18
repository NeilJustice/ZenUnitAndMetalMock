#include "pch.h"

// Windows-only tests until Travis CI no longer runs out of memory
#if _WIN32

namespace ZenUnit
{
   TESTS(FullTestNameTests)
   AFACT(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   AFACT(ThreeArgConstructor_SetsFields)
   FACTS(Value_ReturnsExpected)
   AFACT(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   EVIDENCE

   TEST(DefaultConstructor_SetsClassNameAndTestNameToNullptr)
   {
      const FullTestName defaultTestName;
      FullTestName expectedDefaultTestName;
      expectedDefaultTestName.testClassName = nullptr;
      expectedDefaultTestName.testName = nullptr;
      expectedDefaultTestName.arity = 0;
      ARE_EQUAL(expectedDefaultTestName, defaultTestName);
   }

   TEST(ThreeArgConstructor_SetsFields)
   {
      const string TestClassName = Random<string>();
      const string TestName = Random<string>();
      //
      const FullTestName testName(TestClassName.c_str(), TestName.c_str(), 1);
      //
      ARE_EQUAL(TestClassName, testName.testClassName);
      ARE_EQUAL(TestName, testName.testName);
      ARE_EQUAL(1, testName.arity);
   }

   TEST3X3(Value_ReturnsExpected,
      const string& expectedReturnValue, const char* testClassMacroArgument, unsigned char arity,
      "TESTS(Tests)\nTEST(Test)", "Tests", static_cast<unsigned char>(0),
      "TESTS(Tests)\nTEST1X1(Test)", "Tests", static_cast<unsigned char>(1),
      "TESTS(Tests)\nTEST2X2(Test)", "Tests", static_cast<unsigned char>(2),
      "TEMPLATE_TESTS(Tests<int>)\nTEST(Test)", "Tests<int>", static_cast<unsigned char>(0),
      "TEMPLATE_TESTS(Tests<int, int>)\nTEST1X1(Test)", "Tests<int, int>", static_cast<unsigned char>(1),
      "TEMPLATE_TESTS(Tests<vector<int>>)\nTEST2X2(Test)", "Tests<vector<int>>", static_cast<unsigned char>(2))
   {
      const FullTestName testName(testClassMacroArgument, "Test", arity);
      //
      const string value = testName.Value();
      //
      ARE_EQUAL(expectedReturnValue, value);
   }

   TEST(ZenUnitEqualizer_ThrowsIfClassNameOrTestNameNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(FullTestName);
      EQUALIZER_THROWS_FOR_FIELD(FullTestName, testClassName, "TestClassName");
      EQUALIZER_THROWS_FOR_FIELD(FullTestName, testName, "TestName");
      EQUALIZER_THROWS_FOR_FIELD(FullTestName, arity, static_cast<unsigned char>(1));
   }

}; RUN_TESTS(FullTestNameTests)
}

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
   TryCatchCallerMock* _tryCatchCallerMock = nullptr;
   TestResultFactoryMock* _testResultFactoryMock = nullptr;
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
      _tryCatchCallerMock->CallMock.Return(failedConstructorCallResult);

      const TestResult constructorFailTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->ConstructorFailMock.Return(constructorFailTestResult);
      //
      const vector<TestResult> testResults = _newDeleteTest->Run();
      //
      ZEN(_tryCatchCallerMock->CallMock.CalledOnceWith(
         &Test::CallNewTestClass, _newDeleteTest.get(), TestPhase::Constructor));
      ZEN(_testResultFactoryMock->ConstructorFailMock.CalledOnceWith(
         _newDeleteTest->_fullTestName, failedConstructorCallResult));
      const vector<TestResult> expectedTestResults{ constructorFailTestResult };
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(Run_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_ReturnsCtorDtorSuccessTestResult)
   {
      CallResult successConstructorCallResult;
      successConstructorCallResult.testOutcome = TestOutcome::Success;

      CallResult destructorCallResult;
      _tryCatchCallerMock->CallMock.ReturnValues(successConstructorCallResult, destructorCallResult);

      const TestResult sixArgCtorTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->CtorDtorSuccessMock.Return(sixArgCtorTestResult);
      //
      const vector<TestResult> testResults = _newDeleteTest->Run();
      //
      ZEN(_tryCatchCallerMock->CallMock.CalledAsFollows(
         {
            { &Test::CallNewTestClass, _newDeleteTest.get(), TestPhase::Constructor },
         { &Test::CallDeleteTestClass, _newDeleteTest.get(), TestPhase::Destructor }
         }));
      ZEN(_testResultFactoryMock->CtorDtorSuccessMock.CalledOnceWith(
         _newDeleteTest->_fullTestName, successConstructorCallResult, destructorCallResult));
      const vector<TestResult> expectedTestResults{ sixArgCtorTestResult };
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

}; RUN_TESTS(NewDeleteTestTests)
}

#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Testing/RandomPrintMode.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"

namespace ZenUnit
{
   TESTS(NormalTestTests)
   AFACT(NumberOfTestCases_Returns1)
   AFACT(NonMinimalWritePostTestNameMessage_WritesSpaceArrowSpace)
   AFACT(NonMinimalWritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
   AFACT(Constructor_SetsTestClassNameAndTestName_SetsTestBodyPointer)
   AFACT(NewTestClass_NewsTestClass)
   AFACT(Startup_CallsStartupOnTestClass)
   AFACT(TestBody_CallsMemberTestFunctionBoundToTestClassPointer)
   AFACT(Cleanup_CallsCleanupOnTestClass)
   AFACT(DeleteTestClass_DeletesTestClass)
   EVIDENCE

   unique_ptr<NormalTest<TestingTestClass>> _normalTest;
   const string TestClassName = Random<string>();
   const string TestName = Random<string>();

   STARTUP
   {
      _normalTest = make_unique<NormalTest<TestingTestClass>>(
         TestClassName.c_str(), TestName.c_str(), &TestingTestClass::Test);
   }

   TEST(NumberOfTestCases_Returns1)
   {
      ARE_EQUAL(1, _normalTest->NumberOfTestCases());
   }

   TEST(NonMinimalWritePostTestNameMessage_WritesSpaceArrowSpace)
   {
      ConsoleMock consoleMock;
      consoleMock.NonMinimalWriteMock.Expect();
      const PrintMode printMode = RandomPrintMode();
      //
      _normalTest->NonMinimalWritePostTestNameMessage(&consoleMock, printMode);
      //
      ZEN(consoleMock.NonMinimalWriteMock.CalledOnceWith(" -> ", printMode));
   }

   TEST(NonMinimalWritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
   {
      ConsoleMock consoleMock;
      TestResultMock testResultMock;
      testResultMock.NonMinimalWriteLineOKIfSuccessMock.Expect();
      const PrintMode printMode = RandomPrintMode();
      //
      _normalTest->NonMinimalWritePostTestCompletionMessage(&consoleMock, testResultMock, printMode);
      //
      ZEN(testResultMock.NonMinimalWriteLineOKIfSuccessMock.CalledOnceWith(&consoleMock, printMode));
   }

   TEST(Constructor_SetsTestClassNameAndTestName_SetsTestBodyPointer)
   {
      const NormalTest<TestingTestClass> normalTest(TestClassName.c_str(), TestName.c_str(), &TestingTestClass::Test);
      ARE_EQUAL(TestName, normalTest.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST(" + TestName + ")", normalTest.FullTestNameValue());
      ARE_EQUAL("(0)", normalTest.FileLineString());
      ARE_EQUAL(&TestingTestClass::Test, normalTest._testMemberFunction);
      IS_NULL(normalTest._testClass);
   }

   TEST(NewTestClass_NewsTestClass)
   {
      IS_NULL(_normalTest->_testClass);
      //
      _normalTest->NewTestClass();
      //
      IS_NOT_NULL(_normalTest->_testClass);
      _normalTest->_testClass.reset();
   }

   TEST(Startup_CallsStartupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->StartupMock.Expect();
      //
      _normalTest->Startup();
      //
      ZEN(_normalTest->_testClass->StartupMock.CalledOnce());
   }

   TEST(TestBody_CallsMemberTestFunctionBoundToTestClassPointer)
   {
      _normalTest->_testMemberFunction = &TestingTestClass::Test;
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->TestMock.Expect();
      //
      _normalTest->TestBody();
      //
      ZEN(_normalTest->_testClass->TestMock.CalledOnce());
   }

   TEST(Cleanup_CallsCleanupOnTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      _normalTest->_testClass->CleanupMock.Expect();
      //
      _normalTest->Cleanup();
      //
      ZEN(_normalTest->_testClass->CleanupMock.CalledOnce());
   }

   TEST(DeleteTestClass_DeletesTestClass)
   {
      _normalTest->_testClass = make_unique<TestingTestClass>();
      IS_FALSE(TestingTestClass::s_destructorCalled);
      //
      _normalTest->DeleteTestClass();
      //
      IS_TRUE(TestingTestClass::s_destructorCalled);
   }

}; RUN_TESTS(NormalTestTests)
}


#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"

class TestingTestClass_SpecSectionTestNXNTests
{
public:
   static bool didCallTestNXNPmfToTest;
   static unique_ptr<Test> TestNXNPmfToTestReturnValue;

   static const unique_ptr<Test>* TestNXNPmfToTest(const ZenUnit::PmfToken*)
   {
      didCallTestNXNPmfToTest = true;
      return &TestNXNPmfToTestReturnValue;
   }

   void TestFunction(int) {}
   virtual ~TestingTestClass_SpecSectionTestNXNTests() = default;
};

bool TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest;
unique_ptr<Test> TestingTestClass_SpecSectionTestNXNTests::TestNXNPmfToTestReturnValue;

namespace ZenUnit
{
   TESTS(SpecSectionTestNXNTests)
   AFACT(ThreeArgConstructor_SetsTestName_SetsTestNXNPmf)
   FACTS(NumberOfTestCases_GetsTestFromAddress_ReturnsTestNumberOfTestCases)
   FACTS(NonMinimalWritePostTestNameMessage_WritesEllipsisIfPrintModeNotMinimal)
   AFACT(Run_GetsTestFromAddress_RunsTest_ReturnsTestResults)
   AFACT(PmfTokenToTest_ReturnsTestClassTypeTestNXNPmfToTestReturnValue);
   AFACT(TestFunction_CodeCoverage)
   EVIDENCE

   class SpecSectionTestNXNSelfMocked : public Zen::Mock<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>
   {
   public:
      SpecSectionTestNXNSelfMocked()
         : Zen::Mock<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>("", "", nullptr)
      {
      }
      ZENMOCK_NONVOID0_CONST(const unique_ptr<Test>*, PmfTokenToTest)
   };

   unique_ptr<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>> _specSectionTestNXN;
   unique_ptr<SpecSectionTestNXNSelfMocked> _specSectionTestNXNSelfMocked;

   STARTUP
   {
      _specSectionTestNXN = make_unique<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>("", "", nullptr);
   _specSectionTestNXNSelfMocked = make_unique<SpecSectionTestNXNSelfMocked>();
   }

   TEST(ThreeArgConstructor_SetsTestName_SetsTestNXNPmf)
   {
      const string TestClassName = Random<string>();
      const string TestName = Random<string>();
      //
      const SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests> specifiedTestNXN(
         TestClassName.c_str(), TestName.c_str(), PmfToken::Instantiate<decltype(
            &TestingTestClass_SpecSectionTestNXNTests::TestFunction),
         &TestingTestClass_SpecSectionTestNXNTests::TestFunction>());
      //
      ARE_EQUAL(TestName, specifiedTestNXN.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST(" + TestName + ")", specifiedTestNXN.FullTestNameValue());
      ARE_EQUAL("(0)", specifiedTestNXN.FileLineString());
      const PmfToken* const expectedTestNXNPmfToken = ZenUnit::PmfToken::Instantiate<
         decltype(&TestingTestClass_SpecSectionTestNXNTests::TestFunction),
         &TestingTestClass_SpecSectionTestNXNTests::TestFunction>();
      ARE_EQUAL(expectedTestNXNPmfToken, specifiedTestNXN._testNXNPmfToken);
   }

   TEST1X1(NumberOfTestCases_GetsTestFromAddress_ReturnsTestNumberOfTestCases,
      size_t testNumberOfTestCases,
      size_t(1),
      size_t(2))
   {
      TestMock* testMock = new TestMock;
      testMock->NumberOfTestCasesMock.Return(testNumberOfTestCases);
      const unique_ptr<Test> testMockUniquePtr(testMock);
      _specSectionTestNXNSelfMocked->PmfTokenToTestMock.Return(&testMockUniquePtr);
      //
      const size_t numberOfTestCases = _specSectionTestNXNSelfMocked->NumberOfTestCases();
      //
      ZEN(_specSectionTestNXNSelfMocked->PmfTokenToTestMock.CalledOnce());
      ZEN(testMock->NumberOfTestCasesMock.CalledOnce());
      ARE_EQUAL(testNumberOfTestCases, numberOfTestCases);
   }

   TEST2X2(NonMinimalWritePostTestNameMessage_WritesEllipsisIfPrintModeNotMinimal,
      PrintMode printMode, bool expectWriteLineCall,
      PrintMode::Minimal, false,
      PrintMode::Normal, true,
      PrintMode::Detailed, true)
   {
      ConsoleMock consoleMock;
      if (expectWriteLineCall)
      {
         consoleMock.WriteLineMock.Expect();
      }
      //
      _specSectionTestNXN->NonMinimalWritePostTestNameMessage(&consoleMock, printMode);
      //
      if (expectWriteLineCall)
      {
         ZEN(consoleMock.WriteLineMock.CalledOnceWith("..."));
      }
   }

   TEST(Run_GetsTestFromAddress_RunsTest_ReturnsTestResults)
   {
      TestMock* const testMock = new TestMock;
      const vector<TestResult> testTestResults{ TestResult::TestingNonDefault() };
      testMock->RunMock.Return(testTestResults);
      const unique_ptr<Test> testMockUniquePtr(testMock);
      _specSectionTestNXNSelfMocked->PmfTokenToTestMock.Return(&testMockUniquePtr);
      //
      const vector<TestResult> testResults = _specSectionTestNXNSelfMocked->Run();
      //
      ZEN(_specSectionTestNXNSelfMocked->PmfTokenToTestMock.CalledOnce());
      ZEN(testMock->RunMock.CalledOnce());
      VECTORS_EQUAL(testTestResults, testResults);
   }

   TEST(PmfTokenToTest_ReturnsTestClassTypeTestNXNPmfToTestReturnValue)
   {
      TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest = false;
      //
      const unique_ptr<Test>* testNXN = _specSectionTestNXN->PmfTokenToTest();
      //
      IS_TRUE(TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest);
      ARE_EQUAL(testNXN, &TestingTestClass_SpecSectionTestNXNTests::TestNXNPmfToTestReturnValue);
   }

   TEST(TestFunction_CodeCoverage)
   {
      TestingTestClass_SpecSectionTestNXNTests t;
      t.TestFunction(0);
   }

}; RUN_TESTS(SpecSectionTestNXNTests)
}


#include "pch.h"

struct TestingDerivedTestClassType : public TestClass<TestingDerivedTestClassType>
{
   static bool s_allNXNTestsRegistered;
};

bool TestingDerivedTestClassType::s_allNXNTestsRegistered = false;

namespace ZenUnit
{
   TESTS(TestClassTests)
   AFACT(DefaultConstructor_DoesNotThrow)
   AFACT(Startup_DoesNotThrow)
   AFACT(Cleanup_DoesNotThrow)
   AFACT(Destructor_SetsDerviedTestClassTypeAllTestCasesRegisteredToTrue)
   EVIDENCE

   TestClass _testClass;

   CLEANUP
   {
      TestingDerivedTestClassType::s_allNXNTestsRegistered = false;
   }

   TEST(DefaultConstructor_DoesNotThrow)
   {
      const TestClass testClass{};
   }

   TEST(Startup_DoesNotThrow)
   {
      _testClass.Startup();
   }

   TEST(Cleanup_DoesNotThrow)
   {
      _testClass.Cleanup();
   }

   TEST(Destructor_SetsDerviedTestClassTypeAllTestCasesRegisteredToTrue)
   {
      IS_FALSE(TestingDerivedTestClassType::s_allNXNTestsRegistered);
      {
         const TestClass<TestingDerivedTestClassType> testClass{};
      }
      IS_TRUE(TestingDerivedTestClassType::s_allNXNTestsRegistered);
   }

}; RUN_TESTS(TestClassTests)
}


#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Testing/RandomPrintMode.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"

namespace ZenUnit
{
   static const size_t N = 1;

   TESTS(TestNXNTests)
   AFACT(Constructor_NewsConsole_SetsFields_GettersReturnExpected_2X2With4Args)
   AFACT(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   AFACT(NumberOfTestCases_ReturnsNumberOfTestCaseArgsDividedByN)
   AFACT(Run_RunsAllTestCases_ResetsTestCaseArgsIndexTo0_ReturnsVectorOfTestResults)
   AFACT(NewTestClass_NewsTestClass)
   AFACT(Startup_CallsTestClassStartup)
   AFACT(TestBody_CallsRunNXNTestCase)
   AFACT(RunNXNTestCase_DoesNothing)
   AFACT(Cleanup_CallsCleanup)
   AFACT(DeleteTestClass_DeletesTestClass)
   FACTS(NonMinimalPrintTestCaseNumberArgsThenArrow_WritesTestCaseNumberArrow)
   AFACT(NonMinimalWriteLineOKIfSuccess_CallsTestResultNonMinimalWriteLineOKIfSuccess)
   EVIDENCE

   unique_ptr<TestNXN<TestingTestClass, N, int>> _testNXN;
   ConsoleMock* _consoleMock = nullptr;
   const string TestClassName = Random<string>();
   const string TestName = Random<string>();
   const string TestCaseArgsText = Random<string>();
   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)

      STARTUP
   {
      _testNXN = make_unique<TestNXN<TestingTestClass, N, int>>("", "", "", 0);
      _testNXN->_console.reset(_consoleMock = new ConsoleMock);
      _testNXN->call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
   }

   TEST(Constructor_NewsConsole_SetsFields_GettersReturnExpected_2X2With4Args)
   {
      TestNXN<TestingTestClass, 2, int, int, int, int> testNXN(
         TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0, 0, 0);
      //
      POINTER_WAS_NEWED(testNXN._console);
      STD_FUNCTION_TARGETS(TestRunner::GetArgs, testNXN.call_TestRunner_GetArgs);
      IS_NULL(testNXN._testClass);
      ARE_EQUAL(0, testNXN._testCaseArgsIndex);
      ARE_EQUAL(TestCaseArgsText, testNXN._testCaseArgsText);
      STD_FUNCTION_TARGETS(String::CommaSplitExceptQuotedCommas, testNXN.call_String_CommaSplitExceptQuotedCommas);
      ARE_EQUAL(TestName, testNXN.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST2X2(" + TestName + ")", testNXN.FullTestNameValue());
      ARE_EQUAL("(0)", testNXN.FileLineString());
   }

   TEST(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   {
      const TestNXN<TestingTestClass, 1, int> testNXN_1X1_1Arg(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0);
      ARE_EQUAL(tuple<int>(0), testNXN_1X1_1Arg._testCaseArgs);

      const TestNXN<TestingTestClass, 1, int, int> testNXN_1X1_2Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0);
      const tuple<int, int> expectedTestCaseArgs1(0, 0);
      ARE_EQUAL(expectedTestCaseArgs1, testNXN_1X1_2Args._testCaseArgs);

      const TestNXN<TestingTestClass, 2, const string&, volatile int> testNXN_2X2_4Args(
         TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), string(), 100);
      const tuple<string, int> expectedTestCaseArgs2(string(), 100);
      ARE_EQUAL(expectedTestCaseArgs2, testNXN_2X2_4Args._testCaseArgs);
   }

   TEST(NumberOfTestCases_ReturnsNumberOfTestCaseArgsDividedByN)
   {
      const TestNXN<TestingTestClass, 1, int>
         test1X1(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0);
      ARE_EQUAL(1, test1X1.NumberOfTestCases());

      const TestNXN<TestingTestClass, 1, int, int>
         test1X1_2Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0);
      ARE_EQUAL(2, test1X1_2Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 2, int, int>
         test2X2_2Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0);
      ARE_EQUAL(1, test2X2_2Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 2, int, int, int, int>
         test2X2_4Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0, 0, 0);
      ARE_EQUAL(2, test2X2_4Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 3, int, int, int, int, int, int, int, int, int>
         test3X3_9Args(TestClassName.c_str(), TestName.c_str(), TestCaseArgsText.c_str(), 0, 0, 0, 0, 0, 0, 0, 0, 0);
      ARE_EQUAL(3, test3X3_9Args.NumberOfTestCases());
   }

   TEST(Run_RunsAllTestCases_ResetsTestCaseArgsIndexTo0_ReturnsVectorOfTestResults)
   {
      struct Test1X1SelfMocked : public Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>
      {
         ZENMOCK_NONVOID0(TestResult, MockableCallBaseRunTestCase)
         ZENMOCK_VOID3_CONST(NonMinimalPrintTestCaseNumberArgsThenArrow, unsigned short, const vector<string>&, PrintMode)
         ZENMOCK_VOID2_CONST(NonMinimalWriteLineOKIfSuccess, const TestResult&, PrintMode)
         Test1X1SelfMocked()
         : Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>("", "", "", 0, 0) {}
      } test1X1SelfMocked;

      ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs, _SelfMocked);
      const ZenUnitArgs zenUnitArgs = []
      {
         ZenUnitArgs zenUnitArgs;
         zenUnitArgs.printMode = RandomPrintMode();
         return zenUnitArgs;
      }();
      GetArgs_ZenMock_SelfMocked.Return(zenUnitArgs);
      test1X1SelfMocked.call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock_SelfMocked);

      ZENMOCK_NONVOID0_STATIC(vector<string>, ZenUnit::String, CommaSplitExceptQuotedCommas, _SelfMocked);
      const vector<string> splitTestCaseArgs = { "1", "2", "3" };
      CommaSplitExceptQuotedCommas_ZenMock_SelfMocked.Return(splitTestCaseArgs);
      test1X1SelfMocked.call_String_CommaSplitExceptQuotedCommas
         = ZENMOCK_BIND0(CommaSplitExceptQuotedCommas_ZenMock_SelfMocked);

      test1X1SelfMocked.NonMinimalPrintTestCaseNumberArgsThenArrowMock.Expect();
      TestResult firstTestResult;
      firstTestResult.fullTestName.testName = "FirstTest";
      TestResult secondTestResult;
      secondTestResult.fullTestName.testName = "SecondTest";
      test1X1SelfMocked.MockableCallBaseRunTestCaseMock.ReturnValues(firstTestResult, secondTestResult);
      test1X1SelfMocked.NonMinimalWriteLineOKIfSuccessMock.Expect();
      //
      const vector<TestResult> testResults = test1X1SelfMocked.Run();
      //
      ZEN(CommaSplitExceptQuotedCommas_ZenMock_SelfMocked.CalledOnce());
      ZEN(test1X1SelfMocked.NonMinimalPrintTestCaseNumberArgsThenArrowMock.CalledAsFollows(
         {
            { 0, splitTestCaseArgs, zenUnitArgs.printMode },
         { 1, splitTestCaseArgs, zenUnitArgs.printMode }
         }));
      TestResult expectedFirstTestResult = firstTestResult;
      expectedFirstTestResult.testCaseIndex = 0;
      TestResult expectedSecondTestResult = secondTestResult;
      expectedSecondTestResult.testCaseIndex = 1;
      ZEN(GetArgs_ZenMock_SelfMocked.CalledOnce());
      ZEN(test1X1SelfMocked.MockableCallBaseRunTestCaseMock.CalledNTimes(2));
      ZEN(test1X1SelfMocked.NonMinimalWriteLineOKIfSuccessMock.CalledAsFollows(
         {
            { expectedFirstTestResult, zenUnitArgs.printMode },
         { expectedSecondTestResult, zenUnitArgs.printMode }
         }));
      const vector<TestResult> expectedTestResults =
      {
         expectedFirstTestResult,
         expectedSecondTestResult,
      };
      ARE_EQUAL(0, test1X1SelfMocked._testCaseArgsIndex);
      VECTORS_EQUAL(expectedTestResults, testResults);
   }

   TEST(NewTestClass_NewsTestClass)
   {
      IS_NULL(_testNXN->_testClass);
      //
      _testNXN->NewTestClass();
      //
      POINTER_WAS_NEWED(_testNXN->_testClass);
      _testNXN->_testClass.reset();
   }

   TEST(Startup_CallsTestClassStartup)
   {
      _testNXN->_testClass = make_unique<TestingTestClass>();
      _testNXN->_testClass->StartupMock.Expect();
      //
      _testNXN->Startup();
      //
      ZEN(_testNXN->_testClass->StartupMock.CalledOnce());
   }

   TEST(TestBody_CallsRunNXNTestCase)
   {
      struct TestNXN_RunNXNTestCaseMocked : public Zen::Mock<TestNXN<TestingTestClass, 1, int>>
      {
         ZENMOCK_VOID2(RunNXNTestCase, TestingTestClass*, size_t)
         TestNXN_RunNXNTestCaseMocked()
            : Zen::Mock<TestNXN<TestingTestClass, 1, int>>("", "", "", 0) {}
      } testNXN_RunNXNTestCaseMocked;

      testNXN_RunNXNTestCaseMocked._testClass = make_unique<TestingTestClass>();
      testNXN_RunNXNTestCaseMocked._testCaseArgsIndex = 1;
      testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.Expect();
      //
      testNXN_RunNXNTestCaseMocked.TestBody();
      //
      ZEN(testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.CalledOnceWith(
         testNXN_RunNXNTestCaseMocked._testClass.get(), testNXN_RunNXNTestCaseMocked._testCaseArgsIndex));
   }

   TEST(RunNXNTestCase_DoesNothing)
   {
      _testNXN->RunNXNTestCase(nullptr, 0);
   }

   TEST(Cleanup_CallsCleanup)
   {
      _testNXN->_testClass = make_unique<TestingTestClass>();
      _testNXN->_testClass->CleanupMock.Expect();
      //
      _testNXN->Cleanup();
      //
      ZEN(_testNXN->_testClass->CleanupMock.CalledOnce());
   }

   TEST(DeleteTestClass_DeletesTestClass)
   {
      _testNXN->_testClass = make_unique<TestingTestClass>();
      IS_FALSE(TestingTestClass::s_destructorCalled);
      //
      _testNXN->DeleteTestClass();
      //
      IS_TRUE(TestingTestClass::s_destructorCalled);
   }

   TEST3X3(NonMinimalPrintTestCaseNumberArgsThenArrow_WritesTestCaseNumberArrow,
      unsigned short testCaseIndex, int expectedTestCaseNumber, size_t expectedTestCaseArgsPrintingStartIndex,
      static_cast<unsigned short>(0), 1, size_t(0),
      static_cast<unsigned short>(1), 2, size_t(1),
      static_cast<unsigned short>(2), 3, size_t(2))
   {
      _consoleMock->NonMinimalWriteColorMock.Expect();
      _consoleMock->NonMinimalWriteMock.Expect();
      _consoleMock->NonMinimalWriteStringsCommaSeparatedMock.Expect();
      const PrintMode printMode = RandomPrintMode();
      vector<string> splitTestCaseArgs = { "Arg0", "Argument1" };
      //
      _testNXN->NonMinimalPrintTestCaseNumberArgsThenArrow(testCaseIndex, splitTestCaseArgs, printMode);
      //
      ZEN(_consoleMock->NonMinimalWriteColorMock.CalledAsFollows(
         {
            { " [", Color::Green, printMode },
         { "]", Color::Green, printMode }
         }));
      ZEN(_consoleMock->NonMinimalWriteStringsCommaSeparatedMock.CalledOnceWith(
         splitTestCaseArgs, expectedTestCaseArgsPrintingStartIndex, N, printMode));
      ZEN(_consoleMock->NonMinimalWriteMock.CalledAsFollows(
         {
            { to_string(expectedTestCaseNumber), printMode },
         { " ("s, printMode },
         { ") -> "s, printMode }
         }));
   }

   TEST(NonMinimalWriteLineOKIfSuccess_CallsTestResultNonMinimalWriteLineOKIfSuccess)
   {
      TestResultMock testResultMock;
      testResultMock.NonMinimalWriteLineOKIfSuccessMock.Expect();
      const PrintMode printMode = static_cast<PrintMode>(Random<underlying_type_t<PrintMode>>(
         static_cast<underlying_type_t<PrintMode>>(PrintMode::Unset),
         static_cast<underlying_type_t<PrintMode>>(PrintMode::MaxValue)));
      //
      _testNXN->NonMinimalWriteLineOKIfSuccess(testResultMock, printMode);
      //
      ZEN(testResultMock.NonMinimalWriteLineOKIfSuccessMock.
         CalledOnceWith(_testNXN->_console.get(), printMode));
   }

}; RUN_TESTS(TestNXNTests)

template<typename T>
TEMPLATE_TESTS(AllTestNXNsWithinATemplateTestClass, T)
AFACT(Test)
FACTS(Test1X1)
FACTS(Test2X2)
FACTS(Test3X3)
FACTS(Test4X4)
FACTS(Test5X5)
FACTS(Test6X6)
FACTS(Test7X7)
FACTS(Test8X8)
FACTS(Test9X9)
FACTS(Test10X10)
EVIDENCE

TEST(Test) {}
TEST1X1(Test1X1, int, 0) {}
TEST2X2(Test2X2, int, int, 0, 0) {}
TEST3X3(Test3X3, int, int, int, 0, 0, 0) {}
TEST4X4(Test4X4, int, int, int, int, 0, 0, 0, 0) {}
TEST5X5(Test5X5, int, int, int, int, int, 0, 0, 0, 0, 0) {}
TEST6X6(Test6X6, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0) {}
TEST7X7(Test7X7, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0) {}
TEST8X8(Test8X8, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0) {}
TEST9X9(Test9X9, int, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
TEST10X10(Test10X10, int, int, int, int, int, int, int, int, int, int, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
   };
   RUN_TEMPLATE_TESTS(AllTestNXNsWithinATemplateTestClass, int)
}


#include "pch.h"
#include "ZenUnitTests/Results/Mock/TestResultFactoryMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/TestRunners/Mock/TryCatchCallerMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"

namespace ZenUnit
{
   TESTS(TestTests)
   AFACT(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   FACTS(RunTestCase_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail)
   FACTS(RunTestCase_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail)
   AFACT(RunTestCase_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   AFACT(NonMinimalWritePostTestNameMessage_DoesNothing)
   AFACT(PrintPostTestCompletionMessage_DoesNothing)
   AFACT(StaticCallNewTestClass_CallsNewTestClass)
   AFACT(StaticCallStartup_CallsStartup)
   AFACT(StaticTestBody_CallsTestBody)
   AFACT(StaticCallCleanup_CallsCleanup)
   AFACT(StaticCallDeleteTestClass_CallsDeleteTestClass)
   AFACT(PseudoAbstractFunctions_DoNothingOrReturn0)
   EVIDENCE

   unique_ptr<Test> _test;
   TryCatchCallerMock* _tryCatchCallerMock = nullptr;
   TestResultFactoryMock* _testResultFactoryMock = nullptr;
   TestMock _testMock;

   STARTUP
   {
      _test = make_unique<Test>("", "", static_cast<unsigned char>(0));
      _test->_tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock);
      _test->_testResultFactory.reset(_testResultFactoryMock = new TestResultFactoryMock);
   }

   TEST(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
   {
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      //
      Test test(testClassName.c_str(), testName.c_str(), 0);
      POINTER_WAS_NEWED(test._tryCatchCaller);
      POINTER_WAS_NEWED(test._testResultFactory);
      ARE_EQUAL(FileLine(), test._fileLine);

      const char* const testNameValue = test.Name();
      ARE_EQUAL(testName.c_str(), testNameValue);

      const string fullTestName = test.FullTestNameValue();
      ARE_EQUAL(fullTestName, test._fullTestName.Value());

      test._fileLine = FileLine("FilePath", 1);
      ARE_EQUAL(test._fileLine.ToString(), test.FileLineString());
   }

   TEST(NonMinimalWritePostTestNameMessage_DoesNothing)
   {
      _test->NonMinimalWritePostTestNameMessage(nullptr, PrintMode::Minimal);
      _test->NonMinimalWritePostTestNameMessage(nullptr, PrintMode::Normal);
      _test->NonMinimalWritePostTestNameMessage(nullptr, PrintMode::Detailed);
   }

   TEST(PrintPostTestCompletionMessage_DoesNothing)
   {
      TestResultMock testResultMock;
      _test->NonMinimalWritePostTestCompletionMessage(nullptr, testResultMock, PrintMode::Minimal);
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
      _tryCatchCallerMock->CallMock.Return(constructorFailCallResult);

      const TestResult constructorFailTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->ConstructorFailMock.Return(constructorFailTestResult);
      //
      const TestResult testResult = _test->RunTestCase();
      //
      ZEN(_tryCatchCallerMock->CallMock.CalledOnceWith(
         &Test::CallNewTestClass, _test.get(), TestPhase::Constructor));
      ZEN(_testResultFactoryMock->ConstructorFailMock.CalledOnceWith(
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
      _tryCatchCallerMock->CallMock.ReturnValues(constructorSuccessCallResult, startupFailCallResult, destructorCallResult);

      const TestResult startupFailTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->StartupFailMock.Return(startupFailTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->RunTestCase();
      //
      ZEN(_tryCatchCallerMock->CallMock.CalledAsFollows(
         {
            { &Test::CallNewTestClass, _test.get(), TestPhase::Constructor },
         { &Test::CallStartup, _test.get(), TestPhase::Startup },
         { &Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor }
         }));
      ZEN(_testResultFactoryMock->StartupFailMock.CalledOnceWith(
         _test->_fullTestName, constructorSuccessCallResult, startupFailCallResult, destructorCallResult));
      ARE_EQUAL(startupFailTestResult, testResult);
   }

   TEST(RunTestCase_AllTestPhasesSucceed_ReturnsExpectedTestResult)
   {
      const CallResult successCallResult = CallResultWithOutcome(TestOutcome::Success);
      _tryCatchCallerMock->CallMock.Return(successCallResult);

      const TestResult sixArgTestResult = TestResult::TestingNonDefault();
      _testResultFactoryMock->FullCtorMock.Return(sixArgTestResult);
      const string testClassName = Random<string>();
      const string testName = Random<string>();
      _test->_fullTestName = FullTestName(testClassName.c_str(), testName.c_str(), 0);
      //
      const TestResult testResult = _test->RunTestCase();
      //
      ZEN(_tryCatchCallerMock->CallMock.CalledAsFollows(
         {
            { &Test::CallNewTestClass, _test.get(), TestPhase::Constructor },
         { &Test::CallStartup, _test.get(), TestPhase::Startup },
         { &Test::CallTestBody, _test.get(), TestPhase::TestBody },
         { &Test::CallCleanup, _test.get(), TestPhase::Cleanup },
         { &Test::CallDeleteTestClass, _test.get(), TestPhase::Destructor }
         }));
      ZEN(_testResultFactoryMock->FullCtorMock.CalledOnceWith(
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
      ZEN(_testMock.NewTestClassMock.CalledOnce());
   }

   TEST(StaticCallStartup_CallsStartup)
   {
      _testMock.StartupMock.Expect();
      //
      Test::CallStartup(&_testMock);
      //
      ZEN(_testMock.StartupMock.CalledOnce());
   }

   TEST(StaticTestBody_CallsTestBody)
   {
      _testMock.TestBodyMock.Expect();
      //
      Test::CallTestBody(&_testMock);
      //
      ZEN(_testMock.TestBodyMock.CalledOnce());
   }

   TEST(StaticCallCleanup_CallsCleanup)
   {
      _testMock.CleanupMock.Expect();
      //
      Test::CallCleanup(&_testMock);
      //
      ZEN(_testMock.CleanupMock.CalledOnce());
   }

   TEST(StaticCallDeleteTestClass_CallsDeleteTestClass)
   {
      _testMock.DeleteTestClassMock.Expect();
      //
      Test::CallDeleteTestClass(&_testMock);
      //
      ZEN(_testMock.DeleteTestClassMock.CalledOnce());
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

}; RUN_TESTS(TestTests)

}

#endif

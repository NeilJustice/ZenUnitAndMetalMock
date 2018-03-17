#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"
#include "ZenUnitTests/Results/Mock/TestResultFactoryMock.h"
#include "ZenUnitTests/TestRunners/Mock/TryCatchCallerMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"
#include "ZenUnitTests/Results/Mock/TestResultFactoryMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/TestRunners/Mock/TryCatchCallerMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"

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
   const string testClassName = Random<string>();
   const string testName = Random<string>();
   //
   const FullTestName fullTestName(testClassName.c_str(), testName.c_str(), 1);
   //
   ARE_EQUAL(testClassName, fullTestName.testClassName);
   ARE_EQUAL(testName, fullTestName.testName);
   ARE_EQUAL(1, fullTestName.arity);
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

RUN_TESTS(FullTestNameTests)


TESTS(NewableDeletableTestTests)
AFACT(Constructor_NewsComponents)
AFACT(NumberOfTestCases_Returns1)
FACTS(Run_StartsStopWatch_CallsNewTestClassWhichFails_DoesNotCallDeleteTestClass_StopsStopwatch_ReturnsConstructorFailTestResult)
AFACT(Run_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsCtorDtorSuccessTestResult)
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

TEST1X1(Run_StartsStopWatch_CallsNewTestClassWhichFails_DoesNotCallDeleteTestClass_StopsStopwatch_ReturnsConstructorFailTestResult,
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
   const vector<TestResult> testResults = _newableDeletableTest->Run();
   //
   ZEN(_stopwatchMock->StartMock.CalledOnce());
   ZEN(_tryCatchCallerMock->CallMock.CalledOnceWith(
      &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor));
   ZEN(_testResultFactoryMock->ConstructorFailMock.CalledOnceWith(
      _newableDeletableTest->_fullTestName, failedConstructorCallResult));
   const vector<TestResult> expectedTestResults{ constructorFailTestResult };
   ZEN(_stopwatchMock->StopMock.CalledOnce());
   VECTORS_EQUAL(expectedTestResults, testResults);
}

TEST(Run_StartsStopwatch_CallsNewTestClassWhichSucceeds_CallsDeleteTestClass_StopsStopwatch_ReturnsCtorDtorSuccessTestResult)
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
   const vector<TestResult> testResults = _newableDeletableTest->Run();
   //
   ZEN(_stopwatchMock->StartMock.CalledOnce());
   ZEN(_tryCatchCallerMock->CallMock.CalledAsFollows(
   {
      { &Test::CallNewTestClass, _newableDeletableTest.get(), TestPhase::Constructor },
      { &Test::CallDeleteTestClass, _newableDeletableTest.get(), TestPhase::Destructor }
   }));
   ZEN(_testResultFactoryMock->CtorDtorSuccessMock.CalledOnceWith(
      _newableDeletableTest->_fullTestName, successConstructorCallResult, destructorCallResult));
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


TESTS(NormalTestTests)
AFACT(NumberOfTestCases_Returns1)
AFACT(WritePostTestNameMessage_WritesSpaceArrowSpace)
AFACT(WritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
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

TEST(WritePostTestNameMessage_WritesSpaceArrowSpace)
{
   ConsoleMock consoleMock;
   consoleMock.WriteMock.Expect();
   //
   _normalTest->WritePostTestNameMessage(&consoleMock);
   //
   ZEN(consoleMock.WriteMock.CalledOnceWith(" -> "));
}

TEST(WritePostTestCompletionMessage_CallsTestResultPrintOKIfTestPassedAndDoWriteMessageTrue)
{
   ConsoleMock consoleMock;
   TestResultMock testResultMock;
   testResultMock.WriteLineOKIfSuccessMock.Expect();
   //
   _normalTest->WritePostTestCompletionMessage(&consoleMock, testResultMock);
   //
   ZEN(testResultMock.WriteLineOKIfSuccessMock.CalledOnceWith(&consoleMock));
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

RUN_TESTS(NormalTestTests)


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


TESTS(SpecSectionTestNXNTests)
AFACT(ThreeArgConstructor_SetsTestName_SetsTestNXNPmf)
FACTS(NumberOfTestCases_GetsTestFromAddress_ReturnsTestNumberOfTestCases)
AFACT(WritePostTestNameMessage_WritesEllipsis)
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
   const string testClassName = Random<string>();
   const string testName = Random<string>();
   //
   const SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests> specifiedTestNXN(
      testClassName.c_str(), testName.c_str(), PmfToken::Instantiate<decltype(
         &TestingTestClass_SpecSectionTestNXNTests::TestFunction),
      &TestingTestClass_SpecSectionTestNXNTests::TestFunction>());
   //
   ARE_EQUAL(testName, specifiedTestNXN.Name());
   ARE_EQUAL("TESTS(" + testClassName + ")\nTEST(" + testName + ")", specifiedTestNXN.FullTestNameValue());
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

TEST(WritePostTestNameMessage_WritesEllipsis)
{
   ConsoleMock consoleMock;
   consoleMock.WriteLineMock.Expect();
   //
   _specSectionTestNXN->WritePostTestNameMessage(&consoleMock);
   //
   ZEN(consoleMock.WriteLineMock.CalledOnceWith("..."));
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

RUN_TESTS(SpecSectionTestNXNTests)


struct TestingDerivedTestClassType : public TestClass<TestingDerivedTestClassType>
{
   static bool s_allNXNTestsRegistered;
};

bool TestingDerivedTestClassType::s_allNXNTestsRegistered = false;

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

RUN_TESTS(TestClassTests)


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
FACTS(PrintTestCaseNumberArgsThenArrow_WritesTestCaseNumberArrow)
AFACT(WriteLineOKIfSuccess_CallsTestResultWriteLineOKIfSuccess)
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
      ZENMOCK_VOID2_CONST(PrintTestCaseNumberArgsThenArrow, unsigned short, const vector<string>&)
      ZENMOCK_VOID1_CONST(WriteLineOKIfSuccess, const TestResult&)
      Test1X1SelfMocked()
         : Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>(
            "", // testClassName
            "", // testName
            "", // testCaseArgsText
            0, // test case arg 0
            0 // test case arg 1
            ) {}
   } test1X1SelfMocked;

   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs, _SelfMocked);

   ZENMOCK_NONVOID0_STATIC(vector<string>, ZenUnit::String, CommaSplitExceptQuotedCommas, _SelfMocked);
   const vector<string> splitTestCaseArgs = { ZenUnit::Random<string>(), ZenUnit::Random<string>(), ZenUnit::Random<string>() };
   CommaSplitExceptQuotedCommas_ZenMock_SelfMocked.Return(splitTestCaseArgs);
   test1X1SelfMocked.call_String_CommaSplitExceptQuotedCommas
      = ZENMOCK_BIND0(CommaSplitExceptQuotedCommas_ZenMock_SelfMocked);

   test1X1SelfMocked.PrintTestCaseNumberArgsThenArrowMock.Expect();

   TestResult firstTestResult;
   const string firstTestName = ZenUnit::Random<string>();
   firstTestResult.fullTestName.testName = firstTestName.c_str();

   TestResult secondTestResult;
   const string secondTestName = ZenUnit::Random<string>();
   secondTestResult.fullTestName.testName = secondTestName.c_str();
   test1X1SelfMocked.MockableCallBaseRunTestCaseMock.ReturnValues(firstTestResult, secondTestResult);

   test1X1SelfMocked.WriteLineOKIfSuccessMock.Expect();
   //
   const vector<TestResult> testResults = test1X1SelfMocked.Run();
   //
   ZEN(CommaSplitExceptQuotedCommas_ZenMock_SelfMocked.CalledOnce());
   ZEN(test1X1SelfMocked.PrintTestCaseNumberArgsThenArrowMock.CalledAsFollows(
   {
      { 1, splitTestCaseArgs },
      { 2, splitTestCaseArgs }
   }));
   TestResult expectedFirstTestResult = firstTestResult;
   expectedFirstTestResult.testCaseNumber = 1;
   TestResult expectedSecondTestResult = secondTestResult;
   expectedSecondTestResult.testCaseNumber = 2;
   ZEN(test1X1SelfMocked.MockableCallBaseRunTestCaseMock.CalledNTimes(2));
   ZEN(test1X1SelfMocked.WriteLineOKIfSuccessMock.CalledAsFollows(
   {
      { expectedFirstTestResult },
      { expectedSecondTestResult }
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

TEST3X3(PrintTestCaseNumberArgsThenArrow_WritesTestCaseNumberArrow,
   unsigned short testCaseNumber, int expectedTestCaseNumber, size_t expectedTestCaseArgsPrintingStartIndex,
   static_cast<unsigned short>(1), 1, size_t(0),
   static_cast<unsigned short>(2), 2, size_t(1),
   static_cast<unsigned short>(3), 3, size_t(2))
{
   _consoleMock->WriteColorMock.Expect();
   _consoleMock->WriteMock.Expect();
   _consoleMock->WriteStringsCommaSeparatedMock.Expect();
   const vector<string> splitTestCaseArgs = { "Arg0", "Argument1" };
   //
   _testNXN->PrintTestCaseNumberArgsThenArrow(testCaseNumber, splitTestCaseArgs);
   //
   ZEN(_consoleMock->WriteColorMock.CalledAsFollows(
   {
      { " [", Color::Green },
      { "]", Color::Green }
   }));
   ZEN(_consoleMock->WriteStringsCommaSeparatedMock.CalledOnceWith(
      splitTestCaseArgs, expectedTestCaseArgsPrintingStartIndex, N));
   ZEN(_consoleMock->WriteMock.CalledAsFollows(
   {
      { to_string(expectedTestCaseNumber) },
      { " ("s },
      { ") -> "s }
   }));
}

TEST(WriteLineOKIfSuccess_CallsTestResultWriteLineOKIfSuccess)
{
   TestResultMock testResultMock;
   testResultMock.WriteLineOKIfSuccessMock.Expect();
   //
   _testNXN->WriteLineOKIfSuccess(testResultMock);
   //
   ZEN(testResultMock.WriteLineOKIfSuccessMock.CalledOnceWith(_testNXN->_console.get()));
}

RUN_TESTS(TestNXNTests)


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

RUN_TEMPLATE_TESTS(AllTestNXNsWithinATemplateTestClass, int)


TESTS(TestTests)
AFACT(TwoArgConstructor_NewsComponents_SetsFullName_NameFunctionReturnsTestName)
FACTS(RunTestCase_ConstructorFails_DoesNotCallSubsequentTestPhases_ReturnsTestResultConstructorFail)
FACTS(RunTestCase_ConstructorSucceeds_StartupFails_DoesNotCallTest_DoesNotCallCleanup_CallsDestructor_ReturnsTestResultStartupFail)
AFACT(RunTestCase_AllTestPhasesSucceed_ReturnsExpectedTestResult)
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

RUN_TESTS(TestTests)

}

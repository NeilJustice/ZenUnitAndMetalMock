#include "pch.h"
#include "ZenUnit/Tests/TestNXN.h"
#include "TestingTestClass.h"
#include "ZenUnit.Test/Console/Mock/ConsoleMock.h"
#include "ZenUnit.Test/Results/Mock/TestResultMock.h"

namespace ZenUnit
{
   const size_t N = 1;

   TESTS(TestNXNTests)
   SPEC(Constructor_NewsConsole_SetsFields_GettersReturnExpected_2X2With4Args)
   SPEC(Constructor_NewsConsole_SetsFields_GettersReturnExpected_1X1With1Arg)
   SPEC(Constructor_NewsConsole_SetsFields_GettersReturnExpected_1X1With2Args)
   SPEC(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   SPEC(NumberOfTestCases_ReturnsNumberOfTestCaseArgsDividedByN)
   SPEC(Run_RunsAllTestCases_ResetsTestCaseArgsIndexTo0_ReturnsVectorOfTestResults)
   SPEC(NewTestClass_NewsTestClass)
   SPEC(Startup_CallsTestClassStartup)
   SPEC(TestBody_CallsNXNTestBody)
   SPEC(NXNTestBody_ThrowsLogicError)
   SPEC(Cleanup_CallsCleanup)
   SPEC(DeleteTestClass_DeletesTestClass)
   SPECX(PrintTestCaseNumberArgsArrow_WritesTestCaseNumberArrow)
   SPEC(PrintTestResultOutcome_CallsTestResultPrintTestOutcome)
   SPECEND

   unique_ptr<TestNXN<TestingTestClass, N, int>> _testNXN;
   ConsoleMock* _consoleMock;
   const char* const TestClassName = "TestClassName";
   const char* const TestName = "TestName";
   const char* const TestCaseArgsText = "1, 2, 3";

   STARTUP
   {
      _testNXN.reset(new TestNXN<TestingTestClass, N, int>("", "", "", 0));
      _testNXN->_console.reset(_consoleMock = new ConsoleMock);
   }

   TEST(Constructor_NewsConsole_SetsFields_GettersReturnExpected_2X2With4Args)
   {
      TestNXN<TestingTestClass, 2, int, int, int, int> testNXN(
         TestClassName, TestName, TestCaseArgsText, 0, 0, 0, 0);
      //
      WAS_NEWED(testNXN._console);
      IS_NULL(testNXN._testClass);
      ARE_EQUAL(TestCaseArgsText, testNXN._testCaseArgsText);
      ARE_EQUAL(0, testNXN._testCaseArgsIndex);
      ARE_EQUAL(TestName, testNXN.Name());
      ARE_EQUAL("TESTS(TestClassName)\nTEST(TestName)", testNXN.TestClassTestNameLines());
      ARE_EQUAL("(0)", testNXN.FileLineString());
      ARE_EQUAL(4, testNXN.NumberOfTestCaseArgs);
   }

   TEST(Constructor_NewsConsole_SetsFields_GettersReturnExpected_1X1With1Arg)
   {
      const TestNXN<TestingTestClass, 1, int> testNXN(TestClassName, TestName, TestCaseArgsText, 0);
      ARE_EQUAL(1, testNXN.NumberOfTestCaseArgs);
   }

   TEST(Constructor_NewsConsole_SetsFields_GettersReturnExpected_1X1With2Args)
   {
      const TestNXN<TestingTestClass, 1, int, int> testNXN(TestClassName, TestName, TestCaseArgsText, 0, 0);
      ARE_EQUAL(2, testNXN.NumberOfTestCaseArgs);
   }

   TEST(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   {
      const TestNXN<TestingTestClass, 1, int> testNXN_1X1_1Arg(TestClassName, TestName, TestCaseArgsText, 0);
      ARE_EQUAL(tuple<int>(0), testNXN_1X1_1Arg._testCaseArgs);

      const TestNXN<TestingTestClass, 1, int, int> testNXN_1X1_2Args(TestClassName, TestName, TestCaseArgsText, 0, 0);
      const tuple<int, int> expectedTestCaseArgs1(0, 0);
      ARE_EQUAL(expectedTestCaseArgs1, testNXN_1X1_2Args._testCaseArgs);

      const TestNXN<TestingTestClass, 2, const string&, volatile int> testNXN_2X2_4Args(
         TestClassName, TestName, TestCaseArgsText, string(), 100);
      const tuple<string, int> expectedTestCaseArgs2(string(), 100);
      ARE_EQUAL(expectedTestCaseArgs2, testNXN_2X2_4Args._testCaseArgs);
   }

   TEST(NumberOfTestCases_ReturnsNumberOfTestCaseArgsDividedByN)
   {
      const TestNXN<TestingTestClass, 1, int>
         test1X1(TestClassName, TestName, TestCaseArgsText, 0);
      ARE_EQUAL(1, test1X1.NumberOfTestCases());

      const TestNXN<TestingTestClass, 1, int, int>
         test1X1_2Args(TestClassName, TestName, TestCaseArgsText, 0, 0);
      ARE_EQUAL(2, test1X1_2Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 2, int, int>
         test2X2_2Args(TestClassName, TestName, TestCaseArgsText, 0, 0);
      ARE_EQUAL(1, test2X2_2Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 2, int, int, int, int>
         test2X2_4Args(TestClassName, TestName, TestCaseArgsText, 0, 0, 0, 0);
      ARE_EQUAL(2, test2X2_4Args.NumberOfTestCases());

      const TestNXN<TestingTestClass, 3, int, int, int, int, int, int, int, int, int>
         test3X3_9Args(TestClassName, TestName, TestCaseArgsText, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      ARE_EQUAL(3, test3X3_9Args.NumberOfTestCases());
   }

   TEST(Run_RunsAllTestCases_ResetsTestCaseArgsIndexTo0_ReturnsVectorOfTestResults)
   {
      struct Test1X1SelfMocked : public Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>
      {
         ZENMOCK_NONVOID0(TestResult, MockableCallBaseRunTestCase)
         ZENMOCK_VOID1_CONST(PrintTestCaseNumberArgsArrow, int)
         ZENMOCK_VOID1_CONST(PrintTestResultOutcome, const TestResult&)
         Test1X1SelfMocked()
            : Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>("", "", "", 0, 0) {}
      } test1X1SelfMocked;

      test1X1SelfMocked.PrintTestCaseNumberArgsArrowMock.Expect();
      TestResult firstTestResult;
      firstTestResult.fullName.testName = "FirstTest";
      TestResult secondTestResult;
      secondTestResult.fullName.testName = "SecondTest";
      test1X1SelfMocked.MockableCallBaseRunTestCaseMock.ExpectAndReturnValues(firstTestResult, secondTestResult);
      test1X1SelfMocked.PrintTestResultOutcomeMock.Expect();
      //
      const vector<TestResult> testResults = test1X1SelfMocked.Run();
      //
      ZEN(test1X1SelfMocked.PrintTestCaseNumberArgsArrowMock.AssertCalls({ 0, 1 }));
      TestResult expectedFirstTestResult = firstTestResult;
      expectedFirstTestResult.testCaseIndex = 0;
      TestResult expectedSecondTestResult = secondTestResult;
      expectedSecondTestResult.testCaseIndex = 1;
      ZEN(test1X1SelfMocked.MockableCallBaseRunTestCaseMock.AssertCalledNTimes(2));
      ZEN(test1X1SelfMocked.PrintTestResultOutcomeMock.AssertCalls(
      {
         expectedFirstTestResult,
         expectedSecondTestResult
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
      WAS_NEWED(_testNXN->_testClass);
      _testNXN->_testClass.reset();
   }

   TEST(Startup_CallsTestClassStartup)
   {
      _testNXN->_testClass.reset(new TestingTestClass);
      _testNXN->_testClass->StartupMock.Expect();
      //
      _testNXN->Startup();
      //
      ZEN(_testNXN->_testClass->StartupMock.AssertCalledOnce());
   }

   TEST(TestBody_CallsNXNTestBody)
   {
      struct TestNXN_NXNTestBodyMocked : public Zen::Mock<TestNXN<TestingTestClass, 1, int>>
      {
         ZENMOCK_VOID2(NXNTestBody, TestingTestClass*, size_t)
         TestNXN_NXNTestBodyMocked()
            : Zen::Mock<TestNXN<TestingTestClass, 1, int>>("", "", "", 0) {}
      } testNXN_NXNTestBodyMocked;

      testNXN_NXNTestBodyMocked._testClass.reset(new TestingTestClass);
      testNXN_NXNTestBodyMocked._testCaseArgsIndex = 1;
      testNXN_NXNTestBodyMocked.NXNTestBodyMock.Expect();
      //
      testNXN_NXNTestBodyMocked.TestBody();
      //
      ZEN(testNXN_NXNTestBodyMocked.NXNTestBodyMock.AssertCalledOnceWith(
         testNXN_NXNTestBodyMocked._testClass.get(), testNXN_NXNTestBodyMocked._testCaseArgsIndex));
   }

   TEST(NXNTestBody_ThrowsLogicError)
   {
      THROWS(_testNXN->NXNTestBody(nullptr, 0), logic_error, "N/A");
   }

   TEST(Cleanup_CallsCleanup)
   {
      _testNXN->_testClass.reset(new TestingTestClass);
      _testNXN->_testClass->CleanupMock.Expect();
      //
      _testNXN->Cleanup();
      //
      ZEN(_testNXN->_testClass->CleanupMock.AssertCalledOnce());
   }

   TEST(DeleteTestClass_DeletesTestClass)
   {
      _testNXN->_testClass.reset(new TestingTestClass);
      IS_FALSE(TestingTestClass::s_destructorCalled);
      //
      _testNXN->DeleteTestClass();
      //
      IS_TRUE(TestingTestClass::s_destructorCalled);
   }

   TEST3X3(PrintTestCaseNumberArgsArrow_WritesTestCaseNumberArrow,
      int testCaseIndex, int expectedTestCaseNumber, size_t expectedTestCaseArgsPrintingStartIndex,
      0, 1, 0ull,
      1, 2, 1ull)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->PrintStringsCommaSeparatedMock.Expect();
      _testNXN->_testCaseArgStrings = { "Arg0", "Arg1" };
      //
      _testNXN->PrintTestCaseNumberArgsArrow(testCaseIndex);
      //
      ZEN(_consoleMock->WriteColorMock.AssertCalls(
      {
         { " [", Color::Green },
         { "]", Color::Green }
      }));
      ZEN(_consoleMock->PrintStringsCommaSeparatedMock.AssertCalledOnceWith(
         _testNXN->_testCaseArgStrings, expectedTestCaseArgsPrintingStartIndex, N));
      ZEN(_consoleMock->WriteMock.AssertCalls(
      {
         to_string(expectedTestCaseNumber),
         " ("s,
         ") -> "s
      }));
   }

   TEST(PrintTestResultOutcome_CallsTestResultPrintTestOutcome)
   {
      TestResultMock testResultMock;
      testResultMock.PrintTestOutcomeMock.Expect();
      //
      _testNXN->PrintTestResultOutcome(testResultMock);
      //
      ZEN(testResultMock.PrintTestOutcomeMock.AssertCalledOnceWith(_testNXN->_console.get()));
   }

   }; RUN(TestNXNTests)
}

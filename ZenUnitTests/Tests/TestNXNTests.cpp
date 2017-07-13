#include "pch.h"
#include "ZenUnit/Tests/TestNXN.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Tests/TestingTestClass.h"

namespace ZenUnit
{
   const size_t N = 1;

   TESTS(TestNXNTests)
   SPEC(Constructor_NewsConsole_SetsFields_GettersReturnExpected_2X2With4Args)
   SPEC(Constructor_StoresDecayedTypeCopiesOfTestCaseArguments)
   SPEC(NumberOfTestCases_ReturnsNumberOfTestCaseArgsDividedByN)
   SPEC(Run_RunsAllTestCases_ResetsTestCaseArgsIndexTo0_ReturnsVectorOfTestResults)
   SPEC(NewTestClass_NewsTestClass)
   SPEC(Startup_CallsTestClassStartup)
   SPEC(TestBody_CallsRunNXNTestCase)
   SPEC(RunNXNTestCase_DoesNothing)
   SPEC(Cleanup_CallsCleanup)
   SPEC(DeleteTestClass_DeletesTestClass)
   SPECX(PrintTestCaseNumberArgsThenArrow_WritesTestCaseNumberArrow)
   SPEC(PrintOKIfTestPassed_CallsTestResultPrintOKIfTestPassed)
   SPECEND

   unique_ptr<TestNXN<TestingTestClass, N, int>> _testNXN;
   ConsoleMock* _consoleMock;
   const char* const TestClassName = "Tests";
   const char* const TestName = "Test";
   const char* const TestCaseArgsText = "1, 2, 3";

   STARTUP
   {
      _testNXN = make_unique<TestNXN<TestingTestClass, N, int>>("", "", "", 0);
      _testNXN->_console.reset(_consoleMock = new ConsoleMock);
   }

   TEST(Constructor_NewsConsole_SetsFields_GettersReturnExpected_2X2With4Args)
   {
      TestNXN<TestingTestClass, 2, int, int, int, int> testNXN(
         TestClassName, TestName, TestCaseArgsText, 0, 0, 0, 0);
      //
      WAS_NEWED(testNXN._console);
      IS_NULL(testNXN._testClass);
      ARE_EQUAL(0, testNXN._testCaseArgsIndex);
      ARE_EQUAL(TestName, testNXN.Name());
      ARE_EQUAL("TESTS(Tests)\nTEST2X2(Test)", testNXN.FullTestNameValue());
      ARE_EQUAL("(0)", testNXN.FileLineString());
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
         ZENMOCK_VOID1_CONST(PrintTestCaseNumberArgsThenArrow, unsigned short)
         ZENMOCK_VOID1_CONST(PrintOKIfTestPassed, const TestResult&)
         Test1X1SelfMocked()
            : Zen::Mock<TestNXN<TestingTestClass, 1, int, int>>("", "", "", 0, 0) {}
      } test1X1SelfMocked;

      test1X1SelfMocked.PrintTestCaseNumberArgsThenArrowMock.Expect();
      TestResult firstTestResult;
      firstTestResult.fullTestName.testName = "FirstTest";
      TestResult secondTestResult;
      secondTestResult.fullTestName.testName = "SecondTest";
      test1X1SelfMocked.MockableCallBaseRunTestCaseMock.ExpectAndReturnValues(firstTestResult, secondTestResult);
      test1X1SelfMocked.PrintOKIfTestPassedMock.Expect();
      //
      const vector<TestResult> testResults = test1X1SelfMocked.Run();
      //
      ZEN(test1X1SelfMocked.PrintTestCaseNumberArgsThenArrowMock.AssertCalls({ 0, 1 }));
      TestResult expectedFirstTestResult = firstTestResult;
      expectedFirstTestResult.testCaseIndex = 0;
      TestResult expectedSecondTestResult = secondTestResult;
      expectedSecondTestResult.testCaseIndex = 1;
      ZEN(test1X1SelfMocked.MockableCallBaseRunTestCaseMock.AssertCalledNTimes(2));
      ZEN(test1X1SelfMocked.PrintOKIfTestPassedMock.AssertCalls(
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
      _testNXN->_testClass = make_unique<TestingTestClass>();
      _testNXN->_testClass->StartupMock.Expect();
      //
      _testNXN->Startup();
      //
      ZEN(_testNXN->_testClass->StartupMock.AssertCalledOnce());
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
      ZEN(testNXN_RunNXNTestCaseMocked.RunNXNTestCaseMock.AssertCalledOnceWith(
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
      ZEN(_testNXN->_testClass->CleanupMock.AssertCalledOnce());
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
      unsigned short testCaseIndex, int expectedTestCaseNumber, size_t expectedTestCaseArgsPrintingStartIndex,
      static_cast<unsigned short>(0), 1, size_t(0),
      static_cast<unsigned short>(1), 2, size_t(1))
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteMock.Expect();
      _consoleMock->PrintStringsCommaSeparatedMock.Expect();
      _testNXN->_commaSplitTestCaseArgs = { "Arg0", "Arg1" };
      //
      _testNXN->PrintTestCaseNumberArgsThenArrow(testCaseIndex);
      //
      ZEN(_consoleMock->WriteColorMock.AssertCalls(
      {
         { " [", Color::Green },
         { "]", Color::Green }
      }));
      ZEN(_consoleMock->PrintStringsCommaSeparatedMock.AssertCalledOnceWith(
         _testNXN->_commaSplitTestCaseArgs, expectedTestCaseArgsPrintingStartIndex, N));
      ZEN(_consoleMock->WriteMock.AssertCalls(
      {
         to_string(expectedTestCaseNumber),
         " ("s,
         ") -> "s
      }));
   }

   TEST(PrintOKIfTestPassed_CallsTestResultPrintOKIfTestPassed)
   {
      TestResultMock testResultMock;
      testResultMock.PrintOKIfTestPassedMock.Expect();
      //
      _testNXN->PrintOKIfTestPassed(testResultMock);
      //
      ZEN(testResultMock.PrintOKIfTestPassedMock.AssertCalledOnceWith(_testNXN->_console.get()));
   }

   }; RUN(TestNXNTests)

   template<typename T>
   TEMPLATETESTS(AllTestNXNsWithinATemplateTestClass, T)
   SPEC(Test)
   SPECX(Test1X1)
   SPECX(Test2X2)
   SPECX(Test3X3)
   SPECX(Test4X4)
   SPECX(Test5X5)
   SPECX(Test6X6)
   SPECX(Test7X7)
   SPECX(Test8X8)
   SPECX(Test9X9)
   SPECX(Test10X10)
   SPECEND

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
   RUNTEMPLATE(AllTestNXNsWithinATemplateTestClass, int)
}

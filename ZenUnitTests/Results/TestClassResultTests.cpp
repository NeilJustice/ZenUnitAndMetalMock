#include "pch.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Results/TestClassResult.h"
#include "ZenUnit/Results/TestFailureNumberer.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/ForEacherTwoExtraArgsMock.h"

namespace ZenUnit
{
   TESTS(TestClassResultTests)
   SPEC(DefaultConstructor_NewsForEacher)
   SPEC(Assign_CopiesArgumentToThis)
   SPEC(AddTestResults_AppendTestResultsToEndOfTestResultsVector)
   SPEC(NumberOfFailedTestCases_ReturnsNumberOfNonSuccessTestsInTestResultsVector)
   SPEC(Milliseconds_EmptyTestResultsVector_Returns0)
   SPEC(Milliseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMilliseconds)
   SPEC(PrintTestFailures_PrintsJustTestFailedToConsole)
   SPEC(PrintResultLine_0FailedTest_WritesOKInGreen)
   SPECX(PrintResultLine_1OrMoreFailedTests_WritesFailedInRed)
   SPEC(ZenUnitEqualizer_ThrowsIfTestResultsNotEqual)
   SPEC(PrintTestResultIfFailure_CallsTestResultPrintIfFailure)
   SPECEND

   TestClassResult _testClassResult;

   struct TestClassResultSelfMocked : public Zen::Mock<TestClassResult>
   {
      ZENMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   } _testClassResultSelfMocked;

   TEST(DefaultConstructor_NewsForEacher)
   {
      TestClassResult testClassResult;
      WAS_NEWED(testClassResult._forEacherTwoExtraArgs);
   }

   TEST(Assign_CopiesArgumentToThis)
   {
      TestClassResult otherTestClassResult;
      otherTestClassResult._testResults.resize(1);
      //
      _testClassResult.Assign(otherTestClassResult);
      //
      ARE_EQUAL(otherTestClassResult, _testClassResult);
   }

   TEST(AddTestResults_AppendTestResultsToEndOfTestResultsVector)
   {
      _testClassResult.AddTestResults({});
      //
      TestClassResult expectedTestClassResult;
      ARE_EQUAL(expectedTestClassResult, _testClassResult);

      TestResult testResult1;
      testResult1.fullName.testName = "Test1";
      //
      _testClassResult.AddTestResults({ testResult1 });
      //
      expectedTestClassResult._testResults = { testResult1 };
      ARE_EQUAL(expectedTestClassResult, _testClassResult);

      TestResult testResult2;
      testResult2.fullName.testName = "Test2";
      //
      _testClassResult.AddTestResults({ testResult1, testResult2 });
      //
      expectedTestClassResult._testResults = { testResult1, testResult1, testResult2 };
      ARE_EQUAL(expectedTestClassResult, _testClassResult);
   }

   TEST(NumberOfFailedTestCases_ReturnsNumberOfNonSuccessTestsInTestResultsVector)
   {
      ARE_EQUAL(0, _testClassResult.NumberOfFailedTestCases());
      TestResult testFailure1;
      testFailure1.testOutcome = TestOutcome::Anomaly;
      TestResult testSuccess1;
      testSuccess1.testOutcome = TestOutcome::Success;
      TestResult testFailure2;
      testFailure2.testOutcome = TestOutcome::SuccessButPastDeadline;
      TestResult testSuccess2;
      testSuccess2.testOutcome = TestOutcome::Success;
      TestResult testFailure3;
      testFailure3.testOutcome = TestOutcome::Exception;
      _testClassResult._testResults = { testFailure1, testSuccess1, testFailure2, testSuccess2, testFailure3 };
      //
      const size_t numberOfFailedTestCases = _testClassResult.NumberOfFailedTestCases();
      //
      ARE_EQUAL(3, numberOfFailedTestCases);
   }

   TEST(PrintTestFailures_PrintsJustTestFailedToConsole)
   {
      using TypedefForEacherTwoExtraArgsMock = ForEacherTwoExtraArgsMock<vector<TestResult>,
         void (*)(const TestResult&, const Console*, TestFailureNumberer*),
         const Console*, TestFailureNumberer*>;
      const TypedefForEacherTwoExtraArgsMock* const forEacherTwoExtraArgsMock = new TypedefForEacherTwoExtraArgsMock;
      forEacherTwoExtraArgsMock->ForEachMock.Expect();
      _testClassResult._forEacherTwoExtraArgs.reset(forEacherTwoExtraArgsMock);
      const Console console;
      TestFailureNumberer testFailureNumberer;
      //
      _testClassResult.PrintTestFailures(&console, &testFailureNumberer);
      //
      ZEN(forEacherTwoExtraArgsMock->ForEachMock.AssertCalledOnceWith(
         &_testClassResult._testResults, TestClassResult::PrintTestResultIfFailure, &console, &testFailureNumberer));
   }

   TEST(Milliseconds_EmptyTestResultsVector_Returns0)
   {
      ARE_EQUAL(0, _testClassResult._testResults.size());
      //
      const unsigned milliseconds = _testClassResult.Milliseconds();
      //
      ARE_EQUAL(0, milliseconds);
   }

   TEST(Milliseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMilliseconds)
   {
      TestResult testResultA;
      testResultA.milliseconds = 1;
      TestResult testResultB;
      testResultB.milliseconds = 2;
      _testClassResult._testResults = { testResultA, testResultB };
      //
      const unsigned milliseconds = _testClassResult.Milliseconds();
      //
      ARE_EQUAL(3, milliseconds);
   }

   TEST(PrintResultLine_0FailedTest_WritesOKInGreen)
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.ExpectAndReturn(0);
      ConsoleMock consoleMock;
      consoleMock.WriteColorMock.Expect();
      consoleMock.WriteNewlineMock.Expect();
      //
      _testClassResultSelfMocked.PrintResultLine(&consoleMock);
      //
      ZEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.AssertCalledOnce());
      ZEN(consoleMock.WriteColorMock.AssertCalledOnceWith("[ OK ]", Color::Green));
      ZEN(consoleMock.WriteNewlineMock.AssertCalledOnce());
   }

   TEST1X1(PrintResultLine_1OrMoreFailedTests_WritesFailedInRed,
      size_t numberOfFailedTestCases,
      1ULL,
      2ULL,
      3ULL)
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.ExpectAndReturn(numberOfFailedTestCases);
      ConsoleMock consoleMock;
      consoleMock.WriteColorMock.Expect();
      consoleMock.WriteNewlineMock.Expect();
      //
      _testClassResultSelfMocked.PrintResultLine(&consoleMock);
      //
      ZEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.AssertCalledOnce());
      ZEN(consoleMock.WriteColorMock.AssertCalledOnceWith("[FAILED]", Color::Red));
      ZEN(consoleMock.WriteNewlineMock.AssertCalledOnce());
   }

   TEST(PrintTestResultIfFailure_CallsTestResultPrintIfFailure)
   {
      TestResultMock testResultMock;
      testResultMock.PrintIfFailureMock.Expect();
      const Console console;
      TestFailureNumberer testFailureNumberer;
      //
      _testClassResult.PrintTestResultIfFailure(testResultMock, &console, &testFailureNumberer);
      //
      ZEN(testResultMock.PrintIfFailureMock.AssertCalledOnceWith(&console, &testFailureNumberer));
   }

   TEST(ZenUnitEqualizer_ThrowsIfTestResultsNotEqual)
   {
      EQUALIZER_THROWS_INIT(TestClassResult);
      EQUALIZER_THROWS(TestClassResult, _testResults, vector<TestResult> { TestResult() });
   }

   }; RUN(TestClassResultTests)
}

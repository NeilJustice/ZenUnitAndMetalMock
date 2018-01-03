#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Testing/RandomPrintMode.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TwoExtraArgsForEacherMock.h"

namespace ZenUnit
{
   TESTS(TestClassResultTests)
   AFACT(CopyConstructor_CopiesForEacherAndTestResults)
   AFACT(AssignmentOperator_CopiesForEacherAndTestResults)
   AFACT(AssignmentOperator_SelfAssignment_NothingHappens)
   AFACT(MoveConstructor_MovesForEacherAndTestResults)
   AFACT(MoveAssignmentOperator_MovesForEacherAndTestResults)
   AFACT(AddTestResults_AppendTestResultsToEndOfTestResultsVector)
   AFACT(NumberOfFailedTestCases_ReturnsNumberOfNonSuccessTestsInTestResultsVector)
   AFACT(Milliseconds_EmptyTestResultsVector_Returns0)
   AFACT(Milliseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMilliseconds)
   AFACT(PrintTestFailures_PrintsJustTestFailedToConsole)
   AFACT(NonMinimalPrintResultLine_0FailedTest_WritesOKInGreen)
   FACTS(NonMinimalPrintResultLine_1OrMoreFailedTests_WritesFailedInRed)
   AFACT(PrintTestResultIfFailure_CallsTestResultPrintIfFailure)
   AFACT(ZenUnitEqualizer_ThrowsIfTestResultsNotEqual)
   EVIDENCE

   TestClassResult _testClassResult;

   struct TestClassResultSelfMocked : public Zen::Mock<TestClassResult>
   {
      ZENMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   } _testClassResultSelfMocked;

   TEST(CopyConstructor_CopiesForEacherAndTestResults)
   {
      TestClassResult testClassResult = TestClassResult::TestingNonDefault();
      //
      TestClassResult copy(testClassResult);
      //
      ARE_COPIES(copy, testClassResult);
   }

   TEST(AssignmentOperator_CopiesForEacherAndTestResults)
   {
      TestClassResult testClassResult = TestClassResult::TestingNonDefault();
      TestClassResult copy;
      //
      copy = testClassResult;
      //
      ARE_COPIES(copy, testClassResult);
   }

   TEST(AssignmentOperator_SelfAssignment_NothingHappens)
   {
      TestClassResult testClassResult = TestClassResult::TestingNonDefault();
      //
      testClassResult = testClassResult;
      //
      ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
   }

   TEST(MoveConstructor_MovesForEacherAndTestResults)
   {
      TestClassResult testClassResult = TestClassResult::TestingNonDefault();
      //
      TestClassResult moved(move(testClassResult));
      //
      ARE_EQUAL(TestClassResult(), testClassResult);
      ARE_EQUAL(TestClassResult::TestingNonDefault(), moved);
   }

   TEST(MoveAssignmentOperator_MovesForEacherAndTestResults)
   {
      TestClassResult testClassResult = TestClassResult::TestingNonDefault();
      TestClassResult moved;
      //
      moved = move(testClassResult);
      //
      ARE_EQUAL(TestClassResult(), testClassResult);
      ARE_EQUAL(TestClassResult::TestingNonDefault(), moved);
   }

   TEST(AddTestResults_AppendTestResultsToEndOfTestResultsVector)
   {
      _testClassResult.AddTestResults({});
      //
      TestClassResult expectedTestClassResult;
      ARE_EQUAL(expectedTestClassResult, _testClassResult);

      TestResult testResult1;
      testResult1.fullTestName.testName = "Test1";
      //
      _testClassResult.AddTestResults({ testResult1 });
      //
      expectedTestClassResult._testResults = { testResult1 };
      ARE_EQUAL(expectedTestClassResult, _testClassResult);

      TestResult testResult2;
      testResult2.fullTestName.testName = "Test2";
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
      using TypedefTwoExtraArgsForEacherMock = TwoExtraArgsForEacherMock<vector<TestResult>,
         void (*)(const TestResult&, const Console*, TestFailureNumberer*),
         const Console*, TestFailureNumberer*>;
      const TypedefTwoExtraArgsForEacherMock forEacherTwoExtraArgsMock;
      forEacherTwoExtraArgsMock.TwoExtraArgsForEachMock.Expect();
      const Console console;
      TestFailureNumberer testFailureNumberer;
      //
      _testClassResult.PrintTestFailures(&forEacherTwoExtraArgsMock, &console, &testFailureNumberer);
      //
      ZEN(forEacherTwoExtraArgsMock.TwoExtraArgsForEachMock.CalledOnceWith(
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

   TEST(NonMinimalPrintResultLine_0FailedTest_WritesOKInGreen)
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.ExpectAndReturn(0);
      ConsoleMock consoleMock;
      consoleMock.WriteMock.Expect();
      consoleMock.NonMinimalWriteColorMock.Expect();
      consoleMock.NonMinimalWriteNewLineMock.Expect();
      const PrintMode printMode = RandomPrintMode();
      //
      _testClassResultSelfMocked.NonMinimalPrintResultLine(&consoleMock, printMode);
      //
      ZEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce());
      ZEN(consoleMock.WriteMock.CalledMultipleTimes(
      {
         { "[  " },
         { "  ]" }
      }));
      ZEN(consoleMock.NonMinimalWriteColorMock.CalledOnceWith("OK", Color::Green, printMode));
      ZEN(consoleMock.NonMinimalWriteNewLineMock.CalledOnceWith(printMode));
   }

   TEST1X1(NonMinimalPrintResultLine_1OrMoreFailedTests_WritesFailedInRed,
      size_t numberOfFailedTestCases,
      size_t(1),
      size_t(2),
      size_t(3))
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.ExpectAndReturn(numberOfFailedTestCases);
      ConsoleMock consoleMock;
      consoleMock.NonMinimalWriteColorMock.Expect();
      consoleMock.NonMinimalWriteNewLineMock.Expect();
      const PrintMode printMode = RandomPrintMode();
      _testClassResultSelfMocked.NonMinimalPrintResultLine(&consoleMock, printMode);
      //
      ZEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce());
      ZEN(consoleMock.NonMinimalWriteColorMock.CalledOnceWith("[TestClass Failed]", Color::Red, printMode));
      ZEN(consoleMock.NonMinimalWriteNewLineMock.CalledOnceWith(printMode));
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
      ZEN(testResultMock.PrintIfFailureMock.CalledOnceWith(&console, &testFailureNumberer));
   }

   TEST(ZenUnitEqualizer_ThrowsIfTestResultsNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(TestClassResult);
      EQUALIZER_THROWS_FOR_FIELD(TestClassResult, _testResults, vector<TestResult> { TestResult() });
   }

   }; RUNTESTS(TestClassResultTests)
}

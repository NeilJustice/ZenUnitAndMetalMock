#include "pch.h"
#include "ZenUnitLibraryTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"

namespace ZenUnit
{
   TESTS(TestClassResultTests)
   AFACT(DefaultConstructor_SetsWatchFunction)
   AFACT(CopyConstructor_CopiesForEacherAndTestResults)
   AFACT(AssignmentOperator_CopiesForEacherAndTestResults)
   AFACT(AssignmentOperator_SelfAssignment_NothingHappens)
   AFACT(MoveConstructor_MovesForEacherAndTestResults)
   AFACT(MoveAssignmentOperator_MovesForEacherAndTestResults)
   AFACT(AddTestResults_AppendTestResultsToEndOfTestResultsVector)
   AFACT(NumberOfFailedTestCases_ReturnsNumberOfNonSuccessTestsInTestResultsVector)
   AFACT(SumOfTestResultMicroseconds_EmptyTestResultsVector_Returns0)
   AFACT(SumOfTestResultMicroseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMicroseconds)
   AFACT(PrintTestFailures_PrintsJustTestFailedToConsole)
   AFACT(PrintTestClassResultLine_0FailedTestCases_WritesOKInGreen)
   FACTS(PrintTestClassResultLine_1OrMoreFailedTests_WritesFailedInRed)
   AFACT(PrintTestResultIfFailure_CallsTestResultPrintIfFailure)
   AFACT(ZenUnitEqualizer_ThrowsIfTestResultsNotEqual)
   EVIDENCE

   TestClassResult _testClassResult;

   class TestClassResultSelfMocked : public Zen::Mock<TestClassResult>
   {
   public:
      ZENMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
      ZENMOCK_NONVOID0_CONST(unsigned, SumOfTestResultMicroseconds)
   } _testClassResultSelfMocked;

   ZENMOCK_NONVOID1_STATIC(string, ZenUnit::Watch, MicrosecondsToTwoDecimalPlaceMillisecondsString, unsigned)

   STARTUP
   {
      _testClassResultSelfMocked._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString
         = BIND_1ARG_ZENMOCK_OBJECT(MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject);
   }

   TEST(DefaultConstructor_SetsWatchFunction)
   {
      TestClassResult testClassResult;
      STD_FUNCTION_TARGETS(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString,
         testClassResult._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString);
   }

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
      const TestClassResult moved(std::move(testClassResult));
      //
      ARE_EQUAL(TestClassResult(), testClassResult);
      ARE_EQUAL(TestClassResult::TestingNonDefault(), moved);
   }

   TEST(MoveAssignmentOperator_MovesForEacherAndTestResults)
   {
      TestClassResult testClassResult = TestClassResult::TestingNonDefault();
      TestClassResult moved;
      //
      moved = std::move(testClassResult);
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
      using TypedefThreeArgForEacherMock = ThreeArgForEacherMock<vector<TestResult>,
         void(*)(const TestResult&, const Console*, TestFailureNumberer*),
         const Console*, TestFailureNumberer*>;
      const TypedefThreeArgForEacherMock forEacherThreeArgsMock;
      forEacherThreeArgsMock.ThreeArgForEachMock.Expect();
      const Console console;
      TestFailureNumberer testFailureNumberer;
      //
      _testClassResult.PrintTestFailures(&forEacherThreeArgsMock, &console, &testFailureNumberer);
      //
      ZEN(forEacherThreeArgsMock.ThreeArgForEachMock.CalledOnceWith(
         &_testClassResult._testResults, TestClassResult::PrintTestResultIfFailure, &console, &testFailureNumberer));
   }

   TEST(SumOfTestResultMicroseconds_EmptyTestResultsVector_Returns0)
   {
      ARE_EQUAL(0, _testClassResult._testResults.size());
      //
      const unsigned microseconds = _testClassResult.SumOfTestResultMicroseconds();
      //
      ARE_EQUAL(0, microseconds);
   }

   TEST(SumOfTestResultMicroseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMicroseconds)
   {
      TestResult testResultA;
      testResultA.microseconds = ZenUnit::Random<unsigned>();
      TestResult testResultB;
      testResultB.microseconds = ZenUnit::Random<unsigned>();
      _testClassResult._testResults = { testResultA, testResultB };
      //
      const unsigned microseconds = _testClassResult.SumOfTestResultMicroseconds();
      //
      ARE_EQUAL(testResultA.microseconds + testResultB.microseconds, microseconds);
   }

   TEST(PrintTestClassResultLine_0FailedTestCases_WritesOKInGreen)
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.Return(0);
      const unsigned sumOfTestResultMicroseconds =
         _testClassResultSelfMocked.SumOfTestResultMicrosecondsMock.ReturnRandom();
      const string oneDecimalPlaceMilliseconds = ZenUnit::Random<string>();
      MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject.Return(oneDecimalPlaceMilliseconds);
      ConsoleMock consoleMock;
      consoleMock.WriteMock.Expect();
      consoleMock.WriteColorMock.Expect();
      consoleMock.WriteLineMock.Expect();
      //
      _testClassResultSelfMocked.PrintTestClassResultLine(&consoleMock);
      //
      ZEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce());
      ZEN(_testClassResultSelfMocked.SumOfTestResultMicrosecondsMock.CalledOnce());
      ZEN(MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject.CalledOnceWith(sumOfTestResultMicroseconds));
      ZEN(consoleMock.WriteMock.CalledOnceWith("[  " ));
      ZEN(consoleMock.WriteColorMock.CalledOnceWith("OK", Color::Green));
      ZEN(consoleMock.WriteLineMock.CalledOnceWith("  ] " + oneDecimalPlaceMilliseconds));
   }

   TEST1X1(PrintTestClassResultLine_1OrMoreFailedTests_WritesFailedInRed,
      size_t numberOfFailedTestCases,
      size_t(1),
      size_t(2),
      size_t(3))
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.Return(numberOfFailedTestCases);
      const unsigned microseconds = _testClassResultSelfMocked.SumOfTestResultMicrosecondsMock.ReturnRandom();
      const string oneDecimalPlaceMilliseconds = MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject.ReturnRandom();
      ConsoleMock consoleMock;
      consoleMock.WriteLineColorMock.Expect();
      //
      _testClassResultSelfMocked.PrintTestClassResultLine(&consoleMock);
      //
      ZEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce());
      ZEN(_testClassResultSelfMocked.SumOfTestResultMicrosecondsMock.CalledOnce());
      ZEN(MicrosecondsToTwoDecimalPlaceMillisecondsString_ZenMockObject.CalledOnceWith(microseconds));
      ZEN(consoleMock.WriteLineColorMock.CalledOnceWith("[TestClass Failed] " + oneDecimalPlaceMilliseconds, Color::Yellow));
   }

   TEST(PrintTestResultIfFailure_CallsTestResultPrintIfFailure)
   {
      TestResultMock testResultMock;
      testResultMock.PrintIfFailureMock.Expect();
      const Console console;
      TestFailureNumberer testFailureNumberer;
      //
      TestClassResult::PrintTestResultIfFailure(testResultMock, &console, &testFailureNumberer);
      //
      ZEN(testResultMock.PrintIfFailureMock.CalledOnceWith(&console, &testFailureNumberer));
   }

   TEST(ZenUnitEqualizer_ThrowsIfTestResultsNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(TestClassResult);
      EQUALIZER_THROWS(TestClassResult, _testResults, vector<TestResult> { TestResult() });
   }

   RUN_TESTS(TestClassResultTests)
}

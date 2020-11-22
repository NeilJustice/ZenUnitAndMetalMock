#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/ThreeArgForEacherMock.h"

namespace ZenUnit
{
   TESTS(TestClassResultTests)
   AFACT(DefaultConstructor_SetsWatchFunction)
   AFACT(CopyConstructor_CopiesForEacherAndTestResults)
   AFACT(AssignmentOperator_CopiesForEacherAndTestResults)
   #ifdef _WIN32
   AFACT(AssignmentOperator_SelfAssignment_NothingHappens)
   #endif
   AFACT(MoveConstructor_MovesForEacherAndTestResults)
   AFACT(MoveAssignmentOperator_MovesForEacherAndTestResults)
   AFACT(AddTestResults_AppendTestResultsToEndOfTestResultsVector)
   AFACT(NumberOfFailedTestCases_ReturnsNumberOfNonSuccessTestsInTestResultsVector)
   AFACT(PrintTestFailures_PrintsJustTestFailedToConsole)
   AFACT(PrintTestClassResultLine_0FailedTestCases_WritesOKInGreen)
   FACTS(PrintTestClassResultLine_1OrMoreFailedTests_WritesFailedInRed)
   AFACT(PrintTestResultIfFailure_CallsTestResultPrintIfFailure)
   AFACT(SumOfTestResultMicroseconds_EmptyTestResultsVector_Returns0)
   AFACT(SumOfTestResultMicroseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMicroseconds)
   EVIDENCE

   TestClassResult _testClassResult;

   class TestClassResultSelfMocked : public Metal::Mock<TestClassResult>
   {
   public:
      METALMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
      METALMOCK_NONVOID0_CONST(long long, SumOfTestResultMicroseconds)
   } _testClassResultSelfMocked;

   METALMOCK_NONVOID1_STATIC(string, ZenUnit::Watch, MicrosecondsToTwoDecimalPlaceMillisecondsString, long long)

   STARTUP
   {
      _testClassResultSelfMocked._call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString
         = BIND_1ARG_METALMOCK_OBJECT(MicrosecondsToTwoDecimalPlaceMillisecondsStringMock);
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
      TestClassResult copyOfTestClassResult(testClassResult);
      //
      ARE_COPIES(copyOfTestClassResult, testClassResult);
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

   // Clang treats self assignment as an error
   #ifdef _WIN32
   TEST(AssignmentOperator_SelfAssignment_NothingHappens)
   {
      TestClassResult testClassResult = TestClassResult::TestingNonDefault();
      //
      testClassResult = testClassResult;
      //
      ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
   }
   #endif

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
      TestClassResult movedTestClassResult;
      //
      movedTestClassResult = std::move(testClassResult);
      //
      ARE_EQUAL(TestClassResult(), testClassResult);
      ARE_EQUAL(TestClassResult::TestingNonDefault(), movedTestClassResult);
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
      IS_ZERO(_testClassResult.NumberOfFailedTestCases());

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
      METALMOCK(forEacherThreeArgsMock.ThreeArgForEachMock.CalledOnceWith(
         &_testClassResult._testResults, TestClassResult::PrintTestResultIfFailure, &console, &testFailureNumberer));
   }

   TEST(PrintTestClassResultLine_0FailedTestCases_WritesOKInGreen)
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.Return(0ull);
      const long long sumOfTestResultMicroseconds =
         _testClassResultSelfMocked.SumOfTestResultMicrosecondsMock.ReturnRandom();

      const string oneDecimalPlaceMilliseconds = MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.ReturnRandom();

      ConsoleMock consoleMock;
      consoleMock.WriteMock.Expect();
      consoleMock.WriteColorMock.Expect();
      consoleMock.WriteLineMock.Expect();
      //
      _testClassResultSelfMocked.PrintTestClassResultLine(&consoleMock);
      //
      METALMOCK(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce());
      METALMOCK(_testClassResultSelfMocked.SumOfTestResultMicrosecondsMock.CalledOnce());
      METALMOCK(MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.CalledOnceWith(sumOfTestResultMicroseconds));
      METALMOCK(consoleMock.WriteMock.CalledOnceWith("[  "));
      METALMOCK(consoleMock.WriteColorMock.CalledOnceWith("OK", Color::Green));
      METALMOCK(consoleMock.WriteLineMock.CalledOnceWith("  ] " + oneDecimalPlaceMilliseconds));
   }

   TEST1X1(PrintTestClassResultLine_1OrMoreFailedTests_WritesFailedInRed,
      size_t numberOfFailedTestCases,
      1ull,
      2ull,
      3ull)
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.Return(numberOfFailedTestCases);
      const long long microseconds = _testClassResultSelfMocked.SumOfTestResultMicrosecondsMock.ReturnRandom();

      const string oneDecimalPlaceMilliseconds = MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.ReturnRandom();

      ConsoleMock consoleMock;
      consoleMock.WriteLineColorMock.Expect();
      //
      _testClassResultSelfMocked.PrintTestClassResultLine(&consoleMock);
      //
      METALMOCK(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce());
      METALMOCK(_testClassResultSelfMocked.SumOfTestResultMicrosecondsMock.CalledOnce());
      METALMOCK(MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.CalledOnceWith(microseconds));
      METALMOCK(consoleMock.WriteLineColorMock.CalledOnceWith("[TestClass Failed] " + oneDecimalPlaceMilliseconds, Color::Red));
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
      METALMOCK(testResultMock.PrintIfFailureMock.CalledOnceWith(&console, &testFailureNumberer));
   }

   TEST(SumOfTestResultMicroseconds_EmptyTestResultsVector_Returns0)
   {
      IS_ZERO(_testClassResult._testResults.size());
      //
      const long long microseconds = _testClassResult.SumOfTestResultMicroseconds();
      //
      IS_ZERO(microseconds);
   }

   TEST(SumOfTestResultMicroseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMicroseconds)
   {
      TestResult testResultA;
      testResultA.microseconds = ZenUnit::RandomBetween<long long>(0, 100);

      TestResult testResultB;
      testResultB.microseconds = ZenUnit::RandomBetween<long long>(0, 1000);

      _testClassResult._testResults = { testResultA, testResultB };
      //
      const long long microseconds = _testClassResult.SumOfTestResultMicroseconds();
      //
      ARE_EQUAL(testResultA.microseconds + testResultB.microseconds, microseconds);
   }

   RUN_TESTS(TestClassResultTests)
}

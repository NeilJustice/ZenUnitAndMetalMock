#include "pch.h"
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
   AFACT(AddTestResult_EmplacesBackMovedTestResult)
   AFACT(AddTestResults_EmplacesBackMovedTestResults)
   AFACT(NumberOfFailedTestCases_ReturnsNumberOfNonSuccessTestsInTestResultsVector)
   AFACT(PrintTestFailures_PrintsJustTestFailedToConsole)
   AFACT(PrintTestClassResultLine_0FailedTestCases_WritesOKInGreen)
   FACTS(PrintTestClassResultLine_1OrMoreFailedTests_WritesFailedInRed)
   AFACT(PrintTestResultIfFailure_CallsTestResultPrintIfFailure)
   AFACT(ReserveVectorCapacityForNumberOfTestResults_ReservesTestResultsVector)
   EVIDENCE

   TestClassResult _testClassResult;

   class TestClassResultSelfMocked : public Metal::Mock<TestClassResult>
   {
   public:
      METALMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   } _testClassResultSelfMocked;
   // Function Pointers
   METALMOCK_NONVOID1_STATIC_OR_FREE(string, _call_Watch_MillisecondsToBracketedMillisecondsString, unsigned short)
   // Mutable Fields
   unsigned short _elapsedMilliseconds = 0;

   STARTUP
   {
      // Function Pointers
      _testClassResultSelfMocked._call_Watch_MillisecondsToBracketedMillisecondsString
         = BIND_1ARG_METALMOCK_OBJECT(_call_Watch_MillisecondsToBracketedMillisecondsStringMock);
      // Mutable Fields
      _testClassResult._elapsedMilliseconds = _elapsedMilliseconds = ZenUnit::Random<unsigned short>();
      _testClassResultSelfMocked._elapsedMilliseconds = _elapsedMilliseconds;
   }

   TEST(DefaultConstructor_SetsWatchFunction)
   {
      TestClassResult testClassResult;
      // Function Pointers
      STD_FUNCTION_TARGETS(Watch::MillisecondsToBracketedMillisecondsString,
         testClassResult._call_Watch_MillisecondsToBracketedMillisecondsString);
      // Mutable Fields
      IS_ZERO(testClassResult._elapsedMilliseconds);
      IS_EMPTY(testClassResult._testResults);
   }

   TEST(CopyConstructor_CopiesForEacherAndTestResults)
   {
      TestClassResult testClassResult = TestingNonDefaultTestClassResult();
      //
      TestClassResult copyOfTestClassResult(testClassResult);
      //
      ARE_COPIES(copyOfTestClassResult, testClassResult);
   }

   TEST(AssignmentOperator_CopiesForEacherAndTestResults)
   {
      TestClassResult testClassResult = TestingNonDefaultTestClassResult();
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
      TestClassResult testClassResult = TestingNonDefaultTestClassResult();
      TestClassResult copyOfTestClassResult = testClassResult;
      //
      testClassResult = testClassResult;
      //
      ARE_EQUAL(copyOfTestClassResult, testClassResult);
   }
   #endif

   TEST(MoveConstructor_MovesForEacherAndTestResults)
   {
      TestClassResult testClassResult = TestingNonDefaultTestClassResult();
      TestClassResult copyOfTestClassResult = testClassResult;
      //
      const TestClassResult moved(std::move(testClassResult));
      //
      IS_DEFAULT_VALUE(testClassResult);
      ARE_EQUAL(copyOfTestClassResult, moved);
   }

   TEST(MoveAssignmentOperator_MovesForEacherAndTestResults)
   {
      TestClassResult randomTestClassResult = TestingNonDefaultTestClassResult();
      TestClassResult copyOfRandomTestClassResult = randomTestClassResult;
      TestClassResult movedTestClassResult;
      //
      movedTestClassResult = std::move(randomTestClassResult);
      //
      IS_DEFAULT_VALUE(randomTestClassResult);
      ARE_EQUAL(copyOfRandomTestClassResult, movedTestClassResult);
   }

   TEST(AddTestResult_EmplacesBackMovedTestResult)
   {
      TestResult testResult1 = ZenUnit::Random<TestResult>();
      const TestResult copyOfTestResult1 = testResult1;
      //
      _testClassResult.AddTestResult(std::move(testResult1));
      //
      TestClassResult expectedTestClassResult1;
      expectedTestClassResult1._testResults.emplace_back(copyOfTestResult1);
      ARE_EQUAL(expectedTestClassResult1, _testClassResult);

      TestResult testResult2 = ZenUnit::Random<TestResult>();
      const TestResult copyOfTestResult2 = testResult2;
      //
      _testClassResult.AddTestResult(std::move(testResult2));
      //
      TestClassResult expectedTestClassResult2;
      expectedTestClassResult2._testResults.emplace_back(copyOfTestResult1);
      expectedTestClassResult2._testResults.emplace_back(copyOfTestResult2);
      ARE_EQUAL(expectedTestClassResult2, _testClassResult);
   }

   TEST(AddTestResults_EmplacesBackMovedTestResults)
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

      _testClassResult._testResults =
      {
         testFailure1,
         testSuccess1,
         testFailure2,
         testSuccess2,
         testFailure3
      };
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
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.Return(0ULL);

      const string twoDecimalPlaceMillisecondsString = _call_Watch_MillisecondsToBracketedMillisecondsStringMock.ReturnRandom();

      ConsoleMock consoleMock;
      consoleMock.WriteMock.Expect();
      consoleMock.WriteColorMock.Expect();
      consoleMock.WriteLineMock.Expect();
      //
      _testClassResultSelfMocked.PrintTestClassResultLine(&consoleMock);
      //
      const std::string expected_closingBracket_milliseconds_newline = String::ConcatStrings(
         "  ] ", twoDecimalPlaceMillisecondsString, "\n");

      METALMOCKTHEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce()).Then(

      METALMOCKTHEN(_call_Watch_MillisecondsToBracketedMillisecondsStringMock.CalledOnceWith(
         _elapsedMilliseconds))).Then(

      METALMOCKTHEN(consoleMock.WriteMock.CalledOnceWith(
         "[  "))).Then(

      METALMOCKTHEN(consoleMock.WriteColorMock.CalledOnceWith(
         "OK", Color::Green))).Then(

      METALMOCKTHEN(consoleMock.WriteLineMock.CalledOnceWith(
         expected_closingBracket_milliseconds_newline)));
   }

   TEST1X1(PrintTestClassResultLine_1OrMoreFailedTests_WritesFailedInRed,
      size_t numberOfFailedTestCases,
      1ULL,
      2ULL,
      3ULL)
   {
      _testClassResultSelfMocked.NumberOfFailedTestCasesMock.Return(numberOfFailedTestCases);

      const string bracketedMillisecondsString = _call_Watch_MillisecondsToBracketedMillisecondsStringMock.ReturnRandom();

      ConsoleMock consoleMock;
      consoleMock.WriteLineColorMock.Expect();
      //
      _testClassResultSelfMocked.PrintTestClassResultLine(&consoleMock);
      //
      const std::string expected_testClassFailed_milliseconds_newline = String::ConcatStrings(
         "[TestClass Failed] ", bracketedMillisecondsString, "\n");

      METALMOCKTHEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce()).Then(

      METALMOCKTHEN(_call_Watch_MillisecondsToBracketedMillisecondsStringMock.CalledOnceWith(
         _elapsedMilliseconds))).Then(

      METALMOCKTHEN(consoleMock.WriteLineColorMock.CalledOnceWith(
         expected_testClassFailed_milliseconds_newline, Color::Red)));
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

   TEST(ReserveVectorCapacityForNumberOfTestResults_ReservesTestResultsVector)
   {
      const size_t numberOfTestResults = ZenUnit::RandomBetween<size_t>(0, 3);
      //
      _testClassResult.ReserveVectorCapacityForNumberOfTestResults(numberOfTestResults);
      //
      ARE_EQUAL(numberOfTestResults, _testClassResult._testResults.capacity());
   }

   TEST(SumOfTestResultMilliseconds_EmptyTestResultsVector_Returns0)
   {
      IS_ZERO(_testClassResult._testResults.size());
      //
      const unsigned short sumOfTestResultMilliseconds = _testClassResult.SumOfTestResultMilliseconds();
      //
      IS_ZERO(sumOfTestResultMilliseconds);
   }

   RUN_TESTS(TestClassResultTests)
}

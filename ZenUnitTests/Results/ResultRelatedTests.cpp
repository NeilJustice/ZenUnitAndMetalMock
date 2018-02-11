#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestResultMock.h"
#include "ZenUnitTests/Results/Mock/TestFailureNumbererMock.h"
#include "ZenUnitTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/MemberForEacherMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/ThreeArgForEacherMock.h"

namespace ZenUnit
{

TESTS(AnomalyOrExceptionTests)
AFACT(AnomalyConstructor_SetsAnomaly)
AFACT(ExceptionTypeNameAndExceptionWhatConstructor_SetsExceptionTypeNameAndExceptionWhat)
EVIDENCE

TEST(AnomalyConstructor_SetsAnomaly)
{
   Anomaly anomaly;
   anomaly.why = "NonDefault";
   //
   const AnomalyOrException anomalyOrException(anomaly);
   //
   ARE_EQUAL(anomaly, *anomalyOrException.anomaly);
   IS_NULL(anomalyOrException.exceptionTypeName);
   IS_NULL(anomalyOrException.exceptionWhat);
}

TEST(ExceptionTypeNameAndExceptionWhatConstructor_SetsExceptionTypeNameAndExceptionWhat)
{
   const string exceptionTypeName;
   const string exceptionWhat = Random<string>();
   //
   AnomalyOrException anomalyOrException(&exceptionTypeName, exceptionWhat.c_str());
   //
   IS_NULL(anomalyOrException.anomaly);
   ARE_SAME(exceptionTypeName, *anomalyOrException.exceptionTypeName);
   ARE_EQUAL(exceptionWhat, *anomalyOrException.exceptionWhat);
}

RUN_TESTS(AnomalyOrExceptionTests)


TESTS(CallResultTests)
AFACT(DefaultConstructor_SetsFieldsTo0)
AFACT(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsTo0)
{
   const CallResult defaultCallResult;
   CallResult expectedDefaultCallResult;
   expectedDefaultCallResult.testPhase = TestPhase::Unset;
   expectedDefaultCallResult.testOutcome = TestOutcome::Success;
   expectedDefaultCallResult.microseconds = 0;
   expectedDefaultCallResult.anomalyOrException = nullptr;
   ARE_EQUAL(expectedDefaultCallResult, defaultCallResult);
}

TEST(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
{
   const CallResult callResult(TestPhase::Constructor);
   CallResult expectedCallResult;
   expectedCallResult.testPhase = TestPhase::Constructor;
   expectedCallResult.testOutcome = TestOutcome::Success;
   expectedCallResult.microseconds = 0;
   expectedCallResult.anomalyOrException = nullptr;
   ARE_EQUAL(expectedCallResult, callResult);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_THROWS_TEST(CallResult);
   EQUALIZER_THROWS_FOR_FIELD(CallResult, testPhase, TestPhase::Constructor);
   EQUALIZER_THROWS_FOR_FIELD(CallResult, testOutcome, TestOutcome::Exception);
   EQUALIZER_THROWS_FOR_FIELD(CallResult, microseconds, 1u);

   shared_ptr<AnomalyOrException> nonDefaultAnomalyOrException = make_shared<AnomalyOrException>(Anomaly());
   nonDefaultAnomalyOrException->anomaly->why = "why";
   EQUALIZER_THROWS_FOR_FIELD(CallResult, anomalyOrException, nonDefaultAnomalyOrException);
}

RUN_TESTS(CallResultTests)


TESTS(TestClassResultTests)
AFACT(CopyConstructor_CopiesForEacherAndTestResults)
AFACT(AssignmentOperator_CopiesForEacherAndTestResults)
AFACT(AssignmentOperator_SelfAssignment_NothingHappens)
AFACT(MoveConstructor_MovesForEacherAndTestResults)
AFACT(MoveAssignmentOperator_MovesForEacherAndTestResults)
AFACT(AddTestResults_AppendTestResultsToEndOfTestResultsVector)
AFACT(NumberOfFailedTestCases_ReturnsNumberOfNonSuccessTestsInTestResultsVector)
AFACT(Microseconds_EmptyTestResultsVector_Returns0)
AFACT(Microseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMicroseconds)
FACTS(ThreeDecimalPlaceMilliseconds_ReturnsMicrosecondsAsMillisecondsRoundedToThreePlaces)
AFACT(PrintTestFailures_PrintsJustTestFailedToConsole)
AFACT(PrintTestClassResultLine_0FailedTestCases_WritesOKInGreen)
FACTS(PrintTestClassResultLine_1OrMoreFailedTests_WritesFailedInRed)
AFACT(PrintTestResultIfFailure_CallsTestResultPrintIfFailure)
AFACT(ZenUnitEqualizer_ThrowsIfTestResultsNotEqual)
EVIDENCE

TestClassResult _testClassResult;

struct TestClassResultSelfMocked : public Zen::Mock<TestClassResult>
{
   ZENMOCK_NONVOID0_CONST(size_t, NumberOfFailedTestCases)
   ZENMOCK_NONVOID0_CONST(unsigned, Microseconds)
   ZENMOCK_NONVOID1_CONST(string, ThreeDecimalPlaceMilliseconds, unsigned)
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

TEST(Microseconds_EmptyTestResultsVector_Returns0)
{
   ARE_EQUAL(0, _testClassResult._testResults.size());
   //
   const unsigned microseconds = _testClassResult.Microseconds();
   //
   ARE_EQUAL(0, microseconds);
}

TEST(Microseconds_NonEmptyTestResultsVector_ReturnsSumOfTestResultMicroseconds)
{
   TestResult testResultA;
   testResultA.microseconds = ZenUnit::Random<unsigned>();
   TestResult testResultB;
   testResultB.microseconds = ZenUnit::Random<unsigned>();
   _testClassResult._testResults = { testResultA, testResultB };
   //
   const unsigned microseconds = _testClassResult.Microseconds();
   //
   ARE_EQUAL(testResultA.microseconds + testResultB.microseconds, microseconds);
}

TEST2X2(ThreeDecimalPlaceMilliseconds_ReturnsMicrosecondsAsMillisecondsRoundedToThreePlaces,
   unsigned microseconds, const string& expectedReturnValue,
   0, "(0.000ms)",
   1, "(0.001ms)",
   2, "(0.002ms)",
   10, "(0.010ms)",
   12, "(0.012ms)",
   100, "(0.100ms)",
   120, "(0.120ms)",
   123, "(0.123ms)",
   1000, "(1.000ms)",
   1234, "(1.234ms)",
   12345, "(12.345ms)",
   123456, "(123.456ms)",
   1234567, "(1234.567ms)",
   12345678, "(12345.678ms)",
   123456789, "(123456.789ms)",
   1234567890, "(1234567.890ms)")
{
   const string threeDecimalPlaceMilliseconds = _testClassResult.ThreeDecimalPlaceMilliseconds(microseconds);
   ARE_EQUAL(expectedReturnValue, threeDecimalPlaceMilliseconds);
}

TEST(PrintTestClassResultLine_0FailedTestCases_WritesOKInGreen)
{
   _testClassResultSelfMocked.NumberOfFailedTestCasesMock.Return(0);
   const unsigned microseconds = _testClassResultSelfMocked.MicrosecondsMock.ReturnRandom();
   const string oneDecimalPlaceMilliseconds = ZenUnit::Random<string>();
   _testClassResultSelfMocked.ThreeDecimalPlaceMillisecondsMock.Return(oneDecimalPlaceMilliseconds);
   ConsoleMock consoleMock;
   consoleMock.WriteMock.Expect();
   consoleMock.WriteColorMock.Expect();
   consoleMock.WriteNewLineMock.Expect();
   //
   _testClassResultSelfMocked.PrintTestClassResultLine(&consoleMock);
   //
   ZEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce());
   ZEN(_testClassResultSelfMocked.MicrosecondsMock.CalledOnce());
   ZEN(_testClassResultSelfMocked.ThreeDecimalPlaceMillisecondsMock.CalledOnceWith(microseconds));
   ZEN(consoleMock.WriteMock.CalledAsFollows(
   {
      { "[  " },
      { "  ] " + oneDecimalPlaceMilliseconds }
   }));
   ZEN(consoleMock.WriteColorMock.CalledOnceWith("OK", Color::Green));
   ZEN(consoleMock.WriteNewLineMock.CalledOnce());
}

TEST1X1(PrintTestClassResultLine_1OrMoreFailedTests_WritesFailedInRed,
   size_t numberOfFailedTestCases,
   size_t(1),
   size_t(2),
   size_t(3))
{
   _testClassResultSelfMocked.NumberOfFailedTestCasesMock.Return(numberOfFailedTestCases);
   const unsigned microseconds = _testClassResultSelfMocked.MicrosecondsMock.ReturnRandom();
   const string oneDecimalPlaceMilliseconds = _testClassResultSelfMocked.ThreeDecimalPlaceMillisecondsMock.ReturnRandom();
   ConsoleMock consoleMock;
   consoleMock.WriteLineColorMock.Expect();
   consoleMock.WriteNewLineMock.Expect();
   //
   _testClassResultSelfMocked.PrintTestClassResultLine(&consoleMock);
   //
   ZEN(_testClassResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnce());
   ZEN(_testClassResultSelfMocked.MicrosecondsMock.CalledOnce());
   ZEN(_testClassResultSelfMocked.ThreeDecimalPlaceMillisecondsMock.CalledOnceWith(microseconds));
   ZEN(consoleMock.WriteLineColorMock.CalledOnceWith("[TestClass Failed] " + oneDecimalPlaceMilliseconds, Color::Red));
   ZEN(consoleMock.WriteNewLineMock.CalledOnce());
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

RUN_TESTS(TestClassResultTests)


TESTS(TestFailureNumbererTests)
AFACT(TestFailureNumberer_NextReturnsIncrementingAngleBracketedSequence)
EVIDENCE

TEST(TestFailureNumberer_NextReturnsIncrementingAngleBracketedSequence)
{
   TestFailureNumberer testFailureNumberer;
   ARE_EQUAL("Test Failure 1:", testFailureNumberer.Next());
   ARE_EQUAL("Test Failure 2:", testFailureNumberer.Next());
   ARE_EQUAL("Test Failure 3:", testFailureNumberer.Next());
   testFailureNumberer.Reset();
   ARE_EQUAL("Test Failure 1:", testFailureNumberer.Next());
   ARE_EQUAL("Test Failure 2:", testFailureNumberer.Next());
   ARE_EQUAL("Test Failure 3:", testFailureNumberer.Next());
}

RUN_TESTS(TestFailureNumbererTests)


TESTS(TestPhaseSuffixerTests)
FACTS(TestPhaseToTestPhaseSuffix_ReturnsTestPhaseSuffix)
FACTS(TestPhaseToTestPhaseSuffix_UnsetOrDestructorTestPhase_Throws)
EVIDENCE

TestPhaseSuffixer _testPhaseSuffixer;

TEST2X2(TestPhaseToTestPhaseSuffix_ReturnsTestPhaseSuffix,
   TestPhase testPhase, const char* expectedTestPhaseSuffix,
   TestPhase::Constructor, " in test class constructor",
   TestPhase::Startup, " in STARTUP",
   TestPhase::TestBody, "",
   TestPhase::Cleanup, " in CLEANUP")
{
   ARE_EQUAL(expectedTestPhaseSuffix, _testPhaseSuffixer.TestPhaseToTestPhaseSuffix(testPhase));
}

TEST1X1(TestPhaseToTestPhaseSuffix_UnsetOrDestructorTestPhase_Throws,
   TestPhase testPhase,
   TestPhase::Unset,
   TestPhase::Destructor)
{
   THROWS(_testPhaseSuffixer.TestPhaseToTestPhaseSuffix(testPhase),
      invalid_argument, "Invalid testPhase");
}

RUN_TESTS(TestPhaseSuffixerTests)


TESTS(TestResultFactoryTests)
AFACT(ConstructorFail_ReturnsTestResultConstructorFail)
AFACT(StartupFail_ReturnsTestResultStartupFail)
AFACT(CtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
AFACT(FullConstructor_ReturnsTestResultSixArgCtor)
EVIDENCE

TestResultFactory _testResultFactory;
const FullTestName FullTestNameValue = FullTestName("TestClass", "Test", 0);
CallResult ConstructorCallResult;
CallResult StartupCallResult;
CallResult DestructorCallResult;
CallResult TestBodyCallResult;
CallResult CleanupCallResult;
STARTUP
{
   ConstructorCallResult.testPhase = TestPhase::Constructor;
   StartupCallResult.testPhase = TestPhase::Startup;
   TestBodyCallResult.testPhase = TestPhase::TestBody;
   CleanupCallResult.testPhase = TestPhase::Cleanup;
   DestructorCallResult.testPhase = TestPhase::Destructor;
}

TEST(ConstructorFail_ReturnsTestResultConstructorFail)
{
   const TestResult constructorFailTestResult =
      _testResultFactory.ConstructorFail(FullTestNameValue, ConstructorCallResult);
   //
   const TestResult expectedTestResult = TestResult::ConstructorFail(FullTestNameValue, ConstructorCallResult);
   ARE_EQUAL(expectedTestResult, constructorFailTestResult);
}

TEST(StartupFail_ReturnsTestResultStartupFail)
{
   const TestResult startupFailTestResult = _testResultFactory.StartupFail(
      FullTestNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
   //
   const TestResult expectedTestResult = TestResult::StartupFail(
      FullTestNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
   ARE_EQUAL(expectedTestResult, startupFailTestResult);
}

TEST(CtorDtorSuccess_ReturnsTestResultCtorDtorSuccess)
{
   const TestResult ctorDtorSuccessResult = _testResultFactory.CtorDtorSuccess(
      FullTestNameValue, ConstructorCallResult, DestructorCallResult);
   //
   const TestResult expectedTestResult = TestResult::CtorDtorSuccess(
      FullTestNameValue, ConstructorCallResult, DestructorCallResult);
   ARE_EQUAL(expectedTestResult, ctorDtorSuccessResult);
}

TEST(FullConstructor_ReturnsTestResultSixArgCtor)
{
   const TestResult testResult = _testResultFactory.FullCtor(
      FullTestNameValue, ConstructorCallResult, StartupCallResult,
      TestBodyCallResult, CleanupCallResult, DestructorCallResult);
   //
   const TestResult expectedTestResult(
      FullTestNameValue, ConstructorCallResult, StartupCallResult,
      TestBodyCallResult, CleanupCallResult, DestructorCallResult, TestRunner::GetArgs);
   ARE_EQUAL(expectedTestResult, testResult);
}

RUN_TESTS(TestResultFactoryTests)


TESTS(TestResultTests)
AFACT(DefaultConstructor_SetsFieldsTo0)
FACTS(ConstructorFail_ReturnsExpectedTestResult)
FACTS(StartupFail_ReturnsExpectedTestResult)
AFACT(CtorDtorSuccess_ReturnsExpectedTestResult);
FACTS(SixArgConstructor_SetsFields)
FACTS(WriteLineOKIfSuccess_PrintsOKIfTestOutcomeSuccess)
AFACT(PrintIfFailure_Success_PrintsNothing)
FACTS(PrintIfFailure_Anomaly_PrintsExpected)
FACTS(PrintIfFailure_Exception_PrintsExpected)
AFACT(PrintIfFailure_SuccessButPastDeadline_PrintsExpected)
AFACT(PrintIfFailure_InvalidOutcome_Throws)
FACTS(WriteTestCaseNumberIfAny_WritesToConsoleTestCaseIndexPlus1IfTestCaseIndexNotMaxValue)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TestResult _testResult;
CallResult ConstructorCallResult;
CallResult StartupCallResult;
CallResult DestructorCallResult;
ConsoleMock _consoleMock;
TestFailureNumbererMock _testFailureNumbererMock;
const FullTestName FullTestNameValue = FullTestName("ClassName", "TestClassName", 0);
ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)

   struct TestResult_WriteTestCaseNumberIfAnyMocked : public Zen::Mock<TestResult>
{
   ZENMOCK_VOID2_CONST(WriteTestCaseNumberIfAny, const Console*, unsigned short)
} _testResult_WriteTestCaseNumberIfAnyMocked;

STARTUP
{
   ConstructorCallResult = CallResult(TestPhase::Constructor);
   ConstructorCallResult.microseconds = 1000;
   StartupCallResult = CallResult(TestPhase::Startup);
   StartupCallResult.microseconds = 2000;
   DestructorCallResult = CallResult(TestPhase::Destructor);
   DestructorCallResult.microseconds = 3000;
   _testResult.fullTestName = FullTestNameValue;
}

TEST(DefaultConstructor_SetsFieldsTo0)
{
   const TestResult defaultTestResult;
   TestResult expectedDefaultTestResult;
   expectedDefaultTestResult.fullTestName = FullTestName();
   expectedDefaultTestResult.constructorCallResult = CallResult();
   expectedDefaultTestResult.startupCallResult = CallResult();
   expectedDefaultTestResult.testBodyCallResult = CallResult();
   expectedDefaultTestResult.cleanupCallResult = CallResult();
   expectedDefaultTestResult.destructorCallResult = CallResult();
   expectedDefaultTestResult.responsibleCallResultField = nullptr;
   expectedDefaultTestResult.testOutcome = TestOutcome::Unset;
   expectedDefaultTestResult.testCaseIndex = numeric_limits<unsigned short>::max();
   expectedDefaultTestResult.microseconds = 0;
   ARE_EQUAL(expectedDefaultTestResult, defaultTestResult);
}

TEST2X2(ConstructorFail_ReturnsExpectedTestResult,
   TestOutcome constructorOutcome, TestOutcome expectedTestResultOutcome,
   TestOutcome::Anomaly, TestOutcome::Anomaly,
   TestOutcome::Exception, TestOutcome::Exception)
{
   ConstructorCallResult.testOutcome = constructorOutcome;
   //
   const TestResult constructorFailTestResult =
      TestResult::ConstructorFail(FullTestNameValue, ConstructorCallResult);
   //
   TestResult expectedTestResult;
   expectedTestResult.fullTestName = FullTestNameValue;
   expectedTestResult.constructorCallResult = ConstructorCallResult;
   expectedTestResult.responsibleCallResultField = &TestResult::constructorCallResult;
   expectedTestResult.testOutcome = expectedTestResultOutcome;
   expectedTestResult.microseconds = ConstructorCallResult.microseconds;
   ARE_EQUAL(expectedTestResult, constructorFailTestResult);
}

TEST2X2(StartupFail_ReturnsExpectedTestResult,
   TestOutcome startupOutcome, TestOutcome expectedTestResultOutcome,
   TestOutcome::Anomaly, TestOutcome::Anomaly,
   TestOutcome::Exception, TestOutcome::Exception)
{
   StartupCallResult.testOutcome = startupOutcome;
   //
   const TestResult startupFailTestResult = TestResult::StartupFail(
      FullTestNameValue, ConstructorCallResult, StartupCallResult, DestructorCallResult);
   //
   TestResult expectedTestResult;
   expectedTestResult.fullTestName = FullTestNameValue;
   expectedTestResult.constructorCallResult = ConstructorCallResult;
   expectedTestResult.startupCallResult = StartupCallResult;
   expectedTestResult.destructorCallResult = DestructorCallResult;
   expectedTestResult.responsibleCallResultField = &TestResult::startupCallResult;
   expectedTestResult.testOutcome = expectedTestResultOutcome;
   expectedTestResult.microseconds =
      ConstructorCallResult.microseconds + StartupCallResult.microseconds + DestructorCallResult.microseconds;
   ARE_EQUAL(expectedTestResult, startupFailTestResult);
}

TEST(CtorDtorSuccess_ReturnsExpectedTestResult)
{
   CallResult constructorCallResult(TestPhase::Constructor);
   constructorCallResult.microseconds = 10;
   CallResult destructorCallResult(TestPhase::Destructor);
   destructorCallResult.microseconds = 20;
   //
   const TestResult testResult = TestResult::CtorDtorSuccess(
      FullTestNameValue, constructorCallResult, destructorCallResult);
   //
   TestResult expectedTestResult;
   expectedTestResult.fullTestName = FullTestNameValue;
   expectedTestResult.testOutcome = TestOutcome::Success;
   expectedTestResult.constructorCallResult = constructorCallResult;
   expectedTestResult.destructorCallResult = destructorCallResult;
   expectedTestResult.microseconds = constructorCallResult.microseconds + destructorCallResult.microseconds;
   expectedTestResult.responsibleCallResultField = nullptr;
   ARE_EQUAL(expectedTestResult, testResult);
}

const unsigned MaxTestMilliseconds = 1 + 2 + 3 + 4 + 5;

TEST6X6(SixArgConstructor_SetsFields,
   TestOutcome testBodyOutcome,
   TestOutcome cleanupOutcome,
   unsigned maxtestmilliseconds,
   int relativeMicroseconds,
   TestOutcome expectedOverallOutcome,
   CallResult TestResult::* expectedResponsibleCallResultField,
   //TestOutcome::Success, TestOutcome::Success, 0, 0, TestOutcome::Success, nullptr,
   //TestOutcome::Success, TestOutcome::Success, 0, 1, TestOutcome::Success, nullptr,
   //TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, -1, TestOutcome::Success, nullptr,
   //TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 0, TestOutcome::Success, nullptr,

   TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::SuccessButPastDeadline, nullptr,
   TestOutcome::Success, TestOutcome::Success, MaxTestMilliseconds, 2, TestOutcome::SuccessButPastDeadline, nullptr,

   TestOutcome::Exception, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,
   TestOutcome::Exception, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,
   TestOutcome::Exception, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::testBodyCallResult,

   TestOutcome::Success, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::cleanupCallResult,
   TestOutcome::Anomaly, TestOutcome::Exception, MaxTestMilliseconds, 1, TestOutcome::Exception, &TestResult::cleanupCallResult,

   TestOutcome::Anomaly, TestOutcome::Success, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::testBodyCallResult,
   TestOutcome::Success, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::cleanupCallResult,
   TestOutcome::Anomaly, TestOutcome::Anomaly, MaxTestMilliseconds, 1, TestOutcome::Anomaly, &TestResult::testBodyCallResult)
{
   CallResult testBodyCallResult(TestPhase::TestBody);
   testBodyCallResult.testOutcome = testBodyOutcome;
   testBodyCallResult.microseconds = 4000;
   CallResult cleanupCallResult(TestPhase::Cleanup);
   cleanupCallResult.testOutcome = cleanupOutcome;
   cleanupCallResult.microseconds = 5000 + relativeMicroseconds;

   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.maxtestmilliseconds = maxtestmilliseconds;
   if (expectedOverallOutcome == TestOutcome::Success ||
      expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
   {
      GetArgs_ZenMock.Return(zenUnitArgs);
   }
   const function<const ZenUnitArgs&()> boundMockGetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
   //
   const TestResult testResult(
      FullTestNameValue,
      ConstructorCallResult,
      StartupCallResult,
      testBodyCallResult,
      cleanupCallResult,
      DestructorCallResult,
      boundMockGetArgs);
   //
   if (expectedOverallOutcome == TestOutcome::Success ||
      expectedOverallOutcome == TestOutcome::SuccessButPastDeadline)
   {
      GetArgs_ZenMock.CalledOnce();
   }
   TestResult expectedTestResult;
   expectedTestResult.fullTestName = FullTestNameValue;
   expectedTestResult.constructorCallResult = ConstructorCallResult;
   expectedTestResult.startupCallResult = StartupCallResult;
   expectedTestResult.testBodyCallResult = testBodyCallResult;
   expectedTestResult.cleanupCallResult = cleanupCallResult;
   expectedTestResult.destructorCallResult = DestructorCallResult;
   expectedTestResult.responsibleCallResultField = expectedResponsibleCallResultField;
   expectedTestResult.testOutcome = expectedOverallOutcome;
   expectedTestResult.testCaseIndex = numeric_limits<unsigned short>::max();
   expectedTestResult.microseconds = MaxTestMilliseconds * 1000 + relativeMicroseconds;
   ARE_EQUAL(expectedTestResult, testResult);
}

TEST2X2(WriteLineOKIfSuccess_PrintsOKIfTestOutcomeSuccess,
   TestOutcome testOutcome, bool expectWriteLineOK,
   TestOutcome::Success, true,
   TestOutcome::Anomaly, false,
   TestOutcome::Exception, false,
   TestOutcome::SuccessButPastDeadline, false,
   TestOutcome::Unset, false)
{
   _testResult.testOutcome = testOutcome;
   if (expectWriteLineOK)
   {
      _consoleMock.WriteColorMock.Expect();
      _consoleMock.WriteLineMock.Expect();
   }
   const unsigned microseconds = ZenUnit::Random<unsigned>();
   _testResult.microseconds = microseconds;
   //
   _testResult.WriteLineOKIfSuccess(&_consoleMock);
   //
   if (expectWriteLineOK)
   {
      ZEN(_consoleMock.WriteColorMock.CalledOnceWith("OK ", Color::Green));
      ZEN(_consoleMock.WriteLineMock.CalledOnceWith("(" + to_string(microseconds) + "us)"));
   }
}

TEST(PrintIfFailure_Success_PrintsNothing)
{
   _testResult.testOutcome = TestOutcome::Success;
   _testResult.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
}

TEST3X3(PrintIfFailure_Anomaly_PrintsExpected,
   CallResult TestResult::* expectedResponsibleCallResultField,
   TestPhase testPhase,
   const string& expectedTestPhaseSuffix,
   &TestResult::constructorCallResult, TestPhase::Constructor, " in test class constructor",
   &TestResult::startupCallResult, TestPhase::Startup, " in STARTUP",
   &TestResult::testBodyCallResult, TestPhase::TestBody, "",
   &TestResult::cleanupCallResult, TestPhase::Cleanup, " in CLEANUP")
{
   _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
   _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Anomaly;

   const string anomalyWhy = Random<string>();
   Anomaly anomaly;
   anomaly.why = anomalyWhy;
   (_testResult_WriteTestCaseNumberIfAnyMocked.*
      expectedResponsibleCallResultField).anomalyOrException = make_shared<AnomalyOrException>(anomaly);
   (_testResult_WriteTestCaseNumberIfAnyMocked.*
      expectedResponsibleCallResultField).testPhase = testPhase;

   _testResult_WriteTestCaseNumberIfAnyMocked.responsibleCallResultField = expectedResponsibleCallResultField;

   const string testFailureNumber = _testFailureNumbererMock.NextMock.ReturnRandom();

   _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex = 1;
   _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();

   _consoleMock.WriteMock.Expect();
   _consoleMock.WriteLineMock.Expect();
   _consoleMock.WriteLineColorMock.Expect();
   _consoleMock.WriteNewLineMock.Expect();
   //
   _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
   //
   ZEN(_testFailureNumbererMock.NextMock.CalledOnce());
   ZEN(_consoleMock.WriteMock.CalledAsFollows(
      {
         _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value(),
         expectedTestPhaseSuffix
      }));
   ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
      CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex));
   ZEN(_consoleMock.WriteLineColorMock.CalledOnceWith(testFailureNumber, Color::Red));
   ZEN(_consoleMock.WriteLineMock.CalledOnceWith(anomalyWhy));
   ZEN(_consoleMock.WriteNewLineMock.CalledOnce());
}

TEST3X3(PrintIfFailure_Exception_PrintsExpected,
   CallResult TestResult::* expectedResponsibleCallResultField,
   TestPhase testPhase,
   const string& expectedTestPhaseSuffix,
   &TestResult::constructorCallResult, TestPhase::Constructor, " in test class constructor",
   &TestResult::startupCallResult, TestPhase::Startup, " in STARTUP",
   &TestResult::testBodyCallResult, TestPhase::TestBody, "",
   &TestResult::cleanupCallResult, TestPhase::Cleanup, " in CLEANUP")
{
   _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
   _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::Exception;

   const string exceptionTypeName = Random<string>();
   const string exceptionWhatString = Random<string>();
   const char* const exceptionWhat = exceptionWhatString.c_str();
   (_testResult_WriteTestCaseNumberIfAnyMocked.*
      expectedResponsibleCallResultField).anomalyOrException = make_shared<AnomalyOrException>(&exceptionTypeName, exceptionWhat);
   (_testResult_WriteTestCaseNumberIfAnyMocked.*
      expectedResponsibleCallResultField).testPhase = testPhase;
   _testResult_WriteTestCaseNumberIfAnyMocked.
      responsibleCallResultField = expectedResponsibleCallResultField;

   const string testFailureNumber = _testFailureNumbererMock.NextMock.ReturnRandom();

   _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex = 1;
   _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();

   _consoleMock.WriteMock.Expect();
   _consoleMock.WriteLineColorMock.Expect();
   _consoleMock.WriteLineMock.Expect();
   _consoleMock.WriteNewLineMock.Expect();
   //
   _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
   //
   ZEN(_testFailureNumbererMock.NextMock.CalledOnce());
   ZEN(_consoleMock.WriteMock.CalledAsFollows(
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value(),
      expectedTestPhaseSuffix
   }));
   ZEN(_consoleMock.WriteLineColorMock.CalledAsFollows(
   {
      { testFailureNumber, Color::Red },
   { "\nException", Color::Red }
   }));
   ZEN(_consoleMock.WriteLineMock.CalledOnceWith(
      "  Type: " + exceptionTypeName + "\n"
      "what(): \""s + exceptionWhat + "\""));
   ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
      CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex));
   ZEN(_consoleMock.WriteNewLineMock.CalledOnce());
}

TEST(PrintIfFailure_SuccessButPastDeadline_PrintsExpected)
{
   _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName = FullTestName("TestClass", "Test", 0);
   _testResult_WriteTestCaseNumberIfAnyMocked.testOutcome = TestOutcome::SuccessButPastDeadline;
   _testResult_WriteTestCaseNumberIfAnyMocked.microseconds = 10000;

   const string testFailureNumber = _testFailureNumbererMock.NextMock.ReturnRandom();

   _consoleMock.WriteLineColorMock.Expect();
   _consoleMock.WriteLineMock.Expect();
   _consoleMock.WriteNewLineMock.Expect();

   _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex = 1;
   _testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.Expect();
   //
   _testResult_WriteTestCaseNumberIfAnyMocked.PrintIfFailure(&_consoleMock, &_testFailureNumbererMock);
   //
   ZEN(_testFailureNumbererMock.NextMock.CalledOnce());
   ZEN(_testResult_WriteTestCaseNumberIfAnyMocked.WriteTestCaseNumberIfAnyMock.
      CalledOnceWith(&_consoleMock, _testResult_WriteTestCaseNumberIfAnyMocked.testCaseIndex));
   ZEN(_consoleMock.WriteLineColorMock.CalledOnceWith(testFailureNumber, Color::Red));
   ZEN(_consoleMock.WriteLineMock.CalledAsFollows(
   {
      _testResult_WriteTestCaseNumberIfAnyMocked.fullTestName.Value(),
      "\nFailed because test took longer than -maxtestms=10 milliseconds"s
   }));
   ZEN(_consoleMock.WriteNewLineMock.CalledOnce());
}

TEST(PrintIfFailure_InvalidOutcome_Throws)
{
   ConsoleMock consoleMock;
   TestFailureNumbererMock testFailureNumbererMock;
   _testResult.testOutcome = TestOutcome::Unset;
   THROWS(_testResult.PrintIfFailure(&consoleMock, &testFailureNumbererMock),
      invalid_argument, "Invalid TestOutcome::Unset");
}

TEST3X3(WriteTestCaseNumberIfAny_WritesToConsoleTestCaseIndexPlus1IfTestCaseIndexNotMaxValue,
   unsigned short testCaseIndex, bool expectConsoleWriteLine, unsigned short expectedTestCaseNumberWritten,
   static_cast<unsigned short>(numeric_limits<unsigned short>::max()), false, NA<unsigned short>(),
   static_cast<unsigned short>(0), true, static_cast<unsigned short>(1),
   static_cast<unsigned short>(1), true, static_cast<unsigned short>(2),
   static_cast<unsigned short>(2), true, static_cast<unsigned short>(3))
{
   if (expectConsoleWriteLine)
   {
      _consoleMock.WriteMock.Expect();
   }
   //
   _testResult.WriteTestCaseNumberIfAny(&_consoleMock, testCaseIndex);
   //
   if (expectConsoleWriteLine)
   {
      ZEN(_consoleMock.WriteMock.CalledOnceWith(
         " test case " + to_string(expectedTestCaseNumberWritten)));
   }
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_THROWS_TEST(TestResult);
   EQUALIZER_THROWS_FOR_FIELD(TestResult, fullTestName, FullTestName("ClassName", "TestName", 0));

   CallResult nonDefaultConstructorCallResult;
   nonDefaultConstructorCallResult.testPhase = TestPhase::Constructor;
   EQUALIZER_THROWS_FOR_FIELD(TestResult, constructorCallResult, nonDefaultConstructorCallResult);

   CallResult nonDefaultStartupCallResult;
   nonDefaultStartupCallResult.testPhase = TestPhase::Startup;
   EQUALIZER_THROWS_FOR_FIELD(TestResult, startupCallResult, nonDefaultStartupCallResult);

   CallResult nonDefaultTestBodyCallResult;
   nonDefaultTestBodyCallResult.testPhase = TestPhase::TestBody;
   EQUALIZER_THROWS_FOR_FIELD(TestResult, testBodyCallResult, nonDefaultTestBodyCallResult);

   CallResult nonDefaultCleanupCallResult;
   nonDefaultCleanupCallResult.testPhase = TestPhase::Cleanup;
   EQUALIZER_THROWS_FOR_FIELD(TestResult, cleanupCallResult, nonDefaultCleanupCallResult);

   CallResult nonDefaultDestructorCallResult;
   nonDefaultDestructorCallResult.testPhase = TestPhase::Destructor;
   EQUALIZER_THROWS_FOR_FIELD(TestResult, destructorCallResult, nonDefaultDestructorCallResult);

   EQUALIZER_THROWS_FOR_FIELD(TestResult, responsibleCallResultField, &TestResult::constructorCallResult);
   EQUALIZER_THROWS_FOR_FIELD(TestResult, testOutcome, TestOutcome::Anomaly);
   EQUALIZER_THROWS_FOR_FIELD(TestResult, testCaseIndex, short(10));
   EQUALIZER_THROWS_FOR_FIELD(TestResult, microseconds, 20u);
}

RUN_TESTS(TestResultTests)


TESTS(TestRunResultTests)
AFACT(Constructor_NewsComponents)
AFACT(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
AFACT(AddSkippedTestClassNameAndReason_AddsTestClassNameAndReasonToSkippedTestClassNamesAndReasonsVector)
FACTS(SetTestClassResults_SetsNumberofFailedTestCases_MovesTestClassResultsIntoField)
AFACT(NumberOfFailedTestCases_ZeroTestClassResults_Returns0)
AFACT(NumberOfFailedTestCases_ThreeTestClassResults_ReturnsSumOfNumberOfFailedTestCases)
FACTS(PrintTestFailuresAndSkips_PrintsTestFailures_PrintsSkippedTestClassNames_PrintsSkippedFullTestNames);
AFACT(PrintClosingLines_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
FACTS(PrintClosingLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds)
AFACT(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
FACTS(DetermineExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0)
FACTS(DetermineExitCode_Exit0True_AlwaysReturns0)
FACTS(DetermineExitCode_Exit0True_FailSkipsTrue_AlwaysReturns0)
FACTS(DetermineExitCode_FailSkipsTrue_Returns1IfAnyTestsOrTestClassesSkipped)
AFACT(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
AFACT(PrintSkippedTestReminder_PrintsExpectedToConsole)
AFACT(ResetStateExceptForSkips_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TestRunResult _testRunResult;
const ConsoleMock* _consoleMock;
TestFailureNumbererMock* _testFailureNumbererMock;

using TypedefMemberForEacherTestClassResultsMock = MemberForEacherMock<vector<TestClassResult>,
   TestRunResult, void(TestRunResult::*)(const TestClassResult&) const>;
TypedefMemberForEacherTestClassResultsMock* _memberForEacherTestClassResultsMock;

using TypedefMemberForEacherSkippedTestsMock = MemberForEacherMock<vector<string>,
   TestRunResult, void(TestRunResult::*)(const string&) const>;
TypedefMemberForEacherSkippedTestsMock* _memberForEacherSkippedTestsMock;

STARTUP
{
   _testRunResult._console.reset(_consoleMock = new ConsoleMock);
   _testRunResult._testFailureNumberer.reset(_testFailureNumbererMock = new TestFailureNumbererMock);
   _testRunResult._memberForEacherTestClassResults.reset(
      _memberForEacherTestClassResultsMock = new TypedefMemberForEacherTestClassResultsMock);
   _testRunResult._memberForEacherSkippedTests.reset(
      _memberForEacherSkippedTestsMock = new TypedefMemberForEacherSkippedTestsMock);
}

TEST(Constructor_NewsComponents)
{
   TestRunResult testRunResult;
   POINTER_WAS_NEWED(testRunResult._console);
   POINTER_WAS_NEWED(testRunResult._memberForEacherTestClassResults);
   POINTER_WAS_NEWED(testRunResult._memberForEacherSkippedTests);
   POINTER_WAS_NEWED(testRunResult._threeArgForEacher);
   POINTER_WAS_NEWED(testRunResult._testFailureNumberer);
   IS_EMPTY(testRunResult._testClassResults);
   IS_EMPTY(testRunResult._skippedTestClassNamesAndReasons);
   IS_EMPTY(testRunResult._skippedFullTestNamesAndReasons);
   ARE_EQUAL(0, testRunResult._numberOfFailedTestCases);
}

TEST(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
{
   const string testClassName = Random<string>();
   const char* const TestNameA = "TestA";
   const char* const ReasonA = "ReasonA";
   //
   _testRunResult.AddSkippedTest(testClassName.c_str(), TestNameA, ReasonA);
   //
   TestRunResult expectedTestRunResultA;
   expectedTestRunResultA._skippedFullTestNamesAndReasons = { testClassName + ".TestA because: ReasonA" };
   ARE_EQUAL(expectedTestRunResultA, _testRunResult);

   const char* const TestNameB = "TestB";
   const char* const ReasonB = "ReasonB";
   //
   _testRunResult.AddSkippedTest(testClassName.c_str(), TestNameB, ReasonB);
   //
   TestRunResult expectedTestRunResultB;
   expectedTestRunResultB._skippedFullTestNamesAndReasons =
   {
      testClassName + ".TestA because: ReasonA",
      testClassName + ".TestB because: ReasonB"
   };
   ARE_EQUAL(expectedTestRunResultB, _testRunResult);
}

TEST(AddSkippedTestClassNameAndReason_AddsTestClassNameAndReasonToSkippedTestClassNamesAndReasonsVector)
{
   const char* const SkippedTestClassNameA = "SkippedTestClassA";
   const char* const ReasonA = "ReasonA";
   //
   _testRunResult.AddSkippedTestClassNameAndReason(SkippedTestClassNameA, ReasonA);
   //
   TestRunResult expectedTestRunResultA;
   expectedTestRunResultA._skippedTestClassNamesAndReasons =
   {
      String::Concat(SkippedTestClassNameA, " because: ", ReasonA)
   };
   ARE_EQUAL(expectedTestRunResultA, _testRunResult);

   const char* const SkippedTestClassNameB = "SkippedTestClassB";
   const char* const ReasonB = "ReasonB";
   //
   _testRunResult.AddSkippedTestClassNameAndReason(SkippedTestClassNameB, ReasonB);
   //
   TestRunResult expectedTestRunResultB;
   expectedTestRunResultB._skippedTestClassNamesAndReasons =
   {
      String::Concat(SkippedTestClassNameA, " because: ", ReasonA),
      String::Concat(SkippedTestClassNameB, " because: ", ReasonB)
   };
   ARE_EQUAL(expectedTestRunResultB, _testRunResult);
}

TEST1X1(SetTestClassResults_SetsNumberofFailedTestCases_MovesTestClassResultsIntoField,
   size_t numberOfFailedTestCases,
   size_t(0),
   size_t(1),
   size_t(2))
{
   struct TestRunResultSelfMocked : public Zen::Mock<TestRunResult>
   {
      ZENMOCK_NONVOID1_CONST(size_t, NumberOfFailedTestCases, const vector<TestClassResult>&)
   } testRunResultSelfMocked;
   testRunResultSelfMocked.NumberOfFailedTestCasesMock.Return(numberOfFailedTestCases);

   vector<TestClassResult> testClassResults{ TestClassResult() };
   const vector<TestClassResult> NonMovedFromTestClassResults = testClassResults;
   //
   testRunResultSelfMocked.SetTestClassResults(move(testClassResults));
   //
   IS_EMPTY(testClassResults);
   ZEN(testRunResultSelfMocked.NumberOfFailedTestCasesMock.CalledOnceWith(NonMovedFromTestClassResults));
   VECTORS_EQUAL(NonMovedFromTestClassResults, testRunResultSelfMocked._testClassResults);
   ARE_EQUAL(numberOfFailedTestCases, testRunResultSelfMocked._numberOfFailedTestCases);
}

TEST(NumberOfFailedTestCases_ZeroTestClassResults_Returns0)
{
   const size_t numberOfFailedTestCases = _testRunResult.NumberOfFailedTestCases(vector<TestClassResult>());
   ARE_EQUAL(0, numberOfFailedTestCases);
}

TEST(NumberOfFailedTestCases_ThreeTestClassResults_ReturnsSumOfNumberOfFailedTestCases)
{
   TestClassResult testClassResultA;
   TestResult testResultA1;
   testResultA1.testOutcome = TestOutcome::Anomaly;
   TestResult testResultA2;
   testResultA2.testOutcome = TestOutcome::Exception;
   TestResult testResultA3;
   testResultA3.testOutcome = TestOutcome::Success;
   testClassResultA.AddTestResults({ testResultA1, testResultA2, testResultA3 });

   TestResult testResultB1;
   testResultB1.testOutcome = TestOutcome::Success;
   TestClassResult testClassResultB;
   testClassResultB.AddTestResults({ testResultB1 });

   TestResult testResultC1;
   testResultC1.testOutcome = TestOutcome::Anomaly;
   TestResult testResultC2;
   testResultC2.testOutcome = TestOutcome::Exception;
   TestResult testResultC3;
   testResultC3.testOutcome = TestOutcome::Anomaly;
   TestClassResult testClassResultC;
   testClassResultC.AddTestResults({ testResultC1, testResultC2, testResultC3 });

   const vector<TestClassResult> testClassResults{ testClassResultA, testClassResultB, testClassResultC };
   //
   const size_t numberOfFailedTestCases = _testRunResult.NumberOfFailedTestCases(testClassResults);
   //
   ARE_EQUAL(5, numberOfFailedTestCases);
}

TEST3X3(PrintTestFailuresAndSkips_PrintsTestFailures_PrintsSkippedTestClassNames_PrintsSkippedFullTestNames,
   size_t numberOfFailedTestCases,
   bool expectTestsFailedLineAndPrintFailuresCall,
   const string& expectedTestsFailedLine,
   size_t(0), false, "",
   size_t(1), true, "1 Test Failure:\n",
   size_t(2), true, "2 Test Failures:\n",
   size_t(3), true, "3 Test Failures:\n")
{
   _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
   if (expectTestsFailedLineAndPrintFailuresCall)
   {
      _consoleMock->WriteLineMock.Expect();
      _memberForEacherTestClassResultsMock->MemberForEachMock.Expect();
   }
   _memberForEacherSkippedTestsMock->MemberForEachMock.Expect();
   //
   _testRunResult.PrintTestFailuresAndSkips();
   //
   if (expectTestsFailedLineAndPrintFailuresCall)
   {
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(expectedTestsFailedLine));
      ZEN(_memberForEacherTestClassResultsMock->MemberForEachMock.
         CalledOnceWith(&_testRunResult._testClassResults, &_testRunResult,
            &TestRunResult::PrintTestClassResultFailures));
   }
   ZEN(_memberForEacherSkippedTestsMock->MemberForEachMock.CalledAsFollows(
   {
      { &_testRunResult._skippedTestClassNamesAndReasons,
         &_testRunResult, &TestRunResult::PrintSkippedTestClassReminder },
      { &_testRunResult._skippedFullTestNamesAndReasons,
         &_testRunResult, &TestRunResult::PrintSkippedTestReminder }
   }));
}

TEST(PrintClosingLines_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
{
   _consoleMock->WriteColorMock.Expect();
   _consoleMock->WriteLineMock.Expect();
   //
   _testRunResult.PrintClosingLines(0, 0, ZenUnitArgs());
   //
   ZEN(_consoleMock->WriteColorMock.CalledOnceWith("[ZenUnit] ", Color::Green));
   ZEN(_consoleMock->WriteLineMock.CalledOnceWith("Zero test classes run."));
}

TEST10X10(PrintClosingLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds,
   const string& expectedMiddleLineVictoryOrFail,
   ZenUnit::Color expectedColor,
   size_t numberOfFailedTestCases,
   size_t numberOfTotalTests,
   const string& expectedClosingLineTestsCountText,
   unsigned testRunMilliseconds,
   const string& expectedMillisecondOrMilliseconds,
   bool random,
   bool randomseedsetbyuser,
   bool expectRandomSeedSuffixWrite,
   "<VICTORY>", Color::Green, size_t(0), size_t(1), "1 test passed", 0, "milliseconds", false, false, false,
   "<VICTORY>", Color::Green, size_t(0), size_t(2), "2 tests passed", 1, "millisecond", false, false, false,
   "<VICTORY>", Color::Green, size_t(0), size_t(3), "3 tests passed", 2, "milliseconds", true, false, true,
   "<VICTORY>", Color::Green, size_t(0), size_t(3), "3 tests passed", 2, "milliseconds", true, true, false,
   ">>-FAIL->", Color::Red, size_t(1), size_t(1), "1/1 test failed", 0, "milliseconds", false, false, false,
   ">>-FAIL->", Color::Red, size_t(1), size_t(2), "1/2 tests failed", 1, "millisecond", false, false, false,
   ">>-FAIL->", Color::Red, size_t(1), size_t(3), "1/3 tests failed", 2, "milliseconds", false, false, false,
   ">>-FAIL->", Color::Red, size_t(2), size_t(2), "2/2 tests failed", 3, "milliseconds", false, false, false,
   ">>-FAIL->", Color::Red, size_t(2), size_t(3), "2/3 tests failed", 4, "milliseconds", false, false, false,
   ">>-FAIL->", Color::Red, size_t(2), size_t(3), "2/3 tests failed", 4, "milliseconds", true, false, true,
   ">>-FAIL->", Color::Red, size_t(2), size_t(4), "2/4 tests failed", 5, "milliseconds", true, true, false)
{
   _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteColorMock.Expect();
   _consoleMock->WriteMock.Expect();
   _consoleMock->WriteLineMock.Expect();
   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.commandLine = Random<string>();
   zenUnitArgs.random = random;
   zenUnitArgs.randomseed = Random<unsigned short>();
   zenUnitArgs.randomseedsetbyuser = randomseedsetbyuser;
   //
   _testRunResult.PrintClosingLines(numberOfTotalTests, testRunMilliseconds, zenUnitArgs);
   //
   const string expectedFirstAndThirdLineAsciiArt =
      expectedMiddleLineVictoryOrFail == "<VICTORY>" ? "+===+===+" : ">>------>";
   ZEN(_consoleMock->WriteLineColorMock.CalledOnceWith(
      expectedFirstAndThirdLineAsciiArt + " ", expectedColor));
   ZEN(_consoleMock->WriteColorMock.CalledAsFollows(
      {
         { expectedMiddleLineVictoryOrFail + " ", expectedColor },
      { expectedFirstAndThirdLineAsciiArt + " ", expectedColor }
      }));
   const string expectedClosingLineBody = expectedClosingLineTestsCountText +
      " in " + to_string(testRunMilliseconds) + " " + expectedMillisecondOrMilliseconds;
   const string expectedRandomSeedWriteLine = expectRandomSeedSuffixWrite ?
      " (seed " + to_string(zenUnitArgs.randomseed) + ")" : "";
   ZEN(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         expectedClosingLineBody,
         expectedRandomSeedWriteLine
      }));
   ZEN(_consoleMock->WriteMock.CalledOnceWith(zenUnitArgs.commandLine));
}

TEST(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
{
   TestClassResultMock testClassResultMock;
   testClassResultMock.PrintTestFailuresMock.Expect();
   //
   _testRunResult.PrintTestClassResultFailures(testClassResultMock);
   //
   ZEN(testClassResultMock.PrintTestFailuresMock.CalledOnceWith(
      _testRunResult._threeArgForEacher.get(),
      _testRunResult._console.get(),
      _testRunResult._testFailureNumberer.get()));
}

TEST4X4(DetermineExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0,
   size_t numberOfFailedTestCases,
   size_t numberOfSkippedTests,
   size_t numberOfSkippedTestClasses,
   int expectedExitCode,
   size_t(0), size_t(0), size_t(0), 0,
   size_t(0), size_t(1), size_t(2), 0,
   size_t(1), size_t(0), size_t(0), 1,
   size_t(2), size_t(1), size_t(2), 1)
{
   SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
   const ZenUnitArgs args;
   //
   const int exitCode = _testRunResult.DetermineExitCode(args);
   //
   ARE_EQUAL(expectedExitCode, exitCode);
}

TEST4X4(DetermineExitCode_Exit0True_AlwaysReturns0,
   size_t numberOfFailedTestCases,
   size_t numberOfSkippedTests,
   size_t numberOfSkippedTestClasses,
   int expectedExitCode,
   size_t(0), size_t(0), size_t(0), 0,
   size_t(0), size_t(1), size_t(2), 0,
   size_t(1), size_t(0), size_t(0), 0,
   size_t(2), size_t(1), size_t(2), 0)
{
   SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
   ZenUnitArgs args;
   args.exit0 = true;
   //
   const int exitCode = _testRunResult.DetermineExitCode(args);
   //
   ARE_EQUAL(expectedExitCode, exitCode);
}

TEST4X4(DetermineExitCode_Exit0True_FailSkipsTrue_AlwaysReturns0,
   size_t numberOfFailedTestCases,
   size_t numberOfSkippedTests,
   size_t numberOfSkippedTestClasses,
   int expectedExitCode,
   size_t(0), size_t(0), size_t(0), 0,
   size_t(0), size_t(1), size_t(2), 0,
   size_t(1), size_t(0), size_t(0), 0,
   size_t(2), size_t(1), size_t(2), 0)
{
   SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
   ZenUnitArgs args;
   args.exit0 = true;
   args.failskips = true;
   //
   const int exitCode = _testRunResult.DetermineExitCode(args);
   //
   ARE_EQUAL(expectedExitCode, exitCode);
}

TEST4X4(DetermineExitCode_FailSkipsTrue_Returns1IfAnyTestsOrTestClassesSkipped,
   size_t numberOfFailedTestCases,
   size_t numberOfSkippedTests,
   size_t numberOfSkippedTestClasses,
   int expectedExitCode,
   size_t(0), size_t(0), size_t(0), 0,
   size_t(1), size_t(0), size_t(0), 1,
   size_t(2), size_t(0), size_t(0), 1,
   size_t(0), size_t(1), size_t(0), 1,
   size_t(0), size_t(2), size_t(0), 1,
   size_t(0), size_t(0), size_t(1), 1,
   size_t(0), size_t(0), size_t(2), 1,
   size_t(0), size_t(1), size_t(1), 1,
   size_t(2), size_t(3), size_t(4), 1)
{
   SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
   ZenUnitArgs args;
   args.failskips = true;
   //
   const int exitCode = _testRunResult.DetermineExitCode(args);
   //
   ARE_EQUAL(expectedExitCode, exitCode);
}

void SetState(
   size_t numberOfFailedTestCases,
   size_t numberOfSkippedTests,
   size_t numberOfSkippedTestClasses)
{
   _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
   _testRunResult._skippedFullTestNamesAndReasons.resize(numberOfSkippedTests);
   _testRunResult._skippedTestClassNamesAndReasons.resize(numberOfSkippedTestClasses);
}

TEST(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
{
   _consoleMock->WriteLineColorMock.Expect();
   const string skippedTestClassNameAndReason = Random<string>();
   //
   _testRunResult.PrintSkippedTestClassReminder(skippedTestClassNameAndReason);
   //
   ZEN(_consoleMock->WriteLineColorMock.CalledOnceWith("[SKIPPED] Test class " + skippedTestClassNameAndReason, Color::Yellow));
}

TEST(PrintSkippedTestReminder_PrintsExpectedToConsole)
{
   _consoleMock->WriteLineColorMock.Expect();
   const string skippedTestName = Random<string>();
   //
   _testRunResult.PrintSkippedTestReminder(skippedTestName);
   //
   ZEN(_consoleMock->WriteLineColorMock.CalledOnceWith("[SKIPPED] Test " + skippedTestName, Color::Yellow));
}

TEST(ResetStateExceptForSkips_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
{
   _testFailureNumbererMock->ResetMock.Expect();
   _testRunResult._testClassResults.resize(1);
   _testRunResult._numberOfFailedTestCases = 1;
   //
   _testRunResult.ResetStateExceptForSkips();
   //
   ZEN(_testFailureNumbererMock->ResetMock.CalledOnce());
   IS_EMPTY(_testRunResult._testClassResults);
   ARE_EQUAL(0, _testRunResult._numberOfFailedTestCases);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_THROWS_TEST(TestRunResult);
   EQUALIZER_THROWS_FOR_FIELD(TestRunResult, _testClassResults, vector<TestClassResult> { TestClassResult() });
   EQUALIZER_THROWS_FOR_FIELD(TestRunResult, _skippedTestClassNamesAndReasons, vector<string> { "" });
   EQUALIZER_THROWS_FOR_FIELD(TestRunResult, _skippedFullTestNamesAndReasons, vector<string> { "" });
}

RUN_TESTS(TestRunResultTests)

}
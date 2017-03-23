#include "pch.h"
#include "ZenUnit/Results/TestRunResult.h"
#include "Utils/Iteration/Mock/MemberForEacherMock.h"
#include "Results/Mock/TestClassResultMock.h"
#include "Console/Mock/ConsoleMock.h"
#include "Results/Mock/CallResultMock.h"
#include "Mock/TestFailureNumbererMock.h"

namespace ZenUnit
{
   TESTS(TestRunResultTests)
   SPEC(Constructor_NewsComponents)
   SPEC(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
   SPEC(AddSkippedTestClassNameAndReason_AddsTestClassNameAndReasonToSkippedTestClassNamesAndReasonsVector)
   SPECX(SetTestClassResults_SetsTestClassResultsAndNumberofFailedTestCases)
   SPEC(NumberOfFailedTestCases_ZeroTestClassResults_Returns0)
   SPEC(NumberOfFailedTestCases_ThreeTestClassResults_ReturnsSumOfNumberOfFailedTestCases)
   SPECX(PrintTestFailuresAndSkips_PrintsTestFailures_PrintsSkippedTestClassNames_PrintsSkippedFullTestNames);
   SPEC(PrintClosingLines_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
   SPECX(PrintClosingLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds)
   SPEC(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   SPECX(DetermineExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0)
   SPECX(DetermineExitCode_Exit0_AlwaysReturns0)
   SPECX(DetermineExitCode_Exit0AndNoSkips_AlwaysReturns0)
   SPECX(DetermineExitCode_NoSkips_Returns1IfAnyTestsOrTestClassesSkipped)
   SPEC(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
   SPEC(PrintSkippedTestReminder_PrintsExpectedToConsole)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TestRunResult _testRunResult;
   ConsoleMock* _consoleMock;
   TestFailureNumberer* _testFailureNumbererMock;

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
      WAS_NEWED(testRunResult._console);
      WAS_NEWED(testRunResult._memberForEacherTestClassResults);
      WAS_NEWED(testRunResult._memberForEacherSkippedTests);
      WAS_NEWED(testRunResult._testFailureNumberer);
      IS_EMPTY(testRunResult._testClassResults);
      IS_EMPTY(testRunResult._skippedTestClassNamesAndReasons);
      IS_EMPTY(testRunResult._skippedFullTestNamesAndReasons);
      ARE_EQUAL(0, testRunResult._numberOfFailedTestCases);
   }

   TEST(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
   {
      const char* TestClassName = "TestClass";
      const char* TestNameA = "TestA";
      const char* ReasonA = "ReasonA";
      //
      _testRunResult.AddSkippedTest(TestClassName, TestNameA, ReasonA);
      //
      TestRunResult expectedTestRunResultA;
      expectedTestRunResultA._skippedFullTestNamesAndReasons = { "TestClass.TestA because: ReasonA" };
      ARE_EQUAL(expectedTestRunResultA, _testRunResult);

      const char* TestNameB = "TestB";
      const char* ReasonB = "ReasonB";
      //
      _testRunResult.AddSkippedTest(TestClassName, TestNameB, ReasonB);
      //
      TestRunResult expectedTestRunResultB;
      expectedTestRunResultB._skippedFullTestNamesAndReasons =
         { "TestClass.TestA because: ReasonA", "TestClass.TestB because: ReasonB" };
      ARE_EQUAL(expectedTestRunResultB, _testRunResult);
   }

   TEST(AddSkippedTestClassNameAndReason_AddsTestClassNameAndReasonToSkippedTestClassNamesAndReasonsVector)
   {
      const char* SkippedTestClassNameA = "SkippedTestClassA";
      const char* ReasonA = "ReasonA";
      //
      _testRunResult.AddSkippedTestClassNameAndReason(SkippedTestClassNameA, ReasonA);
      //
      TestRunResult expectedTestRunResultA;
      expectedTestRunResultA._skippedTestClassNamesAndReasons =
         { String::Concat(SkippedTestClassNameA, " because: ", ReasonA) };
      ARE_EQUAL(expectedTestRunResultA, _testRunResult);

      const char* SkippedTestClassNameB = "SkippedTestClassB";
      const char* ReasonB = "ReasonB";
      //
      _testRunResult.AddSkippedTestClassNameAndReason(SkippedTestClassNameB, ReasonB);
      //
      TestRunResult expectedTestRunResultB;
      expectedTestRunResultB._skippedTestClassNamesAndReasons =
      {
         { String::Concat(SkippedTestClassNameA, " because: ", ReasonA) },
         { String::Concat(SkippedTestClassNameB, " because: ", ReasonB) },
      };
      ARE_EQUAL(expectedTestRunResultB, _testRunResult);
   }

   TEST1X1(SetTestClassResults_SetsTestClassResultsAndNumberofFailedTestCases,
      size_t numberOfFailedTestCases,
      0ULL,
      1ULL,
      2ULL)
   {
      struct TestRunResultSelfMocked : public Zen::Mock<TestRunResult>
      {
         ZENMOCK_NONVOID1_CONST(size_t, NumberOfFailedTestCases, const vector<TestClassResult>&)
      } testRunResultSelfMocked;
      testRunResultSelfMocked.NumberOfFailedTestCasesMock.ExpectAndReturn(numberOfFailedTestCases);
      vector<TestClassResult> testClassResults = { TestClassResult() };
      //
      testRunResultSelfMocked.SetTestClassResults(testClassResults);
      //
      ZEN(testRunResultSelfMocked.NumberOfFailedTestCasesMock.AssertCalledOnceWith(testClassResults));
      VECTORS_EQUAL(testClassResults, testRunResultSelfMocked._testClassResults);
      ARE_EQUAL(numberOfFailedTestCases, testRunResultSelfMocked._numberOfFailedTestCases);
   }

   TEST(NumberOfFailedTestCases_ZeroTestClassResults_Returns0)
   {
      size_t numberOfFailedTestCases = _testRunResult.NumberOfFailedTestCases(vector<TestClassResult>());
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

      vector<TestClassResult> testClassResults =
      {
         testClassResultA,
         testClassResultB,
         testClassResultC
      };
      //
      size_t numberOfFailedTestCases = _testRunResult.NumberOfFailedTestCases(testClassResults);
      //
      ARE_EQUAL(5, numberOfFailedTestCases);
   }

   TEST3X3(PrintTestFailuresAndSkips_PrintsTestFailures_PrintsSkippedTestClassNames_PrintsSkippedFullTestNames,
      size_t numberOfFailedTestCases, bool expectTestsFailedLineAndPrintFailuresCall, string expectedTestsFailedLine,
      0ULL, false, "",
      1ULL, true, "1 test failure:\n",
      2ULL, true, "2 test failures:\n",
      3ULL, true, "3 test failures:\n")
   {
      _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
      if (expectTestsFailedLineAndPrintFailuresCall)
      {
         _consoleMock->WriteLineColorMock.Expect();
         _memberForEacherTestClassResultsMock->ForEachMock.Expect();
      }
      _memberForEacherSkippedTestsMock->ForEachMock.Expect();
      //
      _testRunResult.PrintTestFailuresAndSkips();
      //
      if (expectTestsFailedLineAndPrintFailuresCall)
      {
         ZEN(_consoleMock->WriteLineColorMock.AssertCalledOnceWith(expectedTestsFailedLine, Color::Red));
         ZEN(_memberForEacherTestClassResultsMock->ForEachMock.
            AssertCalledOnceWith(&_testRunResult._testClassResults, &_testRunResult,
               &TestRunResult::PrintTestClassResultFailures));
      }
      ZEN(_memberForEacherSkippedTestsMock->ForEachMock.AssertCalls(
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
      _testRunResult.PrintClosingLines(0, 0, "CommandLine");
      //
      ZEN(_consoleMock->WriteColorMock.AssertCalledOnceWith("[ZenUnit] ", Color::Green));
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "Zero test classes (TESTS or TEMPLATETESTS) are registered to run (RUN or TEMPLATERUN)."));
   }

   TEST8X8(PrintClosingLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds,
      string expectedClosingLinePrefix,
      ZenUnit::Color expectedPrefixColor,
      size_t numberOfFailedTestCases,
      size_t numberOfTotalTests,
      string expectedClosingLineTestsCountText,
      long long testRunMilliseconds,
      string expectedMillisecondOrMilliseconds,
      string expectedBottomLineAsciiArt,
      " SUCCESS  ", Color::Green, 0ull, 1ull, "1 test passed", 0ll, "milliseconds", "+===+===+",
      " SUCCESS  ", Color::Green, 0ull, 2ull, "2 tests passed", 1ll, "millisecond", "+===+===+",
      " SUCCESS  ", Color::Green, 0ull, 3ull, "3 tests passed", 2ll, "milliseconds", "+===+===+",
      ">>-FAIL-> ", Color::Red, 1ull, 1ull, "1/1 test failed", 0ll, "milliseconds", ">>------>",
      ">>-FAIL-> ", Color::Red, 1ull, 2ull, "1/2 tests failed", 1ll, "millisecond", ">>------>",
      ">>-FAIL-> ", Color::Red, 1ull, 3ull, "1/3 tests failed", 2ll, "milliseconds", ">>------>",
      ">>-FAIL-> ", Color::Red, 2ull, 2ull, "2/2 tests failed", 3ll, "milliseconds", ">>------>",
      ">>-FAIL-> ", Color::Red, 2ull, 3ull, "2/3 tests failed", 4ll, "milliseconds", ">>------>",
      ">>-FAIL-> ", Color::Red, 2ull, 4ull, "2/4 tests failed", 5ll, "milliseconds", ">>------>")
   {
      _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      const string CommandLine = "CommandLine";
      //
      _testRunResult.PrintClosingLines(numberOfTotalTests, testRunMilliseconds, CommandLine);
      //
      ZEN(_consoleMock->WriteColorMock.AssertCalls(
      {
         { expectedClosingLinePrefix, expectedPrefixColor },
         { expectedBottomLineAsciiArt + " ", expectedPrefixColor }
      }));
      string expectedClosingLineBody = expectedClosingLineTestsCountText +
         " in " + to_string(testRunMilliseconds) + " " + expectedMillisecondOrMilliseconds;
      ZEN(_consoleMock->WriteLineMock.AssertCalls(
      {
         expectedClosingLineBody,
         CommandLine
      }));
   }

   TEST(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintTestFailuresMock.Expect();
      //
      _testRunResult.PrintTestClassResultFailures(testClassResultMock);
      //
      ZEN(testClassResultMock.PrintTestFailuresMock.AssertCalledOnceWith(
         _testRunResult._console.get(), _testRunResult._testFailureNumberer.get()));
   }

   TEST4X4(DetermineExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0,
      size_t numberOfFailedTestCases,
      size_t numberOfSkippedTests,
      size_t numberOfSkippedTestClasses,
      int expectedExitCode,
      0ULL, 0ULL, 0ULL, 0,
      0ULL, 1ULL, 2ULL, 0,
      1ULL, 0ULL, 0ULL, 1,
      2ULL, 1ULL, 2ULL, 1)
   {
      SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
      ZenUnitArgs args;
      //
      int exitCode = _testRunResult.DetermineExitCode(args);
      //
      ARE_EQUAL(expectedExitCode, exitCode);
   }

   TEST4X4(DetermineExitCode_Exit0_AlwaysReturns0,
      size_t numberOfFailedTestCases,
      size_t numberOfSkippedTests,
      size_t numberOfSkippedTestClasses,
      int expectedExitCode,
      0ULL, 0ULL, 0ULL, 0,
      0ULL, 1ULL, 2ULL, 0,
      1ULL, 0ULL, 0ULL, 0,
      2ULL, 1ULL, 2ULL, 0)
   {
      SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
      ZenUnitArgs args;
      args.exit0 = true;
      //
      int exitCode = _testRunResult.DetermineExitCode(args);
      //
      ARE_EQUAL(expectedExitCode, exitCode);
   }

   TEST4X4(DetermineExitCode_Exit0AndNoSkips_AlwaysReturns0,
      size_t numberOfFailedTestCases,
      size_t numberOfSkippedTests,
      size_t numberOfSkippedTestClasses,
      int expectedExitCode,
      0ULL, 0ULL, 0ULL, 0,
      0ULL, 1ULL, 2ULL, 0,
      1ULL, 0ULL, 0ULL, 0,
      2ULL, 1ULL, 2ULL, 0)
   {
      SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
      ZenUnitArgs args;
      args.exit0 = true;
      args.noskips = true;
      //
      int exitCode = _testRunResult.DetermineExitCode(args);
      //
      ARE_EQUAL(expectedExitCode, exitCode);
   }

   TEST4X4(DetermineExitCode_NoSkips_Returns1IfAnyTestsOrTestClassesSkipped,
      size_t numberOfFailedTestCases,
      size_t numberOfSkippedTests,
      size_t numberOfSkippedTestClasses,
      int expectedExitCode,
      0ULL, 0ULL, 0ULL, 0,
      1ULL, 0ULL, 0ULL, 1,
      2ULL, 0ULL, 0ULL, 1,
      0ULL, 1ULL, 0ULL, 1,
      0ULL, 2ULL, 0ULL, 1,
      0ULL, 0ULL, 1ULL, 1,
      0ULL, 0ULL, 2ULL, 1,
      0ULL, 1ULL, 1ULL, 1,
      2ULL, 3ULL, 4ULL, 1)
   {
      SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
      ZenUnitArgs args;
      args.noskips = true;
      //
      int exitCode = _testRunResult.DetermineExitCode(args);
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
      _consoleMock->WriteLineMock.Expect();
      const string SkippedTestClassNameAndReason = "SkippedTestClassName because: Reason";
      //
      _testRunResult.PrintSkippedTestClassReminder(SkippedTestClassNameAndReason);
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "[Warning] Skipped test class " + SkippedTestClassNameAndReason));
   }

   TEST(PrintSkippedTestReminder_PrintsExpectedToConsole)
   {
      _consoleMock->WriteLineMock.Expect();
      const char* SkippedTestName = "SkippedTestName";
      //
      _testRunResult.PrintSkippedTestReminder(SkippedTestName);
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         String::Concat("[Warning] Skipped test ", SkippedTestName)));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(TestRunResult);
      EQUALIZER_THROWS(TestRunResult, _testClassResults, vector<TestClassResult> { TestClassResult() });
      EQUALIZER_THROWS(TestRunResult, _skippedTestClassNamesAndReasons,
         vector<string> { "SkippedTestClassName because: Reason" });
      EQUALIZER_THROWS(TestRunResult, _skippedFullTestNamesAndReasons,
         vector<string> { "SkippedFullTestName because: Reason" });
   }

   }; RUN(TestRunResultTests)
}

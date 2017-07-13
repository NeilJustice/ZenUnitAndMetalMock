#include "pch.h"
#include "ZenUnit/Results/TestRunResult.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitTests/Results/Mock/TestFailureNumbererMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/MemberForEacherMock.h"

namespace ZenUnit
{
   TESTS(TestRunResultTests)
   SPEC(Constructor_NewsComponents)
   SPEC(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
   SPEC(AddSkippedTestClassNameAndReason_AddsTestClassNameAndReasonToSkippedTestClassNamesAndReasonsVector)
   SPECX(SetTestClassResults_SetsNumberofFailedTestCases_MovesTestClassResultsIntoField)
   SPEC(NumberOfFailedTestCases_ZeroTestClassResults_Returns0)
   SPEC(NumberOfFailedTestCases_ThreeTestClassResults_ReturnsSumOfNumberOfFailedTestCases)
   SPECX(PrintTestFailuresAndSkips_PrintsTestFailures_PrintsSkippedTestClassNames_PrintsSkippedFullTestNames);
   SPEC(PrintClosingLines_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
   SPECX(PrintClosingLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds)
   SPEC(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   SPECX(DetermineExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0)
   SPECX(DetermineExitCode_Exit0True_AlwaysReturns0)
   SPECX(DetermineExitCode_Exit0True_FailSkipsTrue_AlwaysReturns0)
   SPECX(DetermineExitCode_FailSkipsTrue_Returns1IfAnyTestsOrTestClassesSkipped)
   SPEC(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
   SPEC(PrintSkippedTestReminder_PrintsExpectedToConsole)
   SPEC(ResetStateExceptForSkips_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

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
      WAS_NEWED(testRunResult._console);
      WAS_NEWED(testRunResult._memberForEacherTestClassResults);
      WAS_NEWED(testRunResult._memberForEacherSkippedTests);
      WAS_NEWED(testRunResult._forEacherTwoExtraArgs);
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
      {
         String::Concat(SkippedTestClassNameA, " because: ", ReasonA)
      };
      ARE_EQUAL(expectedTestRunResultA, _testRunResult);

      const char* SkippedTestClassNameB = "SkippedTestClassB";
      const char* ReasonB = "ReasonB";
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
      testRunResultSelfMocked.NumberOfFailedTestCasesMock.ExpectAndReturn(numberOfFailedTestCases);

      vector<TestClassResult> testClassResults { TestClassResult() };
      const vector<TestClassResult> NonMovedFromTestClassResults = testClassResults;
      //
      testRunResultSelfMocked.SetTestClassResults(std::move(testClassResults));
      //
      IS_EMPTY(testClassResults);
      ZEN(testRunResultSelfMocked.NumberOfFailedTestCasesMock.AssertCalledOnceWith(NonMovedFromTestClassResults));
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

      const vector<TestClassResult> testClassResults { testClassResultA, testClassResultB, testClassResultC };
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
      size_t(1), true, "1 test failure:\n",
      size_t(2), true, "2 test failures:\n",
      size_t(3), true, "3 test failures:\n")
   {
      _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
      if (expectTestsFailedLineAndPrintFailuresCall)
      {
         _consoleMock->WriteLineMock.Expect();
         _memberForEacherTestClassResultsMock->ForEachMock.Expect();
      }
      _memberForEacherSkippedTestsMock->ForEachMock.Expect();
      //
      _testRunResult.PrintTestFailuresAndSkips();
      //
      if (expectTestsFailedLineAndPrintFailuresCall)
      {
         ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(expectedTestsFailedLine));
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
         "Zero test classes (TESTS or TEMPLATETESTS) are registered to run (RUN or RUNTEMPLATE)."));
   }

   TEST8X8(PrintClosingLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds,
      const string& expectedClosingLinePrefix,
      ZenUnit::Color expectedPrefixColor,
      size_t numberOfFailedTestCases,
      size_t numberOfTotalTests,
      const string& expectedClosingLineTestsCountText,
      unsigned testRunMilliseconds,
      const string& expectedMillisecondOrMilliseconds,
      const string& expectedBottomLineAsciiArt,
      "[VICTORY] ", Color::Green, size_t(0), size_t(1), "1 test passed", 0, "milliseconds", "+===+===+",
      "[VICTORY] ", Color::Green, size_t(0), size_t(2), "2 tests passed", 1, "millisecond", "+===+===+",
      "[VICTORY] ", Color::Green, size_t(0), size_t(3), "3 tests passed", 2, "milliseconds", "+===+===+",
      ">>-FAIL-> ", Color::Red, size_t(1), size_t(1), "1/1 test failed", 0, "milliseconds", ">>------>",
      ">>-FAIL-> ", Color::Red, size_t(1), size_t(2), "1/2 tests failed", 1, "millisecond", ">>------>",
      ">>-FAIL-> ", Color::Red, size_t(1), size_t(3), "1/3 tests failed", 2, "milliseconds", ">>------>",
      ">>-FAIL-> ", Color::Red, size_t(2), size_t(2), "2/2 tests failed", 3, "milliseconds", ">>------>",
      ">>-FAIL-> ", Color::Red, size_t(2), size_t(3), "2/3 tests failed", 4, "milliseconds", ">>------>",
      ">>-FAIL-> ", Color::Red, size_t(2), size_t(4), "2/4 tests failed", 5, "milliseconds", ">>------>")
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
      const string expectedClosingLineBody = expectedClosingLineTestsCountText +
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
         _testRunResult._forEacherTwoExtraArgs.get(),
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
      const ZenUnitArgs Args{};
      //
      const int exitCode = _testRunResult.DetermineExitCode(Args);
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
      _consoleMock->WriteLineMock.Expect();
      const string SkippedTestClassNameAndReason = "SkippedTestClassName because: Reason";
      //
      _testRunResult.PrintSkippedTestClassReminder(SkippedTestClassNameAndReason);
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith("[SKIPPED] Test class " + SkippedTestClassNameAndReason));
   }

   TEST(PrintSkippedTestReminder_PrintsExpectedToConsole)
   {
      _consoleMock->WriteLineMock.Expect();
      const string SkippedTestName = "SkippedTestName";
      //
      _testRunResult.PrintSkippedTestReminder(SkippedTestName);
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith("[SKIPPED] Test " + SkippedTestName));
   }

   TEST(ResetStateExceptForSkips_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
   {
      _testFailureNumbererMock->ResetMock.Expect();
      _testRunResult._testClassResults.resize(1);
      _testRunResult._numberOfFailedTestCases = 1;
      //
      _testRunResult.ResetStateExceptForSkips();
      //
      ZEN(_testFailureNumbererMock->ResetMock.AssertCalledOnce());
      IS_EMPTY(_testRunResult._testClassResults);
      ARE_EQUAL(0, _testRunResult._numberOfFailedTestCases);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(TestRunResult);
      EQUALIZER_THROWS(TestRunResult, _testClassResults, vector<TestClassResult> { TestClassResult() });
      EQUALIZER_THROWS(TestRunResult, _skippedTestClassNamesAndReasons, vector<string> { "" });
      EQUALIZER_THROWS(TestRunResult, _skippedFullTestNamesAndReasons, vector<string> { "" });
   }

   }; RUN(TestRunResultTests)
}

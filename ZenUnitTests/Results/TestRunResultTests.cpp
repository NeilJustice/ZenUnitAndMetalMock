#include "pch.h"
#include "ZenUnit/Results/TestRunResult.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitTests/Results/Mock/TestFailureNumbererMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/MemberForEacherMock.h"

namespace ZenUnit
{
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
      POINTER_WAS_NEWED(testRunResult._twoExtraArgsForEacher);
      POINTER_WAS_NEWED(testRunResult._testFailureNumberer);
      IS_EMPTY(testRunResult._testClassResults);
      IS_EMPTY(testRunResult._skippedTestClassNamesAndReasons);
      IS_EMPTY(testRunResult._skippedFullTestNamesAndReasons);
      ARE_EQUAL(0, testRunResult._numberOfFailedTestCases);
   }

   TEST(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
   {
      const string TestClassName = Random<string>();
      const char* const TestNameA = "TestA";
      const char* const ReasonA = "ReasonA";
      //
      _testRunResult.AddSkippedTest(TestClassName.c_str(), TestNameA, ReasonA);
      //
      TestRunResult expectedTestRunResultA;
      expectedTestRunResultA._skippedFullTestNamesAndReasons = { TestClassName + ".TestA because: ReasonA" };
      ARE_EQUAL(expectedTestRunResultA, _testRunResult);

      const char* const TestNameB = "TestB";
      const char* const ReasonB = "ReasonB";
      //
      _testRunResult.AddSkippedTest(TestClassName.c_str(), TestNameB, ReasonB);
      //
      TestRunResult expectedTestRunResultB;
      expectedTestRunResultB._skippedFullTestNamesAndReasons =
         { TestClassName + ".TestA because: ReasonA", TestClassName + ".TestB because: ReasonB" };
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
      testRunResultSelfMocked.NumberOfFailedTestCasesMock.ExpectAndReturn(numberOfFailedTestCases);

      vector<TestClassResult> testClassResults { TestClassResult() };
      const vector<TestClassResult> NonMovedFromTestClassResults = testClassResults;
      //
      testRunResultSelfMocked.SetTestClassResults(move(testClassResults));
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
         _consoleMock->WriteLineColorMock.Expect();
         _memberForEacherTestClassResultsMock->MemberForEachMock.Expect();
      }
      _memberForEacherSkippedTestsMock->MemberForEachMock.Expect();
      //
      _testRunResult.PrintTestFailuresAndSkips();
      //
      if (expectTestsFailedLineAndPrintFailuresCall)
      {
         ZEN(_consoleMock->WriteLineColorMock.AssertCalledOnceWith(expectedTestsFailedLine, Color::Red));
         ZEN(_memberForEacherTestClassResultsMock->MemberForEachMock.
            AssertCalledOnceWith(&_testRunResult._testClassResults, &_testRunResult,
               &TestRunResult::PrintTestClassResultFailures));
      }
      ZEN(_memberForEacherSkippedTestsMock->MemberForEachMock.AssertCalls(
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
      ZEN(_consoleMock->WriteColorMock.AssertCalledOnceWith("[ZenUnit] ", Color::Green));
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "Zero test classes (TESTS or TEMPLATETESTS) are registered to run (RUNTESTS or RUNTEMPLATETESTS)."));
   }

   TEST10X10(PrintClosingLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds,
      const string& expectedClosingLinePrefix,
      ZenUnit::Color expectedColor,
      size_t numberOfFailedTestCases,
      size_t numberOfTotalTests,
      const string& expectedClosingLineTestsCountText,
      unsigned testRunMilliseconds,
      const string& expectedMillisecondOrMilliseconds,
      bool random,
      bool randomseedsetbyuser,
      bool expectRandomSeedSuffixWrite,
      "[VICTORY]", Color::Green, size_t(0), size_t(1), "1 test passed", 0, "milliseconds", false, false, false,
      "[VICTORY]", Color::Green, size_t(0), size_t(2), "2 tests passed", 1, "millisecond", false, false, false,
      "[VICTORY]", Color::Green, size_t(0), size_t(3), "3 tests passed", 2, "milliseconds", true, false, true,
      "[VICTORY]", Color::Green, size_t(0), size_t(3), "3 tests passed", 2, "milliseconds", true, true, false,
      ">>-FAIL->", Color::Red, size_t(1), size_t(1), "1/1 test failed", 0, "milliseconds", false, false, false,
      ">>-FAIL->", Color::Red, size_t(1), size_t(2), "1/2 tests failed", 1, "millisecond", false, false, false,
      ">>-FAIL->", Color::Red, size_t(1), size_t(3), "1/3 tests failed", 2, "milliseconds", false, false, false,
      ">>-FAIL->", Color::Red, size_t(2), size_t(2), "2/2 tests failed", 3, "milliseconds", false, false, false,
      ">>-FAIL->", Color::Red, size_t(2), size_t(3), "2/3 tests failed", 4, "milliseconds", false, false, false,
      ">>-FAIL->", Color::Red, size_t(2), size_t(3), "2/3 tests failed", 4, "milliseconds", true, false, true,
      ">>-FAIL->", Color::Red, size_t(2), size_t(4), "2/4 tests failed", 5, "milliseconds", true, true, false)
   {
      _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
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
      const string expectedBottomLineAsciiArt =
         expectedClosingLinePrefix == "[VICTORY]" ? "+===+===+" : ">>------>";
      ZEN(_consoleMock->WriteColorMock.AssertCalls(
      {
         { expectedClosingLinePrefix + " ", expectedColor },
         { expectedBottomLineAsciiArt + " ", expectedColor }
      }));
      const string expectedClosingLineBody = expectedClosingLineTestsCountText +
         " in " + to_string(testRunMilliseconds) + " " + expectedMillisecondOrMilliseconds;
      const string expectedRandomSeedWriteLine = expectRandomSeedSuffixWrite ?
         " (seed " + to_string(zenUnitArgs.randomseed) + ")" : "";
      ZEN(_consoleMock->WriteLineMock.AssertCalls(
      {
         expectedClosingLineBody,
         expectedRandomSeedWriteLine
      }));
      ZEN(_consoleMock->WriteMock.AssertCalledOnceWith(zenUnitArgs.commandLine));
   }

   TEST(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintTestFailuresMock.Expect();
      //
      _testRunResult.PrintTestClassResultFailures(testClassResultMock);
      //
      ZEN(testClassResultMock.PrintTestFailuresMock.AssertCalledOnceWith(
         _testRunResult._twoExtraArgsForEacher.get(),
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
      _consoleMock->WriteLineMock.Expect();
      const string SkippedTestClassNameAndReason = Random<string>();
      //
      _testRunResult.PrintSkippedTestClassReminder(SkippedTestClassNameAndReason);
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith("[SKIPPED] Test class " + SkippedTestClassNameAndReason));
   }

   TEST(PrintSkippedTestReminder_PrintsExpectedToConsole)
   {
      _consoleMock->WriteLineMock.Expect();
      const string SkippedTestName = Random<string>();
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

   }; RUNTESTS(TestRunResultTests)
}

#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/ZenMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/ZenMock/TestClassResultMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/ZenMock/TestFailureNumbererMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/ZenMock/TestResultMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/ZenMock/MemberForEacherMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/ZenMock/WatchMock.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestRunResultEqualizer.h"

namespace ZenUnit
{
   TESTS(TestRunResultTests)
   AFACT(Constructor_NewsComponents)
   AFACT(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
   AFACT(AddSkippedTestClassNameAndReason_AddsTestClassNameAndReasonToSkippedTestClassNamesAndReasonsVector)
   FACTS(SetTestClassResults_SetsNumberofFailedTestCases_MovesTestClassResultsIntoField)
   AFACT(CalculateNumberOfFailedTestCases_ZeroTestClassResults_Returns0)
   AFACT(CalculateNumberOfFailedTestCases_ThreeTestClassResults_ReturnsSumOfNumberOfFailedTestCases)
   FACTS(PrintTestFailuresAndSkips_PrintsTestFailures_PrintsSkippedTestClassNames_PrintsSkippedFullTestNames);
   AFACT(PrintConclusionLines_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
   FACTS(PrintConclusionLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedSeconds)
   AFACT(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   FACTS(DetermineZenUnitExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0)
   FACTS(DetermineZenUnitExitCode_Exit0True_AlwaysReturns0)
   FACTS(DetermineZenUnitExitCode_Exit0True_noskipsTrue_AlwaysReturns0)
   FACTS(DetermineZenUnitExitCode_noskipsTrue_Returns1IfAnyTestsOrTestClassesSkipped)
   AFACT(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
   AFACT(PrintSkippedTestReminder_PrintsExpectedToConsole)
   AFACT(ResetStateExceptForSkips_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TestRunResult _testRunResult;
   const ConsoleMock* _consoleMock = nullptr;

   using TypedefMemberForEacherSkippedTestsMock = MemberForEacherMock<vector<string>,
      TestRunResult, void(TestRunResult::*)(const string&) const>;
   TypedefMemberForEacherSkippedTestsMock* _memberForEacherSkippedTestsMock = nullptr;

   using TypedefMemberForEacherTestClassResultsMock = MemberForEacherMock<vector<TestClassResult>,
      TestRunResult, void(TestRunResult::*)(const TestClassResult&) const>;
   TypedefMemberForEacherTestClassResultsMock* _memberForEacherTestClassResultsMock = nullptr;

   const WatchMock* _watchMock = nullptr;
   TestFailureNumbererMock* _testFailureNumbererMock = nullptr;

   STARTUP
   {
      _testRunResult._console.reset(_consoleMock = new ConsoleMock);
      _testRunResult._memberForEacherSkippedTests.reset(
         _memberForEacherSkippedTestsMock = new TypedefMemberForEacherSkippedTestsMock);
      _testRunResult._memberForEacherTestClassResults.reset(
         _memberForEacherTestClassResultsMock = new TypedefMemberForEacherTestClassResultsMock);
      _testRunResult._testFailureNumberer.reset(_testFailureNumbererMock = new TestFailureNumbererMock);
      _testRunResult._watch.reset(_watchMock = new WatchMock);
   }

   TEST(Constructor_NewsComponents)
   {
      TestRunResult testRunResult;
      DELETE_TO_ASSERT_NEWED(testRunResult._console);
      DELETE_TO_ASSERT_NEWED(testRunResult._memberForEacherSkippedTests);
      DELETE_TO_ASSERT_NEWED(testRunResult._memberForEacherTestClassResults);
      DELETE_TO_ASSERT_NEWED(testRunResult._threeArgForEacher);
      DELETE_TO_ASSERT_NEWED(testRunResult._watch);

      ARE_EQUAL(0, testRunResult._numberOfFailedTestCases);
      IS_EMPTY(testRunResult._skippedFullTestNamesAndSkipReasons);
      IS_EMPTY(testRunResult._skippedTestClassNamesAndSkipReasons);
      IS_EMPTY(testRunResult._testClassResults);
      DELETE_TO_ASSERT_NEWED(testRunResult._testFailureNumberer);
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
      expectedTestRunResultA._skippedFullTestNamesAndSkipReasons = { testClassName + ".TestA because: ReasonA" };
      ARE_EQUAL(expectedTestRunResultA, _testRunResult);

      const char* const TestNameB = "TestB";
      const char* const ReasonB = "ReasonB";
      //
      _testRunResult.AddSkippedTest(testClassName.c_str(), TestNameB, ReasonB);
      //
      TestRunResult expectedTestRunResultB;
      expectedTestRunResultB._skippedFullTestNamesAndSkipReasons =
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
      expectedTestRunResultA._skippedTestClassNamesAndSkipReasons =
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
      expectedTestRunResultB._skippedTestClassNamesAndSkipReasons =
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
      class TestRunResultSelfMocked : public Zen::Mock<TestRunResult>
      {
      public:
         ZENMOCK_NONVOID1_CONST(size_t, CalculateNumberOfFailedTestCases, const vector<TestClassResult>&)
      } testRunResultSelfMocked;
      testRunResultSelfMocked.CalculateNumberOfFailedTestCasesMock.Return(numberOfFailedTestCases);

      vector<TestClassResult> testClassResults{ TestClassResult() };
      const vector<TestClassResult> NonMovedFromTestClassResults = testClassResults;
      //
      testRunResultSelfMocked.SetTestClassResults(std::move(testClassResults));
      //
      ZENMOCK(testRunResultSelfMocked.CalculateNumberOfFailedTestCasesMock.CalledOnceWith(NonMovedFromTestClassResults));
      VECTORS_EQUAL(NonMovedFromTestClassResults, testRunResultSelfMocked._testClassResults);
      ARE_EQUAL(numberOfFailedTestCases, testRunResultSelfMocked._numberOfFailedTestCases);
   }

   TEST(CalculateNumberOfFailedTestCases_ZeroTestClassResults_Returns0)
   {
      const size_t numberOfFailedTestCases = _testRunResult.CalculateNumberOfFailedTestCases(vector<TestClassResult>());
      ARE_EQUAL(0, numberOfFailedTestCases);
   }

   TEST(CalculateNumberOfFailedTestCases_ThreeTestClassResults_ReturnsSumOfNumberOfFailedTestCases)
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
      const size_t numberOfFailedTestCases = _testRunResult.CalculateNumberOfFailedTestCases(testClassResults);
      //
      ARE_EQUAL(5, numberOfFailedTestCases);
   }

   TEST3X3(PrintTestFailuresAndSkips_PrintsTestFailures_PrintsSkippedTestClassNames_PrintsSkippedFullTestNames,
      size_t numberOfFailedTestCases, bool expectTestsFailedLineAndPrintFailuresCall, const string& expectedTestsFailedLine,
      size_t(0), false, "",
      size_t(1), true, "== 1 Test Failed ==\n===================\n",
      size_t(2), true, "== 2 Tests Failed ==\n====================\n",
      size_t(10), true, "== 10 Tests Failed ==\n=====================\n")
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
         ZENMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedTestsFailedLine, Color::Red));
         ZENMOCK(_memberForEacherTestClassResultsMock->MemberForEachMock.
            CalledOnceWith(&_testRunResult._testClassResults, &_testRunResult, &TestRunResult::PrintTestClassResultFailures));
      }
      ZENMOCK(_memberForEacherSkippedTestsMock->MemberForEachMock.CalledAsFollows(
      {
         { &_testRunResult._skippedTestClassNamesAndSkipReasons, &_testRunResult, &TestRunResult::PrintSkippedTestClassReminder },
         { &_testRunResult._skippedFullTestNamesAndSkipReasons, &_testRunResult, &TestRunResult::PrintSkippedTestReminder }
      }));
   }

   TEST(PrintConclusionLines_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();
      //
      _testRunResult.PrintConclusionLines(ZenUnit::Random<string>(), 0, ZenUnit::Random<string>(), ZenUnit::Random<ZenUnitArgs>());
      //
      ZENMOCK(_consoleMock->WriteColorMock.CalledOnceWith("[ZenUnit]", Color::Red));
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(" Zero test classes run. Exiting with code 1.", 1));
   }

   TEST5X5(PrintConclusionLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedSeconds,
      const string& expectedSuccessOrFailLinePrefix,
      ZenUnit::Color expectedColor,
      size_t numberOfFailedTestCases,
      size_t numberOfTotalTests,
      const char* expectedClosingLineTestsCountText,
      "[ZenUnit]", Color::Green, size_t(0), size_t(1), "All 1 test passed",
      "[ZenUnit]", Color::Green, size_t(0), size_t(2), "All 2 tests passed",
      "[ZenUnit]", Color::Green, size_t(0), size_t(3), "All 3 tests passed",
      "[ZenUnit]", Color::Green, size_t(0), size_t(3), "All 3 tests passed",
      ">>-FAIL->", Color::Red, size_t(1), size_t(1), "1 of 1 test failed",
      ">>-FAIL->", Color::Red, size_t(1), size_t(2), "1 of 2 tests failed",
      ">>-FAIL->", Color::Red, size_t(1), size_t(3), "1 of 3 tests failed",
      ">>-FAIL->", Color::Red, size_t(2), size_t(2), "2 of 2 tests failed",
      ">>-FAIL->", Color::Red, size_t(2), size_t(3), "2 of 3 tests failed",
      ">>-FAIL->", Color::Red, size_t(2), size_t(3), "2 of 3 tests failed",
      ">>-FAIL->", Color::Red, size_t(2), size_t(4), "2 of 4 tests failed")
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();

      const string startDateTime = ZenUnit::Random<string>();
      const string testRunElapsedSeconds = ZenUnit::Random<string>();
      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      //
      _testRunResult.PrintConclusionLines(startDateTime, numberOfTotalTests, testRunElapsedSeconds, args);
      //
      const string expectedTripletLinesPrefix = expectedSuccessOrFailLinePrefix == "[ZenUnit]" ? "[ZenUnit]" : ">>------>";
      ZENMOCK(_consoleMock->WriteColorMock.CalledAsFollows(
      {
         { expectedTripletLinesPrefix, expectedColor },
         { expectedTripletLinesPrefix, expectedColor },
         { expectedTripletLinesPrefix, expectedColor },
         { expectedTripletLinesPrefix, expectedColor },
         { expectedTripletLinesPrefix, expectedColor },
         { expectedSuccessOrFailLinePrefix, expectedColor }
      }));
      const string expectedCompletedLine  = "  Completed: " + args.commandLine;
      const string expectedRandomSeedLine = " RandomSeed: " + to_string(args.randomSeed);
      const string expectedStartTimeLine  = "  StartTime: " + startDateTime;
      const string expectedEndTimeLine    = "    EndTime: " + dateTimeNow;
      const string expectedDurationLine   = "   Duration: " + testRunElapsedSeconds + " seconds";
      const string expectedTestRunResultLine = String::Concat("     Result: ", expectedClosingLineTestsCountText);
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZENMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         { expectedCompletedLine },
         { expectedRandomSeedLine },
         { expectedStartTimeLine },
         { expectedEndTimeLine },
         { expectedDurationLine },
         { expectedTestRunResultLine }
      }));
   }

   TEST(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintTestFailuresMock.Expect();
      //
      _testRunResult.PrintTestClassResultFailures(testClassResultMock);
      //
      ZENMOCK(testClassResultMock.PrintTestFailuresMock.CalledOnceWith(
         _testRunResult._threeArgForEacher.get(),
         _testRunResult._console.get(),
         _testRunResult._testFailureNumberer.get()));
   }

   TEST4X4(DetermineZenUnitExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0,
      size_t numberOfFailedTestCases,
      size_t numberOfSkippedTests,
      size_t numberOfSkippedTestClasses,
      int expectedZenUnitExitCode,
      size_t(0), size_t(0), size_t(0), 0,
      size_t(0), size_t(1), size_t(2), 0,
      size_t(1), size_t(0), size_t(0), 1,
      size_t(2), size_t(1), size_t(2), 1)
   {
      SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
      const ZenUnitArgs args;
      //
      const int zenUnitExitCode = _testRunResult.DetermineZenUnitExitCode(args);
      //
      ARE_EQUAL(expectedZenUnitExitCode, zenUnitExitCode);
   }

   TEST4X4(DetermineZenUnitExitCode_Exit0True_AlwaysReturns0,
      size_t numberOfFailedTestCases,
      size_t numberOfSkippedTests,
      size_t numberOfSkippedTestClasses,
      int expectedZenUnitExitCode,
      size_t(0), size_t(0), size_t(0), 0,
      size_t(0), size_t(1), size_t(2), 0,
      size_t(1), size_t(0), size_t(0), 0,
      size_t(2), size_t(1), size_t(2), 0)
   {
      SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
      ZenUnitArgs args;
      args.alwaysExit0 = true;
      //
      const int zenUnitExitCode = _testRunResult.DetermineZenUnitExitCode(args);
      //
      ARE_EQUAL(expectedZenUnitExitCode, zenUnitExitCode);
   }

   TEST4X4(DetermineZenUnitExitCode_Exit0True_noskipsTrue_AlwaysReturns0,
      size_t numberOfFailedTestCases,
      size_t numberOfSkippedTests,
      size_t numberOfSkippedTestClasses,
      int expectedZenUnitExitCode,
      size_t(0), size_t(0), size_t(0), 0,
      size_t(0), size_t(1), size_t(2), 0,
      size_t(1), size_t(0), size_t(0), 0,
      size_t(2), size_t(1), size_t(2), 0)
   {
      SetState(numberOfFailedTestCases, numberOfSkippedTests, numberOfSkippedTestClasses);
      ZenUnitArgs args;
      args.alwaysExit0 = true;
      args.exit1IfTestsSkipped = true;
      //
      const int zenUnitExitCode = _testRunResult.DetermineZenUnitExitCode(args);
      //
      ARE_EQUAL(expectedZenUnitExitCode, zenUnitExitCode);
   }

   TEST4X4(DetermineZenUnitExitCode_noskipsTrue_Returns1IfAnyTestsOrTestClassesSkipped,
      size_t numberOfFailedTestCases,
      size_t numberOfSkippedTests,
      size_t numberOfSkippedTestClasses,
      int expectedZenUnitExitCode,
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
      args.exit1IfTestsSkipped = true;
      //
      const int zenUnitExitCode = _testRunResult.DetermineZenUnitExitCode(args);
      //
      ARE_EQUAL(expectedZenUnitExitCode, zenUnitExitCode);
   }

   void SetState(size_t numberOfFailedTestCases, size_t numberOfSkippedTests, size_t numberOfSkippedTestClasses)
   {
      _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
      _testRunResult._skippedFullTestNamesAndSkipReasons.resize(numberOfSkippedTests);
      _testRunResult._skippedTestClassNamesAndSkipReasons.resize(numberOfSkippedTestClasses);
   }

   TEST(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
   {
      _consoleMock->WriteLineColorMock.Expect();
      const string skippedTestClassNameAndReason = Random<string>();
      //
      _testRunResult.PrintSkippedTestClassReminder(skippedTestClassNameAndReason);
      //
      ZENMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("[SKIPPED] Test class " + skippedTestClassNameAndReason, Color::Yellow));
   }

   TEST(PrintSkippedTestReminder_PrintsExpectedToConsole)
   {
      _consoleMock->WriteLineColorMock.Expect();
      const string skippedTestName = Random<string>();
      //
      _testRunResult.PrintSkippedTestReminder(skippedTestName);
      //
      ZENMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("[SKIPPED] Test " + skippedTestName, Color::Yellow));
   }

   TEST(ResetStateExceptForSkips_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
   {
      _testFailureNumbererMock->ResetMock.Expect();
      _testRunResult._testClassResults.resize(1);
      _testRunResult._numberOfFailedTestCases = 1;
      //
      _testRunResult.ResetStateExceptForSkips();
      //
      ZENMOCK(_testFailureNumbererMock->ResetMock.CalledOnce());
      IS_EMPTY(_testRunResult._testClassResults);
      ARE_EQUAL(0, _testRunResult._numberOfFailedTestCases);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(TestRunResult);
      EQUALIZER_THROWS(TestRunResult, _testClassResults, vector<TestClassResult> { TestClassResult() });
      EQUALIZER_THROWS(TestRunResult, _skippedTestClassNamesAndSkipReasons, vector<string> { "" });
      EQUALIZER_THROWS(TestRunResult, _skippedFullTestNamesAndSkipReasons, vector<string> { "" });
      EQUALIZER_THROWS(TestRunResult, _numberOfFailedTestCases, 1);
   }

   RUN_TESTS(TestRunResultTests)
}

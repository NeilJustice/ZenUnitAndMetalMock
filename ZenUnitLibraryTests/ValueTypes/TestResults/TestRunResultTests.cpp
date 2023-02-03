#include "pch.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestClassResultMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestFailureNumbererMock.h"
#include "ZenUnitLibraryTests/ValueTypes/TestResults/MetalMock/TestResultMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/MemberForEacherMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/WatchMock.h"

namespace ZenUnit
{
   TESTS(TestRunResultTests)
   AFACT(DefaultConstructor_NewsComponents_SetsFieldsToDefaultValues)
   AFACT(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
   AFACT(AddSkippedTestClassNameAndReason_AddsTestClassNameAndReasonToSkippedTestClassNamesAndReasonsVector)
   FACTS(DetermineZenUnitExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0)
   FACTS(DetermineZenUnitExitCode_Exit0True_AlwaysReturns0)
   FACTS(DetermineZenUnitExitCode_Exit0True_noskipsTrue_AlwaysReturns0)
   FACTS(DetermineZenUnitExitCode_noskipsTrue_Returns1IfAnyTestsOrTestClassesSkipped)
   AFACT(PrintConclusionLines_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
   FACTS(PrintConclusionLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedSeconds)
   FACTS(PrintTestFailuresAndSkips_PrintsTestFailures_PrintsSkippedTestClassNames_PrintsSkippedFullTestNames)
   AFACT(ResetStateInPreparationForNextTestRun_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
   FACTS(SetTestClassResults_SetsNumberofFailedTestCases_MovesTestClassResultsIntoField)
   // Private Functions
   AFACT(CalculateNumberOfFailedTestCases_ZeroTestClassResults_Returns0)
   AFACT(CalculateNumberOfFailedTestCases_ThreeTestClassResults_ReturnsSumOfNumberOfFailedTestCases)
   AFACT(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   AFACT(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
   AFACT(PrintSkippedTestReminder_PrintsExpectedToConsole)
   EVIDENCE

   TestRunResult _testRunResult;
   // Function Callers
   using TypedefMemberForEacherSkippedTestsMock = MemberForEacherMock<vector<string>,
      TestRunResult, void(TestRunResult::*)(const string&) const>;
   TypedefMemberForEacherSkippedTestsMock* _memberForEacherSkippedTestsMock = nullptr;

   using TypedefMemberForEacherTestClassResultsMock = MemberForEacherMock<vector<TestClassResult>,
      TestRunResult, void(TestRunResult::*)(const TestClassResult&) const>;
   TypedefMemberForEacherTestClassResultsMock* _memberForEacherTestClassResultsMock = nullptr;
   // Constant Components
   const ConsoleMock* _consoleMock = nullptr;
   const WatchMock* _watchMock = nullptr;
   // Mutable Components
   TestFailureNumbererMock* _testFailureNumbererMock = nullptr;

   STARTUP
   {
      // Function Callers
      _testRunResult._memberForEacherSkippedTests.reset(
         _memberForEacherSkippedTestsMock = new TypedefMemberForEacherSkippedTestsMock);
      _testRunResult._memberForEacherTestClassResults.reset(
         _memberForEacherTestClassResultsMock = new TypedefMemberForEacherTestClassResultsMock);
      // Constant Components
      _testRunResult._console.reset(_consoleMock = new ConsoleMock);
      _testRunResult._watch.reset(_watchMock = new WatchMock);
      // Mutable Components
      _testRunResult._testFailureNumberer.reset(_testFailureNumbererMock = new TestFailureNumbererMock);
   }

   TEST(DefaultConstructor_NewsComponents_SetsFieldsToDefaultValues)
   {
      TestRunResult testRunResult;
      // Function Callers
      DELETE_TO_ASSERT_NEWED(testRunResult._memberForEacherSkippedTests);
      DELETE_TO_ASSERT_NEWED(testRunResult._memberForEacherTestClassResults);
      DELETE_TO_ASSERT_NEWED(testRunResult._threeArgForEacher);
      // Constant Components
      DELETE_TO_ASSERT_NEWED(testRunResult._console);
      DELETE_TO_ASSERT_NEWED(testRunResult._watch);
      // Mutable Components
      DELETE_TO_ASSERT_NEWED(testRunResult._testFailureNumberer);
      // Mutable Fields
      IS_ZERO(testRunResult._numberOfFailedTestCases);
      IS_EMPTY(testRunResult._skippedFullTestNamesAndSkipReasons);
      IS_EMPTY(testRunResult._skippedTestClassNamesAndSkipReasons);
      IS_EMPTY(testRunResult._testClassResults);
   }

   TEST(AddSkippedTest_AddsTestClassNameDotTestNameToSkippedFullTestNamesVector)
   {
      const string testClassName = Random<string>();
      const char* const testNameA = "TestA";
      const char* const reasonA = "ReasonA";
      //
      _testRunResult.AddSkippedTest(testClassName.c_str(), testNameA, reasonA);
      //
      TestRunResult expectedTestRunResultA;
      expectedTestRunResultA._skippedFullTestNamesAndSkipReasons = { testClassName + ".TestA skipped because \"ReasonA\"" };
      ARE_EQUAL(expectedTestRunResultA, _testRunResult);

      const char* const testNameB = "TestB";
      const char* const reasonB = "ReasonB";
      //
      _testRunResult.AddSkippedTest(testClassName.c_str(), testNameB, reasonB);
      //
      TestRunResult expectedTestRunResultB;
      expectedTestRunResultB._skippedFullTestNamesAndSkipReasons =
      {
         testClassName + ".TestA skipped because \"ReasonA\"",
         testClassName + ".TestB skipped because \"ReasonB\""
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
         String::ConcatStrings(SkippedTestClassNameA, " skipped because \"", ReasonA, "\"")
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
         String::ConcatStrings(SkippedTestClassNameA, " skipped because \"", ReasonA, "\""),
         String::ConcatStrings(SkippedTestClassNameB, " skipped because \"", ReasonB, "\"")
      };
      ARE_EQUAL(expectedTestRunResultB, _testRunResult);
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

   TEST(PrintConclusionLines_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();
      //
      _testRunResult.PrintConclusionLines(
         ZenUnit::Random<string>(), 0, ZenUnit::Random<string>(), ZenUnit::Random<ZenUnitArgs>(), ZenUnit::Random<size_t>());
      //
      METALMOCK(_consoleMock->WriteColorMock.CalledOnceWith("[ZenUnit]", Color::Red));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(" Zero test classes run. Exiting with code 1.", 1));
   }

   TEST5X5(PrintConclusionLines_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedSeconds,
      const string& expectedSuccessOrFailLinePrefix,
      ZenUnit::Color expectedColor,
      size_t numberOfFailedTestCases,
      size_t numberOfTotalTests,
      const char* expectedClosingLineTestsCountText,
      "[SUCCESS]", Color::Green, size_t(0), size_t(1), "All 1 test passed",
      "[SUCCESS]", Color::Green, size_t(0), size_t(2), "All 2 tests passed",
      "[SUCCESS]", Color::Green, size_t(0), size_t(3), "All 3 tests passed",
      "[SUCCESS]", Color::Green, size_t(0), size_t(3), "All 3 tests passed",
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
      const ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();

      const unsigned globalZenUnitModeRandomSeed = ZenUnit::Random<unsigned>();
      globalZenUnitMode.randomSeed = globalZenUnitModeRandomSeed;
      const size_t testRunIndex = ZenUnit::RandomBetween<size_t>(0, 3);
      //
      _testRunResult.PrintConclusionLines(startDateTime, numberOfTotalTests, testRunElapsedSeconds, zenUnitArgs, testRunIndex);
      //
      const string expectedBracketedZenUnitOrFailArrowPrefix =
         expectedSuccessOrFailLinePrefix == "[SUCCESS]" ? "[ZenUnit]" : ">>------>";
      const string expectedCompletedLine = "  Completed: " + zenUnitArgs.commandLine;
      const string expectedRandomSeedLine = " RandomSeed: --random-seed=" + to_string(globalZenUnitModeRandomSeed);
      const string expectedStartTimeLine = "  StartTime: " + startDateTime;
      const string expectedEndTimeLine = "    EndTime: " + dateTimeNow;
      const string expectedDurationLine = "   Duration: " + testRunElapsedSeconds + " seconds";
      const string expectedTestRunMessage = String::ConcatValues("    TestRun: ", testRunIndex + 1, " of ", zenUnitArgs.testRuns);
      const string expectedRunResultLine = String::ConcatStrings("     Result: ", expectedClosingLineTestsCountText);

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith(expectedBracketedZenUnitOrFailArrowPrefix, expectedColor)).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedCompletedLine))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith(expectedBracketedZenUnitOrFailArrowPrefix, expectedColor))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedRandomSeedLine))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith(expectedBracketedZenUnitOrFailArrowPrefix, expectedColor))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedStartTimeLine))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith(expectedBracketedZenUnitOrFailArrowPrefix, expectedColor))).Then(
      METALMOCKTHEN(_watchMock->DateTimeNowMock.CalledOnce())).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedEndTimeLine))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith(expectedBracketedZenUnitOrFailArrowPrefix, expectedColor))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedDurationLine))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith(expectedBracketedZenUnitOrFailArrowPrefix, expectedColor))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedTestRunMessage))).Then(

      METALMOCKTHEN(_consoleMock->WriteColorMock.CalledWith(expectedSuccessOrFailLinePrefix, expectedColor))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedRunResultLine)));
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
         METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedTestsFailedLine, Color::Red));
         METALMOCK(_memberForEacherTestClassResultsMock->MemberForEachMock.
            CalledOnceWith(&_testRunResult._testClassResults, &_testRunResult, &TestRunResult::PrintTestClassResultFailures));
      }
      METALMOCK(_memberForEacherSkippedTestsMock->MemberForEachMock.CalledNTimes(2));
      METALMOCKTHEN(_memberForEacherSkippedTestsMock->MemberForEachMock.CalledWith(
         &_testRunResult._skippedTestClassNamesAndSkipReasons, &_testRunResult, &TestRunResult::PrintSkippedTestClassReminder)).Then(
      METALMOCKTHEN(_memberForEacherSkippedTestsMock->MemberForEachMock.CalledWith(
         &_testRunResult._skippedFullTestNamesAndSkipReasons, &_testRunResult, &TestRunResult::PrintSkippedTestReminder)));
   }

   void SetState(size_t numberOfFailedTestCases, size_t numberOfSkippedTests, size_t numberOfSkippedTestClasses)
   {
      _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
      _testRunResult._skippedFullTestNamesAndSkipReasons.resize(numberOfSkippedTests);
      _testRunResult._skippedTestClassNamesAndSkipReasons.resize(numberOfSkippedTestClasses);
   }

   TEST(ResetStateInPreparationForNextTestRun_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
   {
      _testFailureNumbererMock->ResetTestFailureNumberMock.Expect();
      _testRunResult._testClassResults.resize(1);
      _testRunResult._numberOfFailedTestCases = 1;
      //
      _testRunResult.ResetStateInPreparationForNextTestRun();
      //
      METALMOCK(_testFailureNumbererMock->ResetTestFailureNumberMock.CalledOnce());
      IS_EMPTY(_testRunResult._testClassResults);
      IS_ZERO(_testRunResult._numberOfFailedTestCases);
   }

   TEST1X1(SetTestClassResults_SetsNumberofFailedTestCases_MovesTestClassResultsIntoField,
      size_t numberOfFailedTestCases,
      size_t(0),
      size_t(1),
      size_t(2))
   {
      class TestRunResultSelfMocked : public Metal::Mock<TestRunResult>
      {
      public:
         METALMOCK_NONVOID1_CONST(size_t, CalculateNumberOfFailedTestCases, const vector<TestClassResult>&)
      } testRunResultSelfMocked;
      testRunResultSelfMocked.CalculateNumberOfFailedTestCasesMock.Return(numberOfFailedTestCases);

      vector<TestClassResult> testClassResults{ TestClassResult() };
      const vector<TestClassResult> NonMovedFromTestClassResults = testClassResults;
      //
      testRunResultSelfMocked.SetTestClassResults(std::move(testClassResults));
      //
      METALMOCK(testRunResultSelfMocked.CalculateNumberOfFailedTestCasesMock.CalledOnceWith(NonMovedFromTestClassResults));
      VECTORS_ARE_EQUAL(NonMovedFromTestClassResults, testRunResultSelfMocked._testClassResults);
      ARE_EQUAL(numberOfFailedTestCases, testRunResultSelfMocked._numberOfFailedTestCases);
   }

   // Private Functions

   TEST(CalculateNumberOfFailedTestCases_ZeroTestClassResults_Returns0)
   {
      const size_t numberOfFailedTestCases = _testRunResult.CalculateNumberOfFailedTestCases(vector<TestClassResult>());
      IS_ZERO(numberOfFailedTestCases);
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

   TEST(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintTestFailuresMock.Expect();
      //
      _testRunResult.PrintTestClassResultFailures(testClassResultMock);
      //
      METALMOCK(testClassResultMock.PrintTestFailuresMock.CalledOnceWith(
         _testRunResult._threeArgForEacher.get(),
         _testRunResult._console.get(),
         _testRunResult._testFailureNumberer.get()));
   }

   TEST(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
   {
      _consoleMock->WriteLineColorMock.Expect();
      const string skippedTestClassNameAndReason = Random<string>();
      //
      _testRunResult.PrintSkippedTestClassReminder(skippedTestClassNameAndReason);
      //
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("[SKIPPED] Test class " + skippedTestClassNameAndReason, Color::Yellow));
   }

   TEST(PrintSkippedTestReminder_PrintsExpectedToConsole)
   {
      _consoleMock->WriteLineColorMock.Expect();
      const string skippedTestName = Random<string>();
      //
      _testRunResult.PrintSkippedTestReminder(skippedTestName);
      //
      METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith("[SKIPPED] Test " + skippedTestName, Color::Yellow));
   }

   RUN_TESTS(TestRunResultTests)
}

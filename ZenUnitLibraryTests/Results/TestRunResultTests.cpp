#include "pch.h"
#include "ZenUnitLibraryTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitLibraryTests/Results/Mock/TestFailureNumbererMock.h"
#include "ZenUnitLibraryTests/Results/Mock/TestResultMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Iteration/Mock/MemberForEacherMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Time/Mock/WatchMock.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestRunResultEqualizer.h"

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
   AFACT(PrintConclusion_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
   FACTS(PrintConclusion_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds)
   AFACT(PrintTestClassResultFailures_CallsTestClassResultPrintTestFailures)
   FACTS(DetermineExitCode_DefaultArgs_Returns1IfAnyTestFailures_OtherwiseReturns0)
   FACTS(DetermineExitCode_Exit0True_AlwaysReturns0)
   FACTS(DetermineExitCode_Exit0True_noskipsTrue_AlwaysReturns0)
   FACTS(DetermineExitCode_noskipsTrue_Returns1IfAnyTestsOrTestClassesSkipped)
   AFACT(PrintSkippedTestClassReminder_PrintsExpectedToConsole)
   AFACT(PrintSkippedTestReminder_PrintsExpectedToConsole)
   AFACT(ResetStateExceptForSkips_ResetsTestFailureNumberer_ClearsTestClassResults_SetsNumberOfFailedTestCasesTo0)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TestRunResult _testRunResult;
   const ConsoleMock* _consoleMock = nullptr;
   const WatchMock* _watchMock = nullptr;
   TestFailureNumbererMock* _testFailureNumbererMock = nullptr;

   using TypedefMemberForEacherTestClassResultsMock = MemberForEacherMock<vector<TestClassResult>,
      TestRunResult, void(TestRunResult::*)(const TestClassResult&) const>;
   TypedefMemberForEacherTestClassResultsMock* _memberForEacherTestClassResultsMock;

   using TypedefMemberForEacherSkippedTestsMock = MemberForEacherMock<vector<string>,
      TestRunResult, void(TestRunResult::*)(const string&) const>;
   TypedefMemberForEacherSkippedTestsMock* _memberForEacherSkippedTestsMock;

   STARTUP
   {
      _testRunResult._console.reset(_consoleMock = new ConsoleMock);
      _testRunResult._watch.reset(_watchMock = new WatchMock);
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
      POINTER_WAS_NEWED(testRunResult._watch);
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
      class TestRunResultSelfMocked : public Zen::Mock<TestRunResult>
      {
      public:
         ZENMOCK_NONVOID1_CONST(size_t, NumberOfFailedTestCases, const vector<TestClassResult>&)
      } testRunResultSelfMocked;
      testRunResultSelfMocked.NumberOfFailedTestCasesMock.Return(numberOfFailedTestCases);

      vector<TestClassResult> testClassResults{ TestClassResult() };
      const vector<TestClassResult> NonMovedFromTestClassResults = testClassResults;
      //
      testRunResultSelfMocked.SetTestClassResults(std::move(testClassResults));
      //
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
         ZEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedTestsFailedLine, Color::Yellow));
         ZEN(_memberForEacherTestClassResultsMock->MemberForEachMock.
            CalledOnceWith(&_testRunResult._testClassResults, &_testRunResult, &TestRunResult::PrintTestClassResultFailures));
      }
      ZEN(_memberForEacherSkippedTestsMock->MemberForEachMock.CalledAsFollows(
      {
         { &_testRunResult._skippedTestClassNamesAndReasons, &_testRunResult, &TestRunResult::PrintSkippedTestClassReminder },
         { &_testRunResult._skippedFullTestNamesAndReasons, &_testRunResult, &TestRunResult::PrintSkippedTestReminder }
      }));
   }

   TEST(PrintConclusion_0TotalNumberOfTests_PrintsZeroTestClassesRegisteredToRun)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();
      //
      _testRunResult.PrintConclusion(
         ZenUnit::Random<string>(), 0, ZenUnit::Random<unsigned>(), ZenUnit::Random<ZenUnitArgs>());
      //
      ZEN(_consoleMock->WriteColorMock.CalledOnceWith("[ZenUnit] ", Color::Green));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith("Zero test classes run. Exiting with code 1.", 1));
   }

   TEST7X7(PrintConclusion_PositiveTotalNumberOfTests_PrintsSuccesOrFailureAndElapsedMilliseconds,
      const string& expectedVictoryOrFailLinePrefix,
      ZenUnit::Color expectedColor,
      size_t numberOfFailedTestCases,
      size_t numberOfTotalTests,
      const string& expectedClosingLineTestsCountText,
      unsigned testRunMilliseconds,
      const string& expectedMillisecondOrMilliseconds,
      "<VICTORY>", Color::Green, size_t(0), size_t(1), "1 test passed", 0, "milliseconds",
      "<VICTORY>", Color::Green, size_t(0), size_t(2), "2 tests passed", 1, "millisecond",
      "<VICTORY>", Color::Green, size_t(0), size_t(3), "3 tests passed", 2, "milliseconds",
      "<VICTORY>", Color::Green, size_t(0), size_t(3), "3 tests passed", 2, "milliseconds",
      ">>-FAIL->", Color::Yellow, size_t(1), size_t(1), "1/1 test failed", 0, "milliseconds",
      ">>-FAIL->", Color::Yellow, size_t(1), size_t(2), "1/2 tests failed", 1, "millisecond",
      ">>-FAIL->", Color::Yellow, size_t(1), size_t(3), "1/3 tests failed", 2, "milliseconds",
      ">>-FAIL->", Color::Yellow, size_t(2), size_t(2), "2/2 tests failed", 3, "milliseconds",
      ">>-FAIL->", Color::Yellow, size_t(2), size_t(3), "2/3 tests failed", 4, "milliseconds",
      ">>-FAIL->", Color::Yellow, size_t(2), size_t(3), "2/3 tests failed", 4, "milliseconds",
      ">>-FAIL->", Color::Yellow, size_t(2), size_t(4), "2/4 tests failed", 5, "milliseconds")
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
      _testRunResult._numberOfFailedTestCases = numberOfFailedTestCases;
      const string startTime = ZenUnit::Random<string>();
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
      const ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      //
      _testRunResult.PrintConclusion(startTime, numberOfTotalTests, testRunMilliseconds, zenUnitArgs);
      //
      const string expectedTripletLinesPrefix =
         expectedVictoryOrFailLinePrefix == "<VICTORY>" ? "+=======+ " : ">>------> ";
      ZEN(_consoleMock->WriteColorMock.CalledAsFollows(
      {
         { expectedTripletLinesPrefix, expectedColor },
         { expectedTripletLinesPrefix, expectedColor },
         { expectedTripletLinesPrefix, expectedColor },
         { expectedVictoryOrFailLinePrefix + " ", expectedColor }
      }));
      const string expectedCompletedLine = "Completed: " + zenUnitArgs.commandLine;
      const string expectedStartTimeLine = "StartTime: " + startTime;
      const string expectedEndTimeLine =   "  EndTime: " + dateTimeNow;
      const string expectedNumberOfTestsAndMillisecondsLine = String::Concat("   Result: ",
         expectedClosingLineTestsCountText, " in ", testRunMilliseconds, " ", expectedMillisecondOrMilliseconds,
         " (random seed ", ZenUnitRandomSeed::value, ")");
      ZEN(_watchMock->DateTimeNowMock.CalledOnce());
      ZEN(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         { expectedCompletedLine },
         { expectedStartTimeLine },
         { expectedEndTimeLine },
         { expectedNumberOfTestsAndMillisecondsLine }
      }));
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

   TEST4X4(DetermineExitCode_Exit0True_noskipsTrue_AlwaysReturns0,
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
      args.noskips = true;
      //
      const int exitCode = _testRunResult.DetermineExitCode(args);
      //
      ARE_EQUAL(expectedExitCode, exitCode);
   }

   TEST4X4(DetermineExitCode_noskipsTrue_Returns1IfAnyTestsOrTestClassesSkipped,
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
      args.noskips = true;
      //
      const int exitCode = _testRunResult.DetermineExitCode(args);
      //
      ARE_EQUAL(expectedExitCode, exitCode);
   }

   void SetState(size_t numberOfFailedTestCases, size_t numberOfSkippedTests, size_t numberOfSkippedTestClasses)
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
      EQUALIZER_THROWS(TestRunResult, _testClassResults, vector<TestClassResult> { TestClassResult() });
      EQUALIZER_THROWS(TestRunResult, _skippedTestClassNamesAndReasons, vector<string> { "" });
      EQUALIZER_THROWS(TestRunResult, _skippedFullTestNamesAndReasons, vector<string> { "" });
      EQUALIZER_THROWS(TestRunResult, _numberOfFailedTestCases, 1);
   }

   RUN_TESTS(TestRunResultTests)
}

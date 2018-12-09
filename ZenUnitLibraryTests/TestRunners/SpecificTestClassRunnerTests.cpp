#include "pch.h"
#include "ZenUnitLibraryTests/Args/Mock/RunFilterMock.h"
#include "ZenUnitLibraryTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Random/RandomRunFilter.h"
#include "ZenUnitLibraryTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitLibraryTests/Tests/Mock/TestMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Function/Mock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Function/Mock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Function/Mock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Iteration/Mock/TwoArgAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Iteration/Mock/TwoArgMemberAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Iteration/Mock/TwoArgMemberForEacherMock.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"

namespace ZenUnit
{
   TESTS(SpecificTestClassRunnerTests)
   AFACT(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   AFACT(TestClassName_ReturnsTestClassName)
   AFACT(HasTestThatMatchesRunFilter_RunFilterTestNamePatternIsEmpty_ReturnsTrue)
   AFACT(HasTestThatMatchesRunFilter_RunFilterTestNamePatternIsNotEmpty_ReturnsTrueIfRunFilterMatchesTestNameReturnsTrue)
   AFACT(RunFilterMatchesTestName_ReturnsTrueIfRunFilterMatchesTestNameReturnsTrue)
   AFACT(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   FACTS(RunTests_PrintsTestClassNameAndNumberOfNamedTests_ConfirmsTestClassNewableAndDeletable_RunsTests_PrintsAndReturnsTestClassResult)
   FACTS(DoRunTests_RandomlyRunsTestsIfRandomOtherwiseSequentiallyRunsTests)
   FACTS(PrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests)
   FACTS(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewableDeletableTest_AddsResultToResults_ReturnsTrueIfNewableAndDeletable)
   AFACT(RunTest_RunFiltersNonEmpty_NoneOfTheRunFiltersMatchTheTestName_DoesNotRunTest)
   FACTS(RunTest_RunFiltersEmptyOrIfNotEmptyARunFilterMatchesTheTestName_RunsTest)
   AFACT(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   EVIDENCE

   class TestingTestClass
   {
   public:
      static vector<unique_ptr<Test>> GetTests(const char*)
      {
         vector<unique_ptr<Test>> tests;
         // emplace one Test pointer to make tests vector non-default sized
         tests.emplace_back(nullptr);
         return tests;
      }
   };

   unique_ptr<SpecificTestClassRunner<TestingTestClass>> _specificTestClassRunner;
   ConsoleMock* p_consoleMock = nullptr;
   const string _testClassName = ZenUnit::Random<string>();

   using TwoArgMemberForEacherMockType = TwoArgMemberForEacherMock<
      unique_ptr<Test>, SpecificTestClassRunner<TestingTestClass>,
      void (SpecificTestClassRunner<TestingTestClass>::*)(
         const unique_ptr<Test>& test, TestClassResult*) const, TestClassResult*>;
   TwoArgMemberForEacherMockType* _twoArgMemberForEacherMock = nullptr;
   VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>* _voidZeroArgMemberFunctionCallerMock = nullptr;
   NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>* _nonVoidTwoArgFunctionCallerMock = nullptr;
   VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>* _voidOneArgMemberFunctionCallerMock = nullptr;

   using TwoArgTestAnyerMockType = TwoArgAnyerMock<
      const std::vector<std::unique_ptr<Test>>,
      bool(*)(const std::unique_ptr<Test>&, const RunFilter&),
      const RunFilter&>;
   TwoArgTestAnyerMockType* _twoArgTestAnyerMock = nullptr;

   using TwoArgMemberAnyerMockType = TwoArgMemberAnyerMock<
      std::vector<RunFilter>, TestClassRunner,
      bool(TestClassRunner::*)(const RunFilter&, const char*) const, const char*>;
   TwoArgMemberAnyerMockType* p_twoArgMemberAnyerMock = nullptr;

   ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)

   STARTUP
   {
      _specificTestClassRunner = make_unique<SpecificTestClassRunner<TestingTestClass>>(_testClassName.c_str());
      _specificTestClassRunner->p_console.reset(p_consoleMock = new ConsoleMock);
      _specificTestClassRunner->_call_TestRunner_GetArgs = BIND_0ARG_ZENMOCK_OBJECT(GetArgs_ZenMockObject);
      _specificTestClassRunner->_twoArgMemberForEacher.reset(_twoArgMemberForEacherMock = new TwoArgMemberForEacherMockType);
      _specificTestClassRunner->_voidZeroArgMemberFunctionCaller.reset(
         _voidZeroArgMemberFunctionCallerMock =
         new VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>);
      _specificTestClassRunner->_nonVoidTwoArgFunctionCaller.reset(
         _nonVoidTwoArgFunctionCallerMock =
         new NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>);
      _specificTestClassRunner->_voidOneArgFunctionCaller.reset(_voidOneArgMemberFunctionCallerMock =
         new VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>);
      _specificTestClassRunner->_twoArgTestAnyer.reset(_twoArgTestAnyerMock = new TwoArgTestAnyerMockType);
      _specificTestClassRunner->_call_TestRunner_GetArgs = BIND_0ARG_ZENMOCK_OBJECT(GetArgs_ZenMockObject);
      _specificTestClassRunner->p_twoArgMemberAnyer.reset(p_twoArgMemberAnyerMock = new TwoArgMemberAnyerMockType);
   }

   TEST(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
   {
      SpecificTestClassRunner<TestingTestClass> specificTestClassRunner(_testClassName.c_str());
      //
      POINTER_WAS_NEWED(specificTestClassRunner.p_console);
      POINTER_WAS_NEWED(specificTestClassRunner._twoArgMemberForEacher);
      POINTER_WAS_NEWED(specificTestClassRunner._voidZeroArgMemberFunctionCaller);
      POINTER_WAS_NEWED(specificTestClassRunner._twoArgTestAnyer);
      POINTER_WAS_NEWED(specificTestClassRunner._nonVoidTwoArgFunctionCaller);
      POINTER_WAS_NEWED(specificTestClassRunner._voidOneArgFunctionCaller);
      ARE_EQUAL(_testClassName.c_str(), specificTestClassRunner._testClassName);
      STD_FUNCTION_TARGETS(TestRunner::GetArgs, specificTestClassRunner._call_TestRunner_GetArgs);

      vector<unique_ptr<Test>> expectedTests;
      expectedTests.emplace_back(nullptr);
      VECTORS_EQUAL(expectedTests, specificTestClassRunner._tests);
   }

   TEST(TestClassName_ReturnsTestClassName)
   {
      const char* const testClassName = _specificTestClassRunner->TestClassName();
      ARE_EQUAL(_testClassName.c_str(), testClassName);
   }

   TEST(HasTestThatMatchesRunFilter_RunFilterTestNamePatternIsEmpty_ReturnsTrue)
   {
      const RunFilter runFilterWithEmptyTestName;
      IS_EMPTY(runFilterWithEmptyTestName.testNamePattern);
      //
      const bool hasTestThatMatchesRunFilter = _specificTestClassRunner->HasTestThatMatchesRunFilter(runFilterWithEmptyTestName);
      //
      IS_TRUE(hasTestThatMatchesRunFilter);
   }

   TEST(HasTestThatMatchesRunFilter_RunFilterTestNamePatternIsNotEmpty_ReturnsTrueIfRunFilterMatchesTestNameReturnsTrue)
   {
      const bool twoArgAnyerReturnValue = _twoArgTestAnyerMock->TwoArgAnyMock.ReturnRandom();
      const RunFilter runFilter = ZenUnit::Random<RunFilter>();
      //
      const bool hasTestThatMatchesRunFilter = _specificTestClassRunner->HasTestThatMatchesRunFilter(runFilter);
      //
      ZEN(_twoArgTestAnyerMock->TwoArgAnyMock.CalledOnceWith(
         &_specificTestClassRunner->_tests, SpecificTestClassRunner<TestingTestClass>::RunFilterMatchesTestName, runFilter));
      ARE_EQUAL(twoArgAnyerReturnValue, hasTestThatMatchesRunFilter);
   }

   TEST(RunFilterMatchesTestName_ReturnsTrueIfRunFilterMatchesTestNameReturnsTrue)
   {
      TestMock* testMock = new TestMock;
      const string testName = ZenUnit::Random<string>();
      testMock->NameMock.Return(testName.c_str());
      unique_ptr<Test> test(testMock);

      RunFilterMock runFilterMock;
      const bool runFilterMatchesTestName = ZenUnit::Random<bool>();
      runFilterMock.MatchesTestNameMock.Return(runFilterMatchesTestName);
      //
      const bool returnedRunFilterMatchesTestName = _specificTestClassRunner->RunFilterMatchesTestName(test, runFilterMock);
      //
      ZEN(testMock->NameMock.CalledOnce());
      ZEN(runFilterMock.MatchesTestNameMock.CalledOnceWith(testName.c_str()));
      ARE_EQUAL(runFilterMatchesTestName, returnedRunFilterMatchesTestName);
   }

   TEST(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
   {
      _specificTestClassRunner->_tests.resize(3);
      TestMock* const testMockA = new TestMock;
      testMockA->NumberOfTestCasesMock.Return(10);
      TestMock* const testMockB = new TestMock;
      testMockB->NumberOfTestCasesMock.Return(0);
      TestMock* const testMockC = new TestMock;
      testMockC->NumberOfTestCasesMock.Return(20);
      _specificTestClassRunner->_tests[0].reset(testMockA);
      _specificTestClassRunner->_tests[1].reset(testMockB);
      _specificTestClassRunner->_tests[2].reset(testMockC);
      //
      const size_t numberOfTestCases = _specificTestClassRunner->NumberOfTestCases();
      //
      ZEN(testMockA->NumberOfTestCasesMock.CalledOnce());
      ZEN(testMockB->NumberOfTestCasesMock.CalledOnce());
      ZEN(testMockC->NumberOfTestCasesMock.CalledOnce());
      ARE_EQUAL(30, numberOfTestCases);
   }

   TEST2X2(RunTests_PrintsTestClassNameAndNumberOfNamedTests_ConfirmsTestClassNewableAndDeletable_RunsTests_PrintsAndReturnsTestClassResult,
      bool testClassTypeNewableAndDeletable, bool expectDoRunTestsCall,
      false, false,
      true, true)
   {
      _voidZeroArgMemberFunctionCallerMock->ConstCallMock.Expect();
      _nonVoidTwoArgFunctionCallerMock->ConstCallMock.Return(testClassTypeNewableAndDeletable);
      if (expectDoRunTestsCall)
      {
         _voidZeroArgMemberFunctionCallerMock->NonConstCallMock.Expect();
      }
      _voidOneArgMemberFunctionCallerMock->ConstCallMock.Expect();
      p_consoleMock->WriteNewLineMock.Expect();
      _specificTestClassRunner->_testClassResult = TestClassResult::TestingNonDefault();
      //
      const TestClassResult testClassResult = _specificTestClassRunner->RunTests();
      //
      ZEN(_voidZeroArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassNameAndNumberOfNamedTests));
      ZEN(_nonVoidTwoArgFunctionCallerMock->ConstCallMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests,
         &_specificTestClassRunner->_newableDeletableTest, &_specificTestClassRunner->_testClassResult));
      if (expectDoRunTestsCall)
      {
         ZEN(_voidZeroArgMemberFunctionCallerMock->NonConstCallMock.CalledOnceWith(
            _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::DoRunTests));
      }
      ZEN(_voidOneArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
         _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassResultLine,
         &_specificTestClassRunner->_testClassResult));
      ZEN(p_consoleMock->WriteNewLineMock.CalledOnce());
      ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
      ARE_EQUAL(TestClassResult(), _specificTestClassRunner->_testClassResult);
   }

   TEST2X2(DoRunTests_RandomlyRunsTestsIfRandomOtherwiseSequentiallyRunsTests,
      bool random, bool expectRandomForEach,
      false, false,
      true, true)
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.random = random;
      zenUnitArgs.randomseed = Random<unsigned short>();
      GetArgs_ZenMockObject.Return(zenUnitArgs);
      if (expectRandomForEach)
      {
         _twoArgMemberForEacherMock->RandomTwoArgMemberForEachMock.Expect();
      }
      else
      {
         _twoArgMemberForEacherMock->TwoArgMemberForEachMock.Expect();
      }
      //
      _specificTestClassRunner->DoRunTests();
      //
      ZEN(GetArgs_ZenMockObject.CalledOnce());
      if (expectRandomForEach)
      {
         ZEN(_twoArgMemberForEacherMock->RandomTwoArgMemberForEachMock.CalledOnceWith(
            &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
            &SpecificTestClassRunner<TestingTestClass>::RunTest,
            &_specificTestClassRunner->_testClassResult,
            zenUnitArgs.randomseed));
      }
      else
      {
         ZEN(_twoArgMemberForEacherMock->TwoArgMemberForEachMock.CalledOnceWith(
            &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
            &SpecificTestClassRunner<TestingTestClass>::RunTest,
            &_specificTestClassRunner->_testClassResult));
      }
   }

   TEST2X2(PrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests,
      size_t numberOfTests, bool expectTestsPlural,
      size_t(0), true,
      size_t(1), false,
      size_t(2), true,
      size_t(3), true)
   {
      p_consoleMock->WriteColorMock.Expect();
      p_consoleMock->WriteLineMock.Expect();
      _specificTestClassRunner->_testClassName = _testClassName.c_str();
      _specificTestClassRunner->_tests.resize(numberOfTests);
      //
      _specificTestClassRunner->PrintTestClassNameAndNumberOfNamedTests();
      //
      ZEN(p_consoleMock->WriteColorMock.CalledAsFollows(
         {
            { "@", Color::Green },
            { _testClassName.c_str(), Color::Green }
         }));
      if (expectTestsPlural)
      {
         ZEN(p_consoleMock->WriteLineMock.CalledOnceWith(
            String::Concat(" | ", numberOfTests, " named tests")));
      }
      else
      {
         ZEN(p_consoleMock->WriteLineMock.CalledOnceWith(
            String::Concat(" | ", numberOfTests, " named test")));
      }
   }

   TEST3X3(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewableDeletableTest_AddsResultToResults_ReturnsTrueIfNewableAndDeletable,
      bool expectedReturnValue, TestOutcome newableDeletableTestOutcome, bool expectWriteLineOK,
      false, TestOutcome::Anomaly, false,
      false, TestOutcome::Exception, false,
      true, TestOutcome::Success, true)
   {
      p_consoleMock->WriteColorMock.Expect();
      p_consoleMock->WriteMock.Expect();

      TestClassResultMock testClassResultMock;
      testClassResultMock.AddTestResultsMock.Expect();
      string testResultThreeDecimalMillisecondsString;
      if (expectWriteLineOK)
      {
         p_consoleMock->WriteColorMock.Expect();
         p_consoleMock->WriteLineMock.Expect();
         testResultThreeDecimalMillisecondsString = testClassResultMock.
            MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.ReturnRandom();
      }
      TestMock testMock;

      TestResult testResult;
      testResult.testOutcome = newableDeletableTestOutcome;
      testResult.microseconds = ZenUnit::Random<unsigned>();
      const vector<TestResult> testResults{ testResult };
      testMock.RunTestMock.Return(testResults);
      //
      const bool testClassTypeIsNewableAndDeletable = _specificTestClassRunner->
         ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(&testMock, &testClassResultMock);
      //
      if (expectWriteLineOK)
      {
         ZEN(p_consoleMock->WriteColorMock.CalledAsFollows(
         {
            { "|", Color::Green },
            { "OK ", Color::Green }
         }));
         ZEN(testClassResultMock.MicrosecondsToTwoDecimalPlaceMillisecondsStringMock.
            CalledOnceWith(testResult.microseconds));
         ZEN(p_consoleMock->WriteLineMock.CalledOnceWith(testResultThreeDecimalMillisecondsString));
      }
      else
      {
         ZEN(p_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
      }
      ZEN(p_consoleMock->WriteMock.CalledOnceWith("TestClassIsNewableAndDeletable -> "));
      ZEN(testMock.RunTestMock.CalledOnce());
      ZEN(testClassResultMock.AddTestResultsMock.CalledOnceWith(testResults));
      ARE_EQUAL(expectedReturnValue, testClassTypeIsNewableAndDeletable);
   }

   TEST(RunTest_RunFiltersNonEmpty_NoneOfTheRunFiltersMatchTheTestName_DoesNotRunTest)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.runFilters.resize(ZenUnit::RandomBetween<size_t>(1, 2));
      GetArgs_ZenMockObject.Return(zenUnitArgs);

      TestMock* const testMock = new TestMock;
      const string testName = Random<string>();
      testMock->NameMock.Return(testName.c_str());
      const unique_ptr<Test> test(testMock);

      p_twoArgMemberAnyerMock->TwoArgAnyMock.Return(false);

      TestClassResultMock testClassResultMock;
      //
      _specificTestClassRunner->RunTest(test, &testClassResultMock);
      //
      ZEN(GetArgs_ZenMockObject.CalledOnce());
      ZEN(testMock->NameMock.CalledOnce());
      ZEN(p_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         zenUnitArgs.runFilters, _specificTestClassRunner.get(), &TestClassRunner::RunFilterMatchesTestName, testName.c_str()));
   }

   TEST2X2(RunTest_RunFiltersEmptyOrIfNotEmptyARunFilterMatchesTheTestName_RunsTest,
      size_t runFiltersSize, bool expectAnyerCall,
      0, false,
      1, true,
      2, true)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.runFilters.resize(runFiltersSize);
      GetArgs_ZenMockObject.Return(zenUnitArgs);

      p_consoleMock->WriteColorMock.Expect();
      p_consoleMock->WriteMock.Expect();

      TestMock* const testMock = new TestMock;
      const string testName = Random<string>();
      testMock->NameMock.Return(testName.c_str());
      testMock->WritePostTestNameMessageMock.Expect();
      TestResult test0;
      test0.fullTestName = FullTestName("", "Test0", 0);
      const vector<TestResult> TestResults{ test0, TestResult() };
      testMock->RunTestMock.Return(TestResults);
      testMock->WritePostTestCompletionMessageMock.Expect();
      const unique_ptr<Test> test(testMock);
      if (expectAnyerCall)
      {
         p_twoArgMemberAnyerMock->TwoArgAnyMock.Return(true);
      }
      TestClassResultMock testClassResultMock;
      testClassResultMock.AddTestResultsMock.Expect();
      //
      _specificTestClassRunner->RunTest(test, &testClassResultMock);
      //
      ZEN(GetArgs_ZenMockObject.CalledOnce());
      ZEN(testMock->NameMock.CalledOnce());
      if (expectAnyerCall)
      {
         ZEN(p_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
            zenUnitArgs.runFilters, _specificTestClassRunner.get(), &TestClassRunner::RunFilterMatchesTestName, testName.c_str()));
      }
      ZEN(p_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
      ZEN(p_consoleMock->WriteMock.CalledOnceWith(testName));
      ZEN(testMock->WritePostTestNameMessageMock.CalledOnceWith(_specificTestClassRunner->p_console.get()));
      ZEN(testMock->RunTestMock.CalledOnce());
      ZEN(testClassResultMock.AddTestResultsMock.CalledOnceWith(TestResults));
      ZEN(testMock->WritePostTestCompletionMessageMock.CalledOnceWith(
         _specificTestClassRunner->p_console.get(), test0));
   }

   TEST(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
   {
      TestClassResultMock testClassResultMock;
      testClassResultMock.PrintTestClassResultLineMock.Expect();
      //
      _specificTestClassRunner->PrintTestClassResultLine(&testClassResultMock);
      //
      ZEN(testClassResultMock.PrintTestClassResultLineMock.CalledOnceWith(p_consoleMock));
   }

   RUN_TESTS(SpecificTestClassRunnerTests)
}

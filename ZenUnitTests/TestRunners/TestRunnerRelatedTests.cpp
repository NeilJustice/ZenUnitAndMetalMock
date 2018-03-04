#include "pch.h"
#if defined __linux__
#include <unistd.h>
#endif

#include "ZenUnitTests/Args/Mock/ArgsParserMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TwoArgMemberForEacherMock.h"
#include "ZenUnitTests/Utils/Mock/MachineNameGetterMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/TestRunners/Mock/PreamblePrinterMock.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerRunnerMock.h"
#include "ZenUnitTests/Random/RandomTestResult.h"
#include "ZenUnitTests/Random/RandomZenUnitArgs.h"
#include "ZenUnitTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitTests/Results/Mock/TestRunResultMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TwoArgMemberAnyerMock.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"

namespace ZenUnit
{

TESTS(NoOpTestClassRunnerTests)
AFACT(TestClassName_ReturnsNoOpTestClassRunner)
AFACT(NumberOfTestCases_Returns0)
AFACT(RunTests_ReturnsDefaultTestClassResult)
EVIDENCE

NoOpTestClassRunner _noOpTestClassRunner;

TEST(TestClassName_ReturnsNoOpTestClassRunner)
{
   ARE_EQUAL("NoOpTestClassRunner", _noOpTestClassRunner.TestClassName());
}

TEST(NumberOfTestCases_Returns0)
{
   ARE_EQUAL(0, _noOpTestClassRunner.NumberOfTestCases());
}

TEST(RunTests_ReturnsDefaultTestClassResult)
{
   ARE_EQUAL(TestClassResult(), _noOpTestClassRunner.RunTests());
}

RUN_TESTS(NoOpTestClassRunnerTests)


TESTS(PreamblePrinterTests)
AFACT(Constructor_NewsConsoleAndWatch)
AFACT(PrintOpeningThreeLines_PrintsCommandLineAndTimeZoneAndTestAndTestClassCounts)
FACTS(MakeThirdLinePrefix_ReturnsNumberOfTestClassesBeingRunAndMachineName)
FACTS(MakeThirdLineSuffix_ReturnsRandomSeedIfRandomModeOtherwiseEmptyString)
EVIDENCE

struct PreamblePrinterSelfMocked : public Zen::Mock<PreamblePrinter>
{
   const ConsoleMock* consoleMock;
   const WatchMock* watchMock;
   PreamblePrinterSelfMocked()
   {
      _console.reset(consoleMock = new ConsoleMock);
      _watch.reset(watchMock = new WatchMock);
   }
   ZENMOCK_NONVOID1_CONST(string, MakeThirdLinePrefix, size_t)
   ZENMOCK_NONVOID2_CONST(string, MakeThirdLineSuffix, bool, unsigned short)
} _preamblePrinterSelfMocked;

PreamblePrinter _preamblePrinter;
const MachineNameGetterMock* _machineNameGetterMock = nullptr;

STARTUP
{
   _preamblePrinter._machineNameGetter.reset(_machineNameGetterMock = new MachineNameGetterMock);
}

TEST(Constructor_NewsConsoleAndWatch)
{
   PreamblePrinter preamblePrinter;
   POINTER_WAS_NEWED(preamblePrinter._console);
   POINTER_WAS_NEWED(preamblePrinter._watch);
   POINTER_WAS_NEWED(preamblePrinter._machineNameGetter);
}

TEST(PrintOpeningThreeLines_PrintsCommandLineAndTimeZoneAndTestAndTestClassCounts)
{
   _preamblePrinterSelfMocked.consoleMock->WriteColorMock.Expect();
   _preamblePrinterSelfMocked.consoleMock->WriteLineMock.Expect();
   TestClassRunnerRunnerMock testClassRunnerRunnerMock;
   const size_t numberOfTestClassesToBeRun = testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.ReturnRandom();
   const string timeZoneDateTimeNow = _preamblePrinterSelfMocked.watchMock->TimeZoneDateTimeNowMock.ReturnRandom();
   const string thirdLinePrefix = _preamblePrinterSelfMocked.MakeThirdLinePrefixMock.ReturnRandom();
   const string thirdLineSuffix = _preamblePrinterSelfMocked.MakeThirdLineSuffixMock.ReturnRandom();

   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.commandLine = Random<string>();
   zenUnitArgs.random = Random<bool>();
   zenUnitArgs.randomseed = Random<unsigned short>();
   //
   _preamblePrinterSelfMocked.PrintOpeningThreeLines(zenUnitArgs, &testClassRunnerRunnerMock);
   //
   ZEN(_preamblePrinterSelfMocked.watchMock->TimeZoneDateTimeNowMock.CalledOnce());
   ZEN(testClassRunnerRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce());
   ZEN(_preamblePrinterSelfMocked.consoleMock->WriteColorMock.CalledNTimesWith(3, "[ZenUnit]", Color::Green));
   ZEN(_preamblePrinterSelfMocked.MakeThirdLinePrefixMock.CalledOnceWith(numberOfTestClassesToBeRun));
   ZEN(_preamblePrinterSelfMocked.MakeThirdLineSuffixMock.
      CalledOnceWith(zenUnitArgs.random, zenUnitArgs.randomseed));
   const string expectedThirdLineAndLineBreak = thirdLinePrefix + thirdLineSuffix + "\n";
   ZEN(_preamblePrinterSelfMocked.consoleMock->WriteLineMock.CalledAsFollows(
   {
      " Running " + zenUnitArgs.commandLine,
      " Running at " + timeZoneDateTimeNow,
      expectedThirdLineAndLineBreak
   }));
}

TEST2X2(MakeThirdLinePrefix_ReturnsNumberOfTestClassesBeingRunAndMachineName,
   const string& expectedReturnValuePrefix, size_t numberOfTestClasses,
   " Running 0 test classes on machine ", size_t(0),
   " Running 1 test class on machine ", size_t(1),
   " Running 2 test classes on machine ", size_t(2))
{
   const string machineName = _machineNameGetterMock->GetMachineNameMock.ReturnRandom();
   //
   const string thirdLinePrefix = _preamblePrinter.MakeThirdLinePrefix(numberOfTestClasses);
   //
   ZEN(_machineNameGetterMock->GetMachineNameMock.CalledOnce());
   const string expectedReturnValue = expectedReturnValuePrefix + machineName;
   ARE_EQUAL(expectedReturnValue, thirdLinePrefix);
}

TEST3X3(MakeThirdLineSuffix_ReturnsRandomSeedIfRandomModeOtherwiseEmptyString,
   const string& expectedReturnValue, bool random, unsigned short randomseed,
   "", false, NA<unsigned short>(),
   " with random seed 0", true, static_cast<unsigned short>(0),
   " with random seed 1", true, static_cast<unsigned short>(1))
{
   const string thirdLineSuffix = _preamblePrinter.MakeThirdLineSuffix(random, randomseed);
   ARE_EQUAL(expectedReturnValue, thirdLineSuffix);
}

RUN_TESTS(PreamblePrinterTests)


TESTS(SpecificTestClassRunnerTests)
AFACT(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
AFACT(TestClassName_ReturnsTestClassName)
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
ConsoleMock* _consoleMock = nullptr;
const string _testClassName = ZenUnit::Random<string>();

using TwoArgMemberForEacherMockType = TwoArgMemberForEacherMock<
   unique_ptr<Test>, SpecificTestClassRunner<TestingTestClass>,
   void (SpecificTestClassRunner<TestingTestClass>::*)(
      const unique_ptr<Test>& test, TestClassResult*) const, TestClassResult*>;
TwoArgMemberForEacherMockType* _twoArgMemberForEacherMock;
VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>* _voidZeroArgFunctionCallerMock;
NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>* _nonVoidTwoArgFunctionCallerMock;
VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>* _voidOneArgFunctionCallerMock;
using TwoArgMemberAnyerMockType = TwoArgMemberAnyerMock<
   std::vector<RunFilter>, TestClassRunner,
   bool(TestClassRunner::*)(const RunFilter&, const char*) const, const char*>;
TwoArgMemberAnyerMockType* pro_twoArgMemberAnyerMock;

ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)

STARTUP
{
   _specificTestClassRunner = make_unique<SpecificTestClassRunner<TestingTestClass>>(_testClassName.c_str());
   _specificTestClassRunner->_console.reset(_consoleMock = new ConsoleMock);
   _specificTestClassRunner->call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
   _specificTestClassRunner->_twoArgMemberForEacher.reset(_twoArgMemberForEacherMock = new TwoArgMemberForEacherMockType);
   _specificTestClassRunner->_voidZeroArgFunctionCaller.reset(
      _voidZeroArgFunctionCallerMock =
      new VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>);
   _specificTestClassRunner->_nonVoidTwoArgFunctionCaller.reset(
      _nonVoidTwoArgFunctionCallerMock =
      new NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>);
   _specificTestClassRunner->_voidOneArgFunctionCaller.reset(_voidOneArgFunctionCallerMock =
      new VoidOneArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*>);
   _specificTestClassRunner->call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
   _specificTestClassRunner->pro_twoArgMemberAnyer.reset(pro_twoArgMemberAnyerMock = new TwoArgMemberAnyerMockType);
}

TEST(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
{
   SpecificTestClassRunner<TestingTestClass> specificTestClassRunner(_testClassName.c_str());
   //
   POINTER_WAS_NEWED(specificTestClassRunner._console);
   POINTER_WAS_NEWED(specificTestClassRunner._twoArgMemberForEacher);
   POINTER_WAS_NEWED(specificTestClassRunner._voidZeroArgFunctionCaller);
   POINTER_WAS_NEWED(specificTestClassRunner._nonVoidTwoArgFunctionCaller);
   POINTER_WAS_NEWED(specificTestClassRunner._voidOneArgFunctionCaller);
   ARE_EQUAL(_testClassName.c_str(), specificTestClassRunner._testClassName);
   STD_FUNCTION_TARGETS(TestRunner::GetArgs, specificTestClassRunner.call_TestRunner_GetArgs);

   vector<unique_ptr<Test>> expectedTests;
   expectedTests.emplace_back(nullptr);
   VECTORS_EQUAL(expectedTests, specificTestClassRunner._tests);
}

TEST(TestClassName_ReturnsTestClassName)
{
   const char* const testClassName = _specificTestClassRunner->TestClassName();
   ARE_EQUAL(_testClassName.c_str(), testClassName);
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
   _voidZeroArgFunctionCallerMock->ConstCallMock.Expect();
   _nonVoidTwoArgFunctionCallerMock->ConstCallMock.Return(testClassTypeNewableAndDeletable);
   if (expectDoRunTestsCall)
   {
      _voidZeroArgFunctionCallerMock->NonConstCallMock.Expect();
   }
   _voidOneArgFunctionCallerMock->ConstCallMock.Expect();
   _consoleMock->WriteNewLineMock.Expect();
   _specificTestClassRunner->_testClassResult = TestClassResult::TestingNonDefault();
   //
   const TestClassResult testClassResult = _specificTestClassRunner->RunTests();
   //
   ZEN(_voidZeroArgFunctionCallerMock->ConstCallMock.CalledOnceWith(
       _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassNameAndNumberOfNamedTests));
   ZEN(_nonVoidTwoArgFunctionCallerMock->ConstCallMock.CalledOnceWith(
      _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests,
      &_specificTestClassRunner->_newableDeletableTest, &_specificTestClassRunner->_testClassResult));
   if (expectDoRunTestsCall)
   {
      ZEN(_voidZeroArgFunctionCallerMock->NonConstCallMock.CalledOnceWith(
          _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::DoRunTests));
   }
   ZEN(_voidOneArgFunctionCallerMock->ConstCallMock.CalledOnceWith(
      _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::PrintTestClassResultLine,
      &_specificTestClassRunner->_testClassResult));
   ZEN(_consoleMock->WriteNewLineMock.CalledOnce());
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
   GetArgs_ZenMock.Return(zenUnitArgs);
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
   ZEN(GetArgs_ZenMock.CalledOnce());
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
   _consoleMock->WriteColorMock.Expect();
   _consoleMock->WriteLineMock.Expect();
   _specificTestClassRunner->_testClassName = _testClassName.c_str();
   _specificTestClassRunner->_tests.resize(numberOfTests);
   //
   _specificTestClassRunner->PrintTestClassNameAndNumberOfNamedTests();
   //
   ZEN(_consoleMock->WriteColorMock.CalledAsFollows(
   {
      { "@", Color::Green },
      { _testClassName.c_str(), Color::Green }
   }));
   if (expectTestsPlural)
   {
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         String::Concat(" | ", numberOfTests, " named tests")));
   }
   else
   {
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         String::Concat(" | ", numberOfTests, " named test")));
   }
}

TEST3X3(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewableDeletableTest_AddsResultToResults_ReturnsTrueIfNewableAndDeletable,
   bool expectedReturnValue, TestOutcome newableDeletableTestOutcome, bool expectWriteLineOK,
   false, TestOutcome::Anomaly, false,
   false, TestOutcome::Exception, false,
   true, TestOutcome::Success, true)
{
   _consoleMock->WriteColorMock.Expect();
   _consoleMock->WriteMock.Expect();
   if (expectWriteLineOK)
   {
      _consoleMock->WriteColorMock.Expect();
      _consoleMock->WriteLineMock.Expect();
   }
   TestMock testMock;

   TestResult testResult;
   testResult.testOutcome = newableDeletableTestOutcome;
   testResult.microseconds = ZenUnit::Random<unsigned>();
   const vector<TestResult> testResults{ testResult };
   testMock.RunMock.Return(testResults);

   TestClassResultMock testClassResultMock;
   testClassResultMock.AddTestResultsMock.Expect();
   //
   const bool testClassTypeIsNewableAndDeletable = _specificTestClassRunner->
      ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(&testMock, &testClassResultMock);
   //
   if (expectWriteLineOK)
   {
       ZEN(_consoleMock->WriteColorMock.CalledAsFollows(
       {
          { "|", Color::Green },
          { "OK ", Color::Green }
       }));
       ZEN(_consoleMock->WriteLineMock.CalledOnceWith(String::Concat("(", testResult.microseconds, "us)")));
   }
   else
   {
      ZEN(_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
   }
   ZEN(_consoleMock->WriteMock.CalledOnceWith("TestClassIsNewableAndDeletable -> "));
   ZEN(testMock.RunMock.CalledOnce());
   ZEN(testClassResultMock.AddTestResultsMock.CalledOnceWith(testResults));
   ARE_EQUAL(expectedReturnValue, testClassTypeIsNewableAndDeletable);
}

TEST(RunTest_RunFiltersNonEmpty_NoneOfTheRunFiltersMatchTheTestName_DoesNotRunTest)
{
   ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
   zenUnitArgs.runFilters.resize(ZenUnit::RandomBetween<size_t>(1, 2));
   GetArgs_ZenMock.Return(zenUnitArgs);

   TestMock* const testMock = new TestMock;
   const string testName = Random<string>();
   testMock->NameMock.Return(testName.c_str());
   const unique_ptr<Test> test(testMock);

   pro_twoArgMemberAnyerMock->TwoArgAnyMock.Return(false);

   TestClassResultMock testClassResultMock;
   //
   _specificTestClassRunner->RunTest(test, &testClassResultMock);
   //
   ZEN(GetArgs_ZenMock.CalledOnce());
   ZEN(testMock->NameMock.CalledOnce());
   ZEN(pro_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
      zenUnitArgs.runFilters, _specificTestClassRunner.get(),
      &TestClassRunner::TestNameCaseInsensitiveMatchesRunFilterTestName, testName.c_str()));
}

TEST2X2(RunTest_RunFiltersEmptyOrIfNotEmptyARunFilterMatchesTheTestName_RunsTest,
   size_t runFiltersSize, bool expectAnyerCall,
   0, false,
   1, true,
   2, true)
{
   ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
   zenUnitArgs.runFilters.resize(runFiltersSize);
   GetArgs_ZenMock.Return(zenUnitArgs);

   _consoleMock->WriteColorMock.Expect();
   _consoleMock->WriteMock.Expect();

   TestMock* const testMock = new TestMock;
   const string testName = Random<string>();
   testMock->NameMock.Return(testName.c_str());
   testMock->WritePostTestNameMessageMock.Expect();
   TestResult test0;
   test0.fullTestName = FullTestName("", "Test0", 0);
   const vector<TestResult> TestResults{ test0, TestResult() };
   testMock->RunMock.Return(TestResults);
   testMock->WritePostTestCompletionMessageMock.Expect();
   const unique_ptr<Test> test(testMock);
   if (expectAnyerCall)
   {
      pro_twoArgMemberAnyerMock->TwoArgAnyMock.Return(true);
   }
   TestClassResultMock testClassResultMock;
   testClassResultMock.AddTestResultsMock.Expect();
   //
   _specificTestClassRunner->RunTest(test, &testClassResultMock);
   //
   ZEN(GetArgs_ZenMock.CalledOnce());
   ZEN(testMock->NameMock.CalledOnce());
   if (expectAnyerCall)
   {
      ZEN(pro_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         zenUnitArgs.runFilters, _specificTestClassRunner.get(),
         &TestClassRunner::TestNameCaseInsensitiveMatchesRunFilterTestName, testName.c_str()));
   }
   ZEN(_consoleMock->WriteColorMock.CalledOnceWith("|", Color::Green));
   ZEN(_consoleMock->WriteMock.CalledOnceWith(testName));
   ZEN(testMock->WritePostTestNameMessageMock.CalledOnceWith(_specificTestClassRunner->_console.get()));
   ZEN(testMock->RunMock.CalledOnce());
   ZEN(testClassResultMock.AddTestResultsMock.CalledOnceWith(TestResults));
   ZEN(testMock->WritePostTestCompletionMessageMock.CalledOnceWith(
      _specificTestClassRunner->_console.get(), test0));
}

TEST(PrintTestClassResultLine_CallsTestClassResultPrintResultLine)
{
   TestClassResultMock testClassResultMock;
   testClassResultMock.PrintTestClassResultLineMock.Expect();
   //
   _specificTestClassRunner->PrintTestClassResultLine(&testClassResultMock);
   //
   ZEN(testClassResultMock.PrintTestClassResultLineMock.CalledOnceWith(_consoleMock));
}

RUN_TESTS(SpecificTestClassRunnerTests)


class TestingTestClassRunner : public TestClassRunner
{
   virtual const char* TestClassName() const { return nullptr; }
   virtual size_t NumberOfTestCases() const { return 0; }
   virtual TestClassResult RunTests() { return TestClassResult(); }
};

TESTS(TestClassRunnerTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(TestNameCaseInsensitiveMatchesRunFilterTestName_ReturnsResultFromCallingRunFilterMatchesFilter)
FACTS(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero)
EVIDENCE

TestingTestClassRunner _testingTestClassRunner;
ZENMOCK_NONVOID2_STATIC(bool, RunFilter, StringMatchesFilter, const char*, const string&)

STARTUP
{
   _testingTestClassRunner.call_RunFilter_StringMatchesFilter = ZENMOCK_BIND2(StringMatchesFilter_ZenMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   TestingTestClassRunner testingTestClassRunner;
   POINTER_WAS_NEWED(testingTestClassRunner.pro_twoArgMemberAnyer);
   STD_FUNCTION_TARGETS(RunFilter::StringMatchesFilter, testingTestClassRunner.call_RunFilter_StringMatchesFilter);
}

TEST(TestNameCaseInsensitiveMatchesRunFilterTestName_ReturnsResultFromCallingRunFilterMatchesFilter)
{
   const bool stringMatchesFilterReturnValue = ZenUnit::Random<bool>();
   StringMatchesFilter_ZenMock.Return(stringMatchesFilterReturnValue);
   const RunFilter runFilter(ZenUnit::Random<string>(), ZenUnit::Random<string>(), ZenUnit::Random<unsigned>());
   const string testName = ZenUnit::Random<string>();
   //
   bool testNameCaseInsensitiveMatchesRunFilterTestName =
      _testingTestClassRunner.TestNameCaseInsensitiveMatchesRunFilterTestName(runFilter, testName.c_str());
   //
   ZEN(StringMatchesFilter_ZenMock.CalledOnceWith(testName.c_str(), runFilter.testName));
   ARE_EQUAL(stringMatchesFilterReturnValue, testNameCaseInsensitiveMatchesRunFilterTestName);
}

TEST3X3(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero,
   bool expectedIsLessThan, const char* leftTestClassName, const char* rightTestClassName,
   false, "", "",
   false, "b", "a",
   true, "a", "b",
   true, "WidgetATests", "WidgetBTests",
   false, "WidgetATests", "WidgetATests",
   false, "WidgetBTests", "WidgetATests",
   true, "widgetATests", "WidgetBTests",
   true, "assert_trueTests", "VectorTests",
   false, "is_quoted_when_printedTests", "ConsoleColorerTests")
{
   TestClassRunnerMock* leftTestClassRunnerMock = new TestClassRunnerMock;
   TestClassRunnerMock* rightTestClassRunnerMock = new TestClassRunnerMock;
   leftTestClassRunnerMock->TestClassNameMock.Return(leftTestClassName);
   rightTestClassRunnerMock->TestClassNameMock.Return(rightTestClassName);
   const unique_ptr<TestClassRunner> leftTestClassRunner(leftTestClassRunnerMock);
   const unique_ptr<TestClassRunner> rightTestClassRunner(rightTestClassRunnerMock);
   //
   const bool isLessThan = leftTestClassRunner < rightTestClassRunner;
   //
   ZEN(leftTestClassRunnerMock->TestClassNameMock.CalledOnce());
   ZEN(rightTestClassRunnerMock->TestClassNameMock.CalledOnce());
   ARE_EQUAL(expectedIsLessThan, isLessThan);
}

RUN_TESTS(TestClassRunnerTests)


TESTS(TestRunnerTests)
AFACT(Constructor_NewsComponents)
AFACT(AddTestClassRunner_EmplacesBackTestClassRunner)
AFACT(SkipTest_CallsTestRunResultAddSkippedFullTestName)
AFACT(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
FACTS(ParseArgsRunTestClassesPrintResults_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1)
AFACT(WaitForAnyKeyIfPauseMode_PauseModeFalse_DoesNothing_ReturnsFalse)
AFACT(WaitForAnyKeyIfPauseMode_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
AFACT(WaitForAnyKeyIfPauseMode_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
FACTS(RunTestClassesAndPrintResults_RunsTestsAndPrintsResults_UsingBackgroundThreadIfMaxTotalSecondsGT0_Returns0IfAllTestsPassedOtherwiseReturns1)
AFACT(RunTestClasses_RunsTestClasses)
//FACTS(RunTestClassesWithWaitableRunnerThread_SpawnsThreadToCallRunTestClasses_PrintsResultsAndExits1IfThreadTimesOut)
EVIDENCE

TestRunner _testRunner;
ConsoleMock* _consoleMock = nullptr;
PreamblePrinterMock* _preamblePrinterMock = nullptr;
ArgsParserMock* _argsParserMock = nullptr;

using NonVoidOneArgMemberFunctionCallerMockType = NonVoidOneArgMemberFunctionCallerMock<int, TestRunner, const ZenUnitArgs&>;
NonVoidOneArgMemberFunctionCallerMockType* _nonVoidOneArgMemberFunctionCallerMock;

using VoidOneArgMemberFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<TestRunner, unsigned>;
VoidOneArgMemberFunctionCallerMockType* _voidOneArgMemberFunctionCallerMock;

using NonVoidTwoArgMemberFunctionCallerMockType = NonVoidTwoArgMemberFunctionCallerMock<bool, TestRunner, bool, bool >;
NonVoidTwoArgMemberFunctionCallerMockType* _nonVoidTwoArgMemberFunctionCallerMock = nullptr;

VoidZeroArgMemberFunctionCallerMock<TestRunner>* _voidZeroArgMemberFunctionCallerMock = nullptr;

//FuturistMock<TestRunner>* _futuristMock;
TestClassRunnerRunnerMock* _testClassRunnerRunnerMock = nullptr;
TestRunResultMock* _testRunResultMock = nullptr;
StopwatchMock* _testRunStopwatchMock = nullptr;

class TestingTestClass
{
public:
   static vector<unique_ptr<Test>> GetTests(const char*)
   {
      return {};
   }
};

STARTUP
{
   _testRunner._console.reset(_consoleMock = new ConsoleMock);
   _testRunner._preamblePrinter.reset(_preamblePrinterMock = new PreamblePrinterMock);
   _testRunner._argsParser.reset(_argsParserMock = new ArgsParserMock);
   _testRunner._testRunResult.reset(_testRunResultMock = new TestRunResultMock);
   _testRunner._nonVoidOneArgMemberFunctionCaller.reset(_nonVoidOneArgMemberFunctionCallerMock = new NonVoidOneArgMemberFunctionCallerMockType);
   _testRunner._voidOneArgMemberFunctionCaller.reset(_voidOneArgMemberFunctionCallerMock = new VoidOneArgMemberFunctionCallerMockType);
   _testRunner._nonVoidTwoArgMemberFunctionCaller.reset(_nonVoidTwoArgMemberFunctionCallerMock = new NonVoidTwoArgMemberFunctionCallerMockType);
   _testRunner._voidZeroArgMemberFunctionCaller.reset(_voidZeroArgMemberFunctionCallerMock = new VoidZeroArgMemberFunctionCallerMock<TestRunner>);
   //_testRunner._futurist.reset(_futuristMock = new FuturistMock<TestRunner>);
   _testRunner._testClassRunnerRunner.reset(_testClassRunnerRunnerMock = new TestClassRunnerRunnerMock);
   _testRunner._testRunStopwatch.reset(_testRunStopwatchMock = new StopwatchMock);
}

TEST(Constructor_NewsComponents)
{
   TestRunner testRunner;
   POINTER_WAS_NEWED(testRunner._console);
   POINTER_WAS_NEWED(testRunner._preamblePrinter);
   POINTER_WAS_NEWED(testRunner._argsParser);
   POINTER_WAS_NEWED(testRunner._nonVoidOneArgMemberFunctionCaller);
   POINTER_WAS_NEWED(testRunner._voidOneArgMemberFunctionCaller);
   POINTER_WAS_NEWED(testRunner._nonVoidTwoArgMemberFunctionCaller);
   POINTER_WAS_NEWED(testRunner._voidZeroArgMemberFunctionCaller);
   //POINTER_WAS_NEWED(testRunner._futurist);
   POINTER_WAS_NEWED(testRunner._testClassRunnerRunner);
   POINTER_WAS_NEWED(testRunner._testRunResult);
   POINTER_WAS_NEWED(testRunner._testRunStopwatch);
   ARE_EQUAL(ZenUnitArgs(), testRunner._zenUnitArgs);
   IS_FALSE(testRunner._havePaused);
}

TEST(AddTestClassRunner_EmplacesBackTestClassRunner)
{
   _testClassRunnerRunnerMock->AddTestClassRunnerMock.Expect();
   SpecificTestClassRunner<TestingTestClass> testClassRunner("TestClassName");
   //
   _testRunner.AddTestClassRunner(&testClassRunner);
   //
   ZEN(_testClassRunnerRunnerMock->AddTestClassRunnerMock.CalledOnceWith(&testClassRunner));
}

TEST4X4(ParseArgsRunTestClassesPrintResults_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1,
   int expectedOverallExitCode, unsigned testrunsArgs, int firstTestRunExitCode, int secondTestRunExitCode,
   0, 1, 0, NA<int>(),
   1, 2, 1, 0,
   1, 2, 0, 1,
   1, 2, 1, 1)
{
   ZenUnitArgs parsedZenUnitArgs;
   parsedZenUnitArgs.runFilters = { Random<RunFilter>(), Random<RunFilter>() };
   parsedZenUnitArgs.wait = ZenUnit::Random<bool>();
   parsedZenUnitArgs.testruns = testrunsArgs;
   _argsParserMock->ParseMock.Return(parsedZenUnitArgs);

   _testClassRunnerRunnerMock->ApplyRunFiltersIfAnyMock.Expect();

   _nonVoidOneArgMemberFunctionCallerMock->NonConstCallMock.ReturnValues(firstTestRunExitCode, secondTestRunExitCode);

   _testRunResultMock->ResetStateExceptForSkipsMock.Expect();

   _consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.Expect();

   const vector<string> commandLineArgs{ Random<string>() };
   //
   const int overallExitCode = _testRunner.ParseArgsRunTestClassesPrintResults(commandLineArgs);
   //
   ZEN(_argsParserMock->ParseMock.CalledOnceWith(commandLineArgs));
   ZEN(_testClassRunnerRunnerMock->ApplyRunFiltersIfAnyMock.CalledOnceWith(parsedZenUnitArgs.runFilters));
   ZEN(_nonVoidOneArgMemberFunctionCallerMock->NonConstCallMock.CalledNTimesWith(
      testrunsArgs, &_testRunner, &TestRunner::RunTestClassesAndPrintResults, parsedZenUnitArgs));
   ZEN(_testRunResultMock->ResetStateExceptForSkipsMock.CalledNTimes(testrunsArgs));
   ZEN(_consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.CalledOnceWith(parsedZenUnitArgs.wait));
   ARE_EQUAL(expectedOverallExitCode, overallExitCode);
}

TEST3X3(RunTestClassesAndPrintResults_RunsTestsAndPrintsResults_UsingBackgroundThreadIfMaxTotalSecondsGT0_Returns0IfAllTestsPassedOtherwiseReturns1,
   unsigned maxtotalseconds,
   bool expectRunTestClassesWithWaitableRunnerThread,
   int determineExitCodeReturnValueAndExpectedExitCode,
   0u, false, 0,
   0u, false, 1,
   1u, true, 0,
   1u, true, 1,
   2u, true, 0,
   2u, true, 1)
{
   bool waitForAnyKeyIfPauseModeReturnValue = ZenUnit::Random<bool>();
   _nonVoidTwoArgMemberFunctionCallerMock->ConstCallMock.Return(waitForAnyKeyIfPauseModeReturnValue);
   bool havePausedInitialValue = ZenUnit::Random<bool>();
   _testRunner._havePaused = havePausedInitialValue;

   _testRunStopwatchMock->StartMock.Expect();

   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.commandLine = Random<string>();
   zenUnitArgs.maxtotalseconds = maxtotalseconds;
   _preamblePrinterMock->PrintOpeningThreeLinesMock.Expect();
   if (expectRunTestClassesWithWaitableRunnerThread)
   {
      _voidOneArgMemberFunctionCallerMock->NonConstCallMock.Expect();
   }
   else
   {
      _voidZeroArgMemberFunctionCallerMock->NonConstCallMock.Expect();
   }
   _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
   _testRunResultMock->PrintClosingLinesMock.Expect();

   const size_t TotalNumberOfTestCases = Random<size_t>();
   _testClassRunnerRunnerMock->NumberOfTestCasesMock.Return(TotalNumberOfTestCases);

   const unsigned testRunMicroseconds = _testRunStopwatchMock->StopMock.ReturnRandom();

   _testRunResultMock->DetermineExitCodeMock.Return(determineExitCodeReturnValueAndExpectedExitCode);
   //
   const int exitCode = _testRunner.RunTestClassesAndPrintResults(zenUnitArgs);
   //
   ZEN(_nonVoidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
       &_testRunner, &TestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPaused, zenUnitArgs.pause, havePausedInitialValue));
   ARE_EQUAL(waitForAnyKeyIfPauseModeReturnValue, _testRunner._havePaused);
   ZEN(_testRunStopwatchMock->StartMock.CalledOnce());
   ZEN(_preamblePrinterMock->PrintOpeningThreeLinesMock.CalledOnceWith(
       zenUnitArgs, _testRunner._testClassRunnerRunner.get()));
   if (expectRunTestClassesWithWaitableRunnerThread)
   {
      ZEN(_voidOneArgMemberFunctionCallerMock->NonConstCallMock.CalledOnceWith(
         &_testRunner, &TestRunner::RunTestClassesWithWaitableRunnerThread, zenUnitArgs.maxtotalseconds));
   }
   else
   {
      ZEN(_voidZeroArgMemberFunctionCallerMock->NonConstCallMock.CalledOnceWith(
          &_testRunner, &TestRunner::RunTestClasses));
   }
   const unsigned expectedTestRunMilliseconds = testRunMicroseconds / 1000;
   ZEN(_testRunResultMock->PrintTestFailuresAndSkipsMock.CalledOnce());
   ZEN(_testClassRunnerRunnerMock->NumberOfTestCasesMock.CalledOnce());
   ZEN(_testRunStopwatchMock->StopMock.CalledOnce());
   ZEN(_testRunResultMock->PrintClosingLinesMock.CalledOnceWith(
       TotalNumberOfTestCases, expectedTestRunMilliseconds, zenUnitArgs));
   ZEN(_testRunResultMock->DetermineExitCodeMock.CalledOnceWith(zenUnitArgs));
   ARE_EQUAL(determineExitCodeReturnValueAndExpectedExitCode, exitCode);
}

TEST(WaitForAnyKeyIfPauseMode_PauseModeFalse_DoesNothing_ReturnsFalse)
{
   bool newValueForHavePaused = _testRunner.
      WaitForAnyKeyIfPauseModeAndHaveNotPaused(false, ZenUnit::Random<bool>());
   IS_FALSE(newValueForHavePaused);
}

TEST(WaitForAnyKeyIfPauseMode_PauseModeTrue_HavePausedTrue_DoesNothing_ReturnsTrue)
{
   bool newValueForHavePaused = _testRunner.
      WaitForAnyKeyIfPauseModeAndHaveNotPaused(true, true);
   IS_TRUE(newValueForHavePaused);
}

TEST(WaitForAnyKeyIfPauseMode_PauseModeTrueHavePausedFalse_WritesMessageAndWaitsForAnyKey_ReturnsTrue)
{
   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WaitForAnyKeyMock.Expect();
   //
   bool newValueForHavePaused = _testRunner.
      WaitForAnyKeyIfPauseModeAndHaveNotPaused(true, false);
   //
   ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
      "ZenUnit test runner paused. Press any key to run tests."));
   ZEN(_consoleMock->WaitForAnyKeyMock.CalledOnce());
   IS_TRUE(newValueForHavePaused);
}

TEST(SkipTest_CallsTestRunResultAddSkippedFullTestName)
{
   _testRunResultMock->AddSkippedTestMock.Expect();
   const string TestClassName = Random<string>();
   const string TestName = Random<string>();
   const string Reason = Random<string>();
   //
   _testRunner.SkipTest(TestClassName.c_str(), TestName.c_str(), Reason.c_str());
   //
   ZEN(_testRunResultMock->AddSkippedTestMock.
      CalledOnceWith(TestClassName.c_str(), TestName.c_str(), Reason.c_str()));
}

TEST(SkipTestClass_CallsTestRunResultAddSkippedTestClassNameAndReason)
{
   _testRunResultMock->AddSkippedTestClassNameAndReasonMock.Expect();
   const string SkippedTestClassName = Random<string>();
   const string Reason = Random<string>();
   //
   _testRunner.SkipTestClass(SkippedTestClassName.c_str(), Reason.c_str());
   //
   ZEN(_testRunResultMock->AddSkippedTestClassNameAndReasonMock.
      CalledOnceWith(SkippedTestClassName.c_str(), Reason.c_str()));
}

TEST(RunTestClasses_RunsTestClasses)
{
   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.commandLine = Random<string>();
   _testRunner._zenUnitArgs = zenUnitArgs;

   vector<TestClassResult> testClassResults(1);
   _testClassRunnerRunnerMock->RunTestClassesMock.Return(testClassResults);
   _testRunResultMock->SetTestClassResultsMock.Expect();
   //
   _testRunner.RunTestClasses();
   //
   ZEN(_testClassRunnerRunnerMock->RunTestClassesMock.CalledOnceWith(_testRunner._zenUnitArgs));
   ZEN(_testRunResultMock->SetTestClassResultsMock.CalledOnceWith(testClassResults));
}

//TEST2X2(RunTestClassesWithWaitableRunnerThread_SpawnsThreadToCallRunTestClasses_PrintsResultsAndExits1IfThreadTimesOut,
//   future_status runnerThreadWaitResult, bool expectTimeoutHandling,
//   future_status::ready, false,
//   future_status::timeout, true)
//{
//   const shared_ptr<VoidFutureMock> testClassRunnerDoneFutureMock(new VoidFutureMock);
//   testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.Return(runnerThreadWaitResult);
//   _futuristMock->AsyncMock.Return(testClassRunnerDoneFutureMock);
//   if (expectTimeoutHandling)
//   {
//      _testRunResultMock->PrintTestFailuresAndSkipsMock.Expect();
//      _consoleMock->WriteLineAndExitMock.Expect();
//   }
//   const unsigned MaxTotalSeconds = Random<unsigned>();
//   //
//   _testRunner.RunTestClassesWithWaitableRunnerThread(MaxTotalSeconds);
//   //
//   ZEN(_futuristMock->AsyncMock.CalledOnceWith(&TestRunner::RunTestClasses, &_testRunner));
//   ZEN(testClassRunnerDoneFutureMock->WaitAtMostSecondsMock.CalledOnceWith(MaxTotalSeconds));
//   if (expectTimeoutHandling)
//   {
//      ZEN(_testRunResultMock->PrintTestFailuresAndSkipsMock.CalledOnce());
//      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(
//         "[ZenUnit] Total run time exceeded maximum run time of " + to_string(MaxTotalSeconds) + " seconds.", 1));
//   }
//}

RUN_TESTS(TestRunnerTests)

}

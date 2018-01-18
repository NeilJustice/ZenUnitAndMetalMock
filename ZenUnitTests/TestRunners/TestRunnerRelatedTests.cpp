#include "pch.h"
#if defined __linux__
#include <unistd.h>
#endif

#include "ZenUnitTests/Random/RandomValues.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"
#include "ZenUnitTests/Testing/RandomRunFilter.h"
#include "ZenUnitTests/Utils/Iteration/Mock/ExtraArgAnyerMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/ExtraArgMemberForEacherMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TransformerMock.h"
#include "ZenUnitTests/Utils/Mock/SorterMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"

#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/TestRunners/Mock/MultiTestClassRunnerMock.h"
#include "ZenUnitTests/Utils/Mock/MachineNameGetterMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"

#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestClassResultMock.h"
#include "ZenUnitTests/Testing/RandomPrintMode.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/ExtraArgMemberForEacherMock.h"

#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"

#include "ZenUnitTests/Args/Mock/ArgsParserMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Results/Mock/TestRunResultMock.h"
#include "ZenUnitTests/TestRunners/Mock/MultiTestClassRunnerMock.h"
#include "ZenUnitTests/TestRunners/Mock/PreamblePrinterMock.h"
#include "ZenUnitTests/Testing/RandomRunFilter.h"
//#include "ZenUnitTests/Utils/Concurrency/Mock/FuturistMock.h"
#include "ZenUnitTests/Utils/Concurrency/Mock/VoidFutureMock.h"
#include "ZenUnitTests/Utils/Time/Mock/StopwatchMock.h"

#include "ZenUnitTests/Utils/Function/Mock/VoidZeroArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidTwoArgMemberFunctionCallerMock.h"

namespace ZenUnit
{

TESTS(MachineNameGetterTests)
AFACT(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
AFACT(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
#if defined __linux__
AFACT(GetLinuxMachineName_ReturnsResultOfgethostname)
#elif _WIN32
AFACT(GetWindowsMachineName_ReturnsResultOfGetComputerName)
#endif
EVIDENCE

TEST(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
{
   MachineNameGetter machineNameGetter;
#if defined __linux__
   STD_FUNCTION_TARGETS(::gethostname, machineNameGetter.call_gethostname);
#elif _WIN32
   STD_FUNCTION_TARGETS(::GetComputerName, machineNameGetter.call_GetComputerName);
#endif
}

struct MachineNameGetterSelfMocked : public Zen::Mock<MachineNameGetter>
{
#if defined __linux__
   ZENMOCK_NONVOID0_CONST(string, GetLinuxMachineName)
#elif _WIN32
   ZENMOCK_NONVOID0_CONST(string, GetWindowsMachineName)
#endif
} _machineNameGetterSelfMocked;

MachineNameGetter _machineNameGetter;
#if defined __linux__
ZENMOCK_NONVOID2_FREE(int, gethostname, char*, size_t)
#elif _WIN32
ZENMOCK_NONVOID2_FREE(BOOL, GetComputerName, LPSTR, LPDWORD)
#endif

   STARTUP
{
#if defined __linux__
   _machineNameGetter.call_gethostname = ZENMOCK_BIND2(gethostname_ZenMock);
#elif _WIN32
   _machineNameGetter.call_GetComputerName = ZENMOCK_BIND2(GetComputerName_ZenMock);
#endif
}

#if defined __linux__
TEST(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
{
   const string machineName = ZenUnit::Random<string>();
   _machineNameGetterSelfMocked.GetLinuxMachineNameMock.Return(machineName);
   //
   const string returnedMachineName = _machineNameGetterSelfMocked.GetMachineName();
   //
   ZEN(_machineNameGetterSelfMocked.GetLinuxMachineNameMock.CalledOnce());
   ARE_EQUAL(machineName, returnedMachineName);
}

TEST(GetLinuxMachineName_ReturnsResultOfgethostname)
{
   // Implement after ZenMock gains the ability to set out-parameter return values
}
#elif _WIN32
TEST(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
{
   const string machineName = ZenUnit::Random<string>();
   _machineNameGetterSelfMocked.GetWindowsMachineNameMock.Return(machineName);
   //
   const string returnedMachineName = _machineNameGetterSelfMocked.GetMachineName();
   //
   ZEN(_machineNameGetterSelfMocked.GetWindowsMachineNameMock.CalledOnce());
   ARE_EQUAL(machineName, returnedMachineName);
}

TEST(GetWindowsMachineName_ReturnsResultOfGetComputerName)
{
   // Implement after ZenMock gains the ability to set out-parameter return values
}
#endif

}; //RUN_TESTS(MachineNameGetterTests)


TESTS(MultiTestClassRunnerTests)
AFACT(Constructor_NewsComponents)
AFACT(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
AFACT(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumber)
AFACT(ApplyRunFiltersIfAny_RunFiltersEmpty_DoesNothing)
AFACT(ApplyRunFiltersIfAny_RunFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchRunFilters)
AFACT(ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter_TestClassNameMatchesAtLeastOneRunFilter_DoesNotResetTestClassRunnerWithNoOp)
AFACT(ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter_TestClassNameDoesNotMatchAnyRunFilter_ResetsTestClassRunnerWithNoOp)
FACTS(TestClassMatchesRunFilter_ReturnsTrueIfTestClassNameCaseInsensitiveEqualsRunFilter)
AFACT(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_ReturnsTestClassResults)
FACTS(RunTestClasses_RandomMode_SetsRandomSeedIfNotSetByUser_RunsTestClassesRandomly_ReturnsTestClassResults)
AFACT(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
EVIDENCE

MultiTestClassRunner _multiTestClassRunner;

using ExtraArgMemberForEacherMockType = ExtraArgMemberForEacherMock<
   std::unique_ptr<TestClassRunner>,
   MultiTestClassRunner,
   void(MultiTestClassRunner::*)(std::unique_ptr<TestClassRunner>&, const std::vector<RunFilter>&),
   const std::vector<RunFilter>&>;
ExtraArgMemberForEacherMockType* _extraArgMemberForEacherMock = nullptr;

using ExtraArgAnyerMockType = ExtraArgAnyerMock<
   std::vector<RunFilter>,
   bool(*)(const RunFilter&, const std::unique_ptr<TestClassRunner>*),
   const std::unique_ptr<TestClassRunner>*>;
ExtraArgAnyerMockType* _extraArgAnyerMock = nullptr;

SorterMock<vector<unique_ptr<TestClassRunner>>>* _sorterMock = nullptr;
using TransformerMockType = TransformerMock<unique_ptr<TestClassRunner>, TestClassResult>;
TransformerMockType* _transformerMock = nullptr;
WatchMock* _watchMock = nullptr;

STARTUP
{
   _multiTestClassRunner._extraArgMemberForEacher.reset(_extraArgMemberForEacherMock = new ExtraArgMemberForEacherMockType);
   _multiTestClassRunner._extraArgAnyer.reset(_extraArgAnyerMock = new ExtraArgAnyerMockType);
   _multiTestClassRunner._sorter.reset(_sorterMock = new SorterMock<vector<unique_ptr<TestClassRunner>>>);
   _multiTestClassRunner._transformer.reset(_transformerMock = new TransformerMockType);
   _multiTestClassRunner._watch.reset(_watchMock = new WatchMock);
}

TEST(Constructor_NewsComponents)
{
   POINTER_WAS_NEWED(_multiTestClassRunner._extraArgMemberForEacher);
   POINTER_WAS_NEWED(_multiTestClassRunner._extraArgAnyer);
   POINTER_WAS_NEWED(_multiTestClassRunner._sorter);
   POINTER_WAS_NEWED(_multiTestClassRunner._transformer);
   POINTER_WAS_NEWED(_multiTestClassRunner._watch);
   IS_EMPTY(_multiTestClassRunner._testClassRunners);
}

TEST(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumber)
{
   ARE_EQUAL(0, _multiTestClassRunner.NumberOfTestClassesToBeRun());
   TestClassRunnerMock* testClassRunnerA = new TestClassRunnerMock;
   //
   _multiTestClassRunner.AddTestClassRunner(testClassRunnerA);
   //
   ARE_EQUAL(1, _multiTestClassRunner._testClassRunners.size());
   ARE_EQUAL(testClassRunnerA, _multiTestClassRunner._testClassRunners[0].get());
   testClassRunnerA->TestClassNameMock.Return("WidgetATests");
   ARE_EQUAL(1, _multiTestClassRunner.NumberOfTestClassesToBeRun());
   ZEN(testClassRunnerA->TestClassNameMock.CalledOnce());


   NoOpTestClassRunner* noOpTestClassRunner = new NoOpTestClassRunner;
   //
   _multiTestClassRunner.AddTestClassRunner(noOpTestClassRunner);
   //
   ARE_EQUAL(2, _multiTestClassRunner._testClassRunners.size());
   ARE_EQUAL(testClassRunnerA, _multiTestClassRunner._testClassRunners[0].get());
   ARE_EQUAL(noOpTestClassRunner, _multiTestClassRunner._testClassRunners[1].get());
   ARE_EQUAL(1, _multiTestClassRunner.NumberOfTestClassesToBeRun());


   TestClassRunnerMock* testClassRunnerB = new TestClassRunnerMock;
   //
   _multiTestClassRunner.AddTestClassRunner(testClassRunnerB);
   //
   ARE_EQUAL(3, _multiTestClassRunner._testClassRunners.size());
   ARE_EQUAL(testClassRunnerA, _multiTestClassRunner._testClassRunners[0].get());
   ARE_EQUAL(noOpTestClassRunner, _multiTestClassRunner._testClassRunners[1].get());
   ARE_EQUAL(testClassRunnerB, _multiTestClassRunner._testClassRunners[2].get());
   testClassRunnerB->TestClassNameMock.Return("WidgetBTests");
   ARE_EQUAL(2, _multiTestClassRunner.NumberOfTestClassesToBeRun());
   ZEN(testClassRunnerB->TestClassNameMock.CalledOnce());
}

TEST(ApplyRunFiltersIfAny_RunFiltersEmpty_DoesNothing)
{
   _multiTestClassRunner.ApplyRunFiltersIfAny({});
}

TEST(ApplyRunFiltersIfAny_RunFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchRunFilters)
{
   _extraArgMemberForEacherMock->ExtraArgMemberForEachMock.Expect();
   const vector<RunFilter> runFilters = { RandomRunFilter() };
   //
   _multiTestClassRunner.ApplyRunFiltersIfAny(runFilters);
   //
   ZEN(_extraArgMemberForEacherMock->ExtraArgMemberForEachMock.CalledOnceWith(
      &_multiTestClassRunner._testClassRunners,
      &_multiTestClassRunner,
      &MultiTestClassRunner::ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter,
      runFilters));
}

TEST(ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter_TestClassNameMatchesAtLeastOneRunFilter_DoesNotResetTestClassRunnerWithNoOp)
{
   _extraArgAnyerMock->ExtraArgAnyMock.Return(true);
   unique_ptr<TestClassRunner> testClassRunner{};
   const vector<RunFilter> runFilters = { RandomRunFilter() };
   //
   _multiTestClassRunner.ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter(testClassRunner, runFilters);
   //
   ZEN(_extraArgAnyerMock->ExtraArgAnyMock.CalledOnceWith(
      runFilters, MultiTestClassRunner::TestClassNameMatchesRunFilter, &testClassRunner));
   IS_TRUE(dynamic_cast<NoOpTestClassRunner*>(testClassRunner.get()) == nullptr);
}

TEST(ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter_TestClassNameDoesNotMatchAnyRunFilter_ResetsTestClassRunnerWithNoOp)
{
   _extraArgAnyerMock->ExtraArgAnyMock.Return(false);
   unique_ptr<TestClassRunner> testClassRunner{};
   const vector<RunFilter> runFilters = { RandomRunFilter() };
   //
   _multiTestClassRunner.ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter(testClassRunner, runFilters);
   //
   ZEN(_extraArgAnyerMock->ExtraArgAnyMock.CalledOnceWith(
      runFilters, MultiTestClassRunner::TestClassNameMatchesRunFilter, &testClassRunner));
   IS_TRUE(dynamic_cast<NoOpTestClassRunner*>(testClassRunner.get()) != nullptr);
}

TEST(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
{
   TestClassRunnerMock* testClassRunnerAMock = new TestClassRunnerMock;
   TestClassRunnerMock* testClassRunnerBMock = new TestClassRunnerMock;
   TestClassRunnerMock* testClassRunnerCMock = new TestClassRunnerMock;
   testClassRunnerAMock->NumberOfTestCasesMock.Return(10);
   testClassRunnerBMock->NumberOfTestCasesMock.Return(0);
   testClassRunnerCMock->NumberOfTestCasesMock.Return(20);
   _multiTestClassRunner.AddTestClassRunner(testClassRunnerAMock);
   _multiTestClassRunner.AddTestClassRunner(testClassRunnerBMock);
   _multiTestClassRunner.AddTestClassRunner(testClassRunnerCMock);
   //
   const size_t totalNumberOfTestCases = _multiTestClassRunner.NumberOfTestCases();
   //
   ZEN(testClassRunnerAMock->NumberOfTestCasesMock.CalledOnce());
   ZEN(testClassRunnerBMock->NumberOfTestCasesMock.CalledOnce());
   ZEN(testClassRunnerCMock->NumberOfTestCasesMock.CalledOnce());
   ARE_EQUAL(30, totalNumberOfTestCases);
}

TEST3X3(TestClassMatchesRunFilter_ReturnsTrueIfTestClassNameCaseInsensitiveEqualsRunFilter,
   const string& testClassNameRunFilter, const char* testClassName, bool expectedReturnValue,
   "", "", true,
   "", "WidgetTests", false,
   "WidgetTests", "WidgetTests", true,
   "widgettests", "WidgetTests", true,
   "WidgetTests", "widgettests", true,
   "Widget", "WidgetTests", false,
   "WidgetTests", "WidgetTestsABC", false,
   "WidgetTests", "ABCWidgetTests", false)
{
   TestClassRunnerMock* const testClassRunnerMock = new TestClassRunnerMock;
   testClassRunnerMock->TestClassNameMock.Return(testClassName);
   const std::unique_ptr<TestClassRunner> testClassRunner(testClassRunnerMock);

   RunFilter runFilter;
   runFilter.testClassName = testClassNameRunFilter;
   //
   const bool testClassMatchesRunFilter = MultiTestClassRunner::TestClassNameMatchesRunFilter(runFilter, &testClassRunner);
   //
   ZEN(testClassRunnerMock->TestClassNameMock.CalledOnce());
   ARE_EQUAL(expectedReturnValue, testClassMatchesRunFilter);
}

TEST(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_ReturnsTestClassResults)
{
   const size_t testClassRunnersSize = ZenUnit::Random<size_t>(0, 2);
   _multiTestClassRunner._testClassRunners.resize(testClassRunnersSize);

   ZenUnitArgs zenUnitArgs;
   IS_FALSE(zenUnitArgs.random);

   _sorterMock->SortMock.Expect();

   const vector<TestClassResult> transformReturnValue = { ZenUnit::Random<TestClassResult>() };
   _transformerMock->TransformMock.Return(transformReturnValue);
   //
   const vector<TestClassResult> testClassResults = _multiTestClassRunner.RunTestClasses(zenUnitArgs);
   //
   ZEN(_sorterMock->SortMock.CalledOnceWith(&_multiTestClassRunner._testClassRunners));

   ZEN(_transformerMock->TransformMock.CalledOnceWith(
      &_multiTestClassRunner._testClassRunners, &MultiTestClassRunner::RunTestClassRunner));

   const ZenUnitArgs expectedResultingZenUnitArgs;
   ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);

   VECTORS_EQUAL(transformReturnValue, testClassResults);
}

TEST1X1(RunTestClasses_RandomMode_SetsRandomSeedIfNotSetByUser_RunsTestClassesRandomly_ReturnsTestClassResults,
   bool randomseedsetbyuser,
   false,
   true)
{
   const size_t testClassRunnersSize = ZenUnit::Random<size_t>(0, 2);
   _multiTestClassRunner._testClassRunners.resize(testClassRunnersSize);

   const vector<TestClassResult> transformReturnValue = { ZenUnit::Random<TestClassResult>() };
   _transformerMock->RandomTransformMock.Return(transformReturnValue);

   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.random = true;
   zenUnitArgs.randomseedsetbyuser = randomseedsetbyuser;
   unsigned short therandomseedsetbyuser = 0;
   unsigned short randomseedsetbycode = 0;
   if (randomseedsetbyuser)
   {
      zenUnitArgs.randomseed = therandomseedsetbyuser = ZenUnit::Random<unsigned short>();
   }
   else
   {
      randomseedsetbycode = ZenUnit::Random<unsigned short>();
      _watchMock->SecondsSince1970CastToUnsignedShortMock.Return(randomseedsetbycode);
   }
   //
   const vector<TestClassResult> testClassResults = _multiTestClassRunner.RunTestClasses(zenUnitArgs);
   //
   if (!randomseedsetbyuser)
   {
      _watchMock->SecondsSince1970CastToUnsignedShortMock.CalledOnce();
   }

   ZEN(_transformerMock->RandomTransformMock.CalledOnceWith(
      &_multiTestClassRunner._testClassRunners, &MultiTestClassRunner::RunTestClassRunner, zenUnitArgs.randomseed));

   ZenUnitArgs expectedResultingZenUnitArgs;
   expectedResultingZenUnitArgs.random = true;
   expectedResultingZenUnitArgs.randomseedsetbyuser = randomseedsetbyuser;
   expectedResultingZenUnitArgs.randomseed = randomseedsetbyuser ? therandomseedsetbyuser : randomseedsetbycode;
   ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);

   VECTORS_EQUAL(transformReturnValue, testClassResults);
}

TEST(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
{
   TestClassRunnerMock* testClassRunnerMock = new TestClassRunnerMock;
   testClassRunnerMock->RunTestsMock.Return(TestClassResult::TestingNonDefault());
   const unique_ptr<TestClassRunner> testClassRunnerReallyAMock(testClassRunnerMock);
   //
   const TestClassResult testClassResult = MultiTestClassRunner::RunTestClassRunner(testClassRunnerReallyAMock);
   //
   ZEN(testClassRunnerMock->RunTestsMock.CalledOnce());
   ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
}

}; //RUN_TESTS(MultiTestClassRunnerTests)


TESTS(NoOpTestClassRunnerTests)
AFACT(TestClassName_ReturnsNoOpTestClassRunner)
AFACT(NumberOfTestCases_Returns0)
AFACT(RunTests_ReturnsDefaultTestClassResult)
AFACT(HasTestNameThatCaseInsensitiveMatchesPattern_ReturnsFalse)
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

TEST(HasTestNameThatCaseInsensitiveMatchesPattern_ReturnsFalse)
{
   IS_FALSE(_noOpTestClassRunner.HasTestNameThatCaseInsensitiveMatchesPattern(ZenUnit::Random<string>()));
}

}; //RUN_TESTS(NoOpTestClassRunnerTests)


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
   MultiTestClassRunnerMock multiTestClassRunnerMock;
   const size_t numberOfTestClassesToBeRun = Random<size_t>();
   multiTestClassRunnerMock.NumberOfTestClassesToBeRunMock.Return(numberOfTestClassesToBeRun);

   const string timeZoneDateTimeNow = Random<string>();
   _preamblePrinterSelfMocked.watchMock->TimeZoneDateTimeNowMock.Return(timeZoneDateTimeNow);

   const string thirdLinePrefix = Random<string>();
   _preamblePrinterSelfMocked.MakeThirdLinePrefixMock.Return(thirdLinePrefix);
   const string thirdLineSuffix = Random<string>();
   _preamblePrinterSelfMocked.MakeThirdLineSuffixMock.Return(thirdLineSuffix);

   ZenUnitArgs zenUnitArgs;
   zenUnitArgs.commandLine = Random<string>();
   zenUnitArgs.random = Random<bool>();
   zenUnitArgs.randomseed = Random<unsigned short>();
   //
   _preamblePrinterSelfMocked.PrintOpeningThreeLines(zenUnitArgs, &multiTestClassRunnerMock);
   //
   ZEN(_preamblePrinterSelfMocked.watchMock->TimeZoneDateTimeNowMock.CalledOnce());
   ZEN(multiTestClassRunnerMock.NumberOfTestClassesToBeRunMock.CalledOnce());
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
   const string MachineName = Random<string>();
   _machineNameGetterMock->GetMachineNameMock.Return(MachineName);
   //
   const string thirdLinePrefix = _preamblePrinter.MakeThirdLinePrefix(numberOfTestClasses);
   //
   ZEN(_machineNameGetterMock->GetMachineNameMock.CalledOnce());
   const string expectedReturnValue = expectedReturnValuePrefix + MachineName;
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

}; //RUN_TESTS(PreamblePrinterTests)


TESTS(SpecificTestClassRunnerTests)
AFACT(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
AFACT(TestClassName_ReturnsTestClassName)
AFACT(HasTestNameThatCaseInsensitiveMatchesPattern_ZeroTests_ReturnsFalse)
AFACT(HasTestNameThatCaseInsensitiveMatchesPattern_OneNonMatchingTest_ReturnsFalse)
FACTS(HasTestNameThatCaseInsensitiveMatchesPattern_OneMatchingTest_ReturnsTrue)
AFACT(HasTestNameThatCaseInsensitiveMatchesPattern_FourTestsWhereThirdOneMatches_DoesNotCallFourthTestName_ReturnsTrue)
AFACT(NumberOfTestCases_ReturnsSumOfNumberOfTestCases)
FACTS(RunTests_PrintsTestClassNameAndNumberOfNamedTests_CallsDoRunTests_PrintsTestClassResultLine_MoveReturnsTestClassResult)
FACTS(DoRunTests_RandomlyRunsTestsIfRandomOtherwiseSequentiallyRunsTests)
FACTS(NonMinimalPrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests)
FACTS(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewDeleteTest_AddsResultToResults_ReturnsTrueIfNewableAndDeletable)
AFACT(RunTest_NonMinimalWritesVerticalBarTestName_RunsTest_AddsTestResultsToTestClassResult_NonMinimalWriteTestOutcome)
AFACT(NonMinimalPrintResultLine_CallsTestClassResultPrintResultLine)
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

using ExtraArgMemberForEacherMockType = ExtraArgMemberForEacherMock<
   unique_ptr<Test>, SpecificTestClassRunner<TestingTestClass>,
   void (SpecificTestClassRunner<TestingTestClass>::*)(
      const unique_ptr<Test>& test, TestClassResult*) const, TestClassResult*>;
ExtraArgMemberForEacherMockType* _extraArgMemberForEacherMock;
VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>* _voidZeroArgFunctionCallerMock;
NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>* _nonVoidTwoArgFunctionCallerMock;
VoidTwoArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*, PrintMode>* _voidTwoArgFunctionCallerMock;

ZENMOCK_NONVOID0_STATIC(const ZenUnitArgs&, ZenUnit::TestRunner, GetArgs)

STARTUP
{
   _specificTestClassRunner = make_unique<SpecificTestClassRunner<TestingTestClass>>(_testClassName.c_str());
   _specificTestClassRunner->_console.reset(_consoleMock = new ConsoleMock);
   _specificTestClassRunner->call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
   _specificTestClassRunner->_extraArgMemberForEacher.reset(_extraArgMemberForEacherMock = new ExtraArgMemberForEacherMockType);
   _specificTestClassRunner->_voidZeroArgFunctionCaller.reset(
      _voidZeroArgFunctionCallerMock = new VoidZeroArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>>);
   _specificTestClassRunner->_nonVoidTwoArgFunctionCaller.reset(
      _nonVoidTwoArgFunctionCallerMock = new NonVoidTwoArgMemberFunctionCallerMock<bool, SpecificTestClassRunner<TestingTestClass>, Test*, TestClassResult*>);
   _specificTestClassRunner->_voidTwoArgFunctionCaller.reset(
      _voidTwoArgFunctionCallerMock = new VoidTwoArgMemberFunctionCallerMock<SpecificTestClassRunner<TestingTestClass>, const TestClassResult*, PrintMode>);
   _specificTestClassRunner->call_TestRunner_GetArgs = ZENMOCK_BIND0(GetArgs_ZenMock);
}

TEST(Constructor_NewsComponents_SetsTestClassName_SetsTestsVectorFromCallToTestClassTypeGetTests)
{
   SpecificTestClassRunner<TestingTestClass> specificTestClassRunner(_testClassName.c_str());
   //
   POINTER_WAS_NEWED(specificTestClassRunner._console);
   POINTER_WAS_NEWED(specificTestClassRunner._extraArgMemberForEacher);
   POINTER_WAS_NEWED(specificTestClassRunner._voidZeroArgFunctionCaller);
   POINTER_WAS_NEWED(specificTestClassRunner._nonVoidTwoArgFunctionCaller);
   POINTER_WAS_NEWED(specificTestClassRunner._voidTwoArgFunctionCaller);
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

TEST(HasTestNameThatCaseInsensitiveMatchesPattern_ZeroTests_ReturnsFalse)
{
   _specificTestClassRunner->_tests.resize(0);
   //
   const bool hasMatchingTestName
      = _specificTestClassRunner->HasTestNameThatCaseInsensitiveMatchesPattern("TestName");
   //
   IS_FALSE(hasMatchingTestName);
}

TEST(HasTestNameThatCaseInsensitiveMatchesPattern_OneNonMatchingTest_ReturnsFalse)
{
   TestMock* const testMock = new TestMock;
   testMock->NameMock.Return("TestName");
   _specificTestClassRunner->_tests.resize(0);
   _specificTestClassRunner->_tests.emplace_back(testMock);
   //
   const bool hasMatchingTestName
      = _specificTestClassRunner->HasTestNameThatCaseInsensitiveMatchesPattern("NotTestName");
   //
   ZEN(testMock->NameMock.CalledOnce());
   IS_FALSE(hasMatchingTestName);
}

TEST1X1(HasTestNameThatCaseInsensitiveMatchesPattern_OneMatchingTest_ReturnsTrue,
   const char* testNamePattern,
   "TestName",
   "testname")
{
   TestMock* const testMock = new TestMock;
   testMock->NameMock.Return("TestName");
   _specificTestClassRunner->_tests.resize(0);
   _specificTestClassRunner->_tests.emplace_back(testMock);
   //
   const bool hasMatchingTestName = _specificTestClassRunner->
      HasTestNameThatCaseInsensitiveMatchesPattern(testNamePattern);
   //
   ZEN(testMock->NameMock.CalledOnce());
   IS_TRUE(hasMatchingTestName);
}

TEST(HasTestNameThatCaseInsensitiveMatchesPattern_FourTestsWhereThirdOneMatches_DoesNotCallFourthTestName_ReturnsTrue)
{
   TestMock* const testMock1 = new TestMock;
   TestMock* const testMock2 = new TestMock;
   TestMock* const testMock3 = new TestMock;
   TestMock* const testMock4 = new TestMock;
   testMock1->NameMock.Return("Prefix_TestName");
   testMock2->NameMock.Return("TestName_Suffix");
   testMock3->NameMock.Return("TestName");
   _specificTestClassRunner->_tests.resize(0);
   _specificTestClassRunner->_tests.emplace_back(testMock1);
   _specificTestClassRunner->_tests.emplace_back(testMock2);
   _specificTestClassRunner->_tests.emplace_back(testMock3);
   _specificTestClassRunner->_tests.emplace_back(testMock4);
   const string testNamePattern = ZenUnit::Random<string>();
   //
   const bool hasMatchingTestName
      = _specificTestClassRunner->HasTestNameThatCaseInsensitiveMatchesPattern("TestName");
   //
   ZEN(testMock1->NameMock.CalledOnce());
   ZEN(testMock2->NameMock.CalledOnce());
   ZEN(testMock3->NameMock.CalledOnce());
   IS_TRUE(hasMatchingTestName);
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

TEST2X2(RunTests_PrintsTestClassNameAndNumberOfNamedTests_CallsDoRunTests_PrintsTestClassResultLine_MoveReturnsTestClassResult,
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
   _voidTwoArgFunctionCallerMock->ConstCallMock.Expect();
   _consoleMock->NonMinimalWriteNewLineMock.Expect();
   _specificTestClassRunner->_testClassResult = TestClassResult::TestingNonDefault();

   const ZenUnitArgs zenUnitArgs = []
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.printMode = RandomPrintMode();
      return zenUnitArgs;
   }();
   GetArgs_ZenMock.Return(zenUnitArgs);
   //
   const TestClassResult testClassResult = _specificTestClassRunner->RunTests();
   //
   ZEN(_voidZeroArgFunctionCallerMock->ConstCallMock.CalledOnceWith(
       _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::NonMinimalPrintTestClassNameAndNumberOfNamedTests));
   ZEN(_nonVoidTwoArgFunctionCallerMock->ConstCallMock.CalledOnceWith(
      _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests,
      &_specificTestClassRunner->_newDeleteTest, &_specificTestClassRunner->_testClassResult));
   if (expectDoRunTestsCall)
   {
      ZEN(_voidZeroArgFunctionCallerMock->NonConstCallMock.CalledOnceWith(
          _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::DoRunTests));
   }
   ZEN(GetArgs_ZenMock.CalledOnce());
   ZEN(_voidTwoArgFunctionCallerMock->ConstCallMock.CalledOnceWith(
      _specificTestClassRunner.get(), &SpecificTestClassRunner<TestingTestClass>::NonMinimalPrintResultLine,
      &_specificTestClassRunner->_testClassResult, zenUnitArgs.printMode));
   ZEN(_consoleMock->NonMinimalWriteNewLineMock.CalledOnceWith(zenUnitArgs.printMode));
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
      _extraArgMemberForEacherMock->RandomExtraArgMemberForEachMock.Expect();
   }
   else
   {
      _extraArgMemberForEacherMock->ExtraArgMemberForEachMock.Expect();
   }
   //
   _specificTestClassRunner->DoRunTests();
   //
   ZEN(GetArgs_ZenMock.CalledOnce());
   if (expectRandomForEach)
   {
      ZEN(_extraArgMemberForEacherMock->RandomExtraArgMemberForEachMock.CalledOnceWith(
         &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
         &SpecificTestClassRunner<TestingTestClass>::RunTest,
         &_specificTestClassRunner->_testClassResult,
         zenUnitArgs.randomseed));
   }
   else
   {
      ZEN(_extraArgMemberForEacherMock->ExtraArgMemberForEachMock.CalledOnceWith(
         &_specificTestClassRunner->_tests, _specificTestClassRunner.get(),
         &SpecificTestClassRunner<TestingTestClass>::RunTest,
         &_specificTestClassRunner->_testClassResult));
   }
}

TEST2X2(NonMinimalPrintTestClassNameAndNumberOfNamedTests_WritesTestClassNameVerticalBarNumberOfTests,
   size_t numberOfTests, bool expectTestsPlural,
   size_t(0), true,
   size_t(1), false,
   size_t(2), true,
   size_t(3), true)
{
   _consoleMock->NonMinimalWriteColorMock.Expect();
   _consoleMock->NonMinimalWriteLineMock.Expect();
   _specificTestClassRunner->_testClassName = _testClassName.c_str();
   _specificTestClassRunner->_tests.resize(numberOfTests);
   const ZenUnitArgs zenUnitArgs = []
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.printMode = RandomPrintMode();
      return zenUnitArgs;
   }();
   GetArgs_ZenMock.Return(zenUnitArgs);
   //
   _specificTestClassRunner->NonMinimalPrintTestClassNameAndNumberOfNamedTests();
   //
   ZEN(GetArgs_ZenMock.CalledOnce());
   ZEN(_consoleMock->NonMinimalWriteColorMock.CalledAsFollows(
      {
         { "@", Color::Green, zenUnitArgs.printMode },
      { _testClassName.c_str(), Color::Green, zenUnitArgs.printMode }
      }));
   if (expectTestsPlural)
   {
      ZEN(_consoleMock->NonMinimalWriteLineMock.CalledOnceWith(
         String::Concat(" | ", numberOfTests, " named tests"), zenUnitArgs.printMode));
   }
   else
   {
      ZEN(_consoleMock->NonMinimalWriteLineMock.CalledOnceWith(
         String::Concat(" | ", numberOfTests, " named test"), zenUnitArgs.printMode));
   }
}

TEST3X3(ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests_RunsNewDeleteTest_AddsResultToResults_ReturnsTrueIfNewableAndDeletable,
   bool expectedReturnValue, TestOutcome newDeleteTestOutcome, bool expectWriteLineOK,
   false, TestOutcome::Anomaly, false,
   false, TestOutcome::Exception, false,
   true, TestOutcome::Success, true)
{
   const ZenUnitArgs zenUnitArgs = []
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.printMode = static_cast<PrintMode>(Random<underlying_type_t<PrintMode>>(
         static_cast<underlying_type_t<PrintMode>>(PrintMode::Unset),
         static_cast<underlying_type_t<PrintMode>>(PrintMode::MaxValue)));
      return zenUnitArgs;
   }();
   GetArgs_ZenMock.Return(zenUnitArgs);

   _consoleMock->NonMinimalWriteColorMock.Expect();
   _consoleMock->NonMinimalWriteMock.Expect();
   if (expectWriteLineOK)
   {
      _consoleMock->NonMinimalWriteLineMock.Expect();
   }
   TestMock testMock;

   TestResult testResult;
   testResult.testOutcome = newDeleteTestOutcome;
   const vector<TestResult> testResults{ testResult };
   testMock.RunMock.Return(testResults);

   TestClassResultMock testClassResultMock;
   testClassResultMock.AddTestResultsMock.Expect();
   //
   const bool testClassTypeIsNewableAndDeletable = _specificTestClassRunner->
      ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(&testMock, &testClassResultMock);
   //
   ZEN(GetArgs_ZenMock.CalledOnce());
   ZEN(_consoleMock->NonMinimalWriteColorMock.CalledOnceWith("|", Color::Green, zenUnitArgs.printMode));
   ZEN(_consoleMock->NonMinimalWriteMock.CalledOnceWith("TestClassIsNewableAndDeletable -> ", zenUnitArgs.printMode));
   if (expectWriteLineOK)
   {
      ZEN(_consoleMock->NonMinimalWriteLineMock.CalledOnceWith("OK", zenUnitArgs.printMode));
   }
   ZEN(testMock.RunMock.CalledOnce());
   ZEN(testClassResultMock.AddTestResultsMock.CalledOnceWith(testResults));
   ARE_EQUAL(expectedReturnValue, testClassTypeIsNewableAndDeletable);
}

TEST(RunTest_NonMinimalWritesVerticalBarTestName_RunsTest_AddsTestResultsToTestClassResult_NonMinimalWriteTestOutcome)
{
   const ZenUnitArgs zenUnitArgs = []
   {
      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.printMode = RandomPrintMode();
      return zenUnitArgs;
   }();
   GetArgs_ZenMock.Return(zenUnitArgs);

   _consoleMock->NonMinimalWriteColorMock.Expect();
   _consoleMock->NonMinimalWriteMock.Expect();

   TestMock* const testMock = new TestMock;
   const string TestName = Random<string>();
   testMock->NameMock.Return(TestName.c_str());
   testMock->NonMinimalWritePostTestNameMessageMock.Expect();
   TestResult test0;
   test0.fullTestName = FullTestName("", "Test0", 0);
   const vector<TestResult> TestResults{ test0, TestResult() };
   testMock->RunMock.Return(TestResults);
   testMock->NonMinimalWritePostTestCompletionMessageMock.Expect();
   const unique_ptr<Test> test(testMock);

   TestClassResultMock testClassResultMock;
   testClassResultMock.AddTestResultsMock.Expect();
   //
   _specificTestClassRunner->RunTest(test, &testClassResultMock);
   //
   ZEN(GetArgs_ZenMock.CalledOnce());
   ZEN(_consoleMock->NonMinimalWriteColorMock.CalledOnceWith("|", Color::Green, zenUnitArgs.printMode));
   ZEN(_consoleMock->NonMinimalWriteMock.CalledOnceWith(TestName, zenUnitArgs.printMode));
   ZEN(testMock->NameMock.CalledOnce());
   ZEN(testMock->NonMinimalWritePostTestNameMessageMock.CalledOnceWith(
      _specificTestClassRunner->_console.get(), zenUnitArgs.printMode));
   ZEN(testMock->RunMock.CalledOnce());
   ZEN(testClassResultMock.AddTestResultsMock.CalledOnceWith(TestResults));
   ZEN(testMock->NonMinimalWritePostTestCompletionMessageMock.CalledOnceWith(
      _specificTestClassRunner->_console.get(), test0, zenUnitArgs.printMode));
}

TEST(NonMinimalPrintResultLine_CallsTestClassResultPrintResultLine)
{
   TestClassResultMock testClassResultMock;
   testClassResultMock.NonMinimalPrintResultLineMock.Expect();
   const PrintMode printMode = RandomPrintMode();
   //
   _specificTestClassRunner->NonMinimalPrintResultLine(&testClassResultMock, printMode);
   //
   ZEN(testClassResultMock.NonMinimalPrintResultLineMock.CalledOnceWith(_consoleMock, printMode));
}

}; //RUN_TESTS(SpecificTestClassRunnerTests)


TESTS(TestClassRunnerTests)
FACTS(OperatorLessThan_ReturnsTrueIfTestClassNameStrcmpResultIsLessThanZero)
EVIDENCE

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

}; //RUN_TESTS(TestClassRunnerTests)


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
MultiTestClassRunnerMock* _multiTestClassRunnerMock = nullptr;
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
   _testRunner._multiTestClassRunner.reset(_multiTestClassRunnerMock = new MultiTestClassRunnerMock);
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
   POINTER_WAS_NEWED(testRunner._multiTestClassRunner);
   POINTER_WAS_NEWED(testRunner._testRunResult);
   POINTER_WAS_NEWED(testRunner._testRunStopwatch);
   ARE_EQUAL(ZenUnitArgs(), testRunner._zenUnitArgs);
   IS_FALSE(testRunner._havePaused);
}

TEST(AddTestClassRunner_EmplacesBackTestClassRunner)
{
   _multiTestClassRunnerMock->AddTestClassRunnerMock.Expect();
   SpecificTestClassRunner<TestingTestClass> testClassRunner("TestClassName");
   //
   _testRunner.AddTestClassRunner(&testClassRunner);
   //
   ZEN(_multiTestClassRunnerMock->AddTestClassRunnerMock.CalledOnceWith(&testClassRunner));
}

TEST4X4(ParseArgsRunTestClassesPrintResults_ParsesArgs_RunsTestClassesTimesNumberOfTimes_Returns0IfAllTestRunsPassOtherwiseReturns1,
   int expectedOverallExitCode, unsigned testrunsArgs, int firstTestRunExitCode, int secondTestRunExitCode,
   0, 1, 0, NA<int>(),
   1, 2, 1, 0,
   1, 2, 0, 1,
   1, 2, 1, 1)
{
   ZenUnitArgs parsedZenUnitArgs;
   parsedZenUnitArgs.runFilters = { RandomRunFilter(), RandomRunFilter() };
   parsedZenUnitArgs.wait = ZenUnit::Random<bool>();
   parsedZenUnitArgs.testruns = testrunsArgs;
   _argsParserMock->ParseMock.Return(parsedZenUnitArgs);

   _multiTestClassRunnerMock->ApplyRunFiltersIfAnyMock.Expect();

   _nonVoidOneArgMemberFunctionCallerMock->NonConstCallMock.ReturnValues(firstTestRunExitCode, secondTestRunExitCode);

   _testRunResultMock->ResetStateExceptForSkipsMock.Expect();

   _consoleMock->WaitForAnyKeyIfDebuggerPresentOrValueTrueMock.Expect();

   const vector<string> commandLineArgs{ Random<string>() };
   //
   const int overallExitCode = _testRunner.ParseArgsRunTestClassesPrintResults(commandLineArgs);
   //
   ZEN(_argsParserMock->ParseMock.CalledOnceWith(commandLineArgs));
   ZEN(_multiTestClassRunnerMock->ApplyRunFiltersIfAnyMock.CalledOnceWith(parsedZenUnitArgs.runFilters));
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
   _multiTestClassRunnerMock->NumberOfTestCasesMock.Return(TotalNumberOfTestCases);

   const unsigned TestRunMilliseconds = Random<unsigned>();
   _testRunStopwatchMock->StopMock.Return(TestRunMilliseconds);

   _testRunResultMock->DetermineExitCodeMock.Return(determineExitCodeReturnValueAndExpectedExitCode);
   //
   const int exitCode = _testRunner.RunTestClassesAndPrintResults(zenUnitArgs);
   //
   ZEN(_nonVoidTwoArgMemberFunctionCallerMock->ConstCallMock.CalledOnceWith(
       &_testRunner, &TestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPaused, zenUnitArgs.pause, havePausedInitialValue));
   ARE_EQUAL(waitForAnyKeyIfPauseModeReturnValue, _testRunner._havePaused);
   ZEN(_testRunStopwatchMock->StartMock.CalledOnce());
   ZEN(_preamblePrinterMock->PrintOpeningThreeLinesMock.CalledOnceWith(
       zenUnitArgs, _testRunner._multiTestClassRunner.get()));
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
   ZEN(_testRunResultMock->PrintTestFailuresAndSkipsMock.CalledOnce());
   ZEN(_multiTestClassRunnerMock->NumberOfTestCasesMock.CalledOnce());
   ZEN(_testRunStopwatchMock->StopMock.CalledOnce());
   ZEN(_testRunResultMock->PrintClosingLinesMock.CalledOnceWith(
       TotalNumberOfTestCases, TestRunMilliseconds, zenUnitArgs));
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
   _multiTestClassRunnerMock->RunTestClassesMock.Return(testClassResults);
   _testRunResultMock->SetTestClassResultsMock.Expect();
   //
   _testRunner.RunTestClasses();
   //
   ZEN(_multiTestClassRunnerMock->RunTestClassesMock.CalledOnceWith(_testRunner._zenUnitArgs));
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

}; //RUN_TESTS(TestRunnerTests)

}

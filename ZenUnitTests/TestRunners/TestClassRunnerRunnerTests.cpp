#include "pch.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TwoArgMemberForEacherMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TwoArgMemberAnyerMock.h"
#include "ZenUnitTests/Utils/Mock/SorterMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TransformerMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"
#include "ZenUnitTests/Random/RandomTestClassResult.h"

namespace ZenUnit
{

TESTS(TestClassRunnerRunnerTests)
AFACT(Constructor_NewsComponents)
AFACT(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
AFACT(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumber)
AFACT(ApplyRunFiltersIfAny_RunFiltersEmpty_DoesNothing)
AFACT(ApplyRunFiltersIfAny_RunFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchRunFilters)
AFACT(ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter_TestClassNameMatchesAtLeastOneRunFilter_DoesNotResetTestClassRunnerWithNoOp)
AFACT(ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter_TestClassNameDoesNotMatchAnyRunFilter_ResetsTestClassRunnerWithNoOp)
AFACT(TestClassNameCaseInsensitiveMatchesRunFilter_ReturnsResultOfCallingStringMatchesFilter)
AFACT(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_ReturnsTestClassResults)
FACTS(RunTestClasses_RandomMode_SetsRandomSeedIfNotSetByUser_RunsTestClassesRandomly_ReturnsTestClassResults)
AFACT(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
EVIDENCE

TestClassRunnerRunner _testClassRunnerRunner;

using TwoArgMemberForEacherMockType = TwoArgMemberForEacherMock<
   std::unique_ptr<TestClassRunner>,
   TestClassRunnerRunner,
   void(TestClassRunnerRunner::*)(std::unique_ptr<TestClassRunner>&, const std::vector<RunFilter>&),
   const std::vector<RunFilter>&>;
TwoArgMemberForEacherMockType* _twoArgMemberForEacherMock = nullptr;

using TwoArgMemberAnyerMockType = TwoArgMemberAnyerMock<
   std::vector<RunFilter>,
   TestClassRunnerRunner,
   bool(TestClassRunnerRunner::*)(const RunFilter&, const TestClassRunner*) const,
   const TestClassRunner*>;
TwoArgMemberAnyerMockType* _twoArgMemberAnyerMock = nullptr;

SorterMock<vector<unique_ptr<TestClassRunner>>>* _sorterMock = nullptr;
using TransformerMockType = TransformerMock<unique_ptr<TestClassRunner>, TestClassResult>;
TransformerMockType* _transformerMock = nullptr;
WatchMock* _watchMock = nullptr;

ZENMOCK_NONVOID2_STATIC(bool, RunFilter, StringMatchesFilter, const char*, const string&)

STARTUP
{
   _testClassRunnerRunner._twoArgMemberForEacher.reset(_twoArgMemberForEacherMock = new TwoArgMemberForEacherMockType);
   _testClassRunnerRunner._twoArgMemberAnyer.reset(_twoArgMemberAnyerMock = new TwoArgMemberAnyerMockType);
   _testClassRunnerRunner._sorter.reset(_sorterMock = new SorterMock<vector<unique_ptr<TestClassRunner>>>);
   _testClassRunnerRunner._transformer.reset(_transformerMock = new TransformerMockType);
   _testClassRunnerRunner._watch.reset(_watchMock = new WatchMock);
   _testClassRunnerRunner.call_RunFilter_StringMatchesFilter = ZENMOCK_BIND2(StringMatchesFilter_ZenMock);
}

TEST(Constructor_NewsComponents)
{
   TestClassRunnerRunner testClassRunnerRunner;
   POINTER_WAS_NEWED(testClassRunnerRunner._twoArgMemberForEacher);
   POINTER_WAS_NEWED(testClassRunnerRunner._twoArgMemberAnyer);
   POINTER_WAS_NEWED(testClassRunnerRunner._sorter);
   POINTER_WAS_NEWED(testClassRunnerRunner._transformer);
   POINTER_WAS_NEWED(testClassRunnerRunner._watch);
   IS_EMPTY(testClassRunnerRunner._testClassRunners);
   STD_FUNCTION_TARGETS(RunFilter::StringMatchesFilter, testClassRunnerRunner.call_RunFilter_StringMatchesFilter);
}

TEST(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumber)
{
   ARE_EQUAL(0, _testClassRunnerRunner.NumberOfTestClassesToBeRun());
   TestClassRunnerMock* testClassRunnerA = new TestClassRunnerMock;
   //
   _testClassRunnerRunner.AddTestClassRunner(testClassRunnerA);
   //
   ARE_EQUAL(1, _testClassRunnerRunner._testClassRunners.size());
   ARE_EQUAL(testClassRunnerA, _testClassRunnerRunner._testClassRunners[0].get());
   testClassRunnerA->TestClassNameMock.Return("WidgetATests");
   ARE_EQUAL(1, _testClassRunnerRunner.NumberOfTestClassesToBeRun());
   ZEN(testClassRunnerA->TestClassNameMock.CalledOnce());


   NoOpTestClassRunner* noOpTestClassRunner = new NoOpTestClassRunner;
   //
   _testClassRunnerRunner.AddTestClassRunner(noOpTestClassRunner);
   //
   ARE_EQUAL(2, _testClassRunnerRunner._testClassRunners.size());
   ARE_EQUAL(testClassRunnerA, _testClassRunnerRunner._testClassRunners[0].get());
   ARE_EQUAL(noOpTestClassRunner, _testClassRunnerRunner._testClassRunners[1].get());
   ARE_EQUAL(1, _testClassRunnerRunner.NumberOfTestClassesToBeRun());


   TestClassRunnerMock* testClassRunnerB = new TestClassRunnerMock;
   //
   _testClassRunnerRunner.AddTestClassRunner(testClassRunnerB);
   //
   ARE_EQUAL(3, _testClassRunnerRunner._testClassRunners.size());
   ARE_EQUAL(testClassRunnerA, _testClassRunnerRunner._testClassRunners[0].get());
   ARE_EQUAL(noOpTestClassRunner, _testClassRunnerRunner._testClassRunners[1].get());
   ARE_EQUAL(testClassRunnerB, _testClassRunnerRunner._testClassRunners[2].get());
   testClassRunnerB->TestClassNameMock.Return("WidgetBTests");
   ARE_EQUAL(2, _testClassRunnerRunner.NumberOfTestClassesToBeRun());
   ZEN(testClassRunnerB->TestClassNameMock.CalledOnce());
}

TEST(ApplyRunFiltersIfAny_RunFiltersEmpty_DoesNothing)
{
   _testClassRunnerRunner.ApplyRunFiltersIfAny({});
}

TEST(ApplyRunFiltersIfAny_RunFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchRunFilters)
{
   _twoArgMemberForEacherMock->TwoArgMemberForEachMock.Expect();
   const vector<RunFilter> runFilters = { Random<RunFilter>() };
   //
   _testClassRunnerRunner.ApplyRunFiltersIfAny(runFilters);
   //
   ZEN(_twoArgMemberForEacherMock->TwoArgMemberForEachMock.CalledOnceWith(
      &_testClassRunnerRunner._testClassRunners,
      &_testClassRunnerRunner,
      &TestClassRunnerRunner::ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter,
      runFilters));
}

TEST(ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter_TestClassNameMatchesAtLeastOneRunFilter_DoesNotResetTestClassRunnerWithNoOp)
{
   _twoArgMemberAnyerMock->TwoArgAnyMock.Return(true);
   unique_ptr<TestClassRunner> testClassRunner{};
   const vector<RunFilter> runFilters = { Random<RunFilter>() };
   //
   _testClassRunnerRunner.ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter(testClassRunner, runFilters);
   //
   ZEN(_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
      runFilters, &_testClassRunnerRunner, &TestClassRunnerRunner::TestClassNameCaseInsensitiveMatchesRunFilter, testClassRunner.get()));
   IS_TRUE(dynamic_cast<NoOpTestClassRunner*>(testClassRunner.get()) == nullptr);
}

TEST(ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter_TestClassNameDoesNotMatchAnyRunFilter_ResetsTestClassRunnerWithNoOp)
{
   _twoArgMemberAnyerMock->TwoArgAnyMock.Return(false);
   unique_ptr<TestClassRunner> testClassRunner{};
   const TestClassRunner* const testClassRunnerAddressBeforeBeingOverwrittenWithNoOpTestRunner = testClassRunner.get();
   const vector<RunFilter> runFilters = { Random<RunFilter>() };
   //
   _testClassRunnerRunner.ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter(testClassRunner, runFilters);
   //
   ZEN(_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
      runFilters, &_testClassRunnerRunner, &TestClassRunnerRunner::TestClassNameCaseInsensitiveMatchesRunFilter,
      testClassRunnerAddressBeforeBeingOverwrittenWithNoOpTestRunner));
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
   _testClassRunnerRunner.AddTestClassRunner(testClassRunnerAMock);
   _testClassRunnerRunner.AddTestClassRunner(testClassRunnerBMock);
   _testClassRunnerRunner.AddTestClassRunner(testClassRunnerCMock);
   //
   const size_t totalNumberOfTestCases = _testClassRunnerRunner.NumberOfTestCases();
   //
   ZEN(testClassRunnerAMock->NumberOfTestCasesMock.CalledOnce());
   ZEN(testClassRunnerBMock->NumberOfTestCasesMock.CalledOnce());
   ZEN(testClassRunnerCMock->NumberOfTestCasesMock.CalledOnce());
   ARE_EQUAL(30, totalNumberOfTestCases);
}

TEST(TestClassNameCaseInsensitiveMatchesRunFilter_ReturnsResultOfCallingStringMatchesFilter)
{
   const bool stringMatchesFilterReturnValue = StringMatchesFilter_ZenMock.ReturnRandom();

   TestClassRunnerMock* const testClassRunnerMock = new TestClassRunnerMock;
   const string testClassName = ZenUnit::Random<string>();
   testClassRunnerMock->TestClassNameMock.Return(testClassName.c_str());
   const std::unique_ptr<TestClassRunner> testClassRunner(testClassRunnerMock);

   RunFilter runFilter;
   runFilter.testClassName = ZenUnit::Random<string>();
   //
   const bool testClassMatchesRunFilter =
      _testClassRunnerRunner.TestClassNameCaseInsensitiveMatchesRunFilter(runFilter, testClassRunner.get());
   //
   ZEN(testClassRunnerMock->TestClassNameMock.CalledOnce());
   ZEN(StringMatchesFilter_ZenMock.CalledOnceWith(testClassName.c_str(), runFilter.testClassName));
   ARE_EQUAL(stringMatchesFilterReturnValue, testClassMatchesRunFilter);
}

TEST(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_ReturnsTestClassResults)
{
   const size_t testClassRunnersSize = ZenUnit::Random<size_t>(0, 2);
   _testClassRunnerRunner._testClassRunners.resize(testClassRunnersSize);

   ZenUnitArgs zenUnitArgs;
   IS_FALSE(zenUnitArgs.random);

   _sorterMock->SortMock.Expect();

   const vector<TestClassResult> transformReturnValue = { ZenUnit::Random<TestClassResult>() };
   _transformerMock->TransformMock.Return(transformReturnValue);
   //
   const vector<TestClassResult> testClassResults = _testClassRunnerRunner.RunTestClasses(zenUnitArgs);
   //
   ZEN(_sorterMock->SortMock.CalledOnceWith(&_testClassRunnerRunner._testClassRunners));

   ZEN(_transformerMock->TransformMock.CalledOnceWith(
      &_testClassRunnerRunner._testClassRunners, &TestClassRunnerRunner::RunTestClassRunner));

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
   _testClassRunnerRunner._testClassRunners.resize(testClassRunnersSize);

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
      randomseedsetbycode = _watchMock->SecondsSince1970CastToUnsignedShortMock.ReturnRandom();
   }
   //
   const vector<TestClassResult> testClassResults = _testClassRunnerRunner.RunTestClasses(zenUnitArgs);
   //
   if (!randomseedsetbyuser)
   {
      _watchMock->SecondsSince1970CastToUnsignedShortMock.CalledOnce();
   }

   ZEN(_transformerMock->RandomTransformMock.CalledOnceWith(
      &_testClassRunnerRunner._testClassRunners, &TestClassRunnerRunner::RunTestClassRunner, zenUnitArgs.randomseed));

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
   const TestClassResult testClassResult = TestClassRunnerRunner::RunTestClassRunner(testClassRunnerReallyAMock);
   //
   ZEN(testClassRunnerMock->RunTestsMock.CalledOnce());
   ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
}

}; RUN_TESTS(TestClassRunnerRunnerTests)

}
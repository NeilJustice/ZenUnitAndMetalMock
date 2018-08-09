#include "pch.h"
#include "ZenUnitFrameworkTests/Args/Mock/RunFilterMock.h"
#include "ZenUnitFrameworkTests/Random/RandomRunFilter.h"
#include "ZenUnitFrameworkTests/Random/RandomTestClassResult.h"
#include "ZenUnitFrameworkTests/TestRunners/Mock/TestClassRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Iteration/Mock/TransformerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Iteration/Mock/TwoArgMemberAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Iteration/Mock/TwoArgMemberForEacherMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Mock/SorterMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Time/Mock/WatchMock.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"

namespace ZenUnit
{
   TESTS(TestClassRunnerRunnerTests)
   AFACT(Constructor_NewsComponents)
   AFACT(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   AFACT(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumber)
   AFACT(ApplyRunFiltersIfAny_RunFiltersEmpty_DoesNothing)
   AFACT(ApplyRunFiltersIfAny_RunFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchRunFilters)
   AFACT(ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter_TestClassNameMatchesAtLeastOneRunFilter_DoesNotResetTestClassRunnerWithNoOp)
   AFACT(ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter_TestClassNameDoesNotMatchAnyRunFilter_ResetsTestClassRunnerWithNoOp)
   AFACT(RunFilterMatchesTestClass_RunFilterDoesNotMatchTestClassName_ReturnsFalse)
   AFACT(RunFilterMatchesTestClass_RunFilterMatchesTestClassName_ReturnsTrueIfTestClassHasTestThatMatchesRunFilter)
   AFACT(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_ReturnsTestClassResults)
   AFACT(RunTestClasses_RandomMode_RunsTestClassesRandomly_ReturnsTestClassResults)
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

   STARTUP
   {
      _testClassRunnerRunner._twoArgMemberForEacher.reset(_twoArgMemberForEacherMock = new TwoArgMemberForEacherMockType);
      _testClassRunnerRunner._twoArgMemberAnyer.reset(_twoArgMemberAnyerMock = new TwoArgMemberAnyerMockType);
      _testClassRunnerRunner._sorter.reset(_sorterMock = new SorterMock<vector<unique_ptr<TestClassRunner>>>);
      _testClassRunnerRunner._transformer.reset(_transformerMock = new TransformerMockType);
      _testClassRunnerRunner._watch.reset(_watchMock = new WatchMock);
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
         &TestClassRunnerRunner::ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter,
         runFilters));
   }

   TEST(ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter_TestClassNameMatchesAtLeastOneRunFilter_DoesNotResetTestClassRunnerWithNoOp)
   {
      _twoArgMemberAnyerMock->TwoArgAnyMock.Return(true);
      unique_ptr<TestClassRunner> testClassRunner{};
      const vector<RunFilter> runFilters = { Random<RunFilter>() };
      //
      _testClassRunnerRunner.ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter(testClassRunner, runFilters);
      //
      ZEN(_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         runFilters, &_testClassRunnerRunner, &TestClassRunnerRunner::RunFilterMatchesTestClass, testClassRunner.get()));
      IS_TRUE(dynamic_cast<NoOpTestClassRunner*>(testClassRunner.get()) == nullptr);
   }

   TEST(ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter_TestClassNameDoesNotMatchAnyRunFilter_ResetsTestClassRunnerWithNoOp)
   {
      _twoArgMemberAnyerMock->TwoArgAnyMock.Return(false);
      unique_ptr<TestClassRunner> testClassRunner{};
      const TestClassRunner* const testClassRunnerAddressBeforeBeingOverwrittenWithNoOpTestRunner = testClassRunner.get();
      const vector<RunFilter> runFilters = { Random<RunFilter>() };
      //
      _testClassRunnerRunner.ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter(testClassRunner, runFilters);
      //
      ZEN(_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         runFilters, &_testClassRunnerRunner, &TestClassRunnerRunner::RunFilterMatchesTestClass,
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

   TEST(RunFilterMatchesTestClass_RunFilterDoesNotMatchTestClassName_ReturnsFalse)
   {
      RunFilterMock runFilterMock;
      runFilterMock.MatchesTestClassNameMock.Return(false);

      TestClassRunnerMock* const testClassRunnerMock = new TestClassRunnerMock;
      const string testClassName = ZenUnit::Random<string>();
      testClassRunnerMock->TestClassNameMock.Return(testClassName.c_str());
      const std::unique_ptr<TestClassRunner> testClassRunner(testClassRunnerMock);
      //
      const bool runFilterMatchesTestClass = _testClassRunnerRunner.
         RunFilterMatchesTestClass(runFilterMock, testClassRunner.get());
      //
      ZEN(testClassRunnerMock->TestClassNameMock.CalledOnce());
      ZEN(runFilterMock.MatchesTestClassNameMock.CalledOnceWith(testClassName.c_str()));
      IS_FALSE(runFilterMatchesTestClass);
   }

   TEST(RunFilterMatchesTestClass_RunFilterMatchesTestClassName_ReturnsTrueIfTestClassHasTestThatMatchesRunFilter)
   {
      RunFilterMock runFilterMock;
      runFilterMock.testCaseNumber = ZenUnit::Random<size_t>(); // To make runFilterMock different from RunFilterMock()
      runFilterMock.MatchesTestClassNameMock.Return(true);

      TestClassRunnerMock* const testClassRunnerMock = new TestClassRunnerMock;
      const string testClassName = ZenUnit::Random<string>();
      testClassRunnerMock->TestClassNameMock.Return(testClassName.c_str());
      const bool hasTestThatMatchesRunFilter = testClassRunnerMock->HasTestThatMatchesRunFilterMock.ReturnRandom();
      const std::unique_ptr<TestClassRunner> testClassRunner(testClassRunnerMock);
      //
      const bool runFilterMatchesTestClass = _testClassRunnerRunner.RunFilterMatchesTestClass(runFilterMock, testClassRunner.get());
      //
      ZEN(testClassRunnerMock->TestClassNameMock.CalledOnce());
      ZEN(testClassRunnerMock->HasTestThatMatchesRunFilterMock.CalledOnceWith(runFilterMock));
      ZEN(runFilterMock.MatchesTestClassNameMock.CalledOnceWith(testClassName.c_str()));
      ARE_EQUAL(hasTestThatMatchesRunFilter, runFilterMatchesTestClass);
   }

   TEST(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_ReturnsTestClassResults)
   {
      _testClassRunnerRunner._testClassRunners.resize(ZenUnit::RandomBetween<size_t>(0, 2));

      ZenUnitArgs zenUnitArgs;
      IS_FALSE(zenUnitArgs.random);

      _sorterMock->SortMock.Expect();

      const vector<TestClassResult> transformReturnValue = ZenUnit::RandomVector<TestClassResult>();
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

   TEST(RunTestClasses_RandomMode_RunsTestClassesRandomly_ReturnsTestClassResults)
   {
      _testClassRunnerRunner._testClassRunners.resize(ZenUnit::RandomBetween<size_t>(0, 2));

      const vector<TestClassResult> transformReturnValue = ZenUnit::RandomVector<TestClassResult>();
      _transformerMock->RandomTransformMock.Return(transformReturnValue);

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.random = true;
      zenUnitArgs.randomseedsetbyuser = ZenUnit::Random<bool>();
      zenUnitArgs.randomseed = ZenUnit::Random<unsigned short>();
      //
      const vector<TestClassResult> testClassResults = _testClassRunnerRunner.RunTestClasses(zenUnitArgs);
      //
      ZEN(_transformerMock->RandomTransformMock.CalledOnceWith(
         &_testClassRunnerRunner._testClassRunners, &TestClassRunnerRunner::RunTestClassRunner, zenUnitArgs.randomseed));
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

   RUN_TESTS(TestClassRunnerRunnerTests)
}

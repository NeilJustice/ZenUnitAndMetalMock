#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/MetalMock/TestNameFilterMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitLibraryTests/Components/TestRunners/MetalMock/TestClassRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/TransformerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/TwoArgMemberAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/TwoArgMemberForEacherMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/MetalMock/SorterMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/WatchMock.h"

namespace ZenUnit
{
   TESTS(TestClassRunnerRunnerTests)
   AFACT(DefaultConstructor_NewsComponents)
   AFACT(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   AFACT(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumberAsMoreNonNoOpTestClassRunnersAreAdded)
   AFACT(ApplyTestNameFiltersIfAny_TestNameFiltersAreEmpty_DoesNotThrowException)
   AFACT(ApplyTestNameFiltersIfAny_TestNameFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchTestNameFilters)
   AFACT(ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter_TestClassNameMatchesAtLeastOneTestNameFilter_DoesNotResetTestClassRunnerWithNoOp)
   AFACT(ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter_TestClassNameDoesNotMatchAnyTestNameFilter_ResetsTestClassRunnerWithNoOp)
   AFACT(TestNameFilterMatchesTestClass_TestNameFilterDoesNotMatchTestClassName_ReturnsFalse)
   AFACT(ApplyTestNameFiltersIfAny_TestNameFiltersIsNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatDoNotMatchTestNameFilters)
   AFACT(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_ReturnsTestClassResults)
   AFACT(RunTestClasses_RandomMode_RunsTestClassesRandomly_ReturnsTestClassResults)
   AFACT(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
   EVIDENCE

   TestClassRunnerRunner _testClassRunnerRunner;
   // Function Callers
   TransformerMock<unique_ptr<TestClassRunner>, TestClassResult>* _transformerMock = nullptr;
   using TwoArgMemberAnyerMockType = TwoArgMemberAnyerMock<
      std::vector<TestNameFilter>,
      TestClassRunnerRunner,
      bool(TestClassRunnerRunner::*)(const TestNameFilter&, const TestClassRunner*) const,
      const TestClassRunner*>;
   TwoArgMemberAnyerMockType* _twoArgMemberAnyerMock = nullptr;
   using TwoArgMemberForEacherMockType = TwoArgMemberForEacherMock<
      std::unique_ptr<TestClassRunner>,
      TestClassRunnerRunner,
      void(TestClassRunnerRunner::*)(std::unique_ptr<TestClassRunner>&, const std::vector<TestNameFilter>&),
      const std::vector<TestNameFilter>&>;
   TwoArgMemberForEacherMockType* _twoArgMemberForEacherMock = nullptr;

   // Constant Components
   SorterMock<vector<unique_ptr<TestClassRunner>>>* _testClassRunnerSorterMock = nullptr;
   WatchMock* _watchMock = nullptr;

   STARTUP
   {
      // Function Callers
      _testClassRunnerRunner._transformer.reset(_transformerMock = new TransformerMock<unique_ptr<TestClassRunner>, TestClassResult>);
      _testClassRunnerRunner._twoArgMemberAnyer.reset(_twoArgMemberAnyerMock = new TwoArgMemberAnyerMockType);
      _testClassRunnerRunner._twoArgMemberForEacher.reset(_twoArgMemberForEacherMock = new TwoArgMemberForEacherMockType);
      // Constant Components
      _testClassRunnerRunner._testClassRunnerSorter.reset(_testClassRunnerSorterMock = new SorterMock<vector<unique_ptr<TestClassRunner>>>);
      _testClassRunnerRunner._watch.reset(_watchMock = new WatchMock);
   }

   TEST(DefaultConstructor_NewsComponents)
   {
      TestClassRunnerRunner testClassRunnerRunner;
      // Function Callers
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._transformer);
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._twoArgMemberAnyer);
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._twoArgMemberForEacher);
      // Constant Components
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._testClassRunnerSorter);
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._watch);
      // Mutable Fields
      IS_EMPTY(testClassRunnerRunner._testClassRunners);
   }

   TEST(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   {
      unique_ptr<TestClassRunnerMock> testClassRunner1Mock = make_unique<TestClassRunnerMock>();
      unique_ptr<TestClassRunnerMock> testClassRunner2Mock = make_unique<TestClassRunnerMock>();
      unique_ptr<TestClassRunnerMock> testClassRunner3Mock = make_unique<TestClassRunnerMock>();
      const size_t numberOfTestCases1 = ZenUnit::RandomBetween<size_t>(0, 10);
      const size_t numberOfTestCases2 = ZenUnit::RandomBetween<size_t>(0, 10);
      const size_t numberOfTestCases3 = ZenUnit::RandomBetween<size_t>(0, 10);
      testClassRunner1Mock->NumberOfTestCasesMock.Return(numberOfTestCases1);
      testClassRunner2Mock->NumberOfTestCasesMock.Return(numberOfTestCases2);
      testClassRunner3Mock->NumberOfTestCasesMock.Return(numberOfTestCases3);
      _testClassRunnerRunner._testClassRunners.emplace_back(std::move(testClassRunner1Mock));
      _testClassRunnerRunner._testClassRunners.emplace_back(std::move(testClassRunner2Mock));
      _testClassRunnerRunner._testClassRunners.emplace_back(std::move(testClassRunner3Mock));
      //
      const size_t totalNumberOfTestCases = _testClassRunnerRunner.NumberOfTestCases();
      //
      const TestClassRunnerMock* const testClassRunner1MockAfter = static_cast<const TestClassRunnerMock*>(_testClassRunnerRunner._testClassRunners[0].get());
      const TestClassRunnerMock* const testClassRunner2MockAfter = static_cast<const TestClassRunnerMock*>(_testClassRunnerRunner._testClassRunners[1].get());
      const TestClassRunnerMock* const testClassRunner3MockAfter = static_cast<const TestClassRunnerMock*>(_testClassRunnerRunner._testClassRunners[2].get());
      METALMOCK(testClassRunner1MockAfter->NumberOfTestCasesMock.CalledOnce());
      METALMOCK(testClassRunner2MockAfter->NumberOfTestCasesMock.CalledOnce());
      METALMOCK(testClassRunner3MockAfter->NumberOfTestCasesMock.CalledOnce());
      const size_t expectedTotalNumberOfTestCases = numberOfTestCases1 + numberOfTestCases2 + numberOfTestCases3;
      ARE_EQUAL(expectedTotalNumberOfTestCases, totalNumberOfTestCases);
   }

   TEST(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumberAsMoreNonNoOpTestClassRunnersAreAdded)
   {
      class TestingTestClassRunner : public TestClassRunner
      {
      public:
         const char* TestClassName() const override
         {
            return "TestingTestClassRunner";
         }
      };

      IS_ZERO(_testClassRunnerRunner.NumberOfTestClassesToBeRun());
      unique_ptr<TestClassRunner> testingTestClassRunner1 = make_unique<TestingTestClassRunner>();
      //
      _testClassRunnerRunner.AddTestClassRunner(std::move(testingTestClassRunner1));
      //
      ARE_EQUAL(1, _testClassRunnerRunner._testClassRunners.size());
      ARE_EQUAL(1, _testClassRunnerRunner.NumberOfTestClassesToBeRun());


      unique_ptr<TestClassRunner> noOpTestClassRunner = make_unique<NoOpTestClassRunner>();
      //
      _testClassRunnerRunner.AddTestClassRunner(std::move(noOpTestClassRunner));
      //
      ARE_EQUAL(2, _testClassRunnerRunner._testClassRunners.size());
      ARE_EQUAL(1, _testClassRunnerRunner.NumberOfTestClassesToBeRun());


      unique_ptr<TestClassRunner> testingTestClassRunner2 = make_unique<TestingTestClassRunner>();
      //
      _testClassRunnerRunner.AddTestClassRunner(std::move(testingTestClassRunner2));
      //
      ARE_EQUAL(3, _testClassRunnerRunner._testClassRunners.size());
      ARE_EQUAL(2, _testClassRunnerRunner.NumberOfTestClassesToBeRun());
   }

   TEST(ApplyTestNameFiltersIfAny_TestNameFiltersAreEmpty_DoesNotThrowException)
   {
      _testClassRunnerRunner.ApplyTestNameFiltersIfAny({});
   }

   TEST(ApplyTestNameFiltersIfAny_TestNameFiltersIsNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatDoNotMatchTestNameFilters)
   {
      _twoArgMemberForEacherMock->TwoArgMemberForEachMock.Expect();
      const vector<TestNameFilter> testNameFilters = { Random<TestNameFilter>() };
      //
      _testClassRunnerRunner.ApplyTestNameFiltersIfAny(testNameFilters);
      //
      METALMOCK(_twoArgMemberForEacherMock->TwoArgMemberForEachMock.CalledOnceWith(
         &_testClassRunnerRunner._testClassRunners,
         &_testClassRunnerRunner,
         &TestClassRunnerRunner::ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter,
         testNameFilters));
   }

   TEST(ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter_TestClassNameMatchesAtLeastOneTestNameFilter_DoesNotResetTestClassRunnerWithNoOp)
   {
      _twoArgMemberAnyerMock->TwoArgAnyMock.Return(true);
      unique_ptr<TestClassRunner> testClassRunner{};
      const vector<TestNameFilter> testNameFilters = { Random<TestNameFilter>() };
      //
      _testClassRunnerRunner.ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter(testClassRunner, testNameFilters);
      //
      METALMOCK(_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         testNameFilters, &_testClassRunnerRunner, &TestClassRunnerRunner::TestNameFilterMatchesTestClass, testClassRunner.get()));
      IS_TRUE(dynamic_cast<NoOpTestClassRunner*>(testClassRunner.get()) == nullptr);
   }

   TEST(ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter_TestClassNameDoesNotMatchAnyTestNameFilter_ResetsTestClassRunnerWithNoOp)
   {
      _twoArgMemberAnyerMock->TwoArgAnyMock.Return(false);
      unique_ptr<TestClassRunner> testClassRunner{};
      const TestClassRunner* const testClassRunnerAddressBeforeBeingOverwrittenWithNoOpTestRunner = testClassRunner.get();
      const vector<TestNameFilter> testNameFilters = { Random<TestNameFilter>() };
      //
      _testClassRunnerRunner.ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter(testClassRunner, testNameFilters);
      //
      METALMOCK(_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         testNameFilters, &_testClassRunnerRunner, &TestClassRunnerRunner::TestNameFilterMatchesTestClass,
         testClassRunnerAddressBeforeBeingOverwrittenWithNoOpTestRunner));
      IS_TRUE(dynamic_cast<NoOpTestClassRunner*>(testClassRunner.get()) != nullptr);
   }

   TEST(TestNameFilterMatchesTestClass_TestNameFilterDoesNotMatchTestClassName_ReturnsFalse)
   {
      TestNameFilterMock testNameFilterMock;
      testNameFilterMock.MatchesTestClassNameMock.Return(false);

      TestClassRunnerMock* const testClassRunnerMock = new TestClassRunnerMock;
      const string testClassName = ZenUnit::Random<string>();
      testClassRunnerMock->TestClassNameMock.Return(testClassName.c_str());
      const std::unique_ptr<TestClassRunner> testClassRunner(testClassRunnerMock);
      //
      const bool testNameFilterMatchesTestClass =
         _testClassRunnerRunner.TestNameFilterMatchesTestClass(testNameFilterMock, testClassRunner.get());
      //
      METALMOCK(testClassRunnerMock->TestClassNameMock.CalledOnce());
      METALMOCK(testNameFilterMock.MatchesTestClassNameMock.CalledOnceWith(testClassName.c_str()));
      IS_FALSE(testNameFilterMatchesTestClass);
   }

   TEST(ApplyTestNameFiltersIfAny_TestNameFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchTestNameFilters)
   {
      TestNameFilterMock testNameFilterMock;
      testNameFilterMock.testCaseNumber = ZenUnit::Random<size_t>();
      testNameFilterMock.MatchesTestClassNameMock.Return(true);

      TestClassRunnerMock* const testClassRunnerMock = new TestClassRunnerMock;
      const string testClassName = ZenUnit::Random<string>();
      testClassRunnerMock->TestClassNameMock.Return(testClassName.c_str());
      const bool hasTestThatMatchesTestNameFilter = testClassRunnerMock->HasTestThatMatchesTestNameFilterMock.ReturnRandom();
      const std::unique_ptr<TestClassRunner> testClassRunner(testClassRunnerMock);
      //
      const bool testNameFilterMatchesTestClass =
         _testClassRunnerRunner.TestNameFilterMatchesTestClass(testNameFilterMock, testClassRunner.get());
      //
      METALMOCK(testClassRunnerMock->TestClassNameMock.CalledOnce());
      METALMOCK(testClassRunnerMock->HasTestThatMatchesTestNameFilterMock.CalledOnceWith(testNameFilterMock));
      METALMOCK(testNameFilterMock.MatchesTestClassNameMock.CalledOnceWith(testClassName.c_str()));
      ARE_EQUAL(hasTestThatMatchesTestNameFilter, testNameFilterMatchesTestClass);
   }

   TEST(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_ReturnsTestClassResults)
   {
      _testClassRunnerRunner._testClassRunners.resize(ZenUnit::RandomBetween<size_t>(0, 2));

      ZenUnitArgs zenUnitArgs;
      IS_FALSE(zenUnitArgs.randomTestOrdering);

      _testClassRunnerSorterMock->SortMock.Expect();

      const vector<TestClassResult> transformReturnValue = ZenUnit::RandomVector<TestClassResult>();
      _transformerMock->TransformMock.Return(transformReturnValue);
      //
      const vector<TestClassResult> testClassResults = _testClassRunnerRunner.RunTestClasses(zenUnitArgs);
      //
      METALMOCK(_testClassRunnerSorterMock->SortMock.CalledOnceWith(&_testClassRunnerRunner._testClassRunners));

      METALMOCK(_transformerMock->TransformMock.CalledOnceWith(
         &_testClassRunnerRunner._testClassRunners, &TestClassRunnerRunner::RunTestClassRunner));

      const ZenUnitArgs expectedResultingZenUnitArgs;
      ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);

      VECTORS_ARE_EQUAL(transformReturnValue, testClassResults);
   }

   TEST(RunTestClasses_RandomMode_RunsTestClassesRandomly_ReturnsTestClassResults)
   {
      _testClassRunnerRunner._testClassRunners.resize(ZenUnit::RandomBetween<size_t>(0, 2));

      const vector<TestClassResult> transformReturnValue = ZenUnit::RandomVector<TestClassResult>();
      _transformerMock->RandomTransformMock.Return(transformReturnValue);

      ZenUnitArgs zenUnitArgs;
      zenUnitArgs.randomTestOrdering = true;

      const unsigned globalZenUnitModeRandomSeed = ZenUnit::Random<unsigned>();
      globalZenUnitMode.randomSeed = globalZenUnitModeRandomSeed;
      //
      const vector<TestClassResult> testClassResults = _testClassRunnerRunner.RunTestClasses(zenUnitArgs);
      //
      METALMOCK(_transformerMock->RandomTransformMock.CalledOnceWith(
         &_testClassRunnerRunner._testClassRunners, &TestClassRunnerRunner::RunTestClassRunner, globalZenUnitModeRandomSeed));
      VECTORS_ARE_EQUAL(transformReturnValue, testClassResults);
   }

   TEST(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
   {
      TestClassRunnerMock* testClassRunnerMock = new TestClassRunnerMock;
      testClassRunnerMock->RunTestsMock.Return(TestingNonDefaultTestClassResult());
      const unique_ptr<TestClassRunner> testClassRunnerReallyAMock(testClassRunnerMock);
      //
      const TestClassResult testClassResult = TestClassRunnerRunner::RunTestClassRunner(testClassRunnerReallyAMock);
      //
      METALMOCK(testClassRunnerMock->RunTestsMock.CalledOnce());
      ARE_EQUAL(TestingNonDefaultTestClassResult(), testClassResult);
   }

   RUN_TESTS(TestClassRunnerRunnerTests)
}

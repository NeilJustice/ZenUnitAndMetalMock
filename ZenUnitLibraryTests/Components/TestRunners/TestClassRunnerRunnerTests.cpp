#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/ZenMock/RunFilterMock.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomRunFilter.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestClassResult.h"
#include "ZenUnitLibraryTests/Components/TestRunners/ZenMock/TestClassRunnerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/ZenMock/TransformerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/ZenMock/TwoArgMemberAnyerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/ZenMock/TwoArgMemberForEacherMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/ZenMock/SorterMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/ZenMock/WatchMock.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"

namespace ZenUnit
{
   TESTS(TestClassRunnerRunnerTests)
   AFACT(Constructor_NewsComponents)
   AFACT(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   AFACT(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumberAsMoreNonNoOpTestClassRunnersAreAdded)
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
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._twoArgMemberForEacher);
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._twoArgMemberAnyer);
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._sorter);
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._transformer);
      DELETE_TO_ASSERT_NEWED(testClassRunnerRunner._watch);
      IS_EMPTY(testClassRunnerRunner._testClassRunners);
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

      ARE_EQUAL(0, _testClassRunnerRunner.NumberOfTestClassesToBeRun());
      unique_ptr<TestClassRunner> testingTestClassRunner1 = make_unique<TestingTestClassRunner>();
      const TestClassRunner* const testingTestClassRunner1Pointer = testingTestClassRunner1.get();
      //
      _testClassRunnerRunner.AddTestClassRunner(std::move(testingTestClassRunner1));
      //
      ARE_EQUAL(1, _testClassRunnerRunner._testClassRunners.size());
      ARE_EQUAL(testingTestClassRunner1Pointer, _testClassRunnerRunner._testClassRunners[0].get());
      ARE_EQUAL(1, _testClassRunnerRunner.NumberOfTestClassesToBeRun());


      unique_ptr<NoOpTestClassRunner> noOpTestClassRunner = make_unique<NoOpTestClassRunner>();
      const NoOpTestClassRunner* const noOpTestClassRunnerPointer = noOpTestClassRunner.get();
      //
      _testClassRunnerRunner.AddTestClassRunner(std::move(noOpTestClassRunner));
      //
      ARE_EQUAL(2, _testClassRunnerRunner._testClassRunners.size());
      ARE_EQUAL(testingTestClassRunner1Pointer, _testClassRunnerRunner._testClassRunners[0].get());
      ARE_EQUAL(noOpTestClassRunnerPointer, _testClassRunnerRunner._testClassRunners[1].get());
      ARE_EQUAL(1, _testClassRunnerRunner.NumberOfTestClassesToBeRun());


      unique_ptr<TestClassRunner> testingTestClassRunner2 = make_unique<TestingTestClassRunner>();
      const TestClassRunner* const testingTestClassRunner2Pointer = testingTestClassRunner2.get();
      //
      _testClassRunnerRunner.AddTestClassRunner(std::move(testingTestClassRunner2));
      //
      ARE_EQUAL(3, _testClassRunnerRunner._testClassRunners.size());
      ARE_EQUAL(testingTestClassRunner1Pointer, _testClassRunnerRunner._testClassRunners[0].get());
      ARE_EQUAL(noOpTestClassRunnerPointer, _testClassRunnerRunner._testClassRunners[1].get());
      ARE_EQUAL(testingTestClassRunner2Pointer, _testClassRunnerRunner._testClassRunners[2].get());
      ARE_EQUAL(2, _testClassRunnerRunner.NumberOfTestClassesToBeRun());
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
      ZENMOCK(_twoArgMemberForEacherMock->TwoArgMemberForEachMock.CalledOnceWith(
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
      ZENMOCK(_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
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
      ZENMOCK(_twoArgMemberAnyerMock->TwoArgAnyMock.CalledOnceWith(
         runFilters, &_testClassRunnerRunner, &TestClassRunnerRunner::RunFilterMatchesTestClass,
         testClassRunnerAddressBeforeBeingOverwrittenWithNoOpTestRunner));
      IS_TRUE(dynamic_cast<NoOpTestClassRunner*>(testClassRunner.get()) != nullptr);
   }

   TEST(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   {
      unique_ptr<TestClassRunnerMock> testClassRunner1Mock = make_unique<TestClassRunnerMock>();
      TestClassRunnerMock* testClassRunner1MockPointer = testClassRunner1Mock.get();

      unique_ptr<TestClassRunnerMock> testClassRunner2Mock = make_unique<TestClassRunnerMock>();
      TestClassRunnerMock* testClassRunner2MockPointer = testClassRunner2Mock.get();

      unique_ptr<TestClassRunnerMock> testClassRunner3Mock = make_unique<TestClassRunnerMock>();
      TestClassRunnerMock* testClassRunner3MockPointer = testClassRunner3Mock.get();

      const int numberOfTestCases1 = ZenUnit::RandomBetween<int>(0, 10);
      const int numberOfTestCases2 = ZenUnit::RandomBetween<int>(0, 10);
      const int numberOfTestCases3 = ZenUnit::RandomBetween<int>(0, 10);
      testClassRunner1Mock->NumberOfTestCasesMock.Return(numberOfTestCases1);
      testClassRunner2Mock->NumberOfTestCasesMock.Return(numberOfTestCases2);
      testClassRunner3Mock->NumberOfTestCasesMock.Return(numberOfTestCases3);
      _testClassRunnerRunner.AddTestClassRunner(std::move(testClassRunner1Mock));
      _testClassRunnerRunner.AddTestClassRunner(std::move(testClassRunner2Mock));
      _testClassRunnerRunner.AddTestClassRunner(std::move(testClassRunner3Mock));
      //
      const size_t totalNumberOfTestCases = _testClassRunnerRunner.NumberOfTestCases();
      //
      ZENMOCK(testClassRunner1MockPointer->NumberOfTestCasesMock.CalledOnce());
      ZENMOCK(testClassRunner2MockPointer->NumberOfTestCasesMock.CalledOnce());
      ZENMOCK(testClassRunner3MockPointer->NumberOfTestCasesMock.CalledOnce());
      const int expectedTotalNumberOfTestCases = numberOfTestCases1 + numberOfTestCases2 + numberOfTestCases3;
      ARE_EQUAL(expectedTotalNumberOfTestCases, totalNumberOfTestCases);
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
      ZENMOCK(testClassRunnerMock->TestClassNameMock.CalledOnce());
      ZENMOCK(runFilterMock.MatchesTestClassNameMock.CalledOnceWith(testClassName.c_str()));
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
      ZENMOCK(testClassRunnerMock->TestClassNameMock.CalledOnce());
      ZENMOCK(testClassRunnerMock->HasTestThatMatchesRunFilterMock.CalledOnceWith(runFilterMock));
      ZENMOCK(runFilterMock.MatchesTestClassNameMock.CalledOnceWith(testClassName.c_str()));
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
      ZENMOCK(_sorterMock->SortMock.CalledOnceWith(&_testClassRunnerRunner._testClassRunners));

      ZENMOCK(_transformerMock->TransformMock.CalledOnceWith(
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
      zenUnitArgs.randomSeedSetByUser = ZenUnit::Random<bool>();
      zenUnitArgs.randomSeed = ZenUnit::Random<unsigned>();
      //
      const vector<TestClassResult> testClassResults = _testClassRunnerRunner.RunTestClasses(zenUnitArgs);
      //
      ZENMOCK(_transformerMock->RandomTransformMock.CalledOnceWith(
         &_testClassRunnerRunner._testClassRunners, &TestClassRunnerRunner::RunTestClassRunner, zenUnitArgs.randomSeed));
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
      ZENMOCK(testClassRunnerMock->RunTestsMock.CalledOnce());
      ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
   }

   RUN_TESTS(TestClassRunnerRunnerTests)
}

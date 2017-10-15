#include "pch.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "ZenUnitTests/TestRunners/Mock/TestClassRunnerMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/ExtraArgForEacherMock.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TransformerMock.h"
#include "ZenUnitTests/Utils/Mock/SorterMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"

namespace ZenUnit
{
   TESTS(MultiTestClassRunnerTests)
   AFACT(Constructor_NewsComponents)
   AFACT(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   AFACT(AddTestClassRunner_EmplacesBackTestClassRunner_MakesNumberOfTestClassesToBeRunReturnAnIncreasingNumber)
   AFACT(ApplyRunFiltersIfSpecified_RunFiltersEmpty_DoesNothing)
   AFACT(ApplyRunFiltersIfSpecified_RunFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchRunFilters)
   AFACT(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_MoveReturnsTestClassResultsVector)
   FACTS(RunTestClasses_RandomMode_SetsRandomSeedIfNotSetByUser_RunsTestClassesRandomly_MoveReturnsTestClassResultsVector)
   AFACT(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
   EVIDENCE

   MultiTestClassRunner _multiTestClassRunner;

   using ExtraArgForEacherMockType = ExtraArgForEacherMock<
      std::vector<std::unique_ptr<TestClassRunner>>,
      bool(*)(std::unique_ptr<TestClassRunner>&, const std::vector<std::string>&),
      const std::vector<std::string>&>;
   ExtraArgForEacherMockType* _extraArgForEacherMock;

   SorterMock<vector<unique_ptr<TestClassRunner>>>* _sorterMock;
   using TransformerMockType = TransformerMock<unique_ptr<TestClassRunner>, TestClassResult>;
   TransformerMockType* _transformerMock;
   WatchMock* _watchMock;

   STARTUP
   {
      _multiTestClassRunner._extraArgForEacher.reset(_extraArgForEacherMock = new ExtraArgForEacherMockType);
      _multiTestClassRunner._sorter.reset(_sorterMock = new SorterMock<vector<unique_ptr<TestClassRunner>>>);
      _multiTestClassRunner._transformer.reset(_transformerMock = new TransformerMockType);
      _multiTestClassRunner._watch.reset(_watchMock = new WatchMock);
   }

   TEST(Constructor_NewsComponents)
   {
      POINTER_WAS_NEWED(_multiTestClassRunner._extraArgForEacher);
      POINTER_WAS_NEWED(_multiTestClassRunner._sorter);
      POINTER_WAS_NEWED(_multiTestClassRunner._transformer);
      POINTER_WAS_NEWED(_multiTestClassRunner._watch);
      IS_EMPTY(_multiTestClassRunner._testClassRunners);
      IS_EMPTY(_multiTestClassRunner._testClassResults);
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
      ARE_EQUAL(1, _multiTestClassRunner.NumberOfTestClassesToBeRun());

      TestClassRunnerMock* testClassRunnerB = new TestClassRunnerMock;
      //
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerB);
      //
      ARE_EQUAL(2, _multiTestClassRunner._testClassRunners.size());
      ARE_EQUAL(testClassRunnerA, _multiTestClassRunner._testClassRunners[0].get());
      ARE_EQUAL(testClassRunnerB, _multiTestClassRunner._testClassRunners[1].get());
      ARE_EQUAL(2, _multiTestClassRunner.NumberOfTestClassesToBeRun());
   }

   TEST(ApplyRunFiltersIfSpecified_RunFiltersEmpty_DoesNothing)
   {
      _multiTestClassRunner.ApplyRunFiltersIfSpecified({});
   }

   TEST(ApplyRunFiltersIfSpecified_RunFiltersNotEmpty_ResetsWithNoOpTestClassesThoseTestClassesThatMatchRunFilters)
   {
      _extraArgForEacherMock->NonConstExtraArgForEachMock.Expect();
      const vector<string> runFilters = { ZenUnit::Random<string>() };
      //
      _multiTestClassRunner.ApplyRunFiltersIfSpecified(runFilters);
      //
      ZEN(_extraArgForEacherMock->NonConstExtraArgForEachMock.AssertCalledOnceWith(
         &_multiTestClassRunner._testClassRunners,
         MultiTestClassRunner::ResetWithNoOpIfNameDoesNotMatchRunFilter, runFilters));
   }

   TEST(NumberOfTestCases_ReturnsSumOfAllTestClassNumberOfTests)
   {
      TestClassRunnerMock* testClassRunnerAMock = new TestClassRunnerMock;
      TestClassRunnerMock* testClassRunnerBMock = new TestClassRunnerMock;
      TestClassRunnerMock* testClassRunnerCMock = new TestClassRunnerMock;
      testClassRunnerAMock->NumberOfTestCasesMock.ExpectAndReturn(10);
      testClassRunnerBMock->NumberOfTestCasesMock.ExpectAndReturn(0);
      testClassRunnerCMock->NumberOfTestCasesMock.ExpectAndReturn(20);
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerAMock);
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerBMock);
      _multiTestClassRunner.AddTestClassRunner(testClassRunnerCMock);
      //
      const size_t totalNumberOfTestCases = _multiTestClassRunner.NumberOfTestCases();
      //
      ZEN(testClassRunnerAMock->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testClassRunnerBMock->NumberOfTestCasesMock.AssertCalledOnce());
      ZEN(testClassRunnerCMock->NumberOfTestCasesMock.AssertCalledOnce());
      ARE_EQUAL(30, totalNumberOfTestCases);
   }

   TEST(RunTestClasses_NonRandomMode_SortsTestClassRunnersByName_RunsTestClassesSequentially_MoveReturnsTestClassResultsVector)
   {
      ARE_EQUAL(0, _multiTestClassRunner._testClassResults.size());
      const size_t testClassRunnersSize = ZenUnit::Random<size_t>(1, 3);
      _multiTestClassRunner._testClassRunners.resize(testClassRunnersSize);

      ZenUnitArgs zenUnitArgs;
      IS_FALSE(zenUnitArgs.random);

      _sorterMock->SortMock.Expect();
      _transformerMock->TransformMock.Expect();
      //
      const vector<TestClassResult> testClassResults = _multiTestClassRunner.RunTestClasses(zenUnitArgs);
      //
      ZEN(_sorterMock->SortMock.AssertCalledOnceWith(&_multiTestClassRunner._testClassRunners));
      ZEN(_transformerMock->TransformMock.AssertCalledOnceWith(
         &_multiTestClassRunner._testClassRunners,
         &_multiTestClassRunner._testClassResults,
         &MultiTestClassRunner::RunTestClassRunner));
      const vector<TestClassResult> expectedTestClassResults(testClassRunnersSize);
      VECTORS_EQUAL(expectedTestClassResults, testClassResults);
      ARE_EQUAL(0, _multiTestClassRunner._testClassResults.size());

      ZenUnitArgs expectedResultingZenUnitArgs;
      ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);
   }

   TEST2X2(RunTestClasses_RandomMode_SetsRandomSeedIfNotSetByUser_RunsTestClassesRandomly_MoveReturnsTestClassResultsVector,
      bool randomseedsetbyuser, bool expectRandomSeedSet,
      false, false,
      true, true)
   {
      ARE_EQUAL(0, _multiTestClassRunner._testClassResults.size());
      const size_t testClassRunnersSize = ZenUnit::Random<size_t>(1, 3);
      _multiTestClassRunner._testClassRunners.resize(testClassRunnersSize);

      _transformerMock->RandomTransformMock.Expect();

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
         _watchMock->SecondsSince1970CastToUnsignedShortMock.ExpectAndReturn(randomseedsetbycode);
      }
      //
      const vector<TestClassResult> testClassResults = _multiTestClassRunner.RunTestClasses(zenUnitArgs);
      //
      if (!randomseedsetbyuser)
      {
         _watchMock->SecondsSince1970CastToUnsignedShortMock.AssertCalledOnce();
      }

      ZEN(_transformerMock->RandomTransformMock.AssertCalledOnceWith(
         &_multiTestClassRunner._testClassRunners,
         &_multiTestClassRunner._testClassResults,
         &MultiTestClassRunner::RunTestClassRunner,
         zenUnitArgs.randomseed));

      const vector<TestClassResult> expectedTestClassResults(testClassRunnersSize);
      VECTORS_EQUAL(expectedTestClassResults, testClassResults);
      ARE_EQUAL(0, _multiTestClassRunner._testClassResults.size());

      ZenUnitArgs expectedResultingZenUnitArgs;
      expectedResultingZenUnitArgs.random = true;
      expectedResultingZenUnitArgs.randomseedsetbyuser = randomseedsetbyuser;
      expectedResultingZenUnitArgs.randomseed = randomseedsetbyuser ? therandomseedsetbyuser : randomseedsetbycode;
      ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);
   }

   TEST(RunTestClassRunner_ReturnsCallToTestClassRunnerRunTests)
   {
      TestClassRunnerMock* testClassRunnerMock = new TestClassRunnerMock;
      testClassRunnerMock->RunTestsMock.ExpectAndReturn(TestClassResult::TestingNonDefault());
      const unique_ptr<TestClassRunner> testClassRunnerReallyAMock(testClassRunnerMock);
      //
      const TestClassResult testClassResult = MultiTestClassRunner::RunTestClassRunner(testClassRunnerReallyAMock);
      //
      ZEN(testClassRunnerMock->RunTestsMock.AssertCalledOnce());
      ARE_EQUAL(TestClassResult::TestingNonDefault(), testClassResult);
   }

   }; RUNTESTS(MultiTestClassRunnerTests)
}

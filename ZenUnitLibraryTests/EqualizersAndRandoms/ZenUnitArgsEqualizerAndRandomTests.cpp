#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitTestUtils/MetalMock/ZenUnitTestingRandomGeneratorMock.h"

namespace ZenUnit
{
   TESTS(ZenUnitArgsEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomZenUnitArgs_ReturnsZenUnitArgsWithAllRandomFields)
   AFACT(RandomZenUnitArgs_CodeCoverage)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(ZenUnitArgs);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, commandLine, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, testNameFilters, ZenUnit::RandomNonEmptyVector<TestNameFilter>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, pauseBefore, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, pauseAfter, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, alwaysExit0, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, failFast, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, exit1IfTestsSkipped, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, testRuns, ZenUnit::RandomNon0<int>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, randomTestOrdering, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, globalRandomSeedSetByUser, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, maxTestMilliseconds, ZenUnit::RandomNon0<unsigned>());
   }

   TEST(TestableRandomZenUnitArgs_ReturnsZenUnitArgsWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;

      const string startDateTime = ZenUnit::Random<string>();
      const string commandLine = ZenUnit::Random<string>();
      randomGeneratorMock.StringMock.ReturnValues(startDateTime, commandLine);

      ZenUnitTestingRandomGeneratorMock zenUnitTestingRandomGeneratorMock;
      const vector<TestNameFilter> testNameFilters = zenUnitTestingRandomGeneratorMock.RandomTestNameFiltersVectorMock.ReturnRandom();

      const bool pauseBefore = ZenUnit::Random<bool>();
      const bool pauseAfter = ZenUnit::Random<bool>();
      const bool alwaysExit0 = ZenUnit::Random<bool>();
      const bool failFast = ZenUnit::Random<bool>();
      const bool exit1IfTestsSkipped = ZenUnit::Random<bool>();
      const bool randomTestOrdering = ZenUnit::Random<bool>();
      const bool globalRandomSeedSetByUser = ZenUnit::Random<bool>();
      randomGeneratorMock.BoolMock.ReturnValues(
         pauseBefore, pauseAfter, alwaysExit0, failFast, exit1IfTestsSkipped, randomTestOrdering, globalRandomSeedSetByUser);

      const int testRuns = randomGeneratorMock.IntMock.ReturnRandom();

      const unsigned maxTestMilliseconds = randomGeneratorMock.UnsignedIntMock.ReturnRandom();
      //
      const ZenUnitArgs randomZenUnitArgs = TestableRandomZenUnitArgs(&randomGeneratorMock, &zenUnitTestingRandomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.StringMock.CalledNTimes(2));
      METALMOCK(randomGeneratorMock.BoolMock.CalledNTimes(7));
      METALMOCK(randomGeneratorMock.IntMock.CalledOnce());
      METALMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      METALMOCK(zenUnitTestingRandomGeneratorMock.RandomTestNameFiltersVectorMock.CalledOnce());
      ZenUnitArgs expectedRandomZenUnitArgs;
      expectedRandomZenUnitArgs.startDateTime = startDateTime;
      expectedRandomZenUnitArgs.commandLine = commandLine;
      expectedRandomZenUnitArgs.testNameFilters = testNameFilters;
      expectedRandomZenUnitArgs.pauseBefore = pauseBefore;
      expectedRandomZenUnitArgs.pauseAfter = pauseAfter;
      expectedRandomZenUnitArgs.alwaysExit0 = alwaysExit0;
      expectedRandomZenUnitArgs.failFast = failFast;
      expectedRandomZenUnitArgs.exit1IfTestsSkipped = exit1IfTestsSkipped;
      expectedRandomZenUnitArgs.testRuns = testRuns;
      expectedRandomZenUnitArgs.randomTestOrdering = randomTestOrdering;
      expectedRandomZenUnitArgs.globalRandomSeedSetByUser = globalRandomSeedSetByUser;
      expectedRandomZenUnitArgs.maxTestMilliseconds = maxTestMilliseconds;
      ARE_EQUAL(expectedRandomZenUnitArgs, randomZenUnitArgs);
   }

   TEST(RandomZenUnitArgs_CodeCoverage)
   {
      ZenUnit::Random<ZenUnitArgs>();
   }

   RUN_TESTS(ZenUnitArgsEqualizerAndRandomTests)
}

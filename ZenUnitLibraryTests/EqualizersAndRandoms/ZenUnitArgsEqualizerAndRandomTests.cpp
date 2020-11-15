#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(ZenUnitArgsEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomZenUnitArgs_ReturnsZenUnitArgsWithAllRandomFields)
   AFACT(RandomZenUnitArgs_DoesNotThrowException)
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
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, randomSeed, ZenUnit::RandomNon0<unsigned>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, randomSeedSetByUser, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, maxTestMilliseconds, ZenUnit::RandomNon0<unsigned>());
   }

   TEST(TestableRandomZenUnitArgs_ReturnsZenUnitArgsWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;

      const string startDateTime = ZenUnit::Random<string>();
      const string commandLine = ZenUnit::Random<string>();
      randomGeneratorMock.StringMock.ReturnValues(startDateTime, commandLine);

      const bool pauseBefore = ZenUnit::Random<bool>();
      const bool pauseAfter = ZenUnit::Random<bool>();
      const bool alwaysExit0 = ZenUnit::Random<bool>();
      const bool failFast = ZenUnit::Random<bool>();
      const bool exit1IfTestsSkipped = ZenUnit::Random<bool>();
      const bool randomTestOrdering = ZenUnit::Random<bool>();
      const bool randomSeedSetByUser = ZenUnit::Random<bool>();
      randomGeneratorMock.BoolMock.ReturnValues(
         pauseBefore, pauseAfter, alwaysExit0, failFast, exit1IfTestsSkipped, randomTestOrdering, randomSeedSetByUser);

      const int testRuns = randomGeneratorMock.IntMock.ReturnRandom();

      const unsigned randomSeed = ZenUnit::Random<unsigned>();
      const unsigned maxTestMilliseconds = ZenUnit::Random<unsigned>();
      randomGeneratorMock.UnsignedIntMock.ReturnValues(randomSeed, maxTestMilliseconds);
      //
      const ZenUnitArgs randomZenUnitArgs = TestableRandomZenUnitArgs(&randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.StringMock.CalledNTimes(2));
      METALMOCK(randomGeneratorMock.BoolMock.CalledNTimes(7));
      METALMOCK(randomGeneratorMock.IntMock.CalledOnce());
      METALMOCK(randomGeneratorMock.UnsignedIntMock.CalledNTimes(2));

      ARE_EQUAL(startDateTime, randomZenUnitArgs.startDateTime);
      ARE_EQUAL(commandLine, randomZenUnitArgs.commandLine);

      IS_NOT_EMPTY(randomZenUnitArgs.testNameFilters);
      for (size_t i = 0; i < randomZenUnitArgs.testNameFilters.size(); ++i)
      {
         IS_NOT_DEFAULT_VALUE(randomZenUnitArgs.testNameFilters[i]);
      }

      ARE_EQUAL(pauseBefore, randomZenUnitArgs.pauseBefore);
      ARE_EQUAL(pauseAfter, randomZenUnitArgs.pauseAfter);
      ARE_EQUAL(alwaysExit0, randomZenUnitArgs.alwaysExit0);
      ARE_EQUAL(failFast, randomZenUnitArgs.failFast);
      ARE_EQUAL(exit1IfTestsSkipped, randomZenUnitArgs.exit1IfTestsSkipped);
      ARE_EQUAL(testRuns, randomZenUnitArgs.testRuns);
      ARE_EQUAL(randomTestOrdering, randomZenUnitArgs.randomTestOrdering);
      ARE_EQUAL(randomSeed, randomZenUnitArgs.randomSeed);
      ARE_EQUAL(randomSeedSetByUser, randomZenUnitArgs.randomSeedSetByUser);
      ARE_EQUAL(maxTestMilliseconds, randomZenUnitArgs.maxTestMilliseconds);
   }

   TEST(RandomZenUnitArgs_DoesNotThrowException)
   {
      const ZenUnitArgs randomZenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
   }

   RUN_TESTS(ZenUnitArgsEqualizerAndRandomTests)
}

#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"

namespace ZenUnit
{
   TESTS(RandomZenUnitArgsTests)
   AFACT(RandomZenUnitArgs_CodeCoverage)
   AFACT(TestableRandomZenUnitArgs_ReturnsZenUnitArgsWithAllRandomFields)
   EVIDENCE

   TEST(RandomZenUnitArgs_CodeCoverage)
   {
      const ZenUnitArgs randomZenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
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
      const ZenUnitArgs randomZenUnitArgs = TestableRandomZenUnitArgs(randomGeneratorMock);
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

   RUN_TESTS(RandomZenUnitArgsTests)
}

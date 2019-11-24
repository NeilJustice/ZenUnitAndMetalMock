#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"

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
      ZenMock::RandomGeneratorMock randomGeneratorMock;

      const string startDateTime = ZenUnit::Random<string>();
      const string commandLine = ZenUnit::Random<string>();
      randomGeneratorMock.StringMock.ReturnValues(startDateTime, commandLine);

      const vector<RunFilter> runFilters = ZenUnit::RandomVector<RunFilter>();
      //randomGeneratorMock.VectorMock.Return(runFilters);

      const bool pause = ZenUnit::Random<bool>();
      const bool wait = ZenUnit::Random<bool>();
      const bool exitZero = ZenUnit::Random<bool>();
      const bool failFast = ZenUnit::Random<bool>();
      const bool noSkips = ZenUnit::Random<bool>();
      const bool random = ZenUnit::Random<bool>();
      const bool randomSeedSetByUser = ZenUnit::Random<bool>();
      randomGeneratorMock.BoolMock.ReturnValues(
         pause, wait, exitZero, failFast, noSkips, random, randomSeedSetByUser);

      const int testRuns = randomGeneratorMock.IntMock.ReturnRandom();

      const unsigned randomSeed = ZenUnit::Random<unsigned>();
      const unsigned maxTestMilliseconds = ZenUnit::Random<unsigned>();
      randomGeneratorMock.UnsignedIntMock.ReturnValues(randomSeed, maxTestMilliseconds);
      //
      const ZenUnitArgs randomZenUnitArgs = TestableRandomZenUnitArgs(randomGeneratorMock);
      //
      ZENMOCK(randomGeneratorMock.StringMock.CalledNTimes(2));
      ZENMOCK(randomGeneratorMock.BoolMock.CalledNTimes(7));
      ZENMOCK(randomGeneratorMock.IntMock.CalledOnce());
      ZENMOCK(randomGeneratorMock.UnsignedIntMock.CalledNTimes(2));

      ARE_EQUAL(startDateTime, randomZenUnitArgs.startDateTime);
      ARE_EQUAL(commandLine, randomZenUnitArgs.commandLine);

      IS_NOT_EMPTY(randomZenUnitArgs.runFilters);
      for (size_t i = 0; i < randomZenUnitArgs.runFilters.size(); ++i)
      {
         IS_NOT_DEFAULT_VALUE(randomZenUnitArgs.runFilters[i]);
      }

      ARE_EQUAL(pause, randomZenUnitArgs.pause);
      ARE_EQUAL(wait, randomZenUnitArgs.wait);
      ARE_EQUAL(exitZero, randomZenUnitArgs.exitZero);
      ARE_EQUAL(failFast, randomZenUnitArgs.failFast);
      ARE_EQUAL(noSkips, randomZenUnitArgs.noSkips);
      ARE_EQUAL(testRuns, randomZenUnitArgs.testRuns);
      ARE_EQUAL(random, randomZenUnitArgs.random);
      ARE_EQUAL(randomSeed, randomZenUnitArgs.randomSeed);
      ARE_EQUAL(randomSeedSetByUser, randomZenUnitArgs.randomSeedSetByUser);
      ARE_EQUAL(maxTestMilliseconds, randomZenUnitArgs.maxTestMilliseconds);
   }

   RUN_TESTS(RandomZenUnitArgsTests)
}

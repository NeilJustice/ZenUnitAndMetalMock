#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"
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

      const unsigned testRuns = ZenUnit::Random<unsigned>();
      const unsigned randomSeed = ZenUnit::Random<unsigned>();
      const unsigned maxTestMilliseconds = ZenUnit::Random<unsigned>();
      randomGeneratorMock.UnsignedIntMock.ReturnValues(testRuns, randomSeed, maxTestMilliseconds);
      //
      const ZenUnitArgs randomZenUnitArgs = TestableRandomZenUnitArgs(randomGeneratorMock);
      //
      ZENMOCK(randomGeneratorMock.StringMock.CalledNTimes(2));
      ZENMOCK(randomGeneratorMock.BoolMock.CalledNTimes(7));
      ZENMOCK(randomGeneratorMock.UnsignedIntMock.CalledNTimes(3));
      ZenUnitArgs expectedRandomZenUnitArgs;
      expectedRandomZenUnitArgs.startDateTime = startDateTime;
      expectedRandomZenUnitArgs.commandLine = commandLine;
      expectedRandomZenUnitArgs.runFilters = runFilters;
      expectedRandomZenUnitArgs.pause = pause;
      expectedRandomZenUnitArgs.wait = wait;
      expectedRandomZenUnitArgs.exitZero = exitZero;
      expectedRandomZenUnitArgs.failFast = failFast;
      expectedRandomZenUnitArgs.noSkips = noSkips;
      expectedRandomZenUnitArgs.testRuns = testRuns;
      expectedRandomZenUnitArgs.random = random;
      expectedRandomZenUnitArgs.randomSeed = randomSeed;
      expectedRandomZenUnitArgs.randomSeedSetByUser = randomSeedSetByUser;
      expectedRandomZenUnitArgs.maxTestMilliseconds = maxTestMilliseconds;
      ARE_EQUAL(expectedRandomZenUnitArgs, randomZenUnitArgs);
   }

   RUN_TESTS(RandomZenUnitArgsTests)
}

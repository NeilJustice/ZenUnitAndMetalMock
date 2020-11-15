#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<ZenUnitArgs>::AssertEqual(const ZenUnitArgs& expectedZenUnitArgs, const ZenUnitArgs& actualZenUnitArgs)
   {
      ARE_EQUAL(expectedZenUnitArgs.commandLine, actualZenUnitArgs.commandLine);
      VECTORS_ARE_EQUAL(expectedZenUnitArgs.testNameFilters, actualZenUnitArgs.testNameFilters);
      ARE_EQUAL(expectedZenUnitArgs.pauseBefore, actualZenUnitArgs.pauseBefore);
      ARE_EQUAL(expectedZenUnitArgs.pauseAfter, actualZenUnitArgs.pauseAfter);
      ARE_EQUAL(expectedZenUnitArgs.alwaysExit0, actualZenUnitArgs.alwaysExit0);
      ARE_EQUAL(expectedZenUnitArgs.failFast, actualZenUnitArgs.failFast);
      ARE_EQUAL(expectedZenUnitArgs.exit1IfTestsSkipped, actualZenUnitArgs.exit1IfTestsSkipped);
      ARE_EQUAL(expectedZenUnitArgs.testRuns, actualZenUnitArgs.testRuns);
      ARE_EQUAL(expectedZenUnitArgs.randomTestOrdering, actualZenUnitArgs.randomTestOrdering);
      ARE_EQUAL(expectedZenUnitArgs.randomSeed, actualZenUnitArgs.randomSeed);
      ARE_EQUAL(expectedZenUnitArgs.randomSeedSetByUser, actualZenUnitArgs.randomSeedSetByUser);
      ARE_EQUAL(expectedZenUnitArgs.maxTestMilliseconds, actualZenUnitArgs.maxTestMilliseconds);
   }

   ZenUnitArgs TestableRandomZenUnitArgs(const RandomGenerator* randomGenerator)
   {
      ZenUnitArgs randomZenUnitArgs;
      randomZenUnitArgs.startDateTime = randomGenerator->String();
      randomZenUnitArgs.commandLine = randomGenerator->String();
      randomZenUnitArgs.testNameFilters = ZenUnit::RandomNonEmptyVector<TestNameFilter>();
      randomZenUnitArgs.pauseBefore = randomGenerator->Bool();
      randomZenUnitArgs.pauseAfter = randomGenerator->Bool();
      randomZenUnitArgs.alwaysExit0 = randomGenerator->Bool();
      randomZenUnitArgs.failFast = randomGenerator->Bool();
      randomZenUnitArgs.exit1IfTestsSkipped = randomGenerator->Bool();
      randomZenUnitArgs.testRuns = randomGenerator->Int();
      randomZenUnitArgs.randomTestOrdering = randomGenerator->Bool();
      randomZenUnitArgs.randomSeed = randomGenerator->UnsignedInt();
      randomZenUnitArgs.randomSeedSetByUser = randomGenerator->Bool();
      randomZenUnitArgs.maxTestMilliseconds = randomGenerator->UnsignedInt();
      return randomZenUnitArgs;
   }

   template<>
   ZenUnitArgs Random<ZenUnitArgs>()
   {
      return TestableRandomZenUnitArgs(RandomGenerator::Instance());
   }
}

#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitTestUtils/ZenUnitTestingRandomGenerator.h"

namespace ZenUnit
{
   void Equalizer<ZenUnitArgs>::AssertEqual(const ZenUnitArgs& expectedZenUnitArgs, const ZenUnitArgs& actualZenUnitArgs)
   {
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, commandLine);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, testNameFilters);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, pauseBefore);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, pauseAfter);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, alwaysExit0);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, failFast);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, exit1IfTestsSkipped);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, testRuns);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, randomTestOrdering);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, globalRandomSeedSetByUser);
      FIELDS_ARE_EQUAL(expectedZenUnitArgs, actualZenUnitArgs, maxTestMilliseconds);
   }

   ZenUnitArgs TestableRandomZenUnitArgs(const RandomGenerator* randomGenerator, const ZenUnitTestingRandomGenerator* zenUnitTestingRandomGenerator)
   {
      ZenUnitArgs randomZenUnitArgs;
      randomZenUnitArgs.startDateTime = randomGenerator->String();
      randomZenUnitArgs.commandLine = randomGenerator->String();
      randomZenUnitArgs.testNameFilters = zenUnitTestingRandomGenerator->RandomTestNameFiltersVector();
      randomZenUnitArgs.pauseBefore = randomGenerator->Bool();
      randomZenUnitArgs.pauseAfter = randomGenerator->Bool();
      randomZenUnitArgs.alwaysExit0 = randomGenerator->Bool();
      randomZenUnitArgs.failFast = randomGenerator->Bool();
      randomZenUnitArgs.exit1IfTestsSkipped = randomGenerator->Bool();
      randomZenUnitArgs.testRuns = randomGenerator->Int();
      randomZenUnitArgs.randomTestOrdering = randomGenerator->Bool();
      randomZenUnitArgs.globalRandomSeedSetByUser = randomGenerator->Bool();
      randomZenUnitArgs.maxTestMilliseconds = randomGenerator->Unsigned();
      return randomZenUnitArgs;
   }

   template<>
   ZenUnitArgs Random<ZenUnitArgs>()
   {
      return TestableRandomZenUnitArgs(RandomGenerator::Instance(), ZenUnitTestingRandomGenerator::Instance());
   }
}

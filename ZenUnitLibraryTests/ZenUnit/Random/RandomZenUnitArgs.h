#pragma once
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestNameFilter.h"

namespace ZenUnit
{
   inline ZenUnitArgs TestableRandomZenUnitArgs(const RandomGenerator& randomGenerator)
   {
      ZenUnitArgs randomZenUnitArgs;
      randomZenUnitArgs.startDateTime = randomGenerator.String();
      randomZenUnitArgs.commandLine = randomGenerator.String();
      randomZenUnitArgs.testNameFilters = ZenUnit::RandomNonEmptyVector<TestNameFilter>();
      randomZenUnitArgs.pauseBefore = randomGenerator.Bool();
      randomZenUnitArgs.pauseAfter = randomGenerator.Bool();
      randomZenUnitArgs.alwaysExit0 = randomGenerator.Bool();
      randomZenUnitArgs.failFast = randomGenerator.Bool();
      randomZenUnitArgs.exit1IfTestsSkipped = randomGenerator.Bool();
      randomZenUnitArgs.informalSpecificationMode = randomGenerator.Bool();
      randomZenUnitArgs.testRuns = randomGenerator.Int();
      randomZenUnitArgs.randomTestOrdering = randomGenerator.Bool();
      randomZenUnitArgs.randomSeed = randomGenerator.UnsignedInt();
      randomZenUnitArgs.randomSeedSetByUser = randomGenerator.Bool();
      randomZenUnitArgs.maxTestMilliseconds = randomGenerator.UnsignedInt();
      return randomZenUnitArgs;
   }

   template<>
   inline ZenUnitArgs Random<ZenUnitArgs>()
   {
      return TestableRandomZenUnitArgs(RandomGenerator());
   }
}

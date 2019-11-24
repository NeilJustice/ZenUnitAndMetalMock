#pragma once
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomRunFilter.h"

namespace ZenUnit
{
   inline ZenUnitArgs TestableRandomZenUnitArgs(const RandomGenerator& randomGenerator)
   {
      ZenUnitArgs randomZenUnitArgs;
      randomZenUnitArgs.startDateTime = randomGenerator.String();
      randomZenUnitArgs.commandLine = randomGenerator.String();
      randomZenUnitArgs.runFilters = ZenUnit::RandomVector<RunFilter>();
      randomZenUnitArgs.pause = randomGenerator.Bool();
      randomZenUnitArgs.wait = randomGenerator.Bool();
      randomZenUnitArgs.exitZero = randomGenerator.Bool();
      randomZenUnitArgs.failFast = randomGenerator.Bool();
      randomZenUnitArgs.noSkips = randomGenerator.Bool();
      randomZenUnitArgs.testRuns = randomGenerator.UnsignedInt();
      randomZenUnitArgs.random = randomGenerator.Bool();
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

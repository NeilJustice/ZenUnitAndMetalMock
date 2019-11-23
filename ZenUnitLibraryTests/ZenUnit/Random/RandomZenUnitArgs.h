#pragma once
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomRunFilter.h"

namespace ZenUnit
{
   template<>
   inline ZenUnitArgs Random<ZenUnitArgs>()
   {
      ZenUnitArgs randomZenUnitArgs;
      randomZenUnitArgs.startDateTime = ZenUnit::Random<string>();
      randomZenUnitArgs.commandLine = ZenUnit::Random<string>();
      randomZenUnitArgs.runFilters = ZenUnit::RandomVector<RunFilter>();
      randomZenUnitArgs.pause = ZenUnit::Random<bool>();
      randomZenUnitArgs.wait = ZenUnit::Random<bool>();
      randomZenUnitArgs.exitZero = ZenUnit::Random<bool>();
      randomZenUnitArgs.failFast = ZenUnit::Random<bool>();
      randomZenUnitArgs.noSkips = ZenUnit::Random<bool>();
      randomZenUnitArgs.testRuns = ZenUnit::Random<unsigned>();
      randomZenUnitArgs.random = ZenUnit::Random<bool>();
      randomZenUnitArgs.randomSeed = ZenUnit::Random<unsigned>();
      randomZenUnitArgs.randomSeedSetByUser = ZenUnit::Random<bool>();
      randomZenUnitArgs.maxTestMilliseconds = ZenUnit::Random<unsigned>();
      return randomZenUnitArgs;
   }
}

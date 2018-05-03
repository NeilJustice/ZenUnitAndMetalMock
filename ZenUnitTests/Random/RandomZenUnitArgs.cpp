#include "pch.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"
#include "ZenUnitTests/Random/RandomZenUnitArgs.h"

namespace ZenUnit
{
   template<>
   ZenUnitArgs Random<ZenUnitArgs>()
   {
      ZenUnitArgs randomZenUnitArgs;
      randomZenUnitArgs.commandLine = ZenUnit::Random<string>();
      randomZenUnitArgs.runFilters = ZenUnit::RandomVector<RunFilter>();
      randomZenUnitArgs.pause = ZenUnit::Random<bool>();
      randomZenUnitArgs.wait = ZenUnit::Random<bool>();
      randomZenUnitArgs.exit0 = ZenUnit::Random<bool>();
      randomZenUnitArgs.failfast = ZenUnit::Random<bool>();
      randomZenUnitArgs.failskips = ZenUnit::Random<bool>();
      randomZenUnitArgs.testruns = ZenUnit::Random<unsigned>();
      randomZenUnitArgs.random = ZenUnit::Random<bool>();
      randomZenUnitArgs.randomseed = ZenUnit::Random<unsigned short>();
      randomZenUnitArgs.randomseedsetbyuser = ZenUnit::Random<bool>();
      randomZenUnitArgs.maxtestmilliseconds = ZenUnit::Random<unsigned>();
      randomZenUnitArgs.maxtotalseconds = ZenUnit::Random<unsigned>();
      return randomZenUnitArgs;
   }
}

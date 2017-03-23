#pragma once
#include <unordered_set>
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   struct ZenUnitArgs
   {
      std::string commandLine;
      bool exit0 = false;
      bool noskips = false;
      long long maxtestmilliseconds = 0;
      unsigned maxtotalseconds = 0;

      static const std::unordered_set<std::string> ValidArgs;
   };
}

template<>
struct ZenUnitEqualizer<ZenUnit::ZenUnitArgs>
{
   static void AssertEqual(
      const ZenUnit::ZenUnitArgs& expectedArgs,
      const ZenUnit::ZenUnitArgs& actualArgs);
};

#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include <unordered_set>

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

   #ifdef __linux__
      static_assert(sizeof(ZenUnitArgs) == 56, "sizeof(ZenUnitArgs) != 56");
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(ZenUnitArgs) == 64, "Debug sizeof(ZenUnitArgs) != 64");
      #elif NDEBUG
         static_assert(sizeof(ZenUnitArgs) == 56, "Release sizeof(ZenUnitArgs) != 56");
      #endif
   #endif
}

template<>
struct ZenUnitEqualizer<ZenUnit::ZenUnitArgs>
{
   static void AssertEqual(
      const ZenUnit::ZenUnitArgs& expectedArgs,
      const ZenUnit::ZenUnitArgs& actualArgs);
};

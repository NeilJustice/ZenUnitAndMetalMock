#pragma once
#include "ZenUnit/Args/RunFilter.h"
#include "ZenUnit/Enums/PrintMode.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   struct ZenUnitArgs
   {
      std::string commandLine;
      PrintMode printMode = PrintMode::Normal;
      std::vector<RunFilter> runFilters;
      bool pause = false;
      bool wait = false;
      bool exit0 = false;
      bool failskips = false;
      unsigned testruns = 1;
      bool random = false;
      unsigned short randomseed = 0;
      bool randomseedsetbyuser = false;
      unsigned maxtestmilliseconds = 0;
      unsigned maxtotalseconds = 0;
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(ZenUnitArgs) == 88);
      #endif
   #elif defined(_WIN64)
      #ifdef _DEBUG
         static_assert(sizeof(ZenUnitArgs) == 104);
      #elif NDEBUG
         static_assert(sizeof(ZenUnitArgs) == 88);
      #endif
   #endif

   template<>
   struct Equalizer<ZenUnit::ZenUnitArgs>
   {
      static void AssertEqual(
         const ZenUnit::ZenUnitArgs& expectedArguments,
         const ZenUnit::ZenUnitArgs& actualArgs);
   };
}

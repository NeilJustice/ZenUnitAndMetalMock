#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Utils/Random.h"

namespace ZenUnit
{
   struct RunFilter
   {
      std::string testClassName;
      std::string testName;
      unsigned testCaseNumber;

      RunFilter();
      RunFilter(const std::string& testClassName, const std::string& testName, unsigned testCaseNumber);
   };

   template<>
   struct Equalizer<ZenUnit::RunFilter>
   {
      static void AssertEqual(
         const ZenUnit::RunFilter& expectedRunFilter,
         const ZenUnit::RunFilter& actualRunFilter);
   };

   template<>
   RunFilter Random<RunFilter>();
}
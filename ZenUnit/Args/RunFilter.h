#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Utils/Random.h"

namespace ZenUnit
{
   struct RunFilter
   {
      std::string testClassName;
      std::string testName;
      unsigned testCaseNumber = 0;
   };
}

template<>
struct ZenUnitEqualizer<ZenUnit::RunFilter>
{
   static void AssertEqual(
      const ZenUnit::RunFilter& expectedRunFilter,
      const ZenUnit::RunFilter& actualRunFilter);
};

namespace ZenUnit
{
   template<>
   RunFilter Random<RunFilter>();
}
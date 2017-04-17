#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   struct FullName
   {
      const char* testClassName;
      const char* testName;

      FullName();
      FullName(const char* testClassName, const char* testName);
      std::string TestsAndTestLines() const;
   };
}

template<>
struct ZenUnitEqualizer<ZenUnit::FullName>
{
   static void AssertEqual(
      const ZenUnit::FullName& expectedFullName, 
      const ZenUnit::FullName& actualFullName);
};

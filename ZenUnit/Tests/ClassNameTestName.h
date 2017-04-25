#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   struct ClassNameTestName
   {
      const char* testClassName;
      const char* testName;

      ClassNameTestName();
      ClassNameTestName(const char* testClassName, const char* testName);
      std::string TestsAndTestLines() const;
   };
}

template<>
struct ZenUnitEqualizer<ZenUnit::ClassNameTestName>
{
   static void AssertEqual(
      const ZenUnit::ClassNameTestName& expectedClassNameTestName, 
      const ZenUnit::ClassNameTestName& actualClassNameTestName);
};

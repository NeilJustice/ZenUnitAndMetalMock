#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/ToStringer/SFINAE/has_ZenUnitPrinter.h"

namespace ZenUnit
{
   struct FullTestName
   {
      const char* testClassName;      
      const char* testName;
      unsigned char arity;

      FullTestName();
      FullTestName(const char* testClassName, const char* testName, unsigned char arity);
      std::string Value() const;
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(FullTestName) == 24, "Debug sizeof(FullTestName) != 24");
      #endif
   #elif _MSC_FULL_VER == 191025019 // VS2017 15.2
      #ifdef _DEBUG
         static_assert(sizeof(FullTestName) == 24, "Debug sizeof(FullTestName) != 24");
      #elif NDEBUG
         static_assert(sizeof(FullTestName) == 24, "Release sizeof(FullTestName) != 24");
      #endif
   #endif
}

template<>
struct ZenUnitEqualizer<ZenUnit::FullTestName>
{
   static void AssertEqual(
      const ZenUnit::FullTestName& expectedFullTestName, 
      const ZenUnit::FullTestName& actualFullTestName);
};

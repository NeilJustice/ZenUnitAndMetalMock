#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/ToStringer/SFINAE/has_ZenUnitPrinter.h"

namespace ZenUnit
{
   struct ClassNameTestName
   {
      const char* testClassName;      
      const char* testName;
      unsigned char arity;

      ClassNameTestName();
      ClassNameTestName(const char* testClassName, const char* testName, unsigned char arity);
      std::string Value() const;
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(ClassNameTestName) == 24, "Debug sizeof(ClassNameTestName) != 24");
      #endif
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(ClassNameTestName) == 24, "Debug sizeof(ClassNameTestName) != 24");
      #elif NDEBUG
         static_assert(sizeof(ClassNameTestName) == 24, "Release sizeof(ClassNameTestName) != 24");
      #endif
   #endif
}

template<>
struct ZenUnitEqualizer<ZenUnit::ClassNameTestName>
{
   static void AssertEqual(
      const ZenUnit::ClassNameTestName& expectedClassNameTestName, 
      const ZenUnit::ClassNameTestName& actualClassNameTestName);
};

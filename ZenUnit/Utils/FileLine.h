#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Utils/FileLiner.h"
#include <string>

namespace ZenUnit
{
   struct FileLine
   {
      const char* filePath;
      unsigned lineNumber;

      FileLine();
      FileLine(const char* filePath, unsigned lineNumber);
      std::string ToString() const;
      friend std::ostream& operator<<(std::ostream& os, const FileLine& fileLine);
   };

   template<>
   struct Equalizer<ZenUnit::FileLine>
   {
      static void AssertEqual(
         const ZenUnit::FileLine& expectedFileLine,
         const ZenUnit::FileLine& actualFileLine);
   };
}

#define FILELINE ZenUnit::FileLine(ZenUnit::FileLiner::File(__FILE__), ZenUnit::FileLiner::Line(__LINE__))

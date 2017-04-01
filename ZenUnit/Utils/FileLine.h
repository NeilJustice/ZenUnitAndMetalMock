#pragma once
#include "FileLiner.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
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
}

#define FILELINE ZenUnit::FileLine(ZenUnit::FileLiner::File(__FILE__), ZenUnit::FileLiner::Line(__LINE__))

template<>
struct ZenUnitEqualizer<ZenUnit::FileLine>
{
   static void AssertEqual(
      const ZenUnit::FileLine& expectedFileLine,
      const ZenUnit::FileLine& actualFileLine);
};

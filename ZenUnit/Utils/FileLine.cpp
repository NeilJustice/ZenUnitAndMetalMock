#include "pch.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Utils/FileLine.h"

namespace ZenUnit
{
   inline FileLine::FileLine()
      : filePath("")
      , lineNumber(0)
   {
   }

   inline FileLine::FileLine(const char* filePath, unsigned lineNumber)
      : filePath(filePath == nullptr ? "" : filePath), lineNumber(lineNumber) {}

   inline std::string FileLine::ToString() const
   {
      std::ostringstream oss;
      oss << *this;
      const std::string fileLineAsString = oss.str();
      return fileLineAsString;
   }

   inline std::ostream& operator<<(std::ostream& os, const FileLine& fileLine)
   {
      os << fileLine.filePath << '(' << fileLine.lineNumber << ')';
      return os;
   }
}

inline void ZenUnitEqualizer<ZenUnit::FileLine>::
AssertEqual(
   const ZenUnit::FileLine& expectedFileLine,
   const ZenUnit::FileLine& actualFileLine)
{
   ARE_EQUAL(expectedFileLine.filePath, actualFileLine.filePath);
   ARE_EQUAL(expectedFileLine.lineNumber, actualFileLine.lineNumber);
}

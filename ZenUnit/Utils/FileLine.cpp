#include "pch.h"
#include "FileLine.h"
#include "Macros/ARE_EQUAL.h"

namespace ZenUnit
{
   FileLine::FileLine()
      : filePath(""), lineNumber(0) {}

   FileLine::FileLine(const char* filePath, unsigned lineNumber)
      : filePath(filePath == nullptr ? "" : filePath), lineNumber(lineNumber) {}

   std::string FileLine::ToString() const
   {
      ostringstream oss;
      oss << *this;
      const string fileLineAsString = oss.str();
      return fileLineAsString;
   }

   std::ostream& operator<<(std::ostream& os, const FileLine& fileLine)
   {
      os << fileLine.filePath << '(' << fileLine.lineNumber << ')';
      return os;
   }
}

void ZenUnitEqualizer<ZenUnit::FileLine>::
AssertEqual(
   const ZenUnit::FileLine& expectedFileLine,
   const ZenUnit::FileLine& actualFileLine)
{
   ARE_EQUAL(expectedFileLine.filePath, actualFileLine.filePath);
   ARE_EQUAL(expectedFileLine.lineNumber, actualFileLine.lineNumber);
}

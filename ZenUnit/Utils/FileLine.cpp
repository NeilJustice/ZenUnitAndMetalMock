#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Utils/FileLine.h"

namespace ZenUnit
{
   INLINE FileLine::FileLine()
      : filePath("")
      , lineNumber(0)
   {
   }

   INLINE FileLine::FileLine(const char* filePath, unsigned lineNumber)
      : filePath(filePath == nullptr ? "" : filePath), lineNumber(lineNumber) {}

   INLINE std::string FileLine::ToString() const
   {
      std::ostringstream oss;
      oss << *this;
      const std::string fileLineAsString = oss.str();
      return fileLineAsString;
   }

   INLINE std::ostream& operator<<(std::ostream& os, const FileLine& fileLine)
   {
      os << fileLine.filePath << '(' << fileLine.lineNumber << ')';
      return os;
   }
}

INLINE void ZenUnitEqualizer<ZenUnit::FileLine>::
AssertEqual(
   const ZenUnit::FileLine& expectedFileLine,
   const ZenUnit::FileLine& actualFileLine)
{
   ARE_EQUAL(expectedFileLine.filePath, actualFileLine.filePath);
   ARE_EQUAL(expectedFileLine.lineNumber, actualFileLine.lineNumber);
}

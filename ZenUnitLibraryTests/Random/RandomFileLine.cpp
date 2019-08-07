#include "pch.h"
#include "ZenUnitLibraryTests/Random/RandomFileLine.h"

namespace ZenUnit
{
   template<>
   FileLine Random<FileLine>()
   {
      FileLine randomFileLine;
      //randomFileLine.filePath = ZenUnit::Random<const char*>();
      randomFileLine.lineNumber = ZenUnit::Random<unsigned>();
      return randomFileLine;
   }
}

#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomFileLine.h"

namespace ZenUnit
{
   template<>
   FileLine Random<FileLine>()
   {
      FileLine randomFileLine;
      randomFileLine.lineNumber = ZenUnit::Random<unsigned>();
      return randomFileLine;
   }
}

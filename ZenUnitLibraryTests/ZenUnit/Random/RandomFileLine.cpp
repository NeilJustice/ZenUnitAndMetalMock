#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomFileLine.h"

namespace ZenUnit
{
   template<>
   FileLine Random<FileLine>()
   {
      return TestableRandomFileLine(RandomGenerator());
   }

   FileLine TestableRandomFileLine(const RandomGenerator& randomGenerator)
   {
      FileLine randomFileLine;
      randomFileLine.lineNumber = randomGenerator.UnsignedInt();
      return randomFileLine;
   }
}

#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomFilePathLineNumber.h"

namespace ZenUnit
{
   template<>
   FilePathLineNumber Random<FilePathLineNumber>()
   {
      return TestableRandomFilePathLineNumber(RandomGenerator());
   }

   FilePathLineNumber TestableRandomFilePathLineNumber(const RandomGenerator& randomGenerator)
   {
      FilePathLineNumber randomFilePathLineNumber;
      randomFilePathLineNumber.lineNumber = randomGenerator.UnsignedInt();
      return randomFilePathLineNumber;
   }
}

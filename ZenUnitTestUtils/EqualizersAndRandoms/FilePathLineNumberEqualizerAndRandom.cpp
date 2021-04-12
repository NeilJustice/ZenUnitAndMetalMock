#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<FilePathLineNumber>::AssertEqual(
      const FilePathLineNumber& expectedFilePathLineNumber, const FilePathLineNumber& actualFilePathLineNumber)
   {
      FIELDS_ARE_EQUAL(expectedFilePathLineNumber, actualFilePathLineNumber, filePath);
      FIELDS_ARE_EQUAL(expectedFilePathLineNumber, actualFilePathLineNumber, lineNumber);
   }

   FilePathLineNumber TestableRandomFilePathLineNumber(const RandomGenerator* randomGenerator)
   {
      FilePathLineNumber randomFilePathLineNumber;
      randomFilePathLineNumber.filePath = randomGenerator->ConstCharPointer();
      randomFilePathLineNumber.lineNumber = randomGenerator->UnsignedInt();
      return randomFilePathLineNumber;
   }

   template<>
   FilePathLineNumber Random()
   {
      return TestableRandomFilePathLineNumber(RandomGenerator::Instance());
   }
}

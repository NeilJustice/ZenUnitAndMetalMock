#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<FilePathLineNumber>::AssertEqual(
      const FilePathLineNumber& expectedFilePathLineNumber, const FilePathLineNumber& actualFilePathLineNumber)
   {
      ARE_EQUAL(expectedFilePathLineNumber.filePath, actualFilePathLineNumber.filePath);
      ARE_EQUAL(expectedFilePathLineNumber.lineNumber, actualFilePathLineNumber.lineNumber);
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

#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomFilePathLineNumber.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizer.h"

namespace ZenUnit
{
   TESTS(RandomFilePathLineNumberTests)
   AFACT(RandomFilePathLineNumber_CodeCoverage)
   AFACT(TestableRandomFilePathLineNumber_ReturnsFilePathLineNumberWithRandomLineNumber)
   EVIDENCE

   TEST(RandomFilePathLineNumber_CodeCoverage)
   {
      Random<FilePathLineNumber>();
   }

   TEST(TestableRandomFilePathLineNumber_ReturnsFilePathLineNumberWithRandomLineNumber)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;
      const unsigned lineNumber = randomGeneratorMock.UnsignedIntMock.ReturnRandom();
      //
      const FilePathLineNumber randomFilePathLineNumber = TestableRandomFilePathLineNumber(randomGeneratorMock);
      //
      FilePathLineNumber expectedRandomFilePathLineNumber;
      expectedRandomFilePathLineNumber.lineNumber = lineNumber;
      METALMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      ARE_EQUAL(expectedRandomFilePathLineNumber, randomFilePathLineNumber);
   }

   RUN_TESTS(RandomFilePathLineNumberTests)
}

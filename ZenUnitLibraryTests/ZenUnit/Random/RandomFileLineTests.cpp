#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomFileLine.h"
#include "ZenUnitTestUtils/Equalizers/FileLineEqualizer.h"

namespace ZenUnit
{
   TESTS(RandomFileLineTests)
   AFACT(RandomFileLine_CodeCoverage)
   AFACT(TestableRandomFileLine_ReturnsFileLineWithRandomLineNumber)
   EVIDENCE

   TEST(RandomFileLine_CodeCoverage)
   {
      Random<FileLine>();
   }

   TEST(TestableRandomFileLine_ReturnsFileLineWithRandomLineNumber)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;
      const unsigned lineNumber = randomGeneratorMock.UnsignedIntMock.ReturnRandom();
      //
      const FileLine randomFileLine = TestableRandomFileLine(randomGeneratorMock);
      //
      FileLine expectedRandomFileLine;
      expectedRandomFileLine.lineNumber = lineNumber;
      METALMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      ARE_EQUAL(expectedRandomFileLine, randomFileLine);
   }

   RUN_TESTS(RandomFileLineTests)
}

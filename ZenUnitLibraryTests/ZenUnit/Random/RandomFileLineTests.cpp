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
      const FileLine randomFileLine = Random<FileLine>();
   }

   TEST(TestableRandomFileLine_ReturnsFileLineWithRandomLineNumber)
   {
      ZenMock::RandomGeneratorMock randomGeneratorMock;
      const unsigned lineNumber = randomGeneratorMock.UnsignedIntMock.ReturnRandom();
      //
      const FileLine randomFileLine = TestableRandomFileLine(randomGeneratorMock);
      //
      FileLine expectedRandomFileLine;
      expectedRandomFileLine.lineNumber = lineNumber;
      ZENMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
      ARE_EQUAL(expectedRandomFileLine, randomFileLine);
   }

   RUN_TESTS(RandomFileLineTests)
}

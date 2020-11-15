#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<Anomaly>::AssertEqual(const Anomaly& expectedAnomaly, const Anomaly& actualAnomaly)
   {
      ARE_EQUAL(expectedAnomaly.assertExpression, actualAnomaly.assertExpression);
      ARE_EQUAL(expectedAnomaly.expectedValueAsStringOrExpectedLine, actualAnomaly.expectedValueAsStringOrExpectedLine);
      ARE_EQUAL(expectedAnomaly.actualValueAsStringOrActualLine, actualAnomaly.actualValueAsStringOrActualLine);
      ARE_EQUAL(expectedAnomaly.optionalThirdLine, actualAnomaly.optionalThirdLine);
      ARE_EQUAL(expectedAnomaly.message, actualAnomaly.message);
      ARE_EQUAL(expectedAnomaly.why, actualAnomaly.why);
      ARE_EQUAL(expectedAnomaly.filePathLineNumber, actualAnomaly.filePathLineNumber);
   }

   Anomaly TestableRandomAnomaly(const RandomGenerator* randomGenerator)
   {
      Anomaly randomAnomaly;
      randomAnomaly.assertExpression = randomGenerator->String();
      randomAnomaly.expectedValueAsStringOrExpectedLine = randomGenerator->String();
      randomAnomaly.actualValueAsStringOrActualLine = randomGenerator->String();
      randomAnomaly.optionalThirdLine = randomGenerator->String();
      randomAnomaly.message = randomGenerator->String();
      randomAnomaly.why = randomGenerator->String();
      randomAnomaly.filePathLineNumber = ZenUnit::Random<FilePathLineNumber>();
      return randomAnomaly;
   }

   template<>
   Anomaly Random()
   {
      return TestableRandomAnomaly(RandomGenerator::Instance());
   }
}

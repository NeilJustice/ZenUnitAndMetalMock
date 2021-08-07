#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<Anomaly>::AssertEqual(const Anomaly& expectedAnomaly, const Anomaly& actualAnomaly)
   {
      FIELDS_ARE_EQUAL(expectedAnomaly, actualAnomaly, assertExpression);
      FIELDS_ARE_EQUAL(expectedAnomaly, actualAnomaly, expectedValueAsStringOrExpectedLine);
      FIELDS_ARE_EQUAL(expectedAnomaly, actualAnomaly, actualValueAsStringOrActualLine);
      FIELDS_ARE_EQUAL(expectedAnomaly, actualAnomaly, optionalThirdLine);
      FIELDS_ARE_EQUAL(expectedAnomaly, actualAnomaly, message);
      FIELDS_ARE_EQUAL(expectedAnomaly, actualAnomaly, why);
      FIELDS_ARE_EQUAL(expectedAnomaly, actualAnomaly, filePathLineNumber);
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

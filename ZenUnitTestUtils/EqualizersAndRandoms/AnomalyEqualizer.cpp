#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyEqualizer.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FileLineEqualizer.h"

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
      ARE_EQUAL(expectedAnomaly.fileLine, actualAnomaly.fileLine);
   }
}

#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/AnomalyEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/FileLineEqualizer.h"

namespace ZenUnit
{
   void Equalizer<Anomaly>::AssertEqual(const Anomaly& expectedAnomaly, const Anomaly& actualAnomaly)
   {
      ARE_EQUAL(expectedAnomaly.assertExpression, actualAnomaly.assertExpression);
      ARE_EQUAL(expectedAnomaly.expected, actualAnomaly.expected);
      ARE_EQUAL(expectedAnomaly.actual, actualAnomaly.actual);
      ARE_EQUAL(expectedAnomaly.message, actualAnomaly.message);
      ARE_EQUAL(expectedAnomaly.why, actualAnomaly.why);
      ARE_EQUAL(expectedAnomaly.fileLine, actualAnomaly.fileLine);
   }
}

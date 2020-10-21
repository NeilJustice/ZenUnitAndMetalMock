#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/AnomalyOrExceptionEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/AnomalyEqualizer.h"

namespace ZenUnit
{
   void Equalizer<AnomalyOrException>::AssertEqual(
      const AnomalyOrException& expectedAnomalyOrException,
      const AnomalyOrException& actualAnomalyOrException)
   {
      POINTEES_ARE_EQUAL(expectedAnomalyOrException.anomaly, actualAnomalyOrException.anomaly);
      ARE_EQUAL(expectedAnomalyOrException.exceptionTypeName, actualAnomalyOrException.exceptionTypeName);
      POINTEES_ARE_EQUAL(expectedAnomalyOrException.exceptionWhat, actualAnomalyOrException.exceptionWhat);
   }
}

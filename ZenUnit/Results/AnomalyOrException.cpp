#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/POINTEES_EQUAL.h"
#include "ZenUnit/Results/AnomalyOrException.h"

namespace ZenUnit
{
   INLINE AnomalyOrException::AnomalyOrException(const Anomaly& anomaly)
      : anomaly(std::make_shared<Anomaly>(anomaly))
      , exceptionTypeName(nullptr)
   {
   }

   INLINE AnomalyOrException::AnomalyOrException(const std::string* exceptionTypeName, const char* exceptionWhat)
      : exceptionTypeName(exceptionTypeName)
      , exceptionWhat(std::make_shared<std::string>(exceptionWhat))
   {
   }
}

INLINE void ZenUnitEqualizer<ZenUnit::AnomalyOrException>::AssertEqual(
   const ZenUnit::AnomalyOrException& expectedAnomalyOrException,
   const ZenUnit::AnomalyOrException& actualAnomalyOrException)
{
   POINTEES_EQUAL(expectedAnomalyOrException.anomaly, actualAnomalyOrException.anomaly);
   ARE_EQUAL(expectedAnomalyOrException.exceptionTypeName, actualAnomalyOrException.exceptionTypeName);
   POINTEES_EQUAL(expectedAnomalyOrException.exceptionWhat, actualAnomalyOrException.exceptionWhat);
}

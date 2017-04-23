#include "pch.h"
#include "AnomalyOrException.h"
#include "Anomaly/Anomaly.h"
#include "Macros/ARE_EQUAL.h"
#include "Macros/IS_FALSE.h"

namespace ZenUnit
{
   AnomalyOrException::AnomalyOrException(const Anomaly& anomaly)
      : anomaly(make_shared<Anomaly>(anomaly))
      , exceptionTypeName(nullptr)
   {
   }

   AnomalyOrException::AnomalyOrException(const std::string* exceptionTypeName, const char* exceptionWhat)
      : exceptionTypeName(exceptionTypeName)
      , exceptionWhat(make_shared<string>(exceptionWhat))
   {
   }
}

void ZenUnitEqualizer<ZenUnit::AnomalyOrException>::AssertEqual(
   const ZenUnit::AnomalyOrException& expectedAnomalyOrException, 
   const ZenUnit::AnomalyOrException& actualAnomalyOrException)
{
   if (!expectedAnomalyOrException.anomaly)
   {
      IS_FALSE(actualAnomalyOrException.anomaly);
   }
   else if (!actualAnomalyOrException.anomaly)
   {
      IS_FALSE(expectedAnomalyOrException.anomaly);
   }
   else
   {
      ARE_EQUAL(*expectedAnomalyOrException.anomaly, *actualAnomalyOrException.anomaly);
   }

   ARE_EQUAL(expectedAnomalyOrException.exceptionTypeName, actualAnomalyOrException.exceptionTypeName);

   if (!expectedAnomalyOrException.exceptionWhat)
   {
      IS_FALSE(actualAnomalyOrException.exceptionWhat);
   }
   else if (!actualAnomalyOrException.exceptionWhat)
   {
      IS_FALSE(expectedAnomalyOrException.exceptionWhat);
   }
   else
   {
      ARE_EQUAL(*expectedAnomalyOrException.exceptionWhat, *actualAnomalyOrException.exceptionWhat);
   }
}

#include "pch.h"

namespace ZenUnit
{
   TESTS(AnomalyOrExceptionTests)
   AFACT(AnomalyConstructor_SetsAnomaly)
   AFACT(ExceptionTypeNameAndExceptionWhatConstructor_SetsExceptionTypeNameAndExceptionWhat)
   EVIDENCE

   TEST(AnomalyConstructor_SetsAnomaly)
   {
      Anomaly anomaly;
      anomaly.why = "NonDefault";
      //
      const AnomalyOrException anomalyOrException(anomaly);
      //
      ARE_EQUAL(anomaly, *anomalyOrException.anomaly);
      IS_NULLPTR(anomalyOrException.exceptionTypeName);
      IS_NULLPTR(anomalyOrException.exceptionWhat);
   }

   TEST(ExceptionTypeNameAndExceptionWhatConstructor_SetsExceptionTypeNameAndExceptionWhat)
   {
      const string exceptionTypeName;
      const string exceptionWhat = Random<string>();
      //
      AnomalyOrException anomalyOrException(&exceptionTypeName, exceptionWhat.c_str());
      //
      IS_NULLPTR(anomalyOrException.anomaly);
      ARE_SAME(exceptionTypeName, *anomalyOrException.exceptionTypeName);
      ARE_EQUAL(exceptionWhat, *anomalyOrException.exceptionWhat);
   }

   RUN_TESTS(AnomalyOrExceptionTests)
}

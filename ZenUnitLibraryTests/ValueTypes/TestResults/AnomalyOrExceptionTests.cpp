#include "pch.h"

namespace ZenUnit
{
   TESTS(AnomalyOrExceptionTests)
   AFACT(AnomalyConstructor_SetsAnomaly)
   AFACT(ExceptionTypeNameAndExceptionMessageConstructor_SetsExceptionTypeNameAndExceptionMessage)
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
      IS_NULLPTR(anomalyOrException.exceptionMessage);
   }

   TEST(ExceptionTypeNameAndExceptionMessageConstructor_SetsExceptionTypeNameAndExceptionMessage)
   {
      const string exceptionTypeName = Random<string>();
      const string exceptionMessage = Random<string>();
      //
      AnomalyOrException anomalyOrException(&exceptionTypeName, exceptionMessage.c_str());
      //
      IS_NULLPTR(anomalyOrException.anomaly);
      ARE_SAME(exceptionTypeName, *anomalyOrException.exceptionTypeName);
      ARE_EQUAL(exceptionMessage, *anomalyOrException.exceptionMessage);
   }

   RUN_TESTS(AnomalyOrExceptionTests)
}

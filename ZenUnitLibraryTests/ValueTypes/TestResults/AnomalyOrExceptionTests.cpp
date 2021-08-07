#include "pch.h"

namespace ZenUnit
{
   TESTS(AnomalyOrExceptionTests)
   AFACT(DefaultConstructor_SetsFieldsToDefaultValues)
   AFACT(OneArgAnomalyConstructor_SetsAnomaly)
   AFACT(ExceptionTypeNameAndExceptionMessageConstructor_SetsExceptionTypeNameAndExceptionMessage)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsToDefaultValues)
   {
      const AnomalyOrException defaultAnomalyOrException;
      AnomalyOrException expectedDefaultAnomalyOrException;
      expectedDefaultAnomalyOrException.anomaly = nullptr;
      expectedDefaultAnomalyOrException.exceptionTypeName = nullptr;
      expectedDefaultAnomalyOrException.exceptionMessage = nullptr;
      ARE_EQUAL(expectedDefaultAnomalyOrException, defaultAnomalyOrException);
   }

   TEST(OneArgAnomalyConstructor_SetsAnomaly)
   {
      const Anomaly anomaly = ZenUnit::Random<Anomaly>();
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

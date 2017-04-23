#include "pch.h"
#include "ZenUnit/Results/AnomalyOrException.h"

TESTS(AnomalyOrExceptionTests)
SPEC(AnomalyConstructor_SetsAnomaly)
SPEC(ExceptionTypeNameAndExceptionWhatConstructor_SetsExceptionTypeNameAndExceptionWhat)
SPECEND

TEST(AnomalyConstructor_SetsAnomaly)
{
   Anomaly anomaly;
   anomaly.why = "NonDefault";
   //
   const AnomalyOrException anomalyOrException(anomaly);
   //
   ARE_EQUAL(anomaly, *anomalyOrException.anomaly);
   IS_NULL(anomalyOrException.exceptionTypeName);
   IS_NULL(anomalyOrException.exceptionWhat);
}

TEST(ExceptionTypeNameAndExceptionWhatConstructor_SetsExceptionTypeNameAndExceptionWhat)
{
   const string ExceptionTypeName = "ExceptionTypeName";
   const char* const ExceptionWhat = "ExceptionWhat";
   ARE_EQUAL(ExceptionWhat, ExceptionWhat);
   //
   AnomalyOrException anomalyOrException(&ExceptionTypeName, ExceptionWhat);
   //
   IS_NULL(anomalyOrException.anomaly);
   ARE_EQUAL(&ExceptionTypeName, anomalyOrException.exceptionTypeName);
   ARE_EQUAL(ExceptionWhat, *anomalyOrException.exceptionWhat);
}

}; RUN(AnomalyOrExceptionTests)

#include "pch.h"
#include "ZenUnit/Results/AnomalyOrException.h"
#include "ZenUnit/Utils/Random.h"

TESTS(AnomalyOrExceptionTests)
FACT(AnomalyConstructor_SetsAnomaly)
FACT(ExceptionTypeNameAndExceptionWhatConstructor_SetsExceptionTypeNameAndExceptionWhat)
EVIDENCE

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
   const string ExceptionTypeName;
   const string ExceptionWhat = Random<string>();
   //
   AnomalyOrException anomalyOrException(&ExceptionTypeName, ExceptionWhat.c_str());
   //
   IS_NULL(anomalyOrException.anomaly);
   ARE_SAME(ExceptionTypeName, *anomalyOrException.exceptionTypeName);
   ARE_EQUAL(ExceptionWhat, *anomalyOrException.exceptionWhat);
}

RUNTESTS(AnomalyOrExceptionTests)

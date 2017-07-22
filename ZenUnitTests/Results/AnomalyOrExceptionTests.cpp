#include "pch.h"
#include "ZenUnit/Results/AnomalyOrException.h"
#include "ZenUnit/Utils/TestRandom.h"

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
   const string ExceptionTypeName;
   const string ExceptionWhat = TestRandom<string>();
   //
   AnomalyOrException anomalyOrException(&ExceptionTypeName, ExceptionWhat.c_str());
   //
   IS_NULL(anomalyOrException.anomaly);
   ARE_SAME(ExceptionTypeName, *anomalyOrException.exceptionTypeName);
   ARE_EQUAL(ExceptionWhat, *anomalyOrException.exceptionWhat);
}

}; RUN(AnomalyOrExceptionTests)

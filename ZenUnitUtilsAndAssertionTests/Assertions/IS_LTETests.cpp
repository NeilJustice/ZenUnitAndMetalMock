#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(IS_LTETests, T)
   AFACT(IS_LTE_ValueIsLessThanComparisonValue_DoesNothing)
   AFACT(IS_LTE_ValueIsEqualToComparisonValue_DoesNothing)
   AFACT(IS_LTE_ValueIsGreaterThanComparisonValue_ThrowsAnomaly)
   AFACT(IS_LTE_ValueIsGreaterThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(IS_LTE_ValueIsLessThanComparisonValue_DoesNothing)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = ZenUnit::RandomLessThan<T>(comparisonValue);
      IS_LTE(value, comparisonValue);
   }

   TEST(IS_LTE_ValueIsEqualToComparisonValue_DoesNothing)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = comparisonValue;
      IS_LTE(value, comparisonValue);
   }

   TEST(IS_LTE_ValueIsGreaterThanComparisonValue_ThrowsAnomaly)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = ZenUnit::RandomGreaterThan<T>(comparisonValue);
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LTE(value, comparisonValue)",
"Expected: " + to_string(value),
"  Actual: " + to_string(comparisonValue),
"File.cpp(1)");
      THROWS_EXCEPTION(IS_LTE(value, comparisonValue), Anomaly, expectedExceptionMessage);
   }

   TEST(IS_LTE_ValueIsGreaterThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = ZenUnit::RandomGreaterThan<T>(comparisonValue);
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LTE(value, comparisonValue, messageA, messageB)",
"Expected: " + to_string(value),
"  Actual: " + to_string(comparisonValue),
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)");
      THROWS_EXCEPTION(IS_LTE(value, comparisonValue, messageA, messageB), Anomaly, expectedExceptionMessage);
   }

   RUN_TEMPLATE_TESTS(IS_LTETests, int)
   THEN_RUN_TEMPLATE_TESTS(IS_LTETests, unsigned long long)
}

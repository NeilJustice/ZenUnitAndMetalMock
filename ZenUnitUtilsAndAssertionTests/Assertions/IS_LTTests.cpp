#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(IS_LTTests, T)
   AFACT(IS_LT_ValueIsLessThanComparisonValue_DoesNothing)
   AFACT(IS_LT_ValueIsEqualToComparisonValue_ThrowsAnomaly)
   AFACT(IS_LT_ValueIsGreaterThanComparisonValue_ThrowsAnomaly)
   AFACT(IS_LT_ValueIsGreaterThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(IS_LT_ValueIsLessThanComparisonValue_DoesNothing)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::min());
      const T value = ZenUnit::RandomLessThan<T>(comparisonValue);
      IS_LT(value, comparisonValue);
   }

   TEST(IS_LT_ValueIsEqualToComparisonValue_ThrowsAnomaly)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::min());
      const T value = comparisonValue;
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LT(value, comparisonValue)",
"Expected: " + to_string(value),
"  Actual: " + to_string(comparisonValue),
"File.cpp(1)");
      THROWS_EXCEPTION(IS_LT(value, comparisonValue), Anomaly, expectedExceptionMessage);
   }

   TEST(IS_LT_ValueIsGreaterThanComparisonValue_ThrowsAnomaly)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::max());
      const T value = ZenUnit::RandomGreaterThan<T>(comparisonValue);
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LT(value, comparisonValue)",
"Expected: " + to_string(value),
"  Actual: " + to_string(comparisonValue),
"File.cpp(1)");
      THROWS_EXCEPTION(IS_LT(value, comparisonValue), Anomaly, expectedExceptionMessage);
   }

   TEST(IS_LT_ValueIsGreaterThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::max());
      const T value = ZenUnit::RandomGreaterThan<T>(comparisonValue);
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LT(value, comparisonValue, messageA, messageB)",
"Expected: " + to_string(value),
"  Actual: " + to_string(comparisonValue),
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)");
      THROWS_EXCEPTION(IS_LT(value, comparisonValue, messageA, messageB), Anomaly, expectedExceptionMessage);
   }

   RUN_TEMPLATE_TESTS(IS_LTTests, int)
   THEN_RUN_TEMPLATE_TESTS(IS_LTTests, unsigned long long)
}

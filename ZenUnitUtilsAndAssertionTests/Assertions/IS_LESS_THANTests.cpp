#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(IS_LESS_THANTests, T)
   AFACT(IS_LESS_THAN_ValueIsLessThanComparisonValue_DoesNothing)
   AFACT(IS_LESS_THAN_ValueIsEqualToComparisonValue_ThrowsAnomaly)
   AFACT(IS_LESS_THAN_ValueIsGreaterThanComparisonValue_ThrowsAnomaly)
   AFACT(IS_LESS_THAN_ValueIsGreaterThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(IS_LESS_THAN_ValueIsLessThanComparisonValue_DoesNothing)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::min());
      const T value = ZenUnit::RandomLessThan<T>(comparisonValue);
      IS_LESS_THAN(value, comparisonValue);
   }

   TEST(IS_LESS_THAN_ValueIsEqualToComparisonValue_ThrowsAnomaly)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::min());
      const T value = comparisonValue;
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LESS_THAN(value, comparisonValue)",
"Expected: " + to_string(value),
"  Actual: " + to_string(comparisonValue),
"File.cpp(1)");
      THROWS_EXCEPTION(IS_LESS_THAN(value, comparisonValue), Anomaly, expectedExceptionMessage);
   }

   TEST(IS_LESS_THAN_ValueIsGreaterThanComparisonValue_ThrowsAnomaly)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::max());
      const T value = ZenUnit::RandomGreaterThan<T>(comparisonValue);
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LESS_THAN(value, comparisonValue)",
"Expected: " + to_string(value),
"  Actual: " + to_string(comparisonValue),
"File.cpp(1)");
      THROWS_EXCEPTION(IS_LESS_THAN(value, comparisonValue), Anomaly, expectedExceptionMessage);
   }

   TEST(IS_LESS_THAN_ValueIsGreaterThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::max());
      const T value = ZenUnit::RandomGreaterThan<T>(comparisonValue);
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: IS_LESS_THAN(value, comparisonValue, messageA, messageB)",
"Expected: " + to_string(value),
"  Actual: " + to_string(comparisonValue),
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)");
      THROWS_EXCEPTION(IS_LESS_THAN(value, comparisonValue, messageA, messageB), Anomaly, expectedExceptionMessage);
   }

   RUN_TEMPLATE_TESTS(IS_LESS_THANTests, int)
   THEN_RUN_TEMPLATE_TESTS(IS_LESS_THANTests, unsigned long long)
}

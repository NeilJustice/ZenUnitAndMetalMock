#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(IS_GTETests, T)
   AFACT(IS_GTE_ValueIsEqualToComparisonValue_DoesNothing)
   AFACT(IS_GTE_ValueIsGreaterThanComparisonValue_DoesNothing)
   AFACT(IS_GTE_ValueIsLessThanComparisonValue_ThrowsAnomaly)
   AFACT(IS_GTE_ValueIsLessThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(IS_GTE_ValueIsEqualToComparisonValue_DoesNothing)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = comparisonValue;
      IS_GTE(value, comparisonValue);
   }

   TEST(IS_GTE_ValueIsGreaterThanComparisonValue_DoesNothing)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = ZenUnit::RandomGreaterThan<T>(comparisonValue);
      IS_GTE(value, comparisonValue);
   }

   TEST(IS_GTE_ValueIsLessThanComparisonValue_ThrowsAnomaly)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = ZenUnit::RandomLessThan<T>(comparisonValue);
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: IS_GTE(value, comparisonValue)",
         "Expected: " + to_string(value),
         "  Actual: " + to_string(comparisonValue),
         "File.cpp(1)");
      THROWS_EXCEPTION(IS_GTE(value, comparisonValue), Anomaly, expectedExceptionMessage);
   }

   TEST(IS_GTE_ValueIsLessThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = ZenUnit::RandomLessThan<T>(comparisonValue);
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: IS_GTE(value, comparisonValue, messageA, messageB)",
         "Expected: " + to_string(value),
         "  Actual: " + to_string(comparisonValue),
         " Message: \"" + messageA + "\", \"" + messageB + "\"",
         "File.cpp(1)");
      THROWS_EXCEPTION(IS_GTE(value, comparisonValue, messageA, messageB), Anomaly, expectedExceptionMessage);
   }

   RUN_TEMPLATE_TESTS(IS_GTETests, int)
   THEN_RUN_TEMPLATE_TESTS(IS_GTETests, unsigned long long)
}

#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(IS_GREATER_THAN_OR_EQUALTests, T)
   AFACT(IS_GREATER_THAN_OR_EQUAL_ValueIsEqualToComparisonValue_DoesNothing)
   AFACT(IS_GREATER_THAN_OR_EQUAL_ValueIsGreaterThanComparisonValue_DoesNothing)
   AFACT(IS_GREATER_THAN_OR_EQUAL_ValueIsLessThanComparisonValue_ThrowsAnomaly)
   AFACT(IS_GREATER_THAN_OR_EQUAL_ValueIsLessThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(IS_GREATER_THAN_OR_EQUAL_ValueIsEqualToComparisonValue_DoesNothing)
   {
      const T comparisonValue = ZenUnit::Random<T>();
      const T value = comparisonValue;
      IS_GREATER_THAN_OR_EQUAL(value, comparisonValue);
   }

   TEST(IS_GREATER_THAN_OR_EQUAL_ValueIsGreaterThanComparisonValue_DoesNothing)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::max());
      const T value = ZenUnit::RandomGreaterThan<T>(comparisonValue);
      IS_GREATER_THAN_OR_EQUAL(value, comparisonValue);
   }

   TEST(IS_GREATER_THAN_OR_EQUAL_ValueIsLessThanComparisonValue_ThrowsAnomaly)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::min());
      const T value = ZenUnit::RandomLessThan<T>(comparisonValue);
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: IS_GREATER_THAN_OR_EQUAL(value, comparisonValue)",
         "Expected: " + to_string(value),
         "  Actual: " + to_string(comparisonValue),
         "File.cpp(1)");
      THROWS_EXCEPTION(IS_GREATER_THAN_OR_EQUAL(value, comparisonValue), Anomaly, expectedExceptionMessage);
   }

   TEST(IS_GREATER_THAN_OR_EQUAL_ValueIsLessThanComparisonValue_ThrowsAnomaly__MessagesTestCase)
   {
      const T comparisonValue = ZenUnit::RandomNotEqualToValue<T>(numeric_limits<T>::min());
      const T value = ZenUnit::RandomLessThan<T>(comparisonValue);
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: IS_GREATER_THAN_OR_EQUAL(value, comparisonValue, messageA, messageB)",
         "Expected: " + to_string(value),
         "  Actual: " + to_string(comparisonValue),
         " Message: \"" + messageA + "\", \"" + messageB + "\"",
         "File.cpp(1)");
      THROWS_EXCEPTION(IS_GREATER_THAN_OR_EQUAL(value, comparisonValue, messageA, messageB), Anomaly, expectedExceptionMessage);
   }

   RUN_TEMPLATE_TESTS(IS_GREATER_THAN_OR_EQUALTests, int)
   THEN_RUN_TEMPLATE_TESTS(IS_GREATER_THAN_OR_EQUALTests, unsigned long long)
}

#include "pch.h"

namespace ZenUnit
{
   template<typename EnumUnderlyingType>
   TEMPLATE_TESTS(ENUM_EQUALS_INTTests, EnumUnderlyingType)
   AFACT(EnumClassEqualsInteger_DoesNotThrowException)
   AFACT(EnumClassDoesNotEqualInteger_ThrowsAnomaly)
   AFACT(EnumClassDoesNotEqualInteger_ThrowsAnomaly__MessagesTestCase)
   AFACT(ClassicEnumEqualsInteger_DoesNotThrowException)
   AFACT(ClassicEnumDoesNotEqualInteger_ThrowsAnomaly)
   AFACT(ClassicEnumDoesNotEqualInteger_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   enum class EnumClass : EnumUnderlyingType
   {
      Zero,
      One,
      Two,
      Three
   };

   TEST(EnumClassEqualsInteger_DoesNotThrowException)
   {
      ENUM_EQUALS_INT(0, EnumClass::Zero);
      ENUM_EQUALS_INT(1, EnumClass::One);
      ENUM_EQUALS_INT(2, EnumClass::Two);
      ENUM_EQUALS_INT(3, EnumClass::Three);
   }

   TEST(EnumClassDoesNotEqualInteger_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(ENUM_EQUALS_INT(1, EnumClass::Zero),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ENUM_EQUALS_INT(1, EnumClass::Zero)",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)"));

      THROWS_EXCEPTION(ENUM_EQUALS_INT(3, EnumClass::One),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ENUM_EQUALS_INT(3, EnumClass::One)",
"Expected: 3",
"  Actual: 1",
"File.cpp(1)"));
   }

   TEST(EnumClassDoesNotEqualInteger_ThrowsAnomaly__MessagesTestCase)
   {
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS_EXCEPTION(ENUM_EQUALS_INT(0, EnumClass::Three, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ENUM_EQUALS_INT(0, EnumClass::Three, messageA, messageB)",
"Expected: 0",
"  Actual: 3",
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   enum ClassicEnum // NOLINT
   {
      Zero,
      One,
      Two,
      Three
   };

   TEST(ClassicEnumEqualsInteger_DoesNotThrowException)
   {
      ENUM_EQUALS_INT(0, ClassicEnum::Zero);
      ENUM_EQUALS_INT(1, ClassicEnum::One);
      ENUM_EQUALS_INT(2, ClassicEnum::Two);
      ENUM_EQUALS_INT(3, ClassicEnum::Three);
   }

   TEST(ClassicEnumDoesNotEqualInteger_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(ENUM_EQUALS_INT(1, ClassicEnum::Zero),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ENUM_EQUALS_INT(1, ClassicEnum::Zero)",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)"));

      THROWS_EXCEPTION(ENUM_EQUALS_INT(3, ClassicEnum::One),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ENUM_EQUALS_INT(3, ClassicEnum::One)",
"Expected: 3",
"  Actual: 1",
"File.cpp(1)"));
   }

   TEST(ClassicEnumDoesNotEqualInteger_ThrowsAnomaly__MessagesTestCase)
   {
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS_EXCEPTION(ENUM_EQUALS_INT(0, ClassicEnum::Three, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ENUM_EQUALS_INT(0, ClassicEnum::Three, messageA, messageB)",
"Expected: 0",
"  Actual: 3",
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   RUN_TEMPLATE_TESTS(ENUM_EQUALS_INTTests, char)
   THEN_RUN_TEMPLATE_TESTS(ENUM_EQUALS_INTTests, unsigned char)
   THEN_RUN_TEMPLATE_TESTS(ENUM_EQUALS_INTTests, int)
   THEN_RUN_TEMPLATE_TESTS(ENUM_EQUALS_INTTests, unsigned)
   THEN_RUN_TEMPLATE_TESTS(ENUM_EQUALS_INTTests, long long)
   THEN_RUN_TEMPLATE_TESTS(ENUM_EQUALS_INTTests, unsigned long long)
}

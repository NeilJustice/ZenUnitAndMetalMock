#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_DEFAULT_VALUETests)
   AFACT(ValueIsDefaultValue_DoesNotThrowAnomaly)
   FACTS(IntIsNotZero_ThrowsAnomaly)
   FACTS(DoubleIsNotZero_ThrowsAnomaly)
   AFACT(UserTypeOnlyZenUnitEqualizableIsZero_DoesNotThrowAnomaly)
   AFACT(UserTypeOnlyZenUnitEqualizableIsNotZero_ThrowsAnomaly)
   AFACT(UserTypeIsZero_DoesNotThrowAnomaly)
   AFACT(UserTypeIsNotZero_ThrowsAnomaly)
   AFACT(UserTypeIsNotZero_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(ValueIsDefaultValue_DoesNotThrowAnomaly)
   {
      IS_DEFAULT_VALUE(0);

      int nonConstIntValue = 0;
      IS_DEFAULT_VALUE(nonConstIntValue);

      const int constIntValue = 0;
      IS_DEFAULT_VALUE(constIntValue);

      const int* const nullIntPointer = nullptr;
      IS_DEFAULT_VALUE(nullIntPointer);

      IS_DEFAULT_VALUE(0.0f);
      const float floatZero = 0.0f;
      IS_DEFAULT_VALUE(floatZero);

      IS_DEFAULT_VALUE(0.0);
      const double doubleZero = 0.0;
      IS_DEFAULT_VALUE(doubleZero);

      const string defaultString;
      IS_DEFAULT_VALUE(defaultString);

      const vector<int> defaultVector;
      IS_DEFAULT_VALUE(defaultVector);

      const UserType defaultUserType;
      IS_DEFAULT_VALUE(defaultUserType);
   }

   TEST1X1(IntIsNotZero_ThrowsAnomaly,
      int value,
      -1,
      1)
   {
      THROWS_EXCEPTION(IS_DEFAULT_VALUE(value), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_DEFAULT_VALUE(value)",
"Expected: 0",
"  Actual: " + to_string(value),
"File.cpp(1)"));
   }

   TEST2X2(DoubleIsNotZero_ThrowsAnomaly,
      double value, const string& expectedValueAsString,
      -1.0, "-1",
      1.0, "1")
   {
      THROWS_EXCEPTION(IS_DEFAULT_VALUE(value), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_DEFAULT_VALUE(value)",
"Expected: 0",
"  Actual: " + expectedValueAsString,
"File.cpp(1)"));
   }

   TEST(UserTypeOnlyZenUnitEqualizableIsZero_DoesNotThrowAnomaly)
   {
      const OnlyZenUnitEqualizerUserType defaultUserTypeOnlyZenUnitEqualizable;
      IS_DEFAULT_VALUE(defaultUserTypeOnlyZenUnitEqualizable);
   }

   TEST(UserTypeOnlyZenUnitEqualizableIsNotZero_ThrowsAnomaly)
   {
      const OnlyZenUnitEqualizerUserType userTypeOnlyZenUnitEqualizable1{1};
      THROWS_EXCEPTION(IS_DEFAULT_VALUE(userTypeOnlyZenUnitEqualizable1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_DEFAULT_VALUE(userTypeOnlyZenUnitEqualizable1)",
"Expected: OnlyZenUnitEqualizerUserType@0",
"  Actual: OnlyZenUnitEqualizerUserType@1",
"File.cpp(1)"));
   }

   TEST(UserTypeIsZero_DoesNotThrowAnomaly)
   {
      const UserType userType0(0);
      IS_DEFAULT_VALUE(userType0);
   }

   TEST(UserTypeIsNotZero_ThrowsAnomaly)
   {
      const UserType userType1{1};
      THROWS_EXCEPTION(IS_DEFAULT_VALUE(userType1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_DEFAULT_VALUE(userType1)",
"Expected: UserType@0",
"  Actual: UserType@1",
"File.cpp(1)"));
   }

   TEST(UserTypeIsNotZero_ThrowsAnomaly__MessagesTestCase)
   {
      const UserType userType10(10);
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_DEFAULT_VALUE(userType10, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_DEFAULT_VALUE(userType10, messageA, messageB)",
"Expected: UserType@0",
"  Actual: UserType@10",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_DEFAULT_VALUETests)
}

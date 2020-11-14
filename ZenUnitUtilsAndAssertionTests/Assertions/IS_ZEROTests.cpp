#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_ZEROTests)
   AFACT(ValueIsZero_DoesNotThrowException)
   FACTS(IntNotZero_ThrowsAnomaly)
   FACTS(DoubleNotZero_ThrowsAnomaly)
   AFACT(UserTypeZero_DoesNotThrowException)
   AFACT(UserTypeNotZero_ThrowsAnomaly__MessagesTestCase)
   AFACT(IntializerConstructable_IsZero_DoesNotThrowException)
   AFACT(IntializerConstructable_IsNotZero_ThrowsAnomaly)
   EVIDENCE

   struct IntializerConstructable
   {
      int value;

      friend bool operator==(
         const IntializerConstructable& lhs,
         const IntializerConstructable& rhs)
      {
         return lhs.value == rhs.value;
      }

      friend ostream& operator<<(ostream& os, const IntializerConstructable& right)
      {
         os << "InitializerConstructable@" << right.value;
         return os;
      }
   };

   TEST(ValueIsZero_DoesNotThrowException)
   {
      IS_ZERO(0);

      int nonConstIntValue = 0;
      IS_ZERO(nonConstIntValue);

      const int constIntValue = 0;
      IS_ZERO(constIntValue);

      const int* const nullIntPointer = nullptr;
      IS_ZERO(nullIntPointer);

      IS_ZERO(0.0f);
      const float floatZero = 0.0f;
      IS_ZERO(floatZero);

      IS_ZERO(0.0);
      const double doubleZero = 0.0;
      IS_ZERO(doubleZero);
   }

   TEST1X1(IntNotZero_ThrowsAnomaly,
      int value,
      -1,
      1)
   {
      THROWS_EXCEPTION(IS_ZERO(value), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_ZERO(value)",
"Expected: 0",
"  Actual: " + to_string(value),
"File.cpp(1)"));
   }

   TEST1X1(DoubleNotZero_ThrowsAnomaly,
      double value,
      -1.0,
      1.0)
   {
      THROWS_EXCEPTION(IS_ZERO(value), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_ZERO(value)",
"Expected: 0.000000",
"  Actual: " + to_string(value),
"File.cpp(1)"));
   }

   TEST(UserTypeZero_DoesNotThrowException)
   {
      const UserType userType0(0);
      IS_ZERO(userType0);
   }

   TEST(UserTypeNotZero_ThrowsAnomaly__MessagesTestCase)
   {
      const UserType userType1(1);
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_ZERO(userType1, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_ZERO(userType1, messageA, messageB)",
"Expected: UserType@0",
"  Actual: UserType@1",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   TEST(IntializerConstructable_IsZero_DoesNotThrowException)
   {
      const IntializerConstructable i { 0 };
      IS_ZERO(i);
   }

   TEST(IntializerConstructable_IsNotZero_ThrowsAnomaly)
   {
      const IntializerConstructable i { 1 };
      THROWS_EXCEPTION(IS_ZERO(i), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_ZERO(i)",
"Expected: InitializerConstructable@0",
"  Actual: InitializerConstructable@1",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_ZEROTests)
}

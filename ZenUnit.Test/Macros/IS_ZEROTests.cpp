#include "pch.h"
#include "ZenUnit/Macros/IS_ZERO.h"

namespace ZenUnit
{
   TESTS(IS_ZEROTests)
   SPEC(ValueIsZero_DoesNotThrow)
   SPECX(IntNotZero_Throws)
   SPECX(DoubleNotZero_Throws)
   SPEC(UserTypeZero_DoesNotThrow)
   SPEC(UserTypeNotZero_Throws_MessagesTestCase)
   SPEC(IntializerConstructable_IsZero_DoesNotThrow)
   SPEC(IntializerConstructable_IsNotZero_Throws)
   SPECEND

   struct IntializerConstructable
   {
      const int value;

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

   TEST(ValueIsZero_DoesNotThrow)
   {
      IS_ZERO(0);
      const int intValue = 0;
      IS_ZERO(intValue);

      IS_ZERO(reinterpret_cast<int*>(0));
      const int* const nullIntPointer = nullptr;
      IS_ZERO(nullIntPointer);

      IS_ZERO(0.0f);
      const float floatZero = 0.0f;
      IS_ZERO(floatZero);

      IS_ZERO(0.0);
      const double doubleZero = 0.0;
      IS_ZERO(doubleZero);
   }

   TEST1X1(IntNotZero_Throws,
      int value,
      -1,
      1)
   {
      THROWS(IS_ZERO(value), Anomaly, R"(
  Failed: IS_ZERO(value)
Expected: 0
  Actual: )" + to_string(value) + R"(
File.cpp(1))");
   }

   TEST1X1(DoubleNotZero_Throws,
      double value,
      -1.0,
      1.0)
   {
      THROWS(IS_ZERO(value), Anomaly, R"(
  Failed: IS_ZERO(value)
Expected: 0.000000
  Actual: )" + to_string(value) + R"(
File.cpp(1))");
   }

   TEST(UserTypeZero_DoesNotThrow)
   {
      const UserType userType0(0);
      IS_ZERO(userType0);
   }

   TEST(UserTypeNotZero_Throws_MessagesTestCase)
   {
      const UserType userType1(1);
      const string messageA = "A", messageB = "B";
      THROWS(IS_ZERO(userType1, messageA, messageB), Anomaly, R"(
  Failed: IS_ZERO(userType1, messageA, messageB)
Expected: UserType@0
  Actual: UserType@1
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(IntializerConstructable_IsZero_DoesNotThrow)
   {
      const IntializerConstructable i { 0 };
      IS_ZERO(i);
   }

   TEST(IntializerConstructable_IsNotZero_Throws)
   {
      const IntializerConstructable i { 1 };
      THROWS(IS_ZERO(i), Anomaly, R"(
  Failed: IS_ZERO(i)
Expected: InitializerConstructable@0
  Actual: InitializerConstructable@1
File.cpp(1))");
   }

   }; RUN(IS_ZEROTests)
}

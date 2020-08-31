#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_NOT_DEFAULT_VALUETests)
   AFACT(ValueIsNotDefault_DoesNotThrowException)
   AFACT(IntIsZero_Throws)
   AFACT(DoubleIsZero_Throws)
   AFACT(FloatIsZero_Throws)
   AFACT(StringIsEmptyString_Throws)
   AFACT(IntVectorIsEmpty_Throws)
   AFACT(UserTypeIsDefault_Throws)
   EVIDENCE

   struct IntializerConstructable
   {
      int value;

      friend bool operator==(const IntializerConstructable& lhs, const IntializerConstructable& rhs)
      {
         return lhs.value == rhs.value;
      }

      friend ostream& operator<<(ostream& os, const IntializerConstructable& right)
      {
         os << "InitializerConstructable@" << right.value;
         return os;
      }
   };

   TEST(ValueIsNotDefault_DoesNotThrowException)
   {
      IS_NOT_DEFAULT_VALUE(-1);
      IS_NOT_DEFAULT_VALUE(1);

      IS_NOT_DEFAULT_VALUE(-1.1);
      IS_NOT_DEFAULT_VALUE(1.1);

      IS_NOT_DEFAULT_VALUE(-1.1f);
      IS_NOT_DEFAULT_VALUE(1.1f);

      int nonConstInt = 1;
      IS_NOT_DEFAULT_VALUE(nonConstInt);

      const int constInt = 1;
      IS_NOT_DEFAULT_VALUE(constInt);

      const int* nonNullNonConstIntPointer = reinterpret_cast<int*>(1);
      IS_NOT_DEFAULT_VALUE(nonNullNonConstIntPointer);

      const int* const nonNullConstIntPointer = reinterpret_cast<int*>(1);
      IS_NOT_DEFAULT_VALUE(nonNullConstIntPointer);

      const string nonDefaultString = ZenUnit::Random<string>();
      IS_NOT_DEFAULT_VALUE(nonDefaultString);

      const vector<int> nonDefaultVector = { 1, 2, 3 };
      IS_NOT_DEFAULT_VALUE(nonDefaultVector);

      const UserType nonDefaultUserType(1);
      IS_NOT_DEFAULT_VALUE(nonDefaultUserType);
   }

   TEST(IntIsZero_Throws)
   {
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(0)",
"Expected: Not T{}",
"  Actual: 0",
"File.cpp(1)"));
   }

   TEST(DoubleIsZero_Throws)
   {
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(0.0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(0.0)",
"Expected: Not T{}",
"  Actual: 0.000000",
"File.cpp(1)"));
   }

   TEST(FloatIsZero_Throws)
   {
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(0.0f), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(0.0f)",
"Expected: Not T{}",
"  Actual: 0.000000f",
"File.cpp(1)"));
   }

   TEST(StringIsEmptyString_Throws)
   {
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(""s), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(\"\"s)",
"Expected: Not T{}",
"  Actual: \"\"",
"File.cpp(1)"));
   }

   TEST(IntVectorIsEmpty_Throws)
   {
      const vector<int> defaultIntVector;
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(defaultIntVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(defaultIntVector)",
"Expected: Not T{}",
"  Actual: std::vector<int> (size 0):",
"{",
"}",
"File.cpp(1)"));
   }

   TEST(UserTypeIsDefault_Throws)
   {
      const UserType defaultUserType;
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(defaultUserType), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(defaultUserType)",
"Expected: Not T{}",
"  Actual: UserType@0",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_NOT_DEFAULT_VALUETests)
}

#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_NOT_DEFAULTTests)
   AFACT(ValueIsNotDefault_DoesNotThrow)
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

   TEST(ValueIsNotDefault_DoesNotThrow)
   {
      IS_NOT_DEFAULT(-1);
      IS_NOT_DEFAULT(1);

      IS_NOT_DEFAULT(-1.1);
      IS_NOT_DEFAULT(1.1);

      IS_NOT_DEFAULT(-1.1f);
      IS_NOT_DEFAULT(1.1f);

      int nonConstInt = 1;
      IS_NOT_DEFAULT(nonConstInt);

      const int constInt = 1;
      IS_NOT_DEFAULT(constInt);

      const int* nonNullNonConstIntPointer = reinterpret_cast<int*>(1);
      IS_NOT_DEFAULT(nonNullNonConstIntPointer);

      const int* const nonNullConstIntPointer = reinterpret_cast<int*>(1);
      IS_NOT_DEFAULT(nonNullConstIntPointer);

      const string nonDefaultString = ZenUnit::Random<string>();
      IS_NOT_DEFAULT(nonDefaultString);

      const vector<int> nonDefaultVector = { 1, 2, 3 };
      IS_NOT_DEFAULT(nonDefaultVector);

      const UserType nonDefaultUserType(1);
      IS_NOT_DEFAULT(nonDefaultUserType);
   }

   TEST(IntIsZero_Throws)
   {
      THROWS(IS_NOT_DEFAULT(0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT(0)",
"Expected: Not T{}",
"  Actual: 0",
"File.cpp(1)"));
   }

   TEST(DoubleIsZero_Throws)
   {
      THROWS(IS_NOT_DEFAULT(0.0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT(0.0)",
"Expected: Not T{}",
"  Actual: 0.000000",
"File.cpp(1)"));
   }

   TEST(FloatIsZero_Throws)
   {
      THROWS(IS_NOT_DEFAULT(0.0f), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT(0.0f)",
"Expected: Not T{}",
"  Actual: 0.000000f",
"File.cpp(1)"));
   }

   TEST(StringIsEmptyString_Throws)
   {
      THROWS(IS_NOT_DEFAULT(""s), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT(\"\"s)",
"Expected: Not T{}",
"  Actual: \"\"",
"File.cpp(1)"));
   }

   TEST(IntVectorIsEmpty_Throws)
   {
      const vector<int> defaultIntVector;
      THROWS(IS_NOT_DEFAULT(defaultIntVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT(defaultIntVector)",
"Expected: Not T{}",
"  Actual: std::vector<int> (size 0):",
"{",
"}",
"File.cpp(1)"));
   }

   TEST(UserTypeIsDefault_Throws)
   {
      const UserType defaultUserType;
      THROWS(IS_NOT_DEFAULT(defaultUserType), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT(defaultUserType)",
"Expected: Not T{}",
"  Actual: UserType@0",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_NOT_DEFAULTTests)
}

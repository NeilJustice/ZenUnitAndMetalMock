#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_NOT_DEFAULT_VALUETests)
   AFACT(ValueIsNotDefaultValue_DoesNotThrowAnomaly)
   AFACT(IntIsZero_ThrowsAnomaly)
   AFACT(FloatIsZero_ThrowsAnomaly)
   AFACT(DoubleIsZero_ThrowsAnomaly)
   AFACT(StringIsEmptyString_ThrowsAnomaly)
   AFACT(IntVectorIsEmpty_ThrowsAnomaly)
   AFACT(UserTypeIsDefaultValue_ThrowsAnomaly)
   AFACT(UserTypeIsDefaultValue_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(ValueIsNotDefaultValue_DoesNotThrowAnomaly)
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

   TEST(IntIsZero_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(0)",
"Expected: Not T{}",
"  Actual: 0",
"File.cpp(1)"));
   }

   TEST(FloatIsZero_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(0.0f), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(0.0f)",
"Expected: Not T{}",
"  Actual: 0",
"File.cpp(1)"));
   }

   TEST(DoubleIsZero_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(0.0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(0.0)",
"Expected: Not T{}",
"  Actual: 0",
"File.cpp(1)"));
   }

   TEST(StringIsEmptyString_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(""s), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(\"\"s)",
"Expected: Not T{}",
"  Actual: \"\"",
"File.cpp(1)"));
   }

   TEST(IntVectorIsEmpty_ThrowsAnomaly)
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

   TEST(UserTypeIsDefaultValue_ThrowsAnomaly)
   {
      const UserType defaultUserType;
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(defaultUserType), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(defaultUserType)",
"Expected: Not T{}",
"  Actual: UserType@0",
"File.cpp(1)"));
   }

   TEST(UserTypeIsDefaultValue_ThrowsAnomaly__MessagesTestCase)
   {
      const UserType defaultUserType;
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_NOT_DEFAULT_VALUE(defaultUserType, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_DEFAULT_VALUE(defaultUserType, messageA, messageB)",
"Expected: Not T{}",
"  Actual: UserType@0",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_NOT_DEFAULT_VALUETests)
}

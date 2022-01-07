#include "pch.h"

namespace ZenUnit
{
   TESTS(FIELDS_ARE_EQUALTests)
   AFACT(FieldAreEqual_DoesNotThrowException)
   AFACT(IntFieldsAreNotEqual_ThrowsZenUnitAnomaly)
   AFACT(UserTypeFieldsAreNotEqual_ThrowsZenUnitAnomaly)
   AFACT(StringFieldsAreNotEqual_ThrowsZenUnitAnomaly__MessagesTestCase)
   EVIDENCE

   struct Struct
   {
      int intField = 0;
      string stringField;
      UserType userType;
   };

   TEST(FieldAreEqual_DoesNotThrowException)
   {
      Struct expectedStruct;
      Struct actualStruct;
      FIELDS_ARE_EQUAL(expectedStruct, actualStruct, intField);
   }

   TEST(IntFieldsAreNotEqual_ThrowsZenUnitAnomaly)
   {
      Struct expectedStruct;
      expectedStruct.intField = ZenUnit::Random<int>();
      Struct actualStruct;
      actualStruct.intField = ZenUnit::RandomNotEqualTo(expectedStruct.intField);
      THROWS_EXCEPTION(FIELDS_ARE_EQUAL(expectedStruct, actualStruct, intField), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: ARE_EQUAL(expectedStruct.intField, actualStruct.intField)",
         "Expected: " + to_string(expectedStruct.intField),
         "  Actual: " + to_string(actualStruct.intField),
         "File.cpp(1)"));
   }

   TEST(UserTypeFieldsAreNotEqual_ThrowsZenUnitAnomaly)
   {
      Struct expected;
      expected.userType = UserType(10);
      Struct actual;
      actual.userType = UserType(20);
      THROWS_EXCEPTION(FIELDS_ARE_EQUAL(expected, actual, userType), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: ARE_EQUAL(expected.userType, actual.userType)",
         "Expected: UserType@10",
         "  Actual: UserType@20",
         " Because: ARE_EQUAL(expectedUserType.value, actualUserType.value) failed",
         "Expected: 10",
         "  Actual: 20",
         "File.cpp(1)",
         "File.cpp(1)"));
   }

   TEST(StringFieldsAreNotEqual_ThrowsZenUnitAnomaly__MessagesTestCase)
   {
      Struct expected;
      expected.stringField = ZenUnit::Random<string>();
      Struct actual;
      actual.stringField = ZenUnit::RandomNotEqualTo(expected.stringField);
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS_EXCEPTION(FIELDS_ARE_EQUAL(expected, actual, stringField, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: ARE_EQUAL(expected.stringField, actual.stringField, messageA, messageB)",
         "Expected: \"" + expected.stringField + "\"",
         "  Actual: \"" + actual.stringField + "\"",
         " Message: \"" + messageA + "\", \"" + messageB + "\"",
         "File.cpp(1)"));
   }

   RUN_TESTS(FIELDS_ARE_EQUALTests)
}

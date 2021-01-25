#include "pch.h"

namespace ZenUnit
{
   TESTS(FIELDS_ARE_EQUALTests)
   AFACT(FieldAreEqual_DoesNotThrowException)
   AFACT(IntFieldsAreNotEqual_ThrowsZenUnitAnomaly)
   AFACT(StringFieldsAreNotEqual_ThrowsZenUnitAnomaly__MessagesTestCase)
   EVIDENCE

   struct Struct
   {
      int intField = 0;
      string stringField;
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
      actualStruct.intField = ZenUnit::RandomNotEqualToValue(expectedStruct.intField);
      THROWS_EXCEPTION(FIELDS_ARE_EQUAL(expectedStruct, actualStruct, intField), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: ARE_EQUAL(expectedStruct.intField, actualStruct.intField)",
         "Expected: " + to_string(expectedStruct.intField),
         "  Actual: " + to_string(actualStruct.intField),
         "File.cpp(1)"));
   }

   TEST(StringFieldsAreNotEqual_ThrowsZenUnitAnomaly__MessagesTestCase)
   {
      Struct expected;
      expected.stringField = ZenUnit::Random<string>();
      Struct actual;
      actual.stringField = ZenUnit::RandomNotEqualToValue(expected.stringField);
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

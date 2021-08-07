#include "pch.h"

namespace Namespace
{
   struct TestStruct
   {
      int fieldA;
      int fieldB;

      TestStruct() noexcept
         : fieldA(0)
         , fieldB(0)
      {
      }
   };
}

namespace ZenUnit
{
   template<>
   class Equalizer<Namespace::TestStruct>
   {
   public:
      static void AssertEqual(const Namespace::TestStruct& expected, const Namespace::TestStruct& actual)
      {
         ARE_EQUAL(expected.fieldA, actual.fieldA);
         // Purposeful absence of line ARE_EQUAL(expected.fieldB, actual.fieldB);
      }
   };
}

struct TestStructB
{
   int field;
   TestStructB() noexcept : field(0) {}
   static const int ThrowWithoutFieldNameInWhatText;
   static const int ThrowWithFieldNameInWhatText;
};

const int TestStructB::ThrowWithoutFieldNameInWhatText = 1;
const int TestStructB::ThrowWithFieldNameInWhatText = 2;

namespace ZenUnit
{
   template<>
   class Equalizer<TestStructB>
   {
   public:
      static void AssertEqual(const TestStructB& expected, const TestStructB&)
      {
         if (expected.field == TestStructB::ThrowWithoutFieldNameInWhatText)
         {
            throw Anomaly();
         }
         if (expected.field == TestStructB::ThrowWithFieldNameInWhatText)
         {
            Anomaly anomaly;
            anomaly.expectedValueAsStringOrExpectedLine = "field";
            throw anomaly;
         }
      }
   };

   TESTS(ZENUNIT_EQUALIZER_THROWSTests)
   AFACT(EqualizerDoesNotAssertSpecifiedFieldEqual_ThrowsAnomaly)
   AFACT(EqualizerThrowsAnomalyThatDoesNotContainFieldName_ThrowsAnomaly)
   AFACT(EqualizerThrowsAnomalyThatContainsFieldName_ButStillThrowsThatAnomalyWhenAllFieldsEqual_ThrowsAnomaly)
   AFACT(EqualizerAssertsSpecifiedFieldEqual_DoesNotThrowException)
   EVIDENCE

   TEST(EqualizerDoesNotAssertSpecifiedFieldEqual_ThrowsAnomaly)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Namespace::TestStruct);
      THROWS_EXCEPTION(ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Namespace::TestStruct, fieldB, 1),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Namespace::TestStruct, fieldB, 1)",
"Expected: Function ZenUnit::Equalizer<Namespace::TestStruct>::AssertEqual(expected, actual)",
"          to throw a ZenUnit::Anomaly from an",
"          ARE_EQUAL(expected.fieldB, actual.fieldB) assert statement.",
"  Actual: No ZenUnit::Anomaly was thrown despite field 'fieldB'",
"          differing between the expected and actual objects.",
"File.cpp(1)"));
   }

   TEST(EqualizerThrowsAnomalyThatDoesNotContainFieldName_ThrowsAnomaly)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(TestStructB);
      THROWS_EXCEPTION(ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestStructB, field, TestStructB::ThrowWithoutFieldNameInWhatText),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestStructB, field, TestStructB::ThrowWithoutFieldNameInWhatText)",
"Expected: N/A",
"  Actual: N/A",
" Because: IS_TRUE(String::Contains(anomalyExceptionMessage, fieldName)) failed",
"Expected: true",
"  Actual: false",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(EqualizerThrowsAnomalyThatContainsFieldName_ButStillThrowsThatAnomalyWhenAllFieldsEqual_ThrowsAnomaly)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(TestStructB);
      THROWS_EXCEPTION(ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestStructB, field, TestStructB::ThrowWithFieldNameInWhatText),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestStructB, field, TestStructB::ThrowWithFieldNameInWhatText)",
"Expected: N/A",
"  Actual: N/A",
" Because: ARE_EQUAL(expectedZenUnitEqualizerTestObject, actualZenUnitEqualizerTestObject) failed",
"Expected: <TestStructB>",
"  Actual: <TestStructB>",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(EqualizerAssertsSpecifiedFieldEqual_DoesNotThrowException)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Namespace::TestStruct);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Namespace::TestStruct, fieldA, ZenUnit::RandomNon0<int>());
   }

   RUN_TESTS(ZENUNIT_EQUALIZER_THROWSTests)
}

#include "pch.h"
#include "ZenUnit/Macros/EQUALIZER_THROWS.h"

namespace Namespace
{
   struct TestStruct
   {
      int fieldA;
      int fieldB;
      TestStruct() : fieldA(0), fieldB(0) {}
   };
}

template<>
struct ZenUnitEqualizer<Namespace::TestStruct>
{
   static void AssertEqual(const Namespace::TestStruct& expected, const Namespace::TestStruct& actual)
   {
      ARE_EQUAL(expected.fieldA, actual.fieldA);
      // Absence of line ARE_EQUAL(expected.fieldB, actual.fieldB);
   }
};

struct TestStructB
{
   int field;
   TestStructB() : field(0) {}
   static const int ThrowWithoutFieldNameInWhatText;
   static const int ThrowWithFieldNameInWhatText;
};

const int TestStructB::ThrowWithoutFieldNameInWhatText = 1;
const int TestStructB::ThrowWithFieldNameInWhatText = 2;

template<>
struct ZenUnitEqualizer<TestStructB>
{
   static void AssertEqual(const TestStructB& expected, const TestStructB&)
   {
      if (expected.field == TestStructB::ThrowWithoutFieldNameInWhatText)
      {
         throw Anomaly();
      }
      if (expected.field == TestStructB::ThrowWithFieldNameInWhatText)
      {
         Anomaly anomaly;
         anomaly.expected = "field";
         throw anomaly;
      }
   }
};

namespace ZenUnit
{
   TESTS(EQUALIZER_THROWSTests)
   FACT(EqualizerDoesNotAssertSpecifiedFieldEqual_Throws)
   FACT(EqualizerThrowsAnomalyThatDoesNotContainFieldName_Throws)
   FACT(EqualizerThrowsAnomalyThatContainsFieldName_ButStillThrowsThatAnomalyWhenAllFieldsEqual_Throws)
   FACT(EqualizerAssertsSpecifiedFieldEqual_DoesNotThrow)
   EVIDENCE

   TEST(EqualizerDoesNotAssertSpecifiedFieldEqual_Throws)
   {
      EQUALIZER_THROWS_INIT(Namespace::TestStruct);
      THROWS(EQUALIZER_THROWS(Namespace::TestStruct, fieldB, 1), Anomaly, R"(
  Failed: EQUALIZER_THROWS(Namespace::TestStruct, fieldB, 1)
Expected: Function ZenUnitEqualizer<Namespace::TestStruct>::AssertEqual(expected, actual)
          to throw a ZenUnit::Anomaly from an
          ARE_EQUAL(expected.fieldB, actual.fieldB) assert statement.
  Actual: No ZenUnit::Anomaly thrown despite field 'fieldB'
          differing between objects expected and actual.
File.cpp(1))");
   }

   TEST(EqualizerThrowsAnomalyThatDoesNotContainFieldName_Throws)
   {
      EQUALIZER_THROWS_INIT(TestStructB);
      THROWS(EQUALIZER_THROWS(TestStructB, field, TestStructB::ThrowWithoutFieldNameInWhatText), Anomaly, R"(
  Failed: EQUALIZER_THROWS(TestStructB, field, TestStructB::ThrowWithoutFieldNameInWhatText)
Expected: N/A
  Actual: N/A
 Because: IS_TRUE(String::Contains(anomalyWhat, fieldName)) failed
Expected: true
  Actual: false
File.cpp(1)
File.cpp(1))");
   }

   TEST(EqualizerThrowsAnomalyThatContainsFieldName_ButStillThrowsThatAnomalyWhenAllFieldsEqual_Throws)
   {
      EQUALIZER_THROWS_INIT(TestStructB);
      THROWS(EQUALIZER_THROWS(TestStructB, field, TestStructB::ThrowWithFieldNameInWhatText), Anomaly, R"(
  Failed: EQUALIZER_THROWS(TestStructB, field, TestStructB::ThrowWithFieldNameInWhatText)
Expected: N/A
  Actual: N/A
 Because: ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB) failed
Expected: <TestStructB>
  Actual: <TestStructB>
File.cpp(1)
File.cpp(1))");
   }

   TEST(EqualizerAssertsSpecifiedFieldEqual_DoesNotThrow)
   {
      EQUALIZER_THROWS_INIT(Namespace::TestStruct);
      EQUALIZER_THROWS(Namespace::TestStruct, fieldA, 1);
   }

   RUNTESTS(EQUALIZER_THROWSTests)
}

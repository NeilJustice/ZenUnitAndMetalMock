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
   static const int ThrowWithoutFieldName;
   static const int ThrowWithFieldName;
};

const int TestStructB::ThrowWithoutFieldName = 1;
const int TestStructB::ThrowWithFieldName = 2;

template<>
struct ZenUnitEqualizer<TestStructB>
{
   static void AssertEqual(const TestStructB& expected, const TestStructB&)
   {
      if (expected.field == TestStructB::ThrowWithoutFieldName)
      {
         throw Anomaly();
      }
      if (expected.field == TestStructB::ThrowWithFieldName)
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
   SPEC(EqualizerDoesNotAssertSpecifiedFieldEqual_Throws)
   SPEC(EqualizerThrowsAnomalyThatDoesNotContainFieldName_Throws)
   SPEC(EqualizerThrowsAnomalyThatContainsFieldName_ButStillThrowsThatAnomalyWhenAllFieldsEqual_Throws)
   SPEC(EqualizerAssertsSpecifiedFieldEqual_DoesNotThrow)
   SPECEND

   TEST(EqualizerDoesNotAssertSpecifiedFieldEqual_Throws)
   {
      EQUALIZER_THROWS_INIT(Namespace::TestStruct);
      THROWS(EQUALIZER_THROWS(Namespace::TestStruct, fieldB, 1), Anomaly, R"(
  Failed: EQUALIZER_THROWS(Namespace::TestStruct, fieldB, 1)
Expected: Function ZenUnitEqualizer<Namespace::TestStruct>::AssertEqual to throw a ZenUnit::Anomaly
          from an ARE_EQUAL or similar field assertion when Namespace::TestStruct
          field 'fieldB' differs between two Namespace::TestStruct objects.
  Actual: No ZenUnit::Anomaly thrown
File.cpp(1))");
   }

   TEST(EqualizerThrowsAnomalyThatDoesNotContainFieldName_Throws)
   {
      EQUALIZER_THROWS_INIT(TestStructB);
      THROWS(EQUALIZER_THROWS(TestStructB, field, TestStructB::ThrowWithoutFieldName), Anomaly, R"(
  Failed: EQUALIZER_THROWS(TestStructB, field, TestStructB::ThrowWithoutFieldName)
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
      THROWS(EQUALIZER_THROWS(TestStructB, field, TestStructB::ThrowWithFieldName), Anomaly, R"(
  Failed: EQUALIZER_THROWS(TestStructB, field, TestStructB::ThrowWithFieldName)
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

   }; RUN(EQUALIZER_THROWSTests)
}

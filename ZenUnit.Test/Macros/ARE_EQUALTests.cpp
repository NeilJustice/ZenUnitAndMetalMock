#include "pch.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

struct EqualizerOneTypeTestStruct {};
struct EqualizerTwoTypeTestStruct {};
struct EqualizerBothOneAndTwoTypeTestStruct {};

template<>
struct ZenUnitEqualizer<EqualizerOneTypeTestStruct>
{
   static void AssertEqual(
      const EqualizerOneTypeTestStruct&,
      const EqualizerOneTypeTestStruct&)
   {
      ARE_EQUAL(10, 20);
   }
};

template<>
struct TwoTypeZenUnitEqualizer<EqualizerTwoTypeTestStruct, int>
{
   static void AssertEqual(const EqualizerTwoTypeTestStruct&, const int&)
   {
      ARE_EQUAL(30, 40);
   }
};

template<>
struct ZenUnitEqualizer<EqualizerBothOneAndTwoTypeTestStruct>
{
   static void AssertEqual(
      const EqualizerBothOneAndTwoTypeTestStruct&,
      const EqualizerBothOneAndTwoTypeTestStruct&)
   {
      ARE_EQUAL(50, 60);
   }
};

template<>
struct TwoTypeZenUnitEqualizer<
  EqualizerBothOneAndTwoTypeTestStruct,
  EqualizerBothOneAndTwoTypeTestStruct>
{
   static void AssertEqual(
      const EqualizerBothOneAndTwoTypeTestStruct&,
      const EqualizerBothOneAndTwoTypeTestStruct&)
   {
      ARE_EQUAL(70, 80);
   }
};

namespace ZenUnit
{
   TESTS(ARE_EQTests)
   SPEC(OneTypeEqualizerDefined_CallsIt)
   SPEC(TwoTypeEqualizerDefined_CallsIt)
   SPEC(BothOneAndTwoTypeEqualizersDefined_CallsTheOneTypeEqualizer)
   SPEC(Int32sEqual_DoesNotThrow)
   SPEC(IntLiteralsNotEqual_Throws)
   SPEC(IntVariablesNotEqual_Throws_MessagesTestCase)
   SPEC(StringsNotEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   SPECEND

   TEST(OneTypeEqualizerDefined_CallsIt)
   {
      EqualizerOneTypeTestStruct expected, actual;
      THROWS(ARE_EQUAL(expected, actual), Anomaly, R"(
  Failed: ARE_EQUAL(expected, actual)
Expected: <EqualizerOneTypeTestStruct>
  Actual: <EqualizerOneTypeTestStruct>
 Because: ARE_EQUAL(10, 20) failed
Expected: 10
  Actual: 20
File.cpp(1)
File.cpp(1))");
   }

   TEST(TwoTypeEqualizerDefined_CallsIt)
   {
      EqualizerTwoTypeTestStruct expected;
      THROWS(ARE_EQUAL(expected, 1), Anomaly, R"(
  Failed: ARE_EQUAL(expected, 1)
Expected: <EqualizerTwoTypeTestStruct>
  Actual: 1
 Because: ARE_EQUAL(30, 40) failed
Expected: 30
  Actual: 40
File.cpp(1)
File.cpp(1))");
   }

   TEST(BothOneAndTwoTypeEqualizersDefined_CallsTheOneTypeEqualizer)
   {
      EqualizerBothOneAndTwoTypeTestStruct expected, actual;
      THROWS(ARE_EQUAL(expected, actual), Anomaly, R"(
  Failed: ARE_EQUAL(expected, actual)
Expected: <EqualizerBothOneAndTwoTypeTestStruct>
  Actual: <EqualizerBothOneAndTwoTypeTestStruct>
 Because: ARE_EQUAL(50, 60) failed
Expected: 50
  Actual: 60
File.cpp(1)
File.cpp(1))");
   }

   TEST(Int32sEqual_DoesNotThrow)
   {
      ARE_EQUAL(numeric_limits<int>::min(), numeric_limits<int>::min());
      ARE_EQUAL(numeric_limits<int>::min() + 1, numeric_limits<int>::min() + 1);
      ARE_EQUAL(-1, -1);
      ARE_EQUAL(0, 0);
      ARE_EQUAL(1, 1);
      ARE_EQUAL(numeric_limits<int>::max() - 1, numeric_limits<int>::max() - 1);
      ARE_EQUAL(numeric_limits<int>::max(), numeric_limits<int>::max());
   }

   TEST(IntLiteralsNotEqual_Throws)
   {
      THROWS(ARE_EQUAL(0, 1), Anomaly, R"(
  Failed: ARE_EQUAL(0, 1)
Expected: 0
  Actual: 1
File.cpp(1))");
   }

   TEST(IntVariablesNotEqual_Throws_MessagesTestCase)
   {
      int expected = 0;
      int actual = 1;
      string messageA = "A", messageB = "B";
      THROWS(ARE_EQUAL(expected, actual, messageA, messageB), Anomaly, R"(
  Failed: ARE_EQUAL(expected, actual, messageA, messageB)
Expected: 0
  Actual: 1
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(StringsNotEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   {
      string expected = "expected";
      string actual = "actual";
      THROWS(ARE_EQUAL(expected, actual), Anomaly, R"(
  Failed: ARE_EQUAL(expected, actual)
Expected: "expected"
  Actual: "actual"
File.cpp(1))");
   }

   }; RUN(ARE_EQTests)
}

#include "pch.h"

struct EqualizerOneTypeTestStruct {};
struct EqualizerTwoTypeTestStruct {};
struct EqualizerBothOneAndTwoTypeTestStruct {};

namespace ZenUnit
{
   template<>
   struct Equalizer<EqualizerOneTypeTestStruct>
   {
      static void AssertEqual(
         const EqualizerOneTypeTestStruct&,
         const EqualizerOneTypeTestStruct&)
      {
         ARE_EQUAL(10, 20);
      }
   };

   template<>
   struct TwoTypeEqualizer<EqualizerTwoTypeTestStruct, int>
   {
      static void AssertEqual(const EqualizerTwoTypeTestStruct&, const int&)
      {
         ARE_EQUAL(30, 40);
      }
   };

   template<>
   struct Equalizer<EqualizerBothOneAndTwoTypeTestStruct>
   {
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct&, const EqualizerBothOneAndTwoTypeTestStruct&)
      {
         ARE_EQUAL(50, 60);
      }
   };

   template<>
   struct TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct, EqualizerBothOneAndTwoTypeTestStruct>
   {
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct&, const EqualizerBothOneAndTwoTypeTestStruct&)
      {
         throw invalid_argument("unexpected call");
      }
   };

   TESTS(ARE_EQUALTests)
   AFACT(OneTypeEqualizerDefined_CallsIt)
   AFACT(TwoTypeEqualizerDefined_CallsIt)
   AFACT(BothOneAndTwoTypeEqualizersDefined_CallsTheOneTypeEqualizer)
   AFACT(Int32sEqual_DoesNotThrow)
   AFACT(IntLiteralsNotEqual_Throws)
   AFACT(IntVariablesNotEqual_Throws_MessagesTestCase)
   AFACT(StringsNotEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   AFACT(EqualizerBothOneAndTwoTypeTestStruct_CodeCoverage)
   EVIDENCE

   TEST(OneTypeEqualizerDefined_CallsIt)
   {
      const EqualizerOneTypeTestStruct expected{}, actual{};
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
      const EqualizerTwoTypeTestStruct expected{};
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
      const EqualizerBothOneAndTwoTypeTestStruct expected{}, actual{};
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
      const int expected = 0;
      const int actual = 1;
      const string messageA = "A", messageB = "B";
      THROWS(ARE_EQUAL(expected, actual, messageA, messageB), Anomaly, R"(
  Failed: ARE_EQUAL(expected, actual, messageA, messageB)
Expected: 0
  Actual: 1
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(StringsNotEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   {
      const string expected = "expected";
      const string actual = "actual";
      THROWS(ARE_EQUAL(expected, actual), Anomaly, R"(
  Failed: ARE_EQUAL(expected, actual)
Expected: "expected"
  Actual: "actual"
File.cpp(1))");
   }

   TEST(EqualizerBothOneAndTwoTypeTestStruct_CodeCoverage)
   {
      THROWS(
         TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct Comma EqualizerBothOneAndTwoTypeTestStruct>::AssertEqual(
            EqualizerBothOneAndTwoTypeTestStruct{}, EqualizerBothOneAndTwoTypeTestStruct{}),
         invalid_argument, "unexpected call");
   }

   RUN_TESTS(ARE_EQUALTests)
}
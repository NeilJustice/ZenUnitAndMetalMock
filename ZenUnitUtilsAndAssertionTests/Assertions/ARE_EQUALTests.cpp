#include "pch.h"

struct EqualizerOneTypeTestStruct_AreEqual {};
struct EqualizerTwoTypeTestStruct_AreEqual {};
struct EqualizerBothOneAndTwoTypeTestStruct_AreEqual {};

namespace ZenUnit
{
   template<>
   class Equalizer<EqualizerOneTypeTestStruct_AreEqual>
   {
   public:
      static void AssertEqual(const EqualizerOneTypeTestStruct_AreEqual&, const EqualizerOneTypeTestStruct_AreEqual&)
      {
         ARE_EQUAL(10, 20);
      }
   };

   template<>
   class TwoTypeEqualizer<EqualizerTwoTypeTestStruct_AreEqual, int>
   {
   public:
      static void AssertEqual(const EqualizerTwoTypeTestStruct_AreEqual&, const int&)
      {
         ARE_EQUAL(30, 40);
      }
   };

   template<>
   class Equalizer<EqualizerBothOneAndTwoTypeTestStruct_AreEqual>
   {
   public:
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreEqual&, const EqualizerBothOneAndTwoTypeTestStruct_AreEqual&)
      {
         ARE_EQUAL(50, 60);
      }
   };

   template<>
   class TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreEqual, EqualizerBothOneAndTwoTypeTestStruct_AreEqual>
   {
   public:
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreEqual&, const EqualizerBothOneAndTwoTypeTestStruct_AreEqual&)
      {
         throw invalid_argument("unexpected call");
      }
   };

   TESTS(ARE_EQUALTests)
   AFACT(ARE_EQUAL_OneTypeEqualizerIsDefined_CallsItsAssertEqualFunction)
   AFACT(ARE_EQUAL_TwoTypeEqualizerIsDefined_CallsItsAssertEqualFunction)
   AFACT(ARE_EQUAL_BothOneAndTwoTypeEqualizersAreDefined_CallsOneTypeEqualizerAssertEqual)
   AFACT(ARE_EQUAL_Int32sAreEqual_DoesNotThrowException)
   AFACT(ARE_EQUAL_IntLiteralsAreNotEqual_ThrowsAnomaly)
   AFACT(ARE_EQUAL_IntVariablesAreNotEqual_ThrowsAnomaly__MessagesTestCase)
   AFACT(ARE_EQUAL_StdStringsAreNotEqual_ThrowsAnomaly)
   AFACT(ARE_EQUAL_StringViewsAreNotEqual_ThrowsAnomaly)
   AFACT(EqualizerBothOneAndTwoTypeTestStruct_AssertEqual_CodeCoverage)
   EVIDENCE

   TEST(ARE_EQUAL_OneTypeEqualizerIsDefined_CallsItsAssertEqualFunction)
   {
      const EqualizerOneTypeTestStruct_AreEqual expected{}, actual{};
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: <EqualizerOneTypeTestStruct_AreEqual>",
"  Actual: <EqualizerOneTypeTestStruct_AreEqual>",
" Because: ARE_EQUAL(10, 20) failed",
"Expected: 10",
"  Actual: 20",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ARE_EQUAL_TwoTypeEqualizerIsDefined_CallsItsAssertEqualFunction)
   {
      const EqualizerTwoTypeTestStruct_AreEqual expected{};
      THROWS_EXCEPTION(ARE_EQUAL(expected, 1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, 1)",
"Expected: <EqualizerTwoTypeTestStruct_AreEqual>",
"  Actual: 1",
" Because: ARE_EQUAL(30, 40) failed",
"Expected: 30",
"  Actual: 40",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ARE_EQUAL_BothOneAndTwoTypeEqualizersAreDefined_CallsOneTypeEqualizerAssertEqual)
   {
      const EqualizerBothOneAndTwoTypeTestStruct_AreEqual expected{}, actual{};
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: <EqualizerBothOneAndTwoTypeTestStruct_AreEqual>",
"  Actual: <EqualizerBothOneAndTwoTypeTestStruct_AreEqual>",
" Because: ARE_EQUAL(50, 60) failed",
"Expected: 50",
"  Actual: 60",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ARE_EQUAL_Int32sAreEqual_DoesNotThrowException)
   {
      ARE_EQUAL(numeric_limits<int>::min(), numeric_limits<int>::min());
      ARE_EQUAL(numeric_limits<int>::min() + 1, numeric_limits<int>::min() + 1);
      ARE_EQUAL(-1, -1);
      ARE_EQUAL(0, 0);
      ARE_EQUAL(1, 1);
      ARE_EQUAL(numeric_limits<int>::max() - 1, numeric_limits<int>::max() - 1);
      ARE_EQUAL(numeric_limits<int>::max(), numeric_limits<int>::max());
   }

   TEST(ARE_EQUAL_IntLiteralsAreNotEqual_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(ARE_EQUAL(0, 1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(0, 1)",
"Expected: 0",
"  Actual: 1",
"File.cpp(1)"));
   }

   TEST(ARE_EQUAL_IntVariablesAreNotEqual_ThrowsAnomaly__MessagesTestCase)
   {
      const int expected = 0;
      const int actual = 1;
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual, messageA, messageB)",
"Expected: 0",
"  Actual: 1",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   TEST(ARE_EQUAL_StdStringsAreNotEqual_ThrowsAnomaly)
   {
      const string expected = "expected";
      const string actual = "actual";
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: \"expected\"",
"  Actual: \"actual\"",
"File.cpp(1)"));
   }

   TEST(ARE_EQUAL_StringViewsAreNotEqual_ThrowsAnomaly)
   {
      const string_view expected = "expected";
      const string_view actual = "actual";
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: \"expected\"",
"  Actual: \"actual\"",
"File.cpp(1)"));
   }

   TEST(EqualizerBothOneAndTwoTypeTestStruct_AssertEqual_CodeCoverage)
   {
      THROWS_EXCEPTION(
         (TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreEqual, EqualizerBothOneAndTwoTypeTestStruct_AreEqual>::AssertEqual(
            EqualizerBothOneAndTwoTypeTestStruct_AreEqual{}, EqualizerBothOneAndTwoTypeTestStruct_AreEqual{})),
         invalid_argument, "unexpected call");
   }

   RUN_TESTS(ARE_EQUALTests)
}

#include "pch.h"

struct EqualizerOneTypeTestStruct_AreEqualTests {};
struct EqualizerTwoTypeTestStruct_AreEqualTests {};
struct EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests {};

namespace ZenUnit
{
   template<>
   class Equalizer<EqualizerOneTypeTestStruct_AreEqualTests>
   {
   public:
      static void AssertEqual(const EqualizerOneTypeTestStruct_AreEqualTests&, const EqualizerOneTypeTestStruct_AreEqualTests&)
      {
         ARE_EQUAL(10, 20);
      }
   };

   template<>
   class TwoTypeEqualizer<EqualizerTwoTypeTestStruct_AreEqualTests, int>
   {
   public:
      static void AssertEqual(const EqualizerTwoTypeTestStruct_AreEqualTests&, const int&)
      {
         ARE_EQUAL(30, 40);
      }
   };

   template<>
   class Equalizer<EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests>
   {
   public:
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests&, const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests&)
      {
         ARE_EQUAL(50, 60);
      }
   };

   template<>
   class TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests, EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests>
   {
   public:
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests&, const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests&)
      {
         throw invalid_argument("unexpected call");
      }
   };

   TESTS(ARE_EQUALTests)
   AFACT(OneTypeEqualizerDefined_CallsIt)
   AFACT(TwoTypeEqualizerDefined_CallsIt)
   AFACT(BothOneAndTwoTypeEqualizersAreDefined_CallsTheOneTypeEqualizer)
   AFACT(Int32sAreEqual_DoesNotThrowException)
   AFACT(IntLiteralsAreNotEqual_ThrowsAnomaly)
   AFACT(IntVariablesAreNotEqual_ThrowsAnomaly__MessagesTestCase)
   AFACT(StdStringsAreNotEqual_ThrowsAnomaly)
   AFACT(StringViewsAreNotEqual_ThrowsAnomaly)
   AFACT(EqualizerBothOneAndTwoTypeTestStruct_CodeCoverage)
   EVIDENCE

   TEST(OneTypeEqualizerDefined_CallsIt)
   {
      const EqualizerOneTypeTestStruct_AreEqualTests expected{}, actual{};
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: <EqualizerOneTypeTestStruct_AreEqualTests>",
"  Actual: <EqualizerOneTypeTestStruct_AreEqualTests>",
" Because: ARE_EQUAL(10, 20) failed",
"Expected: 10",
"  Actual: 20",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(TwoTypeEqualizerDefined_CallsIt)
   {
      const EqualizerTwoTypeTestStruct_AreEqualTests expected{};
      THROWS_EXCEPTION(ARE_EQUAL(expected, 1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, 1)",
"Expected: <EqualizerTwoTypeTestStruct_AreEqualTests>",
"  Actual: 1",
" Because: ARE_EQUAL(30, 40) failed",
"Expected: 30",
"  Actual: 40",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(BothOneAndTwoTypeEqualizersAreDefined_CallsTheOneTypeEqualizer)
   {
      const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests expected{}, actual{};
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: <EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests>",
"  Actual: <EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests>",
" Because: ARE_EQUAL(50, 60) failed",
"Expected: 50",
"  Actual: 60",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(Int32sAreEqual_DoesNotThrowException)
   {
      ARE_EQUAL(numeric_limits<int>::min(), numeric_limits<int>::min());
      ARE_EQUAL(numeric_limits<int>::min() + 1, numeric_limits<int>::min() + 1);
      ARE_EQUAL(-1, -1);
      ARE_EQUAL(0, 0);
      ARE_EQUAL(1, 1);
      ARE_EQUAL(numeric_limits<int>::max() - 1, numeric_limits<int>::max() - 1);
      ARE_EQUAL(numeric_limits<int>::max(), numeric_limits<int>::max());
   }

   TEST(IntLiteralsAreNotEqual_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(ARE_EQUAL(0, 1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(0, 1)",
"Expected: 0",
"  Actual: 1",
"File.cpp(1)"));
   }

   TEST(IntVariablesAreNotEqual_ThrowsAnomaly__MessagesTestCase)
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

   TEST(StdStringsAreNotEqual_ThrowsAnomaly)
   {
      const string expected = "expected";
      const string actual = "actual";
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: \"expected\"",
"  Actual: \"actual\"",
"File.cpp(1)"));
   }

   TEST(StringViewsAreNotEqual_ThrowsAnomaly)
   {
      const string_view expected = "expected";
      const string_view actual = "actual";
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: \"expected\"",
"  Actual: \"actual\"",
"File.cpp(1)"));
   }

   TEST(EqualizerBothOneAndTwoTypeTestStruct_CodeCoverage)
   {
      THROWS_EXCEPTION(
         (TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests, EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests>::AssertEqual(
            EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests{}, EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests{})),
         invalid_argument, "unexpected call");
   }

   RUN_TESTS(ARE_EQUALTests)
}

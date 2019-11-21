#include "pch.h"

struct EqualizerOneTypeTestStruct_AreEqualTests {};
struct EqualizerTwoTypeTestStruct_AreEqualTests {};
struct EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests {};

namespace ZenUnit
{
   template<>
   struct Equalizer<EqualizerOneTypeTestStruct_AreEqualTests>
   {
      static void AssertEqual(const EqualizerOneTypeTestStruct_AreEqualTests&, const EqualizerOneTypeTestStruct_AreEqualTests&)
      {
         ARE_EQUAL(10, 20);
      }
   };

   template<>
   struct TwoTypeEqualizer<EqualizerTwoTypeTestStruct_AreEqualTests, int>
   {
      static void AssertEqual(const EqualizerTwoTypeTestStruct_AreEqualTests&, const int&)
      {
         ARE_EQUAL(30, 40);
      }
   };

   template<>
   struct Equalizer<EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests>
   {
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests&, const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests&)
      {
         ARE_EQUAL(50, 60);
      }
   };

   template<>
   struct TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests, EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests>
   {
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests&, const EqualizerBothOneAndTwoTypeTestStruct_AreEqualTests&)
      {
         throw invalid_argument("unexpected call");
      }
   };

   TESTS(ARE_EQUALTests)
   AFACT(OneTypeEqualizerDefined_CallsIt)
   AFACT(TwoTypeEqualizerDefined_CallsIt)
   AFACT(BothOneAndTwoTypeEqualizersDefined_CallsTheOneTypeEqualizer)
   AFACT(Int32sAreEqual_DoesNotThrow)
   AFACT(IntLiteralsNotEqual_Throws)
   AFACT(IntVariablesNotEqual_Throws_MessagesTestCase)
   AFACT(StringsNotEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   AFACT(StringViewsNotEqual_ThrowsWithStringViewsInQuotesToConfirmedToStringed)
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

   TEST(BothOneAndTwoTypeEqualizersDefined_CallsTheOneTypeEqualizer)
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

   TEST(Int32sAreEqual_DoesNotThrow)
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
      THROWS_EXCEPTION(ARE_EQUAL(0, 1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(0, 1)",
"Expected: 0",
"  Actual: 1",
"File.cpp(1)"));
   }

   TEST(IntVariablesNotEqual_Throws_MessagesTestCase)
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

   TEST(StringsNotEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   {
      const string expected = "expected";
      const string actual = "actual";
      THROWS_EXCEPTION(ARE_EQUAL(expected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expected, actual)",
"Expected: \"expected\"",
"  Actual: \"actual\"",
"File.cpp(1)"));
   }

   TEST(StringViewsNotEqual_ThrowsWithStringViewsInQuotesToConfirmedToStringed)
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

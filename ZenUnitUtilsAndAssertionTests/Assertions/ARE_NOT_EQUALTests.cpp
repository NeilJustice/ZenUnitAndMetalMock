#include "pch.h"

struct EqualizerOneTypeTestStruct_AreNotEqualTests {};
struct EqualizerTwoTypeTestStruct_AreNotEqualTests {};
struct EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests {};

namespace ZenUnit
{
   template<>
   class Equalizer<EqualizerOneTypeTestStruct_AreNotEqualTests>
   {
   public:
      static void AssertEqual(const EqualizerOneTypeTestStruct_AreNotEqualTests&, const EqualizerOneTypeTestStruct_AreNotEqualTests&)
      {
         ARE_NOT_EQUAL(10, 10);
      }
   };

   template<>
   class TwoTypeEqualizer<EqualizerTwoTypeTestStruct_AreNotEqualTests, int>
   {
   public:
      static void AssertEqual(const EqualizerTwoTypeTestStruct_AreNotEqualTests&, const int&)
      {
         ARE_NOT_EQUAL(20, 20);
      }
   };

   template<>
   class Equalizer<EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests>
   {
   public:
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests&, const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests&)
      {
         ARE_NOT_EQUAL(30, 30);
      }
   };

   template<>
   class TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests, EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests>
   {
   public:
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests&, const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests&)
      {
         throw invalid_argument("unexpected call");
      }
   };

   TESTS(ARE_NOT_EQUALTests)
   AFACT(OneTypeEqualizerDefined_CallsIt)
   AFACT(TwoTypeEqualizerDefined_CallsIt)
   AFACT(BothOneAndTwoTypeEqualizersDefined_CallsTheOneTypeEqualizer)
   AFACT(Int32sAreNotEqual_DoesNotThrowException)
   AFACT(IntLiteralsAreEqual_Throws)
   AFACT(IntVariablesAreEqual_Throws_MessagesTestCase)
   AFACT(StringsAreEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   AFACT(StringViewsAreEqual_ThrowsWithStringViewsInQuotesToConfirmedToStringed)
   AFACT(EqualizerBothOneAndTwoTypeTestStruct_CodeCoverage)
   EVIDENCE

   TEST(OneTypeEqualizerDefined_CallsIt)
   {
      const EqualizerOneTypeTestStruct_AreNotEqualTests notExpected{}, actual{};
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual)",
"Expected: Not Expected: <EqualizerOneTypeTestStruct_AreNotEqualTests>",
"  Actual:       Actual: <EqualizerOneTypeTestStruct_AreNotEqualTests>",
" Because: ARE_NOT_EQUAL(10, 10) failed",
"Expected: Not Expected: 10",
"  Actual:       Actual: 10",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(TwoTypeEqualizerDefined_CallsIt)
   {
      const EqualizerTwoTypeTestStruct_AreNotEqualTests notExpected{};
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, 1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, 1)",
"Expected: Not Expected: <EqualizerTwoTypeTestStruct_AreNotEqualTests>",
"  Actual:       Actual: 1",
" Because: ARE_NOT_EQUAL(20, 20) failed",
"Expected: Not Expected: 20",
"  Actual:       Actual: 20",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(BothOneAndTwoTypeEqualizersDefined_CallsTheOneTypeEqualizer)
   {
      const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests notExpected{}, actual{};
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual)",
"Expected: Not Expected: <EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests>",
"  Actual:       Actual: <EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests>",
" Because: ARE_NOT_EQUAL(30, 30) failed",
"Expected: Not Expected: 30",
"  Actual:       Actual: 30",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(Int32sAreNotEqual_DoesNotThrowException)
   {
      ARE_NOT_EQUAL(numeric_limits<int>::min() + 1, numeric_limits<int>::min());
      ARE_NOT_EQUAL(numeric_limits<int>::min() + 2, numeric_limits<int>::min() + 1);
      ARE_NOT_EQUAL(-2, -1);
      ARE_NOT_EQUAL(-1, 1);
      ARE_NOT_EQUAL(2, 1);
      ARE_NOT_EQUAL(numeric_limits<int>::max() - 2, numeric_limits<int>::max() - 1);
      ARE_NOT_EQUAL(numeric_limits<int>::max() - 1, numeric_limits<int>::max());
   }

   TEST(IntLiteralsAreEqual_Throws)
   {
      THROWS_EXCEPTION(ARE_NOT_EQUAL(0, 0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(0, 0)",
"Not Expected: 0",
"      Actual: 0",
"File.cpp(1)"));
   }

   TEST(IntVariablesAreEqual_Throws_MessagesTestCase)
   {
      const int notExpected = 0;
      const int actual = notExpected;
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual, messageA, messageB)",
"Not Expected: 0",
"      Actual: 0",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   TEST(StringsAreEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   {
      const string notExpected = "not expected";
      const string actual = notExpected;
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual)",
"Not Expected: \"not expected\"",
"      Actual: \"not expected\"",
"File.cpp(1)"));
   }

   TEST(StringViewsAreEqual_ThrowsWithStringViewsInQuotesToConfirmedToStringed)
   {
      const string_view notExpected = "not expected";
      const string_view actual = notExpected;
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual)",
"Not Expected: \"not expected\"",
"      Actual: \"not expected\"",
"File.cpp(1)"));
   }

   TEST(EqualizerBothOneAndTwoTypeTestStruct_CodeCoverage)
   {
      THROWS_EXCEPTION(
         (TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests, EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests>::AssertEqual(
            EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests{}, EqualizerBothOneAndTwoTypeTestStruct_AreNotEqualTests{})),
         invalid_argument, "unexpected call");
   }

   RUN_TESTS(ARE_NOT_EQUALTests)
}

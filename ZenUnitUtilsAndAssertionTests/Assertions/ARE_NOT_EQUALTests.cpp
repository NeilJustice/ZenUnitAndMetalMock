#include "pch.h"

struct EqualizerOneTypeTestStruct_AreNotEqual {};
struct EqualizerTwoTypeTestStruct_AreNotEqual {};
struct EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual {};

namespace ZenUnit
{
   template<>
   class Equalizer<EqualizerOneTypeTestStruct_AreNotEqual>
   {
   public:
      static void AssertEqual(const EqualizerOneTypeTestStruct_AreNotEqual&, const EqualizerOneTypeTestStruct_AreNotEqual&)
      {
         ARE_NOT_EQUAL(10, 10);
      }
   };

   template<>
   class TwoTypeEqualizer<EqualizerTwoTypeTestStruct_AreNotEqual, int>
   {
   public:
      static void AssertEqual(const EqualizerTwoTypeTestStruct_AreNotEqual&, const int&)
      {
         ARE_NOT_EQUAL(20, 20);
      }
   };

   template<>
   class Equalizer<EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual>
   {
   public:
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual&, const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual&)
      {
         ARE_NOT_EQUAL(30, 30);
      }
   };

   template<>
   class TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual, EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual>
   {
   public:
      static void AssertEqual(const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual&, const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual&)
      {
         throw invalid_argument("unexpected call");
      }
   };

   TESTS(ARE_NOT_EQUALTests)
   AFACT(ARE_NOT_EQUAL_OneTypeEqualizerIsDefined_CallsItsAssertEqualFunction)
   AFACT(ARE_NOT_EQUAL_TwoTypeEqualizerDefined_CallsItsAssertEqualFunction)
   AFACT(ARE_NOT_EQUAL_BothOneAndTwoTypeEqualizersAreDefined_CallsTheOneTypeEqualizer)
   AFACT(ARE_NOT_EQUAL_Int32sAreNotEqual_DoesNotThrowException)
   AFACT(ARE_NOT_EQUAL_IntLiteralsAreEqual_ThrowsAnomaly)
   AFACT(ARE_NOT_EQUAL_IntVariablesAreEqual_ThrowsAnomaly__MessagesTestCase)
   AFACT(ARE_NOT_EQUAL_StringsAreEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   AFACT(ARE_NOT_EQUAL_StringViewsAreEqual_ThrowsWithStringViewsInQuotesToConfirmedToStringed)
   AFACT(EqualizerBothOneAndTwoTypeTestStruct_AssertEqual_CodeCoverage)
   EVIDENCE

   TEST(ARE_NOT_EQUAL_OneTypeEqualizerIsDefined_CallsItsAssertEqualFunction)
   {
      const EqualizerOneTypeTestStruct_AreNotEqual notExpected{}, actual{};
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual)",
"Expected: Not Expected: <EqualizerOneTypeTestStruct_AreNotEqual>",
"  Actual:       Actual: <EqualizerOneTypeTestStruct_AreNotEqual>",
" Because: ARE_NOT_EQUAL(10, 10) failed",
"Expected: Not Expected: 10",
"  Actual:       Actual: 10",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ARE_NOT_EQUAL_TwoTypeEqualizerDefined_CallsItsAssertEqualFunction)
   {
      const EqualizerTwoTypeTestStruct_AreNotEqual notExpected{};
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, 1), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, 1)",
"Expected: Not Expected: <EqualizerTwoTypeTestStruct_AreNotEqual>",
"  Actual:       Actual: 1",
" Because: ARE_NOT_EQUAL(20, 20) failed",
"Expected: Not Expected: 20",
"  Actual:       Actual: 20",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ARE_NOT_EQUAL_BothOneAndTwoTypeEqualizersAreDefined_CallsTheOneTypeEqualizer)
   {
      const EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual notExpected{}, actual{};
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual)",
"Expected: Not Expected: <EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual>",
"  Actual:       Actual: <EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual>",
" Because: ARE_NOT_EQUAL(30, 30) failed",
"Expected: Not Expected: 30",
"  Actual:       Actual: 30",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ARE_NOT_EQUAL_Int32sAreNotEqual_DoesNotThrowException)
   {
      ARE_NOT_EQUAL(numeric_limits<int>::min() + 1, numeric_limits<int>::min());
      ARE_NOT_EQUAL(numeric_limits<int>::min() + 2, numeric_limits<int>::min() + 1);
      ARE_NOT_EQUAL(-2, -1);
      ARE_NOT_EQUAL(-1, 1);
      ARE_NOT_EQUAL(2, 1);
      ARE_NOT_EQUAL(numeric_limits<int>::max() - 2, numeric_limits<int>::max() - 1);
      ARE_NOT_EQUAL(numeric_limits<int>::max() - 1, numeric_limits<int>::max());
   }

   TEST(ARE_NOT_EQUAL_IntLiteralsAreEqual_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(ARE_NOT_EQUAL(0, 0), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(0, 0)",
"Not Expected: 0",
"      Actual: 0",
"File.cpp(1)"));
   }

   TEST(ARE_NOT_EQUAL_IntVariablesAreEqual_ThrowsAnomaly__MessagesTestCase)
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

   TEST(ARE_NOT_EQUAL_StringsAreEqual_ThrowsWithStringsInQuotesToConfirmedToStringed)
   {
      const string notExpected = "not expected";
      const string actual = notExpected;
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual)",
"Not Expected: \"not expected\"",
"      Actual: \"not expected\"",
"File.cpp(1)"));
   }

   TEST(ARE_NOT_EQUAL_StringViewsAreEqual_ThrowsWithStringViewsInQuotesToConfirmedToStringed)
   {
      const string_view notExpected = "not expected";
      const string_view actual = notExpected;
      THROWS_EXCEPTION(ARE_NOT_EQUAL(notExpected, actual), Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARE_NOT_EQUAL(notExpected, actual)",
"Not Expected: \"not expected\"",
"      Actual: \"not expected\"",
"File.cpp(1)"));
   }

   TEST(EqualizerBothOneAndTwoTypeTestStruct_AssertEqual_CodeCoverage)
   {
      THROWS_EXCEPTION(
         (TwoTypeEqualizer<EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual, EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual>::AssertEqual(
            EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual{}, EqualizerBothOneAndTwoTypeTestStruct_AreNotEqual{})),
         invalid_argument, "unexpected call");
   }

   RUN_TESTS(ARE_NOT_EQUALTests)
}

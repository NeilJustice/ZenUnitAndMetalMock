#include "pch.h"

TESTS(CharSpanAndStringTwoTypeEqualizerTests)
AFACT(TwoTypeEqualizer_MutableCharSpan_String_LengthsAreNotEqual_ThrowsAnomaly)
AFACT(TwoTypeEqualizer_MutableCharSpan_String_LengthsAreEqual_CharsAreNotEqual_ThrowsAnomaly)
AFACT(TwoTypeEqualizer_MutableCharSpan_String_LengthsAreEqual_CharsAreEqual_Returns__EmptyTestCase)
AFACT(TwoTypeEqualizer_MutableCharSpan_String_LengthsAreEqual_CharsAreEqual_Returns__NonEmptyTestCase)
AFACT(TwoTypeEqualizer_ConstantCharSpan_String_LengthsAreNotEqual_ThrowsAnomaly)
AFACT(TwoTypeEqualizer_ConstantCharSpan_String_LengthsAreEqual_CharsAreNotEqual_ThrowsAnomaly)
AFACT(TwoTypeEqualizer_ConstantCharSpan_String_LengthsAreEqual_CharsAreEqual_Returns__EmptyTestCase)
AFACT(TwoTypeEqualizer_ConstantCharSpan_String_LengthsAreEqual_CharsAreEqual_Returns__NonEmptyTestCase)
EVIDENCE

TEST(TwoTypeEqualizer_MutableCharSpan_String_LengthsAreNotEqual_ThrowsAnomaly)
{
   string str1WithLength3 = "123";
   string strWithLength5 = "12345";
   const span<char> mutableCharSpanWithLength3 = str1WithLength3;
   try
   {
      ZenUnit::TwoTypeEqualizer<span<char>, string>::AssertEqual(mutableCharSpanWithLength3, strWithLength5);
      FAIL_TEST("ZenUnit::Anomaly unexpectedly not thrown"); // LCOV_EXCL_LINE
   }
   catch (const ZenUnit::Anomaly& anomaly)
   {
      const string anomalyMessage = anomaly.what();
      const string expectedAnomalyMessage = TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expectedMutableCharSpan.size(), actualConstantString.size())",
"Expected: 3",
"  Actual: 5",
R"(File.cpp(1))");
      ARE_EQUAL(expectedAnomalyMessage, anomalyMessage);
   }
}

TEST(TwoTypeEqualizer_MutableCharSpan_String_LengthsAreEqual_CharsAreNotEqual_ThrowsAnomaly)
{
   string str1 = "123";
   string str2 = "120";
   const span<char> mutableCharSpan = str1;
   try
   {
      ZenUnit::TwoTypeEqualizer<span<char>, string>::AssertEqual(mutableCharSpan, str2);
      FAIL_TEST("ZenUnit::Anomaly unexpectedly not thrown"); // LCOV_EXCL_LINE
   }
   catch (const ZenUnit::Anomaly& anomaly)
   {
      const string anomalyMessage = anomaly.what();
#if defined __linux__
      const string expectedAnomalyMessage = TestUtil::NewlineConcat("",
"  Failed: ARRAYS_ARE_EQUAL(expectedMutableCharSpan.data(), const_cast<char*>(actualConstantString.data()), 3)",
"Expected: char*",
"  Actual: char*",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: '3' (51)",
"  Actual: '0' (48)",
" Message: \"i=2\"",
"File.cpp(1)",
"File.cpp(1)");
#elif defined _WIN32
      const string expectedAnomalyMessage = TestUtil::NewlineConcat("",
"  Failed: ARRAYS_ARE_EQUAL(expectedMutableCharSpan.data(), const_cast<char*>(actualConstantString.data()), 3)",
"Expected: char *",
"  Actual: char *",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: '3' (51)",
"  Actual: '0' (48)",
" Message: \"i=2\"",
"File.cpp(1)",
"File.cpp(1)");
#endif
      ARE_EQUAL(expectedAnomalyMessage, anomalyMessage);
   }
}

TEST(TwoTypeEqualizer_MutableCharSpan_String_LengthsAreEqual_CharsAreEqual_Returns__EmptyTestCase)
{
   const string str;
   const span<char> mutableCharSpan;
   ZenUnit::TwoTypeEqualizer<span<char>, string>::AssertEqual(mutableCharSpan, str);
}

TEST(TwoTypeEqualizer_MutableCharSpan_String_LengthsAreEqual_CharsAreEqual_Returns__NonEmptyTestCase)
{
   string str = ZenUnit::Random<string>();
   const span<char> mutableCharSpan = str;
   ZenUnit::TwoTypeEqualizer<span<char>, string>::AssertEqual(mutableCharSpan, str);
}

TEST(TwoTypeEqualizer_ConstantCharSpan_String_LengthsAreNotEqual_ThrowsAnomaly)
{
   string str1WithLength3 = "123";
   string strWithLength5 = "12345";
   const span<const char> constantCharSpanWithLength3 = str1WithLength3;
   try
   {
      ZenUnit::TwoTypeEqualizer<span<const char>, string>::AssertEqual(constantCharSpanWithLength3, strWithLength5);
      FAIL_TEST("ZenUnit::Anomaly unexpectedly not thrown"); // LCOV_EXCL_LINE
   }
   catch (const ZenUnit::Anomaly& anomaly)
   {
      const string anomalyMessage = anomaly.what();
      const string expectedAnomalyMessage = TestUtil::NewlineConcat("",
"  Failed: ARE_EQUAL(expectedConstantCharSpan.size(), actualConstantString.size())",
"Expected: 3",
"  Actual: 5",
"File.cpp(1)");
      ARE_EQUAL(expectedAnomalyMessage, anomalyMessage);
   }
}

TEST(TwoTypeEqualizer_ConstantCharSpan_String_LengthsAreEqual_CharsAreNotEqual_ThrowsAnomaly)
{
   const string str1 = "123";
   const string str2 = "120";
   const span<const char> constantCharSpan = str1;
   try
   {
      ZenUnit::TwoTypeEqualizer<span<const char>, string>::AssertEqual(constantCharSpan, str2);
      FAIL_TEST("ZenUnit::Anomaly unexpectedly not thrown"); // LCOV_EXCL_LINE
   }
   catch (const ZenUnit::Anomaly& anomaly)
   {
      const string anomalyMessage = anomaly.what();
#if defined __linux__
      const string expectedAnomalyMessage = TestUtil::NewlineConcat("",
"  Failed: ARRAYS_ARE_EQUAL(expectedConstantCharSpan.data(), actualConstantString.data(), 3)",
"Expected: char const*",
"  Actual: char const*",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: '3' (51)",
"  Actual: '0' (48)",
" Message: \"i=2\"",
"File.cpp(1)",
"File.cpp(1)");
#elif defined _WIN32
      const string expectedAnomalyMessage = TestUtil::NewlineConcat("",
"  Failed: ARRAYS_ARE_EQUAL(expectedConstantCharSpan.data(), actualConstantString.data(), 3)",
"Expected: char const *",
"  Actual: char const *",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: '3' (51)",
"  Actual: '0' (48)",
" Message: \"i=2\"",
"File.cpp(1)",
"File.cpp(1)");
#endif
      ARE_EQUAL(expectedAnomalyMessage, anomalyMessage);
   }
}

TEST(TwoTypeEqualizer_ConstantCharSpan_String_LengthsAreEqual_CharsAreEqual_Returns__EmptyTestCase)
{
   const span<const char> constantCharSpan;
   const string str;
   ZenUnit::TwoTypeEqualizer<span<const char>, string>::AssertEqual(constantCharSpan, str);
}

TEST(TwoTypeEqualizer_ConstantCharSpan_String_LengthsAreEqual_CharsAreEqual_Returns__NonEmptyTestCase)
{
   const string str = ZenUnit::Random<string>();
   const span<const char> mutableCharSpan = str;
   ZenUnit::TwoTypeEqualizer<span<const char>, string>::AssertEqual(mutableCharSpan, str);
}

RUN_TESTS(CharSpanAndStringTwoTypeEqualizerTests)

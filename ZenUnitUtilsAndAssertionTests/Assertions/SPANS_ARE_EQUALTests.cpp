#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(SPANS_ARE_EQUALTests, T)
   AFACT(ConstEmptySpans_DoesNothing)
   AFACT(ConstNonEmptySpans_AllElementsEqual_DoesNothing)
   AFACT(ConstNonEmptySpans_SizesAreNotEqual_ThrowsAnomaly)
   AFACT(ConstNonEmptySpans_SizesAreEqual_ElementsAreNotEqual_ThrowsAnomaly__TestCase1)
   AFACT(ConstNonEmptySpans_SizesAreEqual_ElementsAreNotEqual_ThrowsAnomaly__TestCase2)
   EVIDENCE

   const string TypeName = *Type::GetName<T>();
   const string _constSpanTypeName = *Type::GetName<span<const T>>();

   TEST(ConstEmptySpans_DoesNothing)
   {
      const span<const T> expectedSpan;
      const span<const T> actualSpan;
      SPANS_ARE_EQUAL(expectedSpan, actualSpan);
   }

   TEST(ConstNonEmptySpans_AllElementsEqual_DoesNothing)
   {
      const vector<T> expectedElements{ 1, 2, 3 };
      const vector<T> actualElements{ 1, 2, 3 };

      const span<const T> expectedSpan = expectedElements;
      const span<const T> actualSpan = actualElements;
      SPANS_ARE_EQUAL(expectedSpan, actualSpan);
   }

   TEST(ConstNonEmptySpans_SizesAreNotEqual_ThrowsAnomaly)
   {
      const vector<T> expectedElements;
      const vector<T> actualElements{ 1 };

      const span<const T> expectedSpan = expectedElements;
      const span<const T> actualSpan = actualElements;

      THROWS_EXCEPTION(SPANS_ARE_EQUAL(expectedSpan, actualSpan),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: SPANS_ARE_EQUAL(expectedSpan, actualSpan)",
"Expected: " + _constSpanTypeName + " (size 0):",
"{",
"}",
"  Actual: " + _constSpanTypeName + " (size 1):",
"{",
"   1",
"}",
" Because: ARE_EQUAL(expectedSpan.size(), actualSpan.size()) failed",
"Expected: 0",
"  Actual: 1",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ConstNonEmptySpans_SizesAreEqual_ElementsAreNotEqual_ThrowsAnomaly__TestCase1)
   {
      const vector<T> expectedElements{ 0 };
      const vector<T> actualElements{ 1 };

      const span<const T> expectedSpan = expectedElements;
      const span<const T> actualSpan = actualElements;

      THROWS_EXCEPTION(SPANS_ARE_EQUAL(expectedSpan, actualSpan),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: SPANS_ARE_EQUAL(expectedSpan, actualSpan)",
"Expected: " + _constSpanTypeName + " (size 1):",
"{",
"   0",
"}",
"  Actual: " + _constSpanTypeName + " (size 1):",
"{",
"   1",
"}",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: 0",
"  Actual: 1",
" Message: \"i=0\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ConstNonEmptySpans_SizesAreEqual_ElementsAreNotEqual_ThrowsAnomaly__TestCase2)
   {
      const vector<T> expectedElements{ 0, 1, 20 };
      const vector<T> actualElements{ 0, 1, 30 };

      const span<const T> expectedSpan = expectedElements;
      const span<const T> actualSpan = actualElements;

      THROWS_EXCEPTION(SPANS_ARE_EQUAL(expectedSpan, actualSpan),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: SPANS_ARE_EQUAL(expectedSpan, actualSpan)",
"Expected: " + _constSpanTypeName + " (size 3):",
"{",
"   0,",
"   1,",
"   20",
"}",
"  Actual: " + _constSpanTypeName + " (size 3):",
"{",
"   0,",
"   1,",
"   30",
"}",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: 20",
"  Actual: 30",
" Message: \"i=2\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   RUN_TEMPLATE_TESTS(SPANS_ARE_EQUALTests, int)
   THEN_RUN_TEMPLATE_TESTS(SPANS_ARE_EQUALTests, unsigned long long)
}

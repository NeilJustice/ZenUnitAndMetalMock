#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(VECTORS_EQUALTests, T)
   AFACT(VectorSizesAreEqualAndVectorElementsAreEqual_DoesNotThrowException)
   AFACT(VectorSizesAreNotEqual_ThrowsAnomaly)
   AFACT(VectorSizesAreNotEqual_ThrowsAnomaly_MessagesTestCase)
   AFACT(VectorSizesAreEqual_ElementsAreNotEqualAtIndex0_ThrowsAnomaly__MessagesTestCase)
   AFACT(VectorSizesAreEqual_ElementsAreNotEqualAtIndex1_ThrowsAnomaly)
   EVIDENCE

   const string TypeName = *Type::GetName<T>();
   const string _messageA = ZenUnit::Random<string>();
   const string _messageB = ZenUnit::Random<string>();

   TEST(VectorSizesAreEqualAndVectorElementsAreEqual_DoesNotThrowException)
   {
      vector<T> expectedVector;;
      vector<T> actualVector;

      VECTORS_EQUAL(expectedVector, actualVector);

      const T randomElement1 = Random<T>();
      expectedVector.push_back(randomElement1);
      actualVector.push_back(randomElement1);
      VECTORS_EQUAL(expectedVector, actualVector);

      const T randomElement2 = Random<T>();
      expectedVector.push_back(randomElement2);
      actualVector.push_back(randomElement2);
      VECTORS_EQUAL(expectedVector, actualVector);

      const T randomElement3 = Random<T>();
      expectedVector.push_back(randomElement3);
      actualVector.push_back(randomElement3);
      VECTORS_EQUAL(expectedVector, actualVector);
   }

   TEST(VectorSizesAreNotEqual_ThrowsAnomaly)
   {
      const vector<T> expectedVector(1);
      const vector<T> actualVector;
      THROWS(VECTORS_EQUAL(expectedVector, actualVector),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_EQUAL(expectedVector, actualVector)",
"Expected: std::vector<" + TypeName + "> (size 1):",
"{",
"   " + ToStringer::ToString(expectedVector[0]),
"}",
"  Actual: std::vector<" + TypeName + "> (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(VectorSizesAreNotEqual_ThrowsAnomaly_MessagesTestCase)
   {
      const vector<T> expectedVector(1);
      const vector<T> actualVector;
      THROWS(VECTORS_EQUAL(expectedVector, actualVector, _messageA, _messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_EQUAL(expectedVector, actualVector, _messageA, _messageB)",
"Expected: std::vector<" + TypeName + "> (size 1):",
"{",
"   " + ToStringer::ToString(expectedVector[0]),
"}",
"  Actual: std::vector<" + TypeName + "> (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed",
"Expected: 1",
"  Actual: 0",
" Message: \"" + _messageA + "\", \"" + _messageB + "\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(VectorSizesAreEqual_ElementsAreNotEqualAtIndex0_ThrowsAnomaly__MessagesTestCase)
   {
      const T randomElement1 = Random<T>();
      const T randomElement2 = RandomNon0<T>();
      const vector<T> v1 { randomElement1 };
      const vector<T> v2 { randomElement1 + randomElement2 };
      THROWS(VECTORS_EQUAL(v1, v2, _messageA, _messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_EQUAL(v1, v2, _messageA, _messageB)",
"Expected: std::vector<" + TypeName + "> (size 1):",
"{",
"   " + ToStringer::ToString(v1[0]),
"}",
"  Actual: std::vector<" + TypeName + "> (size 1):",
"{",
"   " + ToStringer::ToString(v2[0]),
"}",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(v1[0]),
"  Actual: " + ToStringer::ToString(v2[0]),
" Message: \"i=0\"",
" Message: \"" + _messageA + "\", \"" + _messageB + "\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(VectorSizesAreEqual_ElementsAreNotEqualAtIndex1_ThrowsAnomaly)
   {
      const T randomElement1 = Random<T>();
      const T randomElement2 = RandomNon0<T>();
      const T randomElement3 = RandomNon0<T>();
      const vector<T> v1 { randomElement1, randomElement2 };
      const vector<T> v2 { randomElement1, randomElement3 };
      THROWS(VECTORS_EQUAL(v1, v2),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_EQUAL(v1, v2)",
"Expected: std::vector<" + TypeName + "> (size 2):",
"{",
"   " + ToStringer::ToString(v1[0]) + ",",
"   " + ToStringer::ToString(v1[1]),
"}",
"  Actual: std::vector<" + TypeName + "> (size 2):",
"{",
"   " + ToStringer::ToString(v2[0]) + ",",
"   " + ToStringer::ToString(v2[1]),
"}",
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
"Expected: " + ToStringer::ToString(v1[1]),
"  Actual: " + ToStringer::ToString(v2[1]),
" Message: \"i=1\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   RUN_TEMPLATE_TESTS(VECTORS_EQUALTests, char)
   THEN_RUN_TEMPLATE_TESTS(VECTORS_EQUALTests, int)
   THEN_RUN_TEMPLATE_TESTS(VECTORS_EQUALTests, size_t)
   THEN_RUN_TEMPLATE_TESTS(VECTORS_EQUALTests, string)
}

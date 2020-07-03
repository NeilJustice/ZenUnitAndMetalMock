#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(INDEXABLES_ARE_EQUALTests, T)
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
      vector<T> expectedIndexableDataStructure;;
      vector<T> actualIndexableDataStructure;

      INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure);

      const T randomElement1 = Random<T>();
      expectedIndexableDataStructure.push_back(randomElement1);
      actualIndexableDataStructure.push_back(randomElement1);
      INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure);

      const T randomElement2 = Random<T>();
      expectedIndexableDataStructure.push_back(randomElement2);
      actualIndexableDataStructure.push_back(randomElement2);
      INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure);

      const T randomElement3 = Random<T>();
      expectedIndexableDataStructure.push_back(randomElement3);
      actualIndexableDataStructure.push_back(randomElement3);
      INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure);
   }

   TEST(VectorSizesAreNotEqual_ThrowsAnomaly)
   {
      const vector<T> expectedIndexableDataStructure(1);
      const vector<T> actualIndexableDataStructure;
      THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure)",
"Expected: std::vector<" + TypeName + "> (size 1):",
"{",
"   " + ToStringer::ToString(expectedIndexableDataStructure[0]),
"}",
"  Actual: std::vector<" + TypeName + "> (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(VectorSizesAreNotEqual_ThrowsAnomaly_MessagesTestCase)
   {
      const vector<T> expectedIndexableDataStructure(1);
      const vector<T> actualIndexableDataStructure;
      THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure, _messageA, _messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure, _messageA, _messageB)",
"Expected: std::vector<" + TypeName + "> (size 1):",
"{",
"   " + ToStringer::ToString(expectedIndexableDataStructure[0]),
"}",
"  Actual: std::vector<" + TypeName + "> (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed",
"Expected: 1",
"  Actual: 0",
" Message: \"" + _messageA + "\", \"" + _messageB + "\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(VectorSizesAreEqual_ElementsAreNotEqualAtIndex0_ThrowsAnomaly__MessagesTestCase)
   {
      const T randomElement1 = Random<T>();
      const vector<T> v1 { randomElement1 };
      const vector<T> v2 { randomElement1 + T{1} };
      THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL(v1, v2, _messageA, _messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: INDEXABLES_ARE_EQUAL(v1, v2, _messageA, _messageB)",
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
      THROWS_EXCEPTION(INDEXABLES_ARE_EQUAL(v1, v2),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: INDEXABLES_ARE_EQUAL(v1, v2)",
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

   RUN_TEMPLATE_TESTS(INDEXABLES_ARE_EQUALTests, int)
   THEN_RUN_TEMPLATE_TESTS(INDEXABLES_ARE_EQUALTests, size_t)
   THEN_RUN_TEMPLATE_TESTS(INDEXABLES_ARE_EQUALTests, string)
}

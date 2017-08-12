#include "pch.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATETESTS(VECTORS_EQUALTests, T)
   FACT(VectorSizesNotEqual_Throws)
   FACT(VectorSizesNotEqual_Throws_MessagesTestCase)
   FACT(VectorSizesEqual_ElementsNotEqualAtIndex0_Throws_MessagesTestCase)
   FACT(VectorSizesEqual_ElementsNotEqualAtIndex1_Throws)
   FACT(TwoEmptyVectors_DoesNotThrow)
   FACT(VectorSizesEqual_VectorElementsEqual_DoesNotThrow)
   BEGINPROOF

   const string MessageA = "A", MessageB = "B";

   TEST(VectorSizesNotEqual_Throws)
   {
      const vector<T> expectedVector { 1 };
      const vector<T> actualVector;
      THROWS(VECTORS_EQUAL(expectedVector, actualVector), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedVector, actualVector)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))");
   }

   TEST(VectorSizesNotEqual_Throws_MessagesTestCase)
   {
      const vector<T> expectedVector { 1 };
      const vector<T> actualVector;
      THROWS(VECTORS_EQUAL(expectedVector, actualVector, MessageA, MessageB), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedVector, actualVector, MessageA, MessageB)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 0
 Message: "A", "B"
File.cpp(1)
File.cpp(1))");
   }

   TEST(VectorSizesEqual_ElementsNotEqualAtIndex0_Throws_MessagesTestCase)
   {
      const vector<T> v1 { 1 };
      const vector<T> v2 { 2 };
      THROWS(VECTORS_EQUAL(v1, v2, MessageA, MessageB), Anomaly, R"(
  Failed: VECTORS_EQUAL(v1, v2, MessageA, MessageB)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: )" + ToStringer::ToString(v1[0]) + R"(
  Actual: )" + ToStringer::ToString(v2[0]) + R"(
 Message: "i=0"
 Message: "A", "B"
File.cpp(1)
File.cpp(1))");
   }

   TEST(VectorSizesEqual_ElementsNotEqualAtIndex1_Throws)
   {
      const vector<T> v1 { 0, 1 };
      const vector<T> v2 { 0, 2 };
      THROWS(VECTORS_EQUAL(v1, v2), Anomaly, R"(
  Failed: VECTORS_EQUAL(v1, v2)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: )" + ToStringer::ToString(v1[1]) + R"(
  Actual: )" + ToStringer::ToString(v2[1]) + R"(
 Message: "i=1"
File.cpp(1)
File.cpp(1))");
   }

   TEST(TwoEmptyVectors_DoesNotThrow)
   {
      const vector<T> expectedVector;
      const vector<T> actualVector;
      VECTORS_EQUAL(expectedVector, actualVector);
   }

   TEST(VectorSizesEqual_VectorElementsEqual_DoesNotThrow)
   {
      vector<T> expectedVector;;
      vector<T> actualVector;

      expectedVector.push_back(1);
      actualVector.push_back(1);
      VECTORS_EQUAL(expectedVector, actualVector);

      expectedVector.push_back(2);
      actualVector.push_back(2);
      VECTORS_EQUAL(expectedVector, actualVector);
   }

   };
   RUNTEMPLATE(VECTORS_EQUALTests, int)
   RUNTEMPLATE(VECTORS_EQUALTests, UserType)
}

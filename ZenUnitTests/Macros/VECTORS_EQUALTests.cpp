#include "pch.h"
#include "ZenUnitTests/Testing/UserType.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(VECTORS_EQUALTests, T)
   AFACT(VectorSizesNotEqual_Throws)
   AFACT(VectorSizesNotEqual_Throws_MessagesTestCase)
   AFACT(VectorSizesEqual_ElementsNotEqualAtIndex0_Throws_MessagesTestCase)
   AFACT(VectorSizesEqual_ElementsNotEqualAtIndex1_Throws)
   AFACT(TwoEmptyVectors_DoesNotThrow)
   AFACT(VectorSizesEqual_VectorElementsEqual_DoesNotThrow)
   EVIDENCE

   const string TypeName = *Type::GetName<T>();
   const string MessageA = "A";
   const string MessageB = "B";

   TEST(VectorSizesNotEqual_Throws)
   {
      const vector<T> expectedVector { 1 };
      const vector<T> actualVector;
      THROWS(VECTORS_EQUAL(expectedVector, actualVector), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedVector, actualVector)
Expected: vector<)" + TypeName + R"(>: {1}
  Actual: vector<)" + TypeName + R"(>: {}
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
Expected: vector<)" + TypeName + R"(>: {1}
  Actual: vector<)" + TypeName + R"(>: {}
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
Expected: vector<)" + TypeName + R"(>: {1}
  Actual: vector<)" + TypeName + R"(>: {2}
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
Expected: vector<)" + TypeName + R"(>: {0, 1}
  Actual: vector<)" + TypeName + R"(>: {0, 2}
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
   RUN_TEMPLATE_TESTS(VECTORS_EQUALTests, int)
   RUN_TEMPLATE_TESTS(VECTORS_EQUALTests, unsigned)
}

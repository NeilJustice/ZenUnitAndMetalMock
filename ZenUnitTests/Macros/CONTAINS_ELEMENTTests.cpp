#include "pch.h"

//namespace ZenUnit
//{
//   TESTS(CONTAINS_ELEMENTTests)
//   AFACT(Vector_DoesContainElement_DoesNotThrow)
//   AFACT(Vector_DoesNotContainElement_Throws)
//   AFACT(Map_DoesContainElement_DoesNotThrow)
//   AFACT(Map_DoesNotContainElement_Throws)
//   AFACT(Set_DoesContainElement_DoesNotThrow)
//   AFACT(Set_DoesNotContainElement_Throws_MessagesTestCase)
//   EVIDENCE
//
//   TEST(Vector_DoesContainElement_DoesNotThrow)
//   {
//      const vector<int> ints { 1, 2 };
//      CONTAINS_ELEMENT(1, ints);
//      CONTAINS_ELEMENT(2, ints);
//      for (const int i : ints)
//      {
//         CONTAINS_ELEMENT(i, ints);
//      }
//   }
//
//   TEST(Vector_DoesNotContainElement_Throws)
//   {
//      const vector<int> emptyIntVector;
//      THROWS(CONTAINS_ELEMENT(0, emptyIntVector), Anomaly, R"(
//  Failed: CONTAINS_ELEMENT(0, emptyIntVector)
//Expected: Collection contains element '0'
//  Actual: Collection does not contain element '0'
//File.cpp(1))");
//   }
//
//   TEST(Map_DoesContainElement_DoesNotThrow)
//   {
//      const map<int, int> intIntMap { { 0, 0 }, { 1, 1 } };
//      const pair<const int, int> kvp0(0, 0);
//      const pair<const int, int> kvp1(1, 1);
//      CONTAINS_ELEMENT(kvp0, intIntMap);
//      CONTAINS_ELEMENT(kvp1, intIntMap);
//      for (const auto& kvp : intIntMap)
//      {
//         CONTAINS_ELEMENT(kvp, intIntMap);
//      }
//   }
//
//   TEST(Map_DoesNotContainElement_Throws)
//   {
//      const map<int, int> emptyIntIntMap;
//      const pair<const int, int> kvp(0, 0);
//      THROWS(CONTAINS_ELEMENT(kvp, emptyIntIntMap), Anomaly, R"(
//  Failed: CONTAINS_ELEMENT(kvp, emptyIntIntMap)
//Expected: Collection contains element '(0, 0)'
//  Actual: Collection does not contain element '(0, 0)'
//File.cpp(1))");
//   }
//
//   TEST(Set_DoesContainElement_DoesNotThrow)
//   {
//      const set<int> intSet { 1, 2 };
//      CONTAINS_ELEMENT(1, intSet);
//      CONTAINS_ELEMENT(2, intSet);
//      for (int i : intSet)
//      {
//         CONTAINS_ELEMENT(i, intSet);
//      }
//   }
//
//   TEST(Set_DoesNotContainElement_Throws_MessagesTestCase)
//   {
//      const set<int> emptyIntSet;
//      const string messageA = "A", messageB = "B";
//      THROWS(CONTAINS_ELEMENT(0, emptyIntSet, messageA, messageB), Anomaly, R"(
//  Failed: CONTAINS_ELEMENT(0, emptyIntSet, messageA, messageB)
//Expected: Collection contains element '0'
//  Actual: Collection does not contain element '0'
// Message: "A", "B"
//File.cpp(1))");
//   }
//
//   }; RUNTESTS(CONTAINS_ELEMENTTests)
//}

#include "pch.h"
#include "ZenUnit/Macros/CONTAINS.h"

namespace ZenUnit
{
   TESTS(CONTAINSTests)
   FACT(Vector_DoesContainElement_DoesNotThrow)
   FACT(Vector_DoesNotContainElement_Throws)
   FACT(Map_DoesContainElement_DoesNotThrow)
   FACT(Map_DoesNotContainElement_Throws)
   FACT(Set_DoesContainElement_DoesNotThrow)
   FACT(Set_DoesNotContainElement_Throws_MessagesTestCase)
   EVIDENCE

   TEST(Vector_DoesContainElement_DoesNotThrow)
   {
      const vector<int> ints { 1, 2 };
      CONTAINS(1, ints);
      CONTAINS(2, ints);
      for (int i : ints)
      {
         CONTAINS(i, ints);
      }
   }

   TEST(Vector_DoesNotContainElement_Throws)
   {
      const vector<int> emptyIntVector;
      THROWS(CONTAINS(0, emptyIntVector), Anomaly, R"(
  Failed: CONTAINS(0, emptyIntVector)
Expected: Contains element 0
  Actual: Contains no such element
File.cpp(1))");
   }

   TEST(Map_DoesContainElement_DoesNotThrow)
   {
      const map<int, int> intIntMap { { 0, 0 }, { 1, 1 } };
      const pair<const int, int> kvp0(0, 0);
      const pair<const int, int> kvp1(1, 1);
      CONTAINS(kvp0, intIntMap);
      CONTAINS(kvp1, intIntMap);
      for (const auto& kvp : intIntMap)
      {
         CONTAINS(kvp, intIntMap);
      }
   }

   TEST(Map_DoesNotContainElement_Throws)
   {
      const map<int, int> emptyIntIntMap;
      const pair<const int, int> kvp(0, 0);
      THROWS(CONTAINS(kvp, emptyIntIntMap), Anomaly, R"(
  Failed: CONTAINS(kvp, emptyIntIntMap)
Expected: Contains element (0, 0)
  Actual: Contains no such element
File.cpp(1))");
   }

   TEST(Set_DoesContainElement_DoesNotThrow)
   {
      const set<int> intSet { 1, 2 };
      CONTAINS(1, intSet);
      CONTAINS(2, intSet);
      for (int i : intSet)
      {
         CONTAINS(i, intSet);
      }
   }

   TEST(Set_DoesNotContainElement_Throws_MessagesTestCase)
   {
      const set<int> emptyIntSet;
      const string messageA = "A", messageB = "B";
      THROWS(CONTAINS(0, emptyIntSet, messageA, messageB), Anomaly, R"(
  Failed: CONTAINS(0, emptyIntSet, messageA, messageB)
Expected: Contains element 0
  Actual: Contains no such element
 Message: "A", "B"
File.cpp(1))");
   }

   RUNTESTS(CONTAINSTests)
}

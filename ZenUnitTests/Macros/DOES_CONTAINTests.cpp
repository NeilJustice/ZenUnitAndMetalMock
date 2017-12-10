#include "pch.h"

namespace ZenUnit
{
   TESTS(DOES_CONTAINTests)
   AFACT(Vector_DoesContainElement_DoesNotThrow)
   AFACT(Vector_DoesNotContainElement_Throws)
   AFACT(Map_DoesContainElement_DoesNotThrow)
   AFACT(Map_DoesNotContainElement_Throws)
   AFACT(Set_DoesContainElement_DoesNotThrow)
   AFACT(Set_DoesNotContainElement_Throws_MessagesTestCase)
   EVIDENCE

   TEST(Vector_DoesContainElement_DoesNotThrow)
   {
      const vector<int> ints { 1, 2 };
      DOES_CONTAIN(1, ints);
      DOES_CONTAIN(2, ints);
      for (const int i : ints)
      {
         DOES_CONTAIN(i, ints);
      }
   }

   TEST(Vector_DoesNotContainElement_Throws)
   {
      const vector<int> emptyIntVector;
      THROWS(DOES_CONTAIN(0, emptyIntVector), Anomaly, R"(
  Failed: DOES_CONTAIN(0, emptyIntVector)
Expected: Contains element 0
  Actual: Contains no such element
File.cpp(1))");
   }

   TEST(Map_DoesContainElement_DoesNotThrow)
   {
      const map<int, int> intIntMap { { 0, 0 }, { 1, 1 } };
      const pair<const int, int> kvp0(0, 0);
      const pair<const int, int> kvp1(1, 1);
      DOES_CONTAIN(kvp0, intIntMap);
      DOES_CONTAIN(kvp1, intIntMap);
      for (const auto& kvp : intIntMap)
      {
         DOES_CONTAIN(kvp, intIntMap);
      }
   }

   TEST(Map_DoesNotContainElement_Throws)
   {
      const map<int, int> emptyIntIntMap;
      const pair<const int, int> kvp(0, 0);
      THROWS(DOES_CONTAIN(kvp, emptyIntIntMap), Anomaly, R"(
  Failed: DOES_CONTAIN(kvp, emptyIntIntMap)
Expected: Contains element (0, 0)
  Actual: Contains no such element
File.cpp(1))");
   }

   TEST(Set_DoesContainElement_DoesNotThrow)
   {
      const set<int> intSet { 1, 2 };
      DOES_CONTAIN(1, intSet);
      DOES_CONTAIN(2, intSet);
      for (int i : intSet)
      {
         DOES_CONTAIN(i, intSet);
      }
   }

   TEST(Set_DoesNotContainElement_Throws_MessagesTestCase)
   {
      const set<int> emptyIntSet;
      const string messageA = "A", messageB = "B";
      THROWS(DOES_CONTAIN(0, emptyIntSet, messageA, messageB), Anomaly, R"(
  Failed: DOES_CONTAIN(0, emptyIntSet, messageA, messageB)
Expected: Contains element 0
  Actual: Contains no such element
 Message: "A", "B"
File.cpp(1))");
   }

   }; RUNTESTS(DOES_CONTAINTests)
}

#include "pch.h"
#include "ZenUnit/Macros/CONTAINS.h"

namespace ZenUnit
{
   TESTS(CONTAINSTests)
   SPEC(Vector_DoesContain_DoesNotThrow)
   SPEC(Vector_DoesNotContain_Throws)
   SPEC(Map_DoesContain_DoesNotThrow)
   SPEC(Map_DoesNotContain_Throws)
   SPEC(Set_DoesContain_DoesNotThrow)
   SPEC(Set_DoesNotContain_Throws_MessagesTestCase)
   SPECEND

   TEST(Vector_DoesContain_DoesNotThrow)
   {
      vector<int> ints = { 1, 2 };
      CONTAINS(1, ints);
      CONTAINS(2, ints);
      for (int i : ints)
      {
         CONTAINS(i, ints);
      }
   }

   TEST(Vector_DoesNotContain_Throws)
   {
      vector<int> emptyIntVector;
      THROWS(CONTAINS(0, emptyIntVector), Anomaly, R"(
  Failed: CONTAINS(0, emptyIntVector)
Expected: Contains element 0
  Actual: Contains no such element
File.cpp(1))");
   }

   TEST(Map_DoesContain_DoesNotThrow)
   {
      map<int, int> intIntMap = { { 0, 0 }, { 1, 1 } };
      pair<const int, int> kvp0(0, 0);
      pair<const int, int> kvp1(1, 1);
      CONTAINS(kvp0, intIntMap);
      CONTAINS(kvp1, intIntMap);
      for (const auto& kvp : intIntMap)
      {
         CONTAINS(kvp, intIntMap);
      }
   }

   TEST(Map_DoesNotContain_Throws)
   {
      map<int, int> emptyIntIntMap;
      pair<const int, int> kvp(0, 0);
      THROWS(CONTAINS(kvp, emptyIntIntMap), Anomaly, R"(
  Failed: CONTAINS(kvp, emptyIntIntMap)
Expected: Contains element (0, 0)
  Actual: Contains no such element
File.cpp(1))");
   }

   TEST(Set_DoesContain_DoesNotThrow)
   {
      set<int> intSet = { 1, 2 };
      CONTAINS(1, intSet);
      CONTAINS(2, intSet);
      for (int i : intSet)
      {
         CONTAINS(i, intSet);
      }
   }

   TEST(Set_DoesNotContain_Throws_MessagesTestCase)
   {
      set<int> emptyIntSet;
      string messageA = "A", messageB = "B";
      THROWS(CONTAINS(0, emptyIntSet, messageA, messageB), Anomaly, R"(
  Failed: CONTAINS(0, emptyIntSet, messageA, messageB)
Expected: Contains element 0
  Actual: Contains no such element
 Message: "A", "B"
File.cpp(1))");
   }

   }; RUN(CONTAINSTests)
}

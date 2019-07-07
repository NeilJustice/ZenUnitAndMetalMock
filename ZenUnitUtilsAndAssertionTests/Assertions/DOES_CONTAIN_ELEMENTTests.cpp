#include "pch.h"

namespace ZenUnit
{
   TESTS(DOES_CONTAIN_ELEMENTTests)
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
      DOES_CONTAIN_ELEMENT(1, ints);
      DOES_CONTAIN_ELEMENT(2, ints);
      for (const int i : ints)
      {
         DOES_CONTAIN_ELEMENT(i, ints);
      }
   }

   TEST(Vector_DoesNotContainElement_Throws)
   {
      const vector<int> emptyIntVector;
      THROWS(DOES_CONTAIN_ELEMENT(0, emptyIntVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_CONTAIN_ELEMENT(0, emptyIntVector)",
"Expected: Collection contains element '0'",
"  Actual: Collection does not contain element '0'",
"File.cpp(1)"));
   }

   TEST(Map_DoesContainElement_DoesNotThrow)
   {
      const map<int, int> intIntMap { { 0, 0 }, { 1, 1 } };
      const pair<const int, int> kvp0(0, 0);
      const pair<const int, int> kvp1(1, 1);
      DOES_CONTAIN_ELEMENT(kvp0, intIntMap);
      DOES_CONTAIN_ELEMENT(kvp1, intIntMap);
      for (const auto& kvp : intIntMap)
      {
         DOES_CONTAIN_ELEMENT(kvp, intIntMap);
      }
   }

   TEST(Map_DoesNotContainElement_Throws)
   {
      const map<int, int> emptyIntIntMap;
      const pair<const int, int> kvp(0, 0);
      THROWS(DOES_CONTAIN_ELEMENT(kvp, emptyIntIntMap), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_CONTAIN_ELEMENT(kvp, emptyIntIntMap)",
"Expected: Collection contains element '(0, 0)'",
"  Actual: Collection does not contain element '(0, 0)'",
"File.cpp(1)"));
   }

   TEST(Set_DoesContainElement_DoesNotThrow)
   {
      const set<int> intSet { 1, 2 };
      DOES_CONTAIN_ELEMENT(1, intSet);
      DOES_CONTAIN_ELEMENT(2, intSet);
      for (int i : intSet)
      {
         DOES_CONTAIN_ELEMENT(i, intSet);
      }
   }

   TEST(Set_DoesNotContainElement_Throws_MessagesTestCase)
   {
      const set<int> emptyIntSet;
      const string messageA = "A", messageB = "B";
      THROWS(DOES_CONTAIN_ELEMENT(0, emptyIntSet, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOES_CONTAIN_ELEMENT(0, emptyIntSet, messageA, messageB)",
"Expected: Collection contains element '0'",
"  Actual: Collection does not contain element '0'",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(DOES_CONTAIN_ELEMENTTests)
}

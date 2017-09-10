#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      class SetType>
   TEMPLATETESTS(SETS_EQUALTests, SetType)
   AFACT(EmptySets_DoesNotThrow)
   AFACT(OneEqualElement_DoesNotThrow)
   AFACT(TwoEqualElements_DoesNotThrow)
   AFACT(DifferentSize_Throws)
   AFACT(SameSize1_ElementsNotEqual_Throws_MessagesTestCase)
   AFACT(SameSize2_ElementsNotEqual_Throws)
   AFACT(UserTypeSets_SameSize1_ElementsNotEqual_Throws)
   EVIDENCE

   TEST(EmptySets_DoesNotThrow)
   {
      SetType<int> expectedSet, actualSet;
      SETS_EQUAL(expectedSet, actualSet);
   }

   TEST(OneEqualElement_DoesNotThrow)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      SetType<int> actualSet;
      actualSet.insert(1);
      SETS_EQUAL(expectedSet, actualSet);
   }

   TEST(TwoEqualElements_DoesNotThrow)
   {
      SetType<int> expectedSetAscending;
      expectedSetAscending.insert(1);
      expectedSetAscending.insert(2);
      SetType<int> actualSetAscending;
      actualSetAscending.insert(1);
      actualSetAscending.insert(2);
      SETS_EQUAL(expectedSetAscending, actualSetAscending);

      SetType<int> actualSetDescending;
      actualSetDescending.insert(2);
      actualSetDescending.insert(1);
      SETS_EQUAL(expectedSetAscending, actualSetDescending);
   }

   TEST(DifferentSize_Throws)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      SetType<int> actualSet;
      THROWS(SETS_EQUAL(expectedSet, actualSet), Anomaly, R"(
  Failed: SETS_EQUAL(expectedSet, actualSet)
Expected: SetType<T>
  Actual: SetType<T>
 Because: ARE_EQUAL(expectedSet.size(), actualSet.size()) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))");
   }

   TEST(SameSize1_ElementsNotEqual_Throws_MessagesTestCase)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      SetType<int> actualSet;
      actualSet.insert(2);
      const string messageA = "A", messageB = "B";
      THROWS(SETS_EQUAL(expectedSet, actualSet, messageA, messageB), Anomaly, R"(
  Failed: SETS_EQUAL(expectedSet, actualSet, messageA, messageB)
Expected: SetType<T>
  Actual: SetType<T>
 Because: DOES_CONTAIN(expectedElement, actualSet) failed
Expected: Contains element 1
  Actual: Contains no such element
 Message: "A", "B"
File.cpp(1)
File.cpp(1))");
   }

   TEST(SameSize2_ElementsNotEqual_Throws)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      expectedSet.insert(3);
      SetType<int> actualSet;
      actualSet.insert(1);
      actualSet.insert(2);
      THROWS(SETS_EQUAL(expectedSet, actualSet), Anomaly, R"(
  Failed: SETS_EQUAL(expectedSet, actualSet)
Expected: SetType<T>
  Actual: SetType<T>
 Because: DOES_CONTAIN(expectedElement, actualSet) failed
Expected: Contains element 3
  Actual: Contains no such element
File.cpp(1)
File.cpp(1))");
   }

   TEST(UserTypeSets_SameSize1_ElementsNotEqual_Throws)
   {
      SetType<UserType> expectedSet;
      expectedSet.insert(UserType(1));
      SetType<UserType> actualSet;
      actualSet.insert(UserType(2));
      THROWS(SETS_EQUAL(expectedSet, actualSet), Anomaly, R"(
  Failed: SETS_EQUAL(expectedSet, actualSet)
Expected: SetType<T>
  Actual: SetType<T>
 Because: DOES_CONTAIN(expectedElement, actualSet) failed
Expected: Contains element UserType@1
  Actual: Contains no such element
File.cpp(1)
File.cpp(1))");
   }

   };
   RUNTEMPLATETESTS(SETS_EQUALTests, set)
   RUNTEMPLATETESTS(SETS_EQUALTests, unordered_set)
}

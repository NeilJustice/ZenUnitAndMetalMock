#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      class SetType>
   TEMPLATE_TESTS(SETS_ARE_EQUALTests, SetType)
   AFACT(EmptySets_DoesNotThrowException)
   AFACT(OneEqualElement_DoesNotThrowException)
   AFACT(TwoEqualElements_DoesNotThrowException)
   AFACT(DifferentSize_Throws)
   AFACT(SameSize1_ElementsNotEqual_Throws_MessagesTestCase)
   AFACT(SameSize2_ElementsNotEqual_Throws)
   AFACT(UserTypeSets_SameSize1_ElementsNotEqual_Throws)
   EVIDENCE

   string _expectedIntSetTypeName;
   string _expectedUserTypeSetTypeName;

   STARTUP
   {
      _expectedIntSetTypeName = *Type::GetName<SetType<int>>();
      _expectedUserTypeSetTypeName = *Type::GetName<SetType<UserType>>();
   }

   TEST(EmptySets_DoesNotThrowException)
   {
      SetType<int> expectedSet, actualSet;
      SETS_ARE_EQUAL(expectedSet, actualSet);
   }

   TEST(OneEqualElement_DoesNotThrowException)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      SetType<int> actualSet;
      actualSet.insert(1);
      SETS_ARE_EQUAL(expectedSet, actualSet);
   }

   TEST(TwoEqualElements_DoesNotThrowException)
   {
      SetType<int> expectedSetAscending;
      expectedSetAscending.insert(1);
      expectedSetAscending.insert(2);
      SetType<int> actualSetAscending;
      actualSetAscending.insert(1);
      actualSetAscending.insert(2);
      SETS_ARE_EQUAL(expectedSetAscending, actualSetAscending);

      SetType<int> actualSetDescending;
      actualSetDescending.insert(2);
      actualSetDescending.insert(1);
      SETS_ARE_EQUAL(expectedSetAscending, actualSetDescending);
   }

   TEST(DifferentSize_Throws)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      SetType<int> actualSet;
      THROWS_EXCEPTION(SETS_ARE_EQUAL(expectedSet, actualSet), Anomaly, TestUtil::NewlineConcat("",
"  Failed: SETS_ARE_EQUAL(expectedSet, actualSet)",
"Expected: " + _expectedIntSetTypeName,
"{",
"   1",
"}",
"  Actual: " + _expectedIntSetTypeName,
"{",
"}",
" Because: ARE_EQUAL(expectedSet.size(), actualSet.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(SameSize1_ElementsNotEqual_Throws_MessagesTestCase)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      SetType<int> actualSet;
      actualSet.insert(2);
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(SETS_ARE_EQUAL(expectedSet, actualSet, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: SETS_ARE_EQUAL(expectedSet, actualSet, messageA, messageB)",
"Expected: " + _expectedIntSetTypeName,
"{",
"   1",
"}",
"  Actual: " + _expectedIntSetTypeName,
"{",
"   2",
"}",
" Because: CONTAINS_ELEMENT(expectedElement, actualSet) failed",
"Expected: Collection contains element '1'",
"  Actual: Collection does not contain element '1'",
" Message: \"A\", \"B\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(SameSize2_ElementsNotEqual_Throws)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      expectedSet.insert(3);
      SetType<int> actualSet;
      actualSet.insert(1);
      actualSet.insert(2);
      THROWS_EXCEPTION(SETS_ARE_EQUAL(expectedSet, actualSet), Anomaly, TestUtil::NewlineConcat("",
"  Failed: SETS_ARE_EQUAL(expectedSet, actualSet)",
"Expected: " + _expectedIntSetTypeName,
"{",
"   1,",
"   3",
"}",
"  Actual: " + _expectedIntSetTypeName,
"{",
"   1,",
"   2",
"}",
" Because: CONTAINS_ELEMENT(expectedElement, actualSet) failed",
"Expected: Collection contains element '3'",
"  Actual: Collection does not contain element '3'",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(UserTypeSets_SameSize1_ElementsNotEqual_Throws)
   {
      SetType<UserType> expectedSet;
      expectedSet.insert(UserType(1));
      SetType<UserType> actualSet;
      actualSet.insert(UserType(2));
      THROWS_EXCEPTION(SETS_ARE_EQUAL(expectedSet, actualSet), Anomaly, TestUtil::NewlineConcat("",
"  Failed: SETS_ARE_EQUAL(expectedSet, actualSet)",
"Expected: " + _expectedUserTypeSetTypeName,
"{",
"   UserType@1",
"}",
"  Actual: " + _expectedUserTypeSetTypeName,
"{",
"   UserType@2",
"}",
" Because: CONTAINS_ELEMENT(expectedElement, actualSet) failed",
"Expected: Collection contains element 'UserType@1'",
"  Actual: Collection does not contain element 'UserType@1'",
"File.cpp(1)",
"File.cpp(1)"));
   }

   RUN_TEMPLATE_TESTS(SETS_ARE_EQUALTests, set)
   //THEN_RUN_TEMPLATE_TESTS(SETS_ARE_EQUALTests, unordered_set)
}
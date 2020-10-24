#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      class SetType>
   TEMPLATE_TESTS(SETS_ARE_EQUALTests, SetType)
   AFACT(EmptySets_DoesNotThrowException)
   AFACT(ConstNonConstEmptySets_CompilesAndDoesNotThrowException)
   AFACT(SetsWithOneEqualElement_DoesNotThrowException)
   AFACT(SetsWithTwoEqualElements_DoesNotThrowException)
   AFACT(SetsWithDifferentSizes_ThrowsAnomaly)
   AFACT(SetsWithSameSizeOf1_ElementsAreNotEqual_ThrowsAnomaly__MessagesTestCase)
   AFACT(UserTypeSetsWithSameSizeOf1_ElementsAreNotEqual_ThrowsAnomaly)
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
      SetType<int> expectedEmptySet;
      SetType<int> actualEmptySet;
      SETS_ARE_EQUAL(expectedEmptySet, actualEmptySet);
   }

   TEST(ConstNonConstEmptySets_CompilesAndDoesNotThrowException)
   {
      const SetType<int> constSet;
      SetType<int> nonConstSet;
      SETS_ARE_EQUAL(constSet, nonConstSet);
      SETS_ARE_EQUAL(nonConstSet, constSet);
   }

   TEST(SetsWithOneEqualElement_DoesNotThrowException)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      SetType<int> actualSet;
      actualSet.insert(1);
      SETS_ARE_EQUAL(expectedSet, actualSet);
   }

   TEST(SetsWithTwoEqualElements_DoesNotThrowException)
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

   TEST(SetsWithDifferentSizes_ThrowsAnomaly)
   {
      SetType<int> expectedSet;
      expectedSet.insert(1);
      SetType<int> actualSet;
      THROWS_EXCEPTION(SETS_ARE_EQUAL(expectedSet, actualSet),
         Anomaly, TestUtil::NewlineConcat("",
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

   TEST(SetsWithSameSizeOf1_ElementsAreNotEqual_ThrowsAnomaly__MessagesTestCase)
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

   TEST(UserTypeSetsWithSameSizeOf1_ElementsAreNotEqual_ThrowsAnomaly)
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
   THEN_RUN_TEMPLATE_TESTS(SETS_ARE_EQUALTests, unordered_set)
}

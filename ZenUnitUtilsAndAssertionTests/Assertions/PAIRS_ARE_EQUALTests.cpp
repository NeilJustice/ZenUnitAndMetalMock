#include "pch.h"

namespace ZenUnit
{
   TESTS(PAIRS_ARE_EQUALTests)
   AFACT(FirstValueIsEqual_SecondValueIsEqual_DoesNotThrowException)
   AFACT(FirstValueIsEqual_SecondValueIsEqual_DoesNotThrowException__UserTypeTestCase)
   AFACT(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly)
   AFACT(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly__MessagesTestCase)
   AFACT(FirstValueIsEqual_SecondValueIsNotEqual_ThrowsAnomaly)
   AFACT(FirstValueIsNotEqual_SecondValueIsNotEqual_ThrowsAnomaly)
   AFACT(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly_UserTypeTestCase)
   AFACT(FirstValueIsEqual_SecondValueIsNotEqual_ThrowsAnomaly__UserTypeTestCase)
   EVIDENCE

   TEST(FirstValueIsEqual_SecondValueIsEqual_DoesNotThrowException)
   {
      const pair<int, int> constExpectedPair;
      const pair<int, int> constActualPair;
      PAIRS_ARE_EQUAL(constExpectedPair, constActualPair);

      pair<int, int> nonConstExpectedPair;
      pair<int, int> nonConstActualPair;
      PAIRS_ARE_EQUAL(nonConstExpectedPair, nonConstActualPair);

      PAIRS_ARE_EQUAL(constExpectedPair, nonConstActualPair);
      PAIRS_ARE_EQUAL(nonConstActualPair, constExpectedPair);
   }

   TEST(FirstValueIsEqual_SecondValueIsEqual_DoesNotThrowException__UserTypeTestCase)
   {
      const UserType value1 = ZenUnit::Random<UserType>();
      const UserType value2 = ZenUnit::Random<UserType>();
      const pair<UserType, UserType> expectedPair{ value1, value2 };
      const pair<UserType, UserType> actualPair{ value1, value2 };
      PAIRS_ARE_EQUAL(expectedPair, actualPair);
   }

   TEST(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly)
   {
      const pair<int, int> expectedPair{1, 0};
      const pair<int, int> actualPair{0, 0};
      THROWS_EXCEPTION(PAIRS_ARE_EQUAL(expectedPair, actualPair), Anomaly, TestUtil::NewlineConcat("",
"  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair)",
"Expected: (1, 0)",
"  Actual: (0, 0)",
" Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly__MessagesTestCase)
   {
      const pair<int, int> expectedPair{1, 0};
      const pair<int, int> actualPair{0, 0};
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(PAIRS_ARE_EQUAL(expectedPair, actualPair, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair, messageA, messageB)",
"Expected: (1, 0)",
"  Actual: (0, 0)",
" Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed",
"Expected: 1",
"  Actual: 0",
" Message: \"A\", \"B\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsNotEqual_SecondValueIsNotEqual_ThrowsAnomaly)
   {
      const pair<int, int> expectedPair{1, 1};
      const pair<int, int> actualPair{0, 0};
      THROWS_EXCEPTION(PAIRS_ARE_EQUAL(expectedPair, actualPair), Anomaly, TestUtil::NewlineConcat("",
"  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair)",
"Expected: (1, 1)",
"  Actual: (0, 0)",
" Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsEqual_SecondValueIsNotEqual_ThrowsAnomaly)
   {
      const pair<int, int> expectedPair{1, 1};
      const pair<int, int> actualPair{1, 0};
      THROWS_EXCEPTION(PAIRS_ARE_EQUAL(expectedPair, actualPair), Anomaly, TestUtil::NewlineConcat("",
"  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair)",
"Expected: (1, 1)",
"  Actual: (1, 0)",
" Because: ARE_EQUAL(expectedPair.second, actualPair.second) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly_UserTypeTestCase)
   {
      const pair<UserType, UserType> expectedPair{1,0};
      const pair<UserType, UserType> actualPair{0,0};
      THROWS_EXCEPTION(PAIRS_ARE_EQUAL(expectedPair, actualPair), Anomaly, TestUtil::NewlineConcat("",
"  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair)",
"Expected: (UserType@1, UserType@0)",
"  Actual: (UserType@0, UserType@0)",
" Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed",
"Expected: UserType@1",
"  Actual: UserType@0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsEqual_SecondValueIsNotEqual_ThrowsAnomaly__UserTypeTestCase)
   {
      const pair<UserType, UserType> expectedPair{0,0};
      const pair<UserType, UserType> actualPair{0,1};
      THROWS_EXCEPTION(PAIRS_ARE_EQUAL(expectedPair, actualPair), Anomaly, TestUtil::NewlineConcat("",
"  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair)",
"Expected: (UserType@0, UserType@0)",
"  Actual: (UserType@0, UserType@1)",
" Because: ARE_EQUAL(expectedPair.second, actualPair.second) failed",
"Expected: UserType@0",
"  Actual: UserType@1",
"File.cpp(1)",
"File.cpp(1)"));
   }

   RUN_TESTS(PAIRS_ARE_EQUALTests)
}

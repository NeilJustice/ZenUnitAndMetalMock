#include "pch.h"
#include "ZenUnit/Macros/PAIRS_EQUAL.h"

namespace ZenUnit
{
   TESTS(PAIRS_EQUALTests)
   SPEC(FirstNotEqual_SecondEqual_Throws)
   SPEC(FirstNotEqual_SecondEqual_Throws_MessagesTestCase)
   SPEC(FirstEqual_SecondNotEqual_Throws)
   SPEC(FirstNotEqual_SecondNotEqual_Throws)
   SPEC(FirstEqual_SecondEqual_DoesNotThrow)
   SPEC(FirstNotEqual_SecondEqual_Throws_UserTypeTestCase)
   SPEC(FirstEqual_SecondNotEqual_Throws_UserTypeTestCase)
   SPEC(FirstEqual_SecondEqual_DoesNotThrow_UserTypeTestCase)
   SPECEND

   TEST(FirstNotEqual_SecondEqual_Throws)
   {
      pair<int, int> expectedPair{1, 0};
      pair<int, int> actualPair{0, 0};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (1, 0)
  Actual: (0, 0)
 Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))");
   }

   TEST(FirstNotEqual_SecondEqual_Throws_MessagesTestCase)
   {
      pair<int, int> expectedPair{1, 0};
      pair<int, int> actualPair{0, 0};
      string messageA = "A", messageB = "B";
      THROWS(PAIRS_EQUAL(expectedPair, actualPair, messageA, messageB), Anomaly, R"(
  Failed: PAIRS_EQUAL(expectedPair, actualPair, messageA, messageB)
Expected: (1, 0)
  Actual: (0, 0)
 Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed
Expected: 1
  Actual: 0
 Message: "A", "B"
File.cpp(1)
File.cpp(1))");
   }

   TEST(FirstNotEqual_SecondNotEqual_Throws)
   {
      pair<int, int> expectedPair{1, 1};
      pair<int, int> actualPair{0, 0};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (1, 1)
  Actual: (0, 0)
 Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))");
   }

   TEST(FirstEqual_SecondNotEqual_Throws)
   {
      pair<int, int> expectedPair{1, 1};
      pair<int, int> actualPair{1, 0};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (1, 1)
  Actual: (1, 0)
 Because: ARE_EQUAL(expectedPair.second, actualPair.second) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))");
   }

   TEST(FirstEqual_SecondEqual_DoesNotThrow)
   {
      pair<int, int> expectedPair;
      pair<int, int> actualPair;
      PAIRS_EQUAL(expectedPair, actualPair);
   }

   TEST(FirstNotEqual_SecondEqual_Throws_UserTypeTestCase)
   {
      pair<UserType, UserType> expectedPair{1,0};
      pair<UserType, UserType> actualPair{0,0};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (UserType@1, UserType@0)
  Actual: (UserType@0, UserType@0)
 Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed
Expected: UserType@1
  Actual: UserType@0
File.cpp(1)
File.cpp(1))");
   }

   TEST(FirstEqual_SecondNotEqual_Throws_UserTypeTestCase)
   {
      pair<UserType, UserType> expectedPair{0,0};
      pair<UserType, UserType> actualPair{0,1};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (UserType@0, UserType@0)
  Actual: (UserType@0, UserType@1)
 Because: ARE_EQUAL(expectedPair.second, actualPair.second) failed
Expected: UserType@0
  Actual: UserType@1
File.cpp(1)
File.cpp(1))");
   }

   TEST(FirstEqual_SecondEqual_DoesNotThrow_UserTypeTestCase)
   {
      pair<UserType, UserType> expectedPair{10,10};
      pair<UserType, UserType> actualPair{10,10};
      PAIRS_EQUAL(expectedPair, actualPair);
   }

   }; RUN(PAIRS_EQUALTests)
}

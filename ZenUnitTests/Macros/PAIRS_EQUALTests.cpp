#include "pch.h"
#include "ZenUnit/Macros/PAIRS_EQUAL.h"

namespace ZenUnit
{
   TESTS(PAIRS_EQUALTests)
   AFACT(FirstNotEqual_SecondEqual_Throws)
   AFACT(FirstNotEqual_SecondEqual_Throws_MessagesTestCase)
   AFACT(FirstEqual_SecondNotEqual_Throws)
   AFACT(FirstNotEqual_SecondNotEqual_Throws)
   AFACT(FirstEqual_SecondEqual_DoesNotThrow)
   AFACT(FirstNotEqual_SecondEqual_Throws_UserTypeTestCase)
   AFACT(FirstEqual_SecondNotEqual_Throws_UserTypeTestCase)
   AFACT(FirstEqual_SecondEqual_DoesNotThrow_UserTypeTestCase)
   EVIDENCE

   TEST(FirstNotEqual_SecondEqual_Throws)
   {
      const pair<int, int> expectedPair{1, 0};
      const pair<int, int> actualPair{0, 0};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"%(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (1, 0)
  Actual: (0, 0)
 Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))%");
   }

   TEST(FirstNotEqual_SecondEqual_Throws_MessagesTestCase)
   {
      const pair<int, int> expectedPair{1, 0};
      const pair<int, int> actualPair{0, 0};
      const string messageA = "A", messageB = "B";
      THROWS(PAIRS_EQUAL(expectedPair, actualPair, messageA, messageB), Anomaly, R"%(
  Failed: PAIRS_EQUAL(expectedPair, actualPair, messageA, messageB)
Expected: (1, 0)
  Actual: (0, 0)
 Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed
Expected: 1
  Actual: 0
 Message: "A", "B"
File.cpp(1)
File.cpp(1))%");
   }

   TEST(FirstNotEqual_SecondNotEqual_Throws)
   {
      const pair<int, int> expectedPair{1, 1};
      const pair<int, int> actualPair{0, 0};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"%(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (1, 1)
  Actual: (0, 0)
 Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))%");
   }

   TEST(FirstEqual_SecondNotEqual_Throws)
   {
      const pair<int, int> expectedPair{1, 1};
      const pair<int, int> actualPair{1, 0};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"%(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (1, 1)
  Actual: (1, 0)
 Because: ARE_EQUAL(expectedPair.second, actualPair.second) failed
Expected: 1
  Actual: 0
File.cpp(1)
File.cpp(1))%");
   }

   TEST(FirstEqual_SecondEqual_DoesNotThrow)
   {
      const pair<int, int> expectedPair;
      const pair<int, int> actualPair;
      PAIRS_EQUAL(expectedPair, actualPair);
   }

   TEST(FirstNotEqual_SecondEqual_Throws_UserTypeTestCase)
   {
      const pair<UserType, UserType> expectedPair{1,0};
      const pair<UserType, UserType> actualPair{0,0};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"%(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (UserType@1, UserType@0)
  Actual: (UserType@0, UserType@0)
 Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed
Expected: UserType@1
  Actual: UserType@0
File.cpp(1)
File.cpp(1))%");
   }

   TEST(FirstEqual_SecondNotEqual_Throws_UserTypeTestCase)
   {
      const pair<UserType, UserType> expectedPair{0,0};
      const pair<UserType, UserType> actualPair{0,1};
      THROWS(PAIRS_EQUAL(expectedPair, actualPair), Anomaly, R"%(
  Failed: PAIRS_EQUAL(expectedPair, actualPair)
Expected: (UserType@0, UserType@0)
  Actual: (UserType@0, UserType@1)
 Because: ARE_EQUAL(expectedPair.second, actualPair.second) failed
Expected: UserType@0
  Actual: UserType@1
File.cpp(1)
File.cpp(1))%");
   }

   TEST(FirstEqual_SecondEqual_DoesNotThrow_UserTypeTestCase)
   {
      const pair<UserType, UserType> expectedPair{10,10};
      const pair<UserType, UserType> actualPair{10,10};
      PAIRS_EQUAL(expectedPair, actualPair);
   }

   }; RUNTESTS(PAIRS_EQUALTests)
}

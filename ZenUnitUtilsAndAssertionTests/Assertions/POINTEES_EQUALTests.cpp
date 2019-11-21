#include "pch.h"

namespace ZenUnit
{
   TESTS(POINTEES_EQUALTests)
   AFACT(ExpectedPointerIsNullptr_ActualPointerIsNullptr_DoesNotThrowException)
   AFACT(ExpectedPointerIsNullptr_ActualPointerIsNotNullptr_ThrowsAnomaly)
   AFACT(ExpectedPointerIsNotNullptr_ActualPointerIsNullptr_ThrowsAnomaly)
   AFACT(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreNotEqual_ThrowsAnomaly__StringPointersTestCase)
   AFACT(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreNotEqual_ThrowsAnomaly__StringPointersTestCase_MessagesTestCase)
   AFACT(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreNotEqual_ThrowsAnomaly__UserTypesTestCase)
   AFACT(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreEqual_DoesNotThrowException__StringPointersTestCase)
   AFACT(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreEqual_DoesNotThrowExceeption__UserTypePointersTestCase)
   EVIDENCE

   TEST(ExpectedPointerIsNullptr_ActualPointerIsNullptr_DoesNotThrowException)
   {
      POINTEES_EQUAL(nullptr, nullptr);
      int* x = nullptr;
      int* y = nullptr;
      POINTEES_EQUAL(x, y);
   }

   TEST(ExpectedPointerIsNullptr_ActualPointerIsNotNullptr_ThrowsAnomaly)
   {
      const int i = 0;
      const int* const intPointer = &i;
      THROWS_EXCEPTION(POINTEES_EQUAL(nullptr, intPointer),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTEES_EQUAL(nullptr, intPointer)",
"Expected: expected pointer != nullptr",
"  Actual: expected pointer == nullptr",
"File.cpp(1)"));
   }

   TEST(ExpectedPointerIsNotNullptr_ActualPointerIsNullptr_ThrowsAnomaly)
   {
      const int i = 0;
      const int* const intPointer = &i;
      THROWS_EXCEPTION(POINTEES_EQUAL(intPointer, nullptr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTEES_EQUAL(intPointer, nullptr)",
"Expected: actual pointer != nullptr",
"  Actual: actual pointer == nullptr",
"File.cpp(1)"));
   }

   TEST(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreNotEqual_ThrowsAnomaly__StringPointersTestCase)
   {
      const string expectedPointee = ZenUnit::Random<string>();
      const string actualPointee = ZenUnit::Random<string>();
      const string* const expectedPointer = &expectedPointee;
      const string* const actualPointer = &actualPointee;
      THROWS_EXCEPTION(POINTEES_EQUAL(expectedPointer, actualPointer),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTEES_EQUAL(expectedPointer, actualPointer)",
"Expected: \"" + expectedPointee + "\"",
"  Actual: \"" + actualPointee + "\"",
" Because: ARE_EQUAL(*expectedPointee, *actualPointee) failed",
"Expected: \"" + expectedPointee + "\"",
"  Actual: \"" + actualPointee + "\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreNotEqual_ThrowsAnomaly__StringPointersTestCase_MessagesTestCase)
   {
      const string expectedPointee = ZenUnit::Random<string>();
      const string actualPointee = ZenUnit::Random<string>();
      const string* const expectedPointer = &expectedPointee;
      const string* const actualPointer = &actualPointee;
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS_EXCEPTION(POINTEES_EQUAL(expectedPointer, actualPointer, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
            "  Failed: POINTEES_EQUAL(expectedPointer, actualPointer, messageA, messageB)",
            "Expected: \"" + expectedPointee + "\"",
            "  Actual: \"" + actualPointee + "\"",
            " Because: ARE_EQUAL(*expectedPointee, *actualPointee) failed",
            "Expected: \"" + expectedPointee + "\"",
            "  Actual: \"" + actualPointee + "\"",
            " Message: \"" + messageA + "\", \"" + messageB + "\"",
            "File.cpp(1)",
            "File.cpp(1)"));
   }

   TEST(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreNotEqual_ThrowsAnomaly__UserTypesTestCase)
   {
      const unique_ptr<const UserType> expectedPointer(new UserType(1));
      const unique_ptr<const UserType> actualPointer(new UserType(2));
      THROWS_EXCEPTION(POINTEES_EQUAL(expectedPointer, actualPointer),
         Anomaly, TestUtil::NewlineConcat("",
            "  Failed: POINTEES_EQUAL(expectedPointer, actualPointer)",
            "Expected: UserType@1",
            "  Actual: UserType@2",
            " Because: ARE_EQUAL(*expectedPointee, *actualPointee) failed",
            "Expected: UserType@1",
            "  Actual: UserType@2",
            "File.cpp(1)",
            "File.cpp(1)"));
   }

   TEST(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreEqual_DoesNotThrowException__StringPointersTestCase)
   {
      const string expectedPointee = ZenUnit::Random<string>();
      const string actualPointee = expectedPointee;
      const string* const expectedPointer = &expectedPointee;
      const string* const actualPointer = &actualPointee;
      POINTEES_EQUAL(expectedPointer, actualPointer);
   }

   TEST(ExpectedPointerIsNotNull_ActualPointerIsNotNull_PointeesAreEqual_DoesNotThrowExceeption__UserTypePointersTestCase)
   {
      const int randomInt = ZenUnit::Random<int>();
      const shared_ptr<const UserType> expectedPointer(new UserType(randomInt));
      const shared_ptr<const UserType> actualPointer(new UserType(randomInt));
      POINTEES_EQUAL(expectedPointer, actualPointer);
   }

   RUN_TESTS(POINTEES_EQUALTests)
}

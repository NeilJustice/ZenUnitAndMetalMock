#include "pch.h"
#include "ZenUnitTests/Testing/UserType.h"

TESTS(POINTEES_EQUALTests)
AFACT(ExpectedPointerNullptr_ActualPointerNullptr_DoesNotThrow)
AFACT(ExpectedPointerNullptr_ActualPointerNotNullptr_Throws)
AFACT(ExpectedPointerNotNullptr_ActualPointerNullptr_Throws)
AFACT(ExpectedPointerNotNull_ActualPointerNotNull_PointeesNotEqual_Throws)
AFACT(ExpectedPointerNotNull_ActualPointerNotNull_PointeesNotEqual_Throws_MessagesTestCase)
AFACT(ExpectedPointerNotNull_ActualPointerNotNull_PointeesNotEqual_UserTypes_Throws)
AFACT(ExpectedPointerNotNull_ActualPointerNotNull_PointeesEqual_DoesNotThrow)
AFACT(ExpectedPointerNotNull_ActualPointerNotNull_PointeesEqual_UserTypes_DoesNotThrow)
EVIDENCE

TEST(ExpectedPointerNullptr_ActualPointerNullptr_DoesNotThrow)
{
   POINTEES_EQUAL(nullptr, nullptr);
   int* x = nullptr;
   int* y = nullptr;
   POINTEES_EQUAL(x, y);
}

TEST(ExpectedPointerNullptr_ActualPointerNotNullptr_Throws)
{
   const int i = 0;
   const int* const intPointer = &i;
   THROWS(POINTEES_EQUAL(nullptr, intPointer), Anomaly, R"(
  Failed: POINTEES_EQUAL(nullptr, intPointer)
Expected: expected pointer != nullptr
  Actual: expected pointer == nullptr
File.cpp(1))");
}

TEST(ExpectedPointerNotNullptr_ActualPointerNullptr_Throws)
{
   const int i = 0;
   const int* const intPointer = &i;
   THROWS(POINTEES_EQUAL(intPointer, nullptr), Anomaly, R"(
  Failed: POINTEES_EQUAL(intPointer, nullptr)
Expected: actual pointer != nullptr
  Actual: actual pointer == nullptr
File.cpp(1))");
}

TEST(ExpectedPointerNotNull_ActualPointerNotNull_PointeesNotEqual_Throws)
{
   const string expectedPointee = "expected_text";
   const string actualPointee = "actual_text";
   const string* const expectedPointer = &expectedPointee;
   const string* const actualPointer = &actualPointee;
   THROWS(POINTEES_EQUAL(expectedPointer, actualPointer), Anomaly, R"(
  Failed: POINTEES_EQUAL(expectedPointer, actualPointer)
Expected: "expected_text"
  Actual: "actual_text"
 Because: ARE_EQUAL(*expectedPointee, *actualPointee) failed
Expected: "expected_text"
  Actual: "actual_text"
File.cpp(1)
File.cpp(1))");
}

TEST(ExpectedPointerNotNull_ActualPointerNotNull_PointeesNotEqual_Throws_MessagesTestCase)
{
   const string expectedPointee = "expected_text";
   const string actualPointee = "actual_text";
   const string* const expectedPointer = &expectedPointee;
   const string* const actualPointer = &actualPointee;
   const string MessageA = "A", MessageB = "B";
   THROWS(POINTEES_EQUAL(expectedPointer, actualPointer, MessageA, MessageB), Anomaly, R"(
  Failed: POINTEES_EQUAL(expectedPointer, actualPointer, MessageA, MessageB)
Expected: "expected_text"
  Actual: "actual_text"
 Because: ARE_EQUAL(*expectedPointee, *actualPointee) failed
Expected: "expected_text"
  Actual: "actual_text"
 Message: "A", "B"
File.cpp(1)
File.cpp(1))");
}

TEST(ExpectedPointerNotNull_ActualPointerNotNull_PointeesNotEqual_UserTypes_Throws)
{
   const unique_ptr<const UserType> expectedPointer(new UserType(1));
   const unique_ptr<const UserType> actualPointer(new UserType(2));
   THROWS(POINTEES_EQUAL(expectedPointer, actualPointer), Anomaly, R"(
  Failed: POINTEES_EQUAL(expectedPointer, actualPointer)
Expected: UserType@1
  Actual: UserType@2
 Because: ARE_EQUAL(*expectedPointee, *actualPointee) failed
Expected: UserType@1
  Actual: UserType@2
File.cpp(1)
File.cpp(1))");
}

TEST(ExpectedPointerNotNull_ActualPointerNotNull_PointeesEqual_DoesNotThrow)
{
   const string expectedPointee = "expected_text";
   const string actualPointee = "expected_text";
   const string* const expectedPointer = &expectedPointee;
   const string* const actualPointer = &actualPointee;
   POINTEES_EQUAL(expectedPointer, actualPointer);
}

TEST(ExpectedPointerNotNull_ActualPointerNotNull_PointeesEqual_UserTypes_DoesNotThrow)
{
   const shared_ptr<const UserType> expectedPointer(new UserType(1));
   const shared_ptr<const UserType> actualPointer(new UserType(1));
   POINTEES_EQUAL(expectedPointer, actualPointer);
}

}; RUNTESTS(POINTEES_EQUALTests)

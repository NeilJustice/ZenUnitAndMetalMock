#include "pch.h"
#include "ZenUnit/Macros/POINTER_WAS_NEWED.h"

TESTS(POINTER_WAS_NEWEDTests_RawPointers)
SPEC(NullRawPointer_Throws)
SPEC(NullRawPointer_Throws_MessagesTestCase)
SPEC(EmptyUniquePointer_Throws)
SPEC(EmptySharedPointer_Throws)
SPEC(NonNullRawPointer_DoesNotThrow_CannotBeCalledTwiceWithoutUndefinedBehavior)
SPEC(NonEmptyUniquePointer_DoesNotThrow_ThrowsWhenCalledAgain)
SPEC(NonEmptySharedPointer_DoesNotThrow_ThrowsWhenCalledAgain)
SPEC(NonEmptyUserTypeUniquePointer_CallsDestructor_ThrowsWhenCalledAgain)
SPEC(NonEmptyUserTypeSharedPointer_CallsDestructor_ThrowsWhenCalledAgain)
SPECEND

struct Deletable
{
   const function<void()> _incrementDestructorCallCount;

   Deletable(function<void()> incrementDestructorCallCount)
      : _incrementDestructorCallCount(std::move(incrementDestructorCallCount))
   {
   }

   ~Deletable()
   {
      _incrementDestructorCallCount();
   }
};

TEST(NullRawPointer_Throws)
{
   const int* nullRawPointer = nullptr;
   THROWS(POINTER_WAS_NEWED(nullRawPointer), Anomaly, R"(
  Failed: POINTER_WAS_NEWED(nullRawPointer)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

TEST(NullRawPointer_Throws_MessagesTestCase)
{
   const char* nullRawPointer = nullptr;
   const string MessageA = "A", MessageB = "B";
   THROWS(POINTER_WAS_NEWED(nullRawPointer, MessageA, MessageB), Anomaly, R"(
  Failed: POINTER_WAS_NEWED(nullRawPointer, MessageA, MessageB)
Expected: not a nullptr
  Actual: nullptr
 Message: "A", "B"
File.cpp(1))");
}

TEST(EmptyUniquePointer_Throws)
{
   unique_ptr<const int> emptyUniquePtr;
   THROWS(POINTER_WAS_NEWED(emptyUniquePtr), Anomaly, R"(
  Failed: POINTER_WAS_NEWED(emptyUniquePtr)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

TEST(EmptySharedPointer_Throws)
{
   shared_ptr<const int> emptySharedPtr;
   THROWS(POINTER_WAS_NEWED(emptySharedPtr), Anomaly, R"(
  Failed: POINTER_WAS_NEWED(emptySharedPtr)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

TEST(NonNullRawPointer_DoesNotThrow_CannotBeCalledTwiceWithoutUndefinedBehavior)
{
   unsigned destructorCallCount = 0;
   const Deletable* nonNullRawPointer = new Deletable([&] { ++destructorCallCount; });
   //
   POINTER_WAS_NEWED(nonNullRawPointer);
   //
   ARE_EQUAL(1, destructorCallCount);
}

TEST(NonEmptyUniquePointer_DoesNotThrow_ThrowsWhenCalledAgain)
{
   unique_ptr<const int> nonEmptyUniquePtr(new int);
   POINTER_WAS_NEWED(nonEmptyUniquePtr);

   THROWS(POINTER_WAS_NEWED(nonEmptyUniquePtr), Anomaly, R"(
  Failed: POINTER_WAS_NEWED(nonEmptyUniquePtr)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

TEST(NonEmptySharedPointer_DoesNotThrow_ThrowsWhenCalledAgain)
{
   shared_ptr<const int> nonEmptySharedPtr(new int);
   POINTER_WAS_NEWED(nonEmptySharedPtr);

   THROWS(POINTER_WAS_NEWED(nonEmptySharedPtr), Anomaly, R"(
  Failed: POINTER_WAS_NEWED(nonEmptySharedPtr)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

TEST(NonEmptyUserTypeUniquePointer_CallsDestructor_ThrowsWhenCalledAgain)
{
   unsigned destructorCallCount = 0;
   unique_ptr<const Deletable> uniquePtr(new Deletable([&] { ++destructorCallCount; }));
   //
   POINTER_WAS_NEWED(uniquePtr);
   //
   ARE_EQUAL(1, destructorCallCount);
   THROWS(POINTER_WAS_NEWED(uniquePtr), Anomaly, R"(
  Failed: POINTER_WAS_NEWED(uniquePtr)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

TEST(NonEmptyUserTypeSharedPointer_CallsDestructor_ThrowsWhenCalledAgain)
{
   unsigned destructorCallCount = 0;
   shared_ptr<const Deletable> sharedPtr(new Deletable([&] { ++destructorCallCount; }));
   //
   POINTER_WAS_NEWED(sharedPtr);
   //
   ARE_EQUAL(1, destructorCallCount);
   THROWS(POINTER_WAS_NEWED(sharedPtr), Anomaly, R"(
  Failed: POINTER_WAS_NEWED(sharedPtr)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

}; RUN(POINTER_WAS_NEWEDTests_RawPointers)

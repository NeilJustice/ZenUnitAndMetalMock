#include "pch.h"
#include "ZenUnit/Macros/WAS_ARRAY_NEWED.h"

TESTS(WAS_ARRAY_NEWEDTests)
SPEC(NullRawPointer_Throws)
SPEC(NullRawPointer_Throws_MessagesTestCase)
SPEC(EmptyUniqueArrayPtr_Throws)
SPEC(NonNullRawPointer_DestructsEachElement_NotCallableTwiceWithoutUndefinedBehavior)
SPEC(NonNullUniqueArrayPointer_DestructsEachElement_ThrowsWhenCalledTwice)
SPECEND

struct Deletable
{
   static unsigned s_destructorCallCount;
   ~Deletable() { ++s_destructorCallCount; }
};

CLEANUP
{
   Deletable::s_destructorCallCount = 0;
}

TEST(NullRawPointer_Throws)
{
   char* nullRawPointer = nullptr;
   THROWS(WAS_ARRAY_NEWED(nullRawPointer), Anomaly, R"(
  Failed: WAS_ARRAY_NEWED(nullRawPointer)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

TEST(NullRawPointer_Throws_MessagesTestCase)
{
   char* nullRawPointer = nullptr;
   const string MessageA = "A", MessageB = "B";
   THROWS(WAS_ARRAY_NEWED(nullRawPointer, MessageA, MessageB), Anomaly, R"(
  Failed: WAS_ARRAY_NEWED(nullRawPointer, MessageA, MessageB)
Expected: not a nullptr
  Actual: nullptr
 Message: "A", "B"
File.cpp(1))");
}

TEST(EmptyUniqueArrayPtr_Throws)
{
   unique_ptr<int[]> emptyUniqueArrayPtr;
   THROWS(WAS_ARRAY_NEWED(emptyUniqueArrayPtr), Anomaly, R"(
  Failed: WAS_ARRAY_NEWED(emptyUniqueArrayPtr)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

TEST(NonNullRawPointer_DestructsEachElement_NotCallableTwiceWithoutUndefinedBehavior)
{
   Deletable* deletables = new Deletable[3];
   ARE_EQUAL(0, Deletable::s_destructorCallCount);
   //
   WAS_ARRAY_NEWED(deletables);
   //
   ARE_EQUAL(3, Deletable::s_destructorCallCount);

   int* ints = new int[1];
   WAS_ARRAY_NEWED(ints);
}

TEST(NonNullUniqueArrayPointer_DestructsEachElement_ThrowsWhenCalledTwice)
{
   unique_ptr<Deletable[]> nonNullUniqueArrayPtr(new Deletable[5]);
   ARE_EQUAL(0, Deletable::s_destructorCallCount);
   //
   WAS_ARRAY_NEWED(nonNullUniqueArrayPtr);
   //
   ARE_EQUAL(5, Deletable::s_destructorCallCount);

   THROWS(WAS_ARRAY_NEWED(nonNullUniqueArrayPtr), Anomaly, R"(
  Failed: WAS_ARRAY_NEWED(nonNullUniqueArrayPtr)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");

   unique_ptr<int[]> ints(new int[1]);
   WAS_ARRAY_NEWED(ints);
   THROWS(WAS_ARRAY_NEWED(ints), Anomaly, R"(
  Failed: WAS_ARRAY_NEWED(ints)
Expected: not a nullptr
  Actual: nullptr
File.cpp(1))");
}

}; RUN(WAS_ARRAY_NEWEDTests)

unsigned WAS_ARRAY_NEWEDTests::Deletable::s_destructorCallCount = 0;

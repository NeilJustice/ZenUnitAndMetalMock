#include "pch.h"

namespace ZenUnit
{
   TESTS(ARRAY_DELETE_TO_ASSERT_ARRAY_NEWEDTests)
   AFACT(PointerIsNullRawPointer_ThrowsAnomaly)
   AFACT(PointerIsNullRawPointer_ThrowsAnomaly__MessagesTestCase)
   AFACT(PointerIsEmptyUniqueArrayPtr_ThrowsAnomaly)
   AFACT(PointerIsNonNullRawPointer_DestructsEachElement)
   AFACT(PointerIsNonNullUniqueArrayPtr_DestructsEachElement_ThrowsWhenCalledTwice)
   EVIDENCE

   struct DestructorCountingElement
   {
      static size_t s_destructorCallCount;
      ~DestructorCountingElement() { ++s_destructorCallCount; }
   };

   CLEANUP
   {
      DestructorCountingElement::s_destructorCallCount = 0;
   }

   TEST(PointerIsNullRawPointer_ThrowsAnomaly)
   {
      const char* nullRawPointer = nullptr;
      THROWS_EXCEPTION(ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(nullRawPointer),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(nullRawPointer)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsNullRawPointer_ThrowsAnomaly__MessagesTestCase)
   {
      const char* nullRawPointer = nullptr;
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS_EXCEPTION(ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(nullRawPointer, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(nullRawPointer, messageA, messageB)",
"Expected: not a nullptr",
"  Actual: nullptr",
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   TEST(PointerIsEmptyUniqueArrayPtr_ThrowsAnomaly)
   {
      unique_ptr<const int[]> emptyUniqueArrayPtr;
      THROWS_EXCEPTION(ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(emptyUniqueArrayPtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(emptyUniqueArrayPtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsNonNullRawPointer_DestructsEachElement)
   {
      DestructorCountingElement* destructorCountingElements = new DestructorCountingElement[3];
      IS_ZERO(DestructorCountingElement::s_destructorCallCount);
      //
      ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(destructorCountingElements);
      //
      ARE_EQUAL(3, DestructorCountingElement::s_destructorCallCount);

      int* ints = new int[1];
      ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(ints);
   }

   TEST(PointerIsNonNullUniqueArrayPtr_DestructsEachElement_ThrowsWhenCalledTwice)
   {
      unique_ptr<const DestructorCountingElement[]> nonNullUniqueArrayPtr(new DestructorCountingElement[5]);
      IS_ZERO(DestructorCountingElement::s_destructorCallCount);
      //
      ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(nonNullUniqueArrayPtr);
      //
      ARE_EQUAL(5, DestructorCountingElement::s_destructorCallCount);

      THROWS_EXCEPTION(ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(nonNullUniqueArrayPtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(nonNullUniqueArrayPtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));

      unique_ptr<const int[]> ints(new int[1]);
      ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(ints);
      THROWS_EXCEPTION(ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(ints),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(ints)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   RUN_TESTS(ARRAY_DELETE_TO_ASSERT_ARRAY_NEWEDTests)

   size_t ARRAY_DELETE_TO_ASSERT_ARRAY_NEWEDTests::DestructorCountingElement::s_destructorCallCount = 0;
}

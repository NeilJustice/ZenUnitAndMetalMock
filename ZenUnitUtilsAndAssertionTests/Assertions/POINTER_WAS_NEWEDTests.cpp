#include "pch.h"

namespace ZenUnit
{
   TESTS(POINTER_WAS_NEWEDTests_RawPointers)
   AFACT(PointerIsNullRawPointer_ThrowsAnomaly)
   AFACT(PointerIsNullRawPointer_ThrowsAnomaly__MessagesTestCase)
   AFACT(PointerIsEmptyUniquePtr_ThrowsAnomaly)
   AFACT(PointerIsEmptySharedPtr_ThrowsAnomaly)
   AFACT(PointerIsNonNullRawPointer_OperatorDeletesPointer)
   AFACT(PointerIsNonEmptyUniquePtr_DeletesPointer_ThrowsAnomalyWhenCalledTwice)
   AFACT(PointerIsNonEmptySharedPtr_DeletesPointer_ThrowsAnomalyWhenCalledTwice)
   AFACT(NonEmptyUserTypeUniquePointer_CallsDestructor_ThrowsWhenCalledTwice)
   AFACT(NonEmptyUserTypeSharedPointer_CallsDestructor_ThrowsWhenCalledTwice)
   EVIDENCE

   class DestructorCountingElement
   {
   public:
      const function<void()> _incrementDestructorCallCount;

      DestructorCountingElement(function<void()> incrementDestructorCallCount)
         : _incrementDestructorCallCount(std::move(incrementDestructorCallCount))
      {
      }

      ~DestructorCountingElement()
      {
         _incrementDestructorCallCount();
      }
   };

   TEST(PointerIsNullRawPointer_ThrowsAnomaly)
   {
      const int* nullRawPointer = nullptr;
      THROWS_EXCEPTION(POINTER_WAS_NEWED(nullRawPointer), Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_WAS_NEWED(nullRawPointer)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsNullRawPointer_ThrowsAnomaly__MessagesTestCase)
   {
      const char* nullRawPointer = nullptr;
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS_EXCEPTION(POINTER_WAS_NEWED(nullRawPointer, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_WAS_NEWED(nullRawPointer, messageA, messageB)",
"Expected: not a nullptr",
"  Actual: nullptr",
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   TEST(PointerIsEmptyUniquePtr_ThrowsAnomaly)
   {
      unique_ptr<const int> emptyUniquePtr;
      THROWS_EXCEPTION(POINTER_WAS_NEWED(emptyUniquePtr), Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_WAS_NEWED(emptyUniquePtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsEmptySharedPtr_ThrowsAnomaly)
   {
      shared_ptr<const int> emptySharedPtr;
      THROWS_EXCEPTION(POINTER_WAS_NEWED(emptySharedPtr), Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_WAS_NEWED(emptySharedPtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsNonNullRawPointer_OperatorDeletesPointer)
   {
      size_t destructorCallCount = 0;
      const DestructorCountingElement* nonNullRawPointer = new DestructorCountingElement([&] { ++destructorCallCount; });
      //
      POINTER_WAS_NEWED(nonNullRawPointer);
      //
      ARE_EQUAL(1, destructorCallCount);
   }

   TEST(PointerIsNonEmptyUniquePtr_DeletesPointer_ThrowsAnomalyWhenCalledTwice)
   {
      unique_ptr<const int> nonEmptyUniquePtr(new int);
      POINTER_WAS_NEWED(nonEmptyUniquePtr);

      THROWS_EXCEPTION(POINTER_WAS_NEWED(nonEmptyUniquePtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_WAS_NEWED(nonEmptyUniquePtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsNonEmptySharedPtr_DeletesPointer_ThrowsAnomalyWhenCalledTwice)
   {
      shared_ptr<const int> nonEmptySharedPtr(new int);
      POINTER_WAS_NEWED(nonEmptySharedPtr);

      THROWS_EXCEPTION(POINTER_WAS_NEWED(nonEmptySharedPtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_WAS_NEWED(nonEmptySharedPtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(NonEmptyUserTypeUniquePointer_CallsDestructor_ThrowsWhenCalledTwice)
   {
      size_t destructorCallCount = 0;
      unique_ptr<const DestructorCountingElement> uniquePtr(new DestructorCountingElement([&] { ++destructorCallCount; }));
      //
      POINTER_WAS_NEWED(uniquePtr);
      //
      ARE_EQUAL(1, destructorCallCount);
      THROWS_EXCEPTION(POINTER_WAS_NEWED(uniquePtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_WAS_NEWED(uniquePtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(NonEmptyUserTypeSharedPointer_CallsDestructor_ThrowsWhenCalledTwice)
   {
      size_t destructorCallCount = 0;
      shared_ptr<const DestructorCountingElement> sharedPtr(new DestructorCountingElement([&] { ++destructorCallCount; }));
      //
      POINTER_WAS_NEWED(sharedPtr);
      //
      ARE_EQUAL(1, destructorCallCount);
      THROWS_EXCEPTION(POINTER_WAS_NEWED(sharedPtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_WAS_NEWED(sharedPtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   RUN_TESTS(POINTER_WAS_NEWEDTests_RawPointers)
}
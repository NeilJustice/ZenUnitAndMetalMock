#include "pch.h"

namespace ZenUnit
{
   TESTS(DELETE_TO_ASSERT_NEWEDTests)
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

      explicit DestructorCountingElement(function<void()> incrementDestructorCallCount)
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
      const int* const nullRawPointer = nullptr;
      THROWS_EXCEPTION(DELETE_TO_ASSERT_NEWED(nullRawPointer), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DELETE_TO_ASSERT_NEWED(nullRawPointer)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsNullRawPointer_ThrowsAnomaly__MessagesTestCase)
   {
      const char* const nullRawPointer = nullptr;
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS_EXCEPTION(DELETE_TO_ASSERT_NEWED(nullRawPointer, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DELETE_TO_ASSERT_NEWED(nullRawPointer, messageA, messageB)",
"Expected: not a nullptr",
"  Actual: nullptr",
" Message: \"" + messageA + "\", \"" + messageB + "\"",
"File.cpp(1)"));
   }

   TEST(PointerIsEmptyUniquePtr_ThrowsAnomaly)
   {
      unique_ptr<const int> emptyUniquePtr{};
      THROWS_EXCEPTION(DELETE_TO_ASSERT_NEWED(emptyUniquePtr), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DELETE_TO_ASSERT_NEWED(emptyUniquePtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsEmptySharedPtr_ThrowsAnomaly)
   {
      shared_ptr<const int> emptySharedPtr{};
      THROWS_EXCEPTION(DELETE_TO_ASSERT_NEWED(emptySharedPtr), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DELETE_TO_ASSERT_NEWED(emptySharedPtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsNonNullRawPointer_OperatorDeletesPointer)
   {
      size_t destructorCallCount = 0;
      const DestructorCountingElement* const nonNullRawPointer = new DestructorCountingElement([&] { ++destructorCallCount; });
      //
      DELETE_TO_ASSERT_NEWED(nonNullRawPointer);
      //
      ARE_EQUAL(1, destructorCallCount);
   }

   TEST(PointerIsNonEmptyUniquePtr_DeletesPointer_ThrowsAnomalyWhenCalledTwice)
   {
      unique_ptr<const int> nonEmptyUniquePtr(new int);
      DELETE_TO_ASSERT_NEWED(nonEmptyUniquePtr);

      THROWS_EXCEPTION(DELETE_TO_ASSERT_NEWED(nonEmptyUniquePtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: DELETE_TO_ASSERT_NEWED(nonEmptyUniquePtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(PointerIsNonEmptySharedPtr_DeletesPointer_ThrowsAnomalyWhenCalledTwice)
   {
      shared_ptr<const int> nonEmptySharedPtr(new int);
      DELETE_TO_ASSERT_NEWED(nonEmptySharedPtr);

      THROWS_EXCEPTION(DELETE_TO_ASSERT_NEWED(nonEmptySharedPtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: DELETE_TO_ASSERT_NEWED(nonEmptySharedPtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(NonEmptyUserTypeUniquePointer_CallsDestructor_ThrowsWhenCalledTwice)
   {
      size_t destructorCallCount = 0;
      unique_ptr<const DestructorCountingElement> uniquePtr(new DestructorCountingElement([&] { ++destructorCallCount; }));
      //
      DELETE_TO_ASSERT_NEWED(uniquePtr);
      //
      ARE_EQUAL(1, destructorCallCount);
      THROWS_EXCEPTION(DELETE_TO_ASSERT_NEWED(uniquePtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: DELETE_TO_ASSERT_NEWED(uniquePtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(NonEmptyUserTypeSharedPointer_CallsDestructor_ThrowsWhenCalledTwice)
   {
      size_t destructorCallCount = 0;
      shared_ptr<const DestructorCountingElement> sharedPtr(new DestructorCountingElement([&] { ++destructorCallCount; }));
      //
      DELETE_TO_ASSERT_NEWED(sharedPtr);
      //
      ARE_EQUAL(1, destructorCallCount);
      THROWS_EXCEPTION(DELETE_TO_ASSERT_NEWED(sharedPtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: DELETE_TO_ASSERT_NEWED(sharedPtr)",
"Expected: not a nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   RUN_TESTS(DELETE_TO_ASSERT_NEWEDTests)
}

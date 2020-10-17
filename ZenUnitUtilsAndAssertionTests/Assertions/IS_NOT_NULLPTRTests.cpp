#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_NOT_NULLPTRTests)
   AFACT(RawPointerIsNotNull_DoesNotThrowException)
   AFACT(UniquePointerIsNotNull_DoesNotThrowException)
   AFACT(SharedPointerIsNotNull_DoesNotThrowException)
   AFACT(RawPointerIsNull_ThrowsAnomaly__MessagesTestCase)
   AFACT(UniquePointerIsNull_ThrowsAnomaly)
   AFACT(SharedPointerIsNull_ThrowsAnomaly)
   EVIDENCE

   TEST(RawPointerIsNotNull_DoesNotThrowException)
   {
      const int x = 10;
      const int* const nonNullRawPointer = &x;
      IS_NOT_NULLPTR(nonNullRawPointer);
   }

   TEST(UniquePointerIsNotNull_DoesNotThrowException)
   {
      const unique_ptr<const char> nonNullUniquePtr(new char);
      IS_NOT_NULLPTR(nonNullUniquePtr);
   }

   TEST(SharedPointerIsNotNull_DoesNotThrowException)
   {
      const shared_ptr<const char> nonNullSharedPtr(new char);
      IS_NOT_NULLPTR(nonNullSharedPtr);
   }

   TEST(RawPointerIsNull_ThrowsAnomaly__MessagesTestCase)
   {
      const int* const nullRawPointer = nullptr;
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_NOT_NULLPTR(nullRawPointer, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_NULLPTR(nullRawPointer, messageA, messageB)",
"Expected: not nullptr",
"  Actual: nullptr",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   TEST(UniquePointerIsNull_ThrowsAnomaly)
   {
      const unique_ptr<const int> nullUniquePtr = nullptr;
      THROWS_EXCEPTION(IS_NOT_NULLPTR(nullUniquePtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_NULLPTR(nullUniquePtr)",
"Expected: not nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(SharedPointerIsNull_ThrowsAnomaly)
   {
      const shared_ptr<const int> nullSharedPtr = nullptr;
      THROWS_EXCEPTION(IS_NOT_NULLPTR(nullSharedPtr),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_NULLPTR(nullSharedPtr)",
"Expected: not nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_NOT_NULLPTRTests)
}

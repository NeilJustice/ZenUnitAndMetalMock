#include "pch.h"

namespace ZenUnit
{
   TESTS(POINTER_IS_NOT_NULLTests)
   AFACT(PointerIsNullRawPointer_ThrowsAnomaly)
   AFACT(NullUniquePointer_Throws_MessagesTestCase)
   AFACT(NonNullRawPointer_DoesNotThrow)
   AFACT(NonNullUniquePointer_DoesNotThrow)
   EVIDENCE

   TEST(PointerIsNullRawPointer_ThrowsAnomaly)
   {
      const int* const nullRawPointer = nullptr;
      THROWS_EXCEPTION(POINTER_IS_NOT_NULL(nullRawPointer), Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_IS_NOT_NULL(nullRawPointer)",
"Expected: not nullptr",
"  Actual: nullptr",
"File.cpp(1)"));
   }

   TEST(NullUniquePointer_Throws_MessagesTestCase)
   {
      const unique_ptr<const int> nullUniquePtr = nullptr;
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(POINTER_IS_NOT_NULL(nullUniquePtr, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: POINTER_IS_NOT_NULL(nullUniquePtr, messageA, messageB)",
"Expected: not nullptr",
"  Actual: nullptr",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   TEST(NonNullRawPointer_DoesNotThrow)
   {
      const int x = 10;
      const int* const nonNullRawPointer = &x;
      POINTER_IS_NOT_NULL(nonNullRawPointer);
   }

   TEST(NonNullUniquePointer_DoesNotThrow)
   {
      const unique_ptr<const char> nonNullUniquePtr(new char);
      POINTER_IS_NOT_NULL(nonNullUniquePtr);
   }

   RUN_TESTS(POINTER_IS_NOT_NULLTests)
}

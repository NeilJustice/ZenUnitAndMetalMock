#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_NOT_NULLTests)
   AFACT(NullRawPointer_Throws)
   AFACT(NullUniquePointer_Throws_MessagesTestCase)
   AFACT(NonNullRawPointer_DoesNotThrow)
   AFACT(NonNullUniquePointer_DoesNotThrow)
   EVIDENCE

   TEST(NullRawPointer_Throws)
   {
      const int* const nullRawPointer = nullptr;
      THROWS(IS_NOT_NULL(nullRawPointer), Anomaly, R"(
  Failed: IS_NOT_NULL(nullRawPointer)
Expected: not nullptr
  Actual: nullptr
File.cpp(1))");
   }

   TEST(NullUniquePointer_Throws_MessagesTestCase)
   {
      const unique_ptr<const int> nullUniquePtr = nullptr;
      const string messageA = "A", messageB = "B";
      THROWS(IS_NOT_NULL(nullUniquePtr, messageA, messageB), Anomaly, R"(
  Failed: IS_NOT_NULL(nullUniquePtr, messageA, messageB)
Expected: not nullptr
  Actual: nullptr
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(NonNullRawPointer_DoesNotThrow)
   {
      int x = 10;
      const int* const nonNullRawPointer = &x;
      IS_NOT_NULL(nonNullRawPointer);
   }

   TEST(NonNullUniquePointer_DoesNotThrow)
   {
      const unique_ptr<const char> nonNullUniquePtr(new char);
      IS_NOT_NULL(nonNullUniquePtr);
   }

   RUN_TESTS(IS_NOT_NULLTests)
}

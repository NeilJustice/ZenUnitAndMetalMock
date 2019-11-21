#include "pch.h"

namespace ZenUnit
{
   TESTS(POINTER_IS_NULL_Tests)
   AFACT(NullRawPointer_DoesNotThrow)
   AFACT(NullUniquePointer_DoesNotThrow)
   AFACT(NullSharedPointer_DoesNotThrow)
   AFACT(NonNullRawPointer_Throws_MessagesTestCase)
   AFACT(NonNullUniquePtr_Throws)
   AFACT(NonNullSharedPtr_Throws)
   EVIDENCE

   TEST(NullRawPointer_DoesNotThrow)
   {
      const int* const nullRawPointer = nullptr;
      POINTER_IS_NULL(nullRawPointer);
   }

   TEST(NullUniquePointer_DoesNotThrow)
   {
      const unique_ptr<const int> nullUniquePtr;
      POINTER_IS_NULL(nullUniquePtr);
   }

   TEST(NullSharedPointer_DoesNotThrow)
   {
      const shared_ptr<const int> nullSharedPtr;
      POINTER_IS_NULL(nullSharedPtr);
   }

   TEST(NonNullRawPointer_Throws_MessagesTestCase)
   {
      const int* const nonNullRawPointer = reinterpret_cast<const int*>(0x123);
      string expectedWhat = R"(
  Failed: POINTER_IS_NULL(nonNullRawPointer, messageA, messageB)
Expected: nullptr
  Actual: )";
#if defined __linux__ || defined __APPLE__
      expectedWhat += "0x123\n";
#elif defined _WIN64
      expectedWhat += "0x0000000000000123\n";
#elif defined _WIN32
      expectedWhat += "0x00000123\n";
#endif
      expectedWhat += " Message: \"A\", \"B\"\n";
      expectedWhat += "File.cpp(1)";
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(POINTER_IS_NULL(nonNullRawPointer, messageA, messageB), Anomaly, expectedWhat);
   }

   struct NullDeleter
   {
      template<typename T>
      void operator()(T*)
      {
      }
   };

   TEST(NonNullUniquePtr_Throws)
   {
      const int* const intPtr = reinterpret_cast<int*>(0x1234567890123);
      const unique_ptr<const int, NullDeleter> nonNullUniquePointer(intPtr);
      string expectedWhat = R"(
  Failed: POINTER_IS_NULL(nonNullUniquePointer)
Expected: nullptr
  Actual: )";
#if defined __linux__ || defined __APPLE__
      expectedWhat += "0x1234567890123";
#elif defined _WIN64
      expectedWhat += "0x0001234567890123";
#elif defined _WIN32
      expectedWhat += "0x67890123";
#endif
      expectedWhat += "\nFile.cpp(1)";
      THROWS_EXCEPTION(POINTER_IS_NULL(nonNullUniquePointer), Anomaly, expectedWhat);
   }

   TEST(NonNullSharedPtr_Throws)
   {
      const int* const intPtr = reinterpret_cast<int*>(0x1234567890123);
      const shared_ptr<const int> nonNullSharedPointer(intPtr, NullDeleter());
      string expectedWhat = R"(
  Failed: POINTER_IS_NULL(nonNullSharedPointer)
Expected: nullptr
  Actual: )";
#if defined __linux__ || defined __APPLE__
      expectedWhat += "0x1234567890123";
#elif defined _WIN64
      expectedWhat += "0x0001234567890123";
#elif defined _WIN32
      expectedWhat += "0x67890123";
#endif
      expectedWhat += "\nFile.cpp(1)";
      THROWS_EXCEPTION(POINTER_IS_NULL(nonNullSharedPointer), Anomaly, expectedWhat);
   }

   RUN_TESTS(POINTER_IS_NULL_Tests)
}

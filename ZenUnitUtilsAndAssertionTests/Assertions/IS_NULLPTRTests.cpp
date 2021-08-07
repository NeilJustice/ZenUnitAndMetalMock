#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_NULLPTR_Tests)
   AFACT(RawPointerIsNull_DoesNotThrowException)
   AFACT(UniquePointerIsNull_DoesNotThrowException)
   AFACT(SharedPointerIsNull_DoesNotThrowException)
   AFACT(RawPointerIsNotNull_ThrowsAnomaly__MessagesTestCase)
   AFACT(UniquePtrIsNotNull_ThrowsAnomaly)
   AFACT(SharedPtrIsNotNull_ThrowsAnomaly)
   EVIDENCE

   TEST(RawPointerIsNull_DoesNotThrowException)
   {
      const int* const nullRawPointer = nullptr;
      IS_NULLPTR(nullRawPointer);
   }

   TEST(UniquePointerIsNull_DoesNotThrowException)
   {
      const unique_ptr<const int> nullUniquePtr = nullptr;
      IS_NULLPTR(nullUniquePtr);
   }

   TEST(SharedPointerIsNull_DoesNotThrowException)
   {
      const shared_ptr<const int> nullSharedPtr = nullptr;
      IS_NULLPTR(nullSharedPtr);
   }

   TEST(RawPointerIsNotNull_ThrowsAnomaly__MessagesTestCase)
   {
      const int* const nonNullRawPointer = reinterpret_cast<const int*>(0x123);
      string expectedWhat = R"(
  Failed: IS_NULLPTR(nonNullRawPointer, messageA, messageB)
Expected: nullptr
  Actual: )";
#if defined __linux__ || defined __APPLE__
      expectedWhat += "0x123\n";
#elif defined _WIN32
      expectedWhat += "0x0000000000000123\n";
#endif
      expectedWhat += " Message: \"A\", \"B\"\n";
      expectedWhat += "File.cpp(1)";
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_NULLPTR(nonNullRawPointer, messageA, messageB),
         Anomaly, expectedWhat);
   }

   struct NullDeleter
   {
      template<typename T>
      void operator()(T*)
      {
      }
   };

   TEST(UniquePtrIsNotNull_ThrowsAnomaly)
   {
      const int* const intPtr = reinterpret_cast<int*>(0x1234567890123);
      const unique_ptr<const int, NullDeleter> nonNullUniquePointer(intPtr);
      string expectedWhat = R"(
  Failed: IS_NULLPTR(nonNullUniquePointer)
Expected: nullptr
  Actual: )";
#if defined __linux__ || defined __APPLE__
      expectedWhat += "0x1234567890123";
#elif defined _WIN32
      expectedWhat += "0x0001234567890123";
#endif
      expectedWhat += "\nFile.cpp(1)";
      THROWS_EXCEPTION(IS_NULLPTR(nonNullUniquePointer),
         Anomaly, expectedWhat);
   }

   TEST(SharedPtrIsNotNull_ThrowsAnomaly)
   {
      const int* const intPtr = reinterpret_cast<int*>(0x1234567890123);
      const shared_ptr<const int> nonNullSharedPointer(intPtr, NullDeleter());
      string expectedWhat = R"(
  Failed: IS_NULLPTR(nonNullSharedPointer)
Expected: nullptr
  Actual: )";
#if defined __linux__ || defined __APPLE__
      expectedWhat += "0x1234567890123";
#elif defined _WIN32
      expectedWhat += "0x0001234567890123";
#endif
      expectedWhat += "\nFile.cpp(1)";
      THROWS_EXCEPTION(IS_NULLPTR(nonNullSharedPointer),
         Anomaly, expectedWhat);
   }

   RUN_TESTS(IS_NULLPTR_Tests)
}

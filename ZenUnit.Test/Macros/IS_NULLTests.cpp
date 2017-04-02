#include "pch.h"
#include "ZenUnit/Macros/IS_NULL.h"

namespace ZenUnit
{
   TESTS(IS_NULL_Tests)
   SPEC(NullRawPointer_DoesNotThrow)
   SPEC(NullUniquePointer_DoesNotThrow)
   SPEC(NullSharedPointer_DoesNotThrow)
   SPEC(NonNullRawPointer_Throws_MessagesTestCase)
   SPEC(NonNullUniquePtr_Throws)
   SPEC(NonNullSharedPtr_Throws)
   SPECEND

   TEST(NullRawPointer_DoesNotThrow)
   {
      const int* const nullRawPointer = nullptr;
      IS_NULL(nullRawPointer);
   }

   TEST(NullUniquePointer_DoesNotThrow)
   {
      const unique_ptr<const int> nullUniquePtr;
      IS_NULL(nullUniquePtr);
   }

   TEST(NullSharedPointer_DoesNotThrow)
   {
      const shared_ptr<const int> nullSharedPtr;
      IS_NULL(nullSharedPtr);
   }

   TEST(NonNullRawPointer_Throws_MessagesTestCase)
   {
      const int* const nonNullRawPointer = reinterpret_cast<const int*>(0x123);
      string expectedWhat = R"(
  Failed: IS_NULL(nonNullRawPointer, messageA, messageB)
Expected: nullptr
  Actual: )";
#ifdef __linux__
      expectedWhat += "0x123\n";
#elif _WIN32
      expectedWhat += "0x0000000000000123\n";
#endif
      expectedWhat += " Message: \"A\", \"B\"\n";
      expectedWhat += "File.cpp(1)";
      const string messageA = "A", messageB = "B";
      THROWS(IS_NULL(nonNullRawPointer, messageA, messageB), Anomaly, expectedWhat);
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
  Failed: IS_NULL(nonNullUniquePointer)
Expected: nullptr
  Actual: )";
   #ifdef __linux__
      expectedWhat += "0x1234567890123";
   #elif _WIN32
      expectedWhat += "0x0001234567890123";
   #endif
      expectedWhat += "\nFile.cpp(1)";
      THROWS(IS_NULL(nonNullUniquePointer), Anomaly, expectedWhat);
   }

   TEST(NonNullSharedPtr_Throws)
   {
      const int* const intPtr = reinterpret_cast<int*>(0x1234567890123);
      const shared_ptr<const int> nonNullSharedPointer(intPtr, NullDeleter());
      string expectedWhat = R"(
  Failed: IS_NULL(nonNullSharedPointer)
Expected: nullptr
  Actual: )";
   #ifdef __linux__
      expectedWhat += "0x1234567890123";
   #elif _WIN32
      expectedWhat += "0x0001234567890123";
   #endif
      expectedWhat += "\nFile.cpp(1)";
      THROWS(IS_NULL(nonNullSharedPointer), Anomaly, expectedWhat);
   }

   }; RUN(IS_NULL_Tests)
}

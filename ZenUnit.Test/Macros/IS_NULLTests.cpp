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
      int* nullRawPointer = nullptr;
      IS_NULL(nullRawPointer);
   }

   TEST(NullUniquePointer_DoesNotThrow)
   {
      unique_ptr<int> nullUniquePtr;
      IS_NULL(nullUniquePtr);
   }

   TEST(NullSharedPointer_DoesNotThrow)
   {
      shared_ptr<int> nullSharedPtr;
      IS_NULL(nullSharedPtr);
   }

   TEST(NonNullRawPointer_Throws_MessagesTestCase)
   {
      int* nonNullRawPointer = (int*)0x123;
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
      string messageA = "A", messageB = "B";
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
      int* intPtr = reinterpret_cast<int*>(0x1234567890123);
      unique_ptr<int, NullDeleter> nonNullUniquePointer(intPtr);
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
      int* intPtr = reinterpret_cast<int*>(0x1234567890123);
      shared_ptr<int> nonNullSharedPointer(intPtr, NullDeleter());
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

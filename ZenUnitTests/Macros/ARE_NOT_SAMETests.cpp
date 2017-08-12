#include "pch.h"
#include "ZenUnit/Macros/ARE_NOT_SAME.h"

namespace ZenUnit
{
   TESTS(ARE_NOT_SAMETests)
   FACT(ExpectedAndActualAddressesNotEqual_DoesNotThrow)
   FACT(ExpectedAndActualAddressesEqual_Throws)
   FACT(ExpectedAndActualAddressesEqual_Throws_MessagesTestCase)
   BEGINPROOF

   TEST(ExpectedAndActualAddressesNotEqual_DoesNotThrow)
   {
      const int notExpectedObject = 0;
      const int actualObject = 0;
      ARE_NOT_SAME(notExpectedObject, actualObject);
   }

   TEST(ExpectedAndActualAddressesEqual_Throws)
   {
      int notExpectedObject = 0;
      const int& actualObject = notExpectedObject;
      string expectedWhat = MakeExpectedWhat(
         "notExpectedObject", "actualObject", &notExpectedObject, &actualObject, false);
      THROWS(ARE_NOT_SAME(notExpectedObject, actualObject), Anomaly, expectedWhat);
   }

   TEST(ExpectedAndActualAddressesEqual_Throws_MessagesTestCase)
   {
      const string a = "a";
      const string& b = a;
      const string expectedWhat = MakeExpectedWhat("a", "b", &a, &b, true);
      const string messageA = "A", messageB = "B";
      THROWS(ARE_NOT_SAME(a, b, messageA, messageB), Anomaly, expectedWhat);
   }

   static string MakeExpectedWhat(
      const char* notExpectedObjectText, const char* actualObjectText,
      const void* notExpectedAddress, const void* actualAddress,
      bool doAppendMessage)
   {
      ostringstream expectedWhatPatternBuilder;
      expectedWhatPatternBuilder << R"(
  Failed: ARE_NOT_SAME()" << notExpectedObjectText << ", " << actualObjectText;
      if (doAppendMessage)
      {
         expectedWhatPatternBuilder << ", messageA, messageB";
      }
      expectedWhatPatternBuilder << R"()
Expected: Not )";
   #ifdef __linux__
     expectedWhatPatternBuilder << notExpectedAddress << R"(
  Actual:     )" << actualAddress;
   #elif _WIN32
      expectedWhatPatternBuilder << "0x" << notExpectedAddress << R"(
  Actual:     0x)" << actualAddress;
   #endif
      if (doAppendMessage)
      {
         expectedWhatPatternBuilder << "\n Message: \"A\", \"B\"";
      }
      expectedWhatPatternBuilder << "\nFile.cpp(1)";
      const string expectedWhatPattern = expectedWhatPatternBuilder.str();
      return expectedWhatPattern;
   }

   }; RUN(ARE_NOT_SAMETests)
}

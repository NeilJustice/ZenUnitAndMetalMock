#include "pch.h"

namespace ZenUnit
{
   TESTS(ARE_SAMETests)
   AFACT(ExpectedAndActualAddressesEqual_DoesNotThrow)
   AFACT(ExpectedAndActualValuesEqual_AddressesNotEqual_Throws)
   AFACT(ExpectedAndActualValuesNotEqual_AddressesNotEqual_Throws_MessagesTestCase)
   EVIDENCE

   TEST(ExpectedAndActualAddressesEqual_DoesNotThrow)
   {
      const int expectedObject = 0;
      const int& actualObject = expectedObject;
      ARE_SAME(expectedObject, expectedObject);
      ARE_SAME(expectedObject, actualObject);
   }

   TEST(ExpectedAndActualValuesEqual_AddressesNotEqual_Throws)
   {
      int expectedObject = 0;
      int actualObject = 0;
      const string expectedWhat = MakeExpectedWhat(
         "expectedObject", "actualObject", &expectedObject, &actualObject, false);
      THROWS(ARE_SAME(expectedObject, actualObject), Anomaly, expectedWhat);
   }

   TEST(ExpectedAndActualValuesNotEqual_AddressesNotEqual_Throws_MessagesTestCase)
   {
      const string expectedObject = "a";
      const string actualObject = "b";
      const string expectedWhat = MakeExpectedWhat(
         "expectedObject", "actualObject", &expectedObject, &actualObject, true);
      const string messageA = "A", messageB = "B";
      THROWS(ARE_SAME(expectedObject, actualObject, messageA, messageB), Anomaly, expectedWhat);
   }

   static string MakeExpectedWhat(
      const char* expectedObjectText, const char* actualObjectText,
      const void* expectedAddress, const void* actualAddress, bool doAppendMessage)
   {
      ostringstream expectedWhatPatternBuilder;
      expectedWhatPatternBuilder << R"(
  Failed: ARE_SAME()" << expectedObjectText << ", " << actualObjectText;
      if (doAppendMessage)
      {
         expectedWhatPatternBuilder << ", messageA, messageB";
      }
      expectedWhatPatternBuilder << R"()
Expected: )";
   #if defined __linux__
     expectedWhatPatternBuilder << expectedAddress << R"(
  Actual: )" << actualAddress;
   #elif _WIN32
      expectedWhatPatternBuilder << "0x" << expectedAddress << R"(
  Actual: 0x)" << actualAddress;
   #endif
      if (doAppendMessage)
      {
         expectedWhatPatternBuilder << "\n Message: \"A\", \"B\"";
      }
      expectedWhatPatternBuilder << "\nFile.cpp(1)";
      const string expectedWhatPattern = expectedWhatPatternBuilder.str();
      return expectedWhatPattern;
   }

   }; RUNTESTS(ARE_SAMETests)
}

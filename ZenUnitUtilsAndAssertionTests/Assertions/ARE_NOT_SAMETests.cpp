#include "pch.h"

namespace ZenUnit
{
   TESTS(ARE_NOT_SAMETests)
   AFACT(ExpectedAndActualAddressesNotEqual_DoesNotThrowException)
   AFACT(ExpectedAndActualAddressesEqual_ThrowsAnomaly)
   AFACT(ExpectedAndActualAddressesEqual_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(ExpectedAndActualAddressesNotEqual_DoesNotThrowException)
   {
      const int notExpectedObject = 0;
      const int actualObject = 0;
      ARE_NOT_SAME(notExpectedObject, actualObject);
   }

   TEST(ExpectedAndActualAddressesEqual_ThrowsAnomaly)
   {
      int notExpectedObject = 0;
      const int& actualObject = notExpectedObject;
      string expectedWhat = MakeExpectedWhat(
         "notExpectedObject", "actualObject", &notExpectedObject, &actualObject, false);
      THROWS_EXCEPTION(ARE_NOT_SAME(notExpectedObject, actualObject), Anomaly, expectedWhat);
   }

   TEST(ExpectedAndActualAddressesEqual_ThrowsAnomaly__MessagesTestCase)
   {
      const string a = "a";
      const string& b = a;
      const string expectedWhat = MakeExpectedWhat("a", "b", &a, &b, true);
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(ARE_NOT_SAME(a, b, messageA, messageB), Anomaly, expectedWhat);
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
#if defined __linux__ || defined __APPLE__
      expectedWhatPatternBuilder << notExpectedAddress << R"(
  Actual:     )" << actualAddress;
#elif defined _WIN32
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

   RUN_TESTS(ARE_NOT_SAMETests)
}

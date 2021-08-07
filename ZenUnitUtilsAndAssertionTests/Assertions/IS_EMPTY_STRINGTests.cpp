#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_EMPTY_STRINGTests)
   AFACT(StringIsEmpty_DoesNotThrowException)
   AFACT(StringIsNotEmpty_ThrowsAnomaly)
   AFACT(StringIsNotEmpty_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(StringIsEmpty_DoesNotThrowException)
   {
      IS_EMPTY_STRING("");
      IS_EMPTY_STRING(string());
      const string constString;
      IS_EMPTY_STRING(constString);
      string nonConstString;
      IS_EMPTY_STRING(nonConstString);
      //string_view stringView = constString;
      //IS_EMPTY_STRING(stringView);
   }

   TEST(StringIsNotEmpty_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(IS_EMPTY_STRING("foo"),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_EMPTY_STRING(\"foo\")",
"Expected: str to be empty string",
"  Actual: str is not empty string: \"foo\"",
"File.cpp(1)"));
   }

   TEST(StringIsNotEmpty_ThrowsAnomaly__MessagesTestCase)
   {
      const string messageA = "A", messageB = "B";
      const string nonEmptyString = "bar";
      THROWS_EXCEPTION(IS_EMPTY_STRING(nonEmptyString, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_EMPTY_STRING(nonEmptyString, messageA, messageB)",
"Expected: str to be empty string",
"  Actual: str is not empty string: \"bar\"",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_EMPTY_STRINGTests)
}

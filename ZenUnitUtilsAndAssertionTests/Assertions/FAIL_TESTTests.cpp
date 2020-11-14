#include "pch.h"

namespace ZenUnit
{
   TESTS(FAIL_TESTTests)
   AFACT(StringLiteralBecause_ThrowsAnomaly)
   AFACT(StringVariableBecause_MessagesTestCase_ThrowsAnomaly)
   EVIDENCE

   TEST(StringLiteralBecause_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(FAIL_TEST("Because"), Anomaly, TestUtil::NewlineConcat("",
" Failed: FAIL_TEST(\"Because\")",
"File.cpp(1)"));
   }

   TEST(StringVariableBecause_MessagesTestCase_ThrowsAnomaly)
   {
      const string Because = "BecauseValue";
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(FAIL_TEST(Because, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
" Failed: FAIL_TEST(Because, messageA, messageB)",
"Because: \"BecauseValue\"",
"Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(FAIL_TESTTests)
}

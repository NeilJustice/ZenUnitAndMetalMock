#include "pch.h"

namespace ZenUnit
{
   TESTS(FAIL_TESTTests)
   AFACT(ThrowsAnomaly__StringLiteralTestFailureReasonTestCase)
   AFACT(ThrowsAnomaly__StringVariableTestFailureReasonTestCase)
   EVIDENCE

   TEST(ThrowsAnomaly__StringLiteralTestFailureReasonTestCase)
   {
      THROWS_EXCEPTION(FAIL_TEST("Test failure reason A"), Anomaly, TestUtil::NewlineConcat("",
" Failed: FAIL_TEST(\"Test failure reason A\")",
"Because: \"Test failure reason A\"",
"File.cpp(1)"));
   }

   TEST(ThrowsAnomaly__StringVariableTestFailureReasonTestCase)
   {
      const string testFailureReason = "Test failure reason B";
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(FAIL_TEST(testFailureReason, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
" Failed: FAIL_TEST(testFailureReason, messageA, messageB)",
"Because: \"Test failure reason B\"",
"Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(FAIL_TESTTests)
}

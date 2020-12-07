#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_EMPTY_PATHTests)
   AFACT(PathIsEmpty_DoesNotThrowException)
   AFACT(StringIsNotEmpty_ThrowsAnomaly)
   AFACT(StringIsNotEmpty_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(PathIsEmpty_DoesNotThrowException)
   {
      IS_EMPTY_PATH("");
      IS_EMPTY_PATH(fs::path());
   }

   TEST(StringIsNotEmpty_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(IS_EMPTY_PATH(fs::path("foo/bar")),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_EMPTY_PATH(fs::path(\"foo/bar\"))",
"Expected: fsPath == std::filesystem::path()",
"  Actual: fsPath != std::filesystem::path() (\"foo/bar\")",
"File.cpp(1)"));
   }

   TEST(StringIsNotEmpty_ThrowsAnomaly__MessagesTestCase)
   {
      const string messageA = "A", messageB = "B";
      const fs::path fsPath("foo");
      THROWS_EXCEPTION(IS_EMPTY_PATH(fsPath, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_EMPTY_PATH(fsPath, messageA, messageB)",
"Expected: fsPath == std::filesystem::path()",
"  Actual: fsPath != std::filesystem::path() (\"foo\")",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_EMPTY_PATHTests)
}

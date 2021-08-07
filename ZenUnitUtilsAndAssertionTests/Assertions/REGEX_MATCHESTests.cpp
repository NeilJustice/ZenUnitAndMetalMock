#include "pch.h"
#include "ZenUnitUtilsAndAssertionTests/Assertions/REGEX_MATCHES.h"

namespace ZenUnit
{
   TESTS(REGEX_MATCHESTests)
   AFACT(PatternMatchesAllOfInput_DoesNotThrowException)
   AFACT(PatternDoesNotMatchAnyOfInput_ThrowsAnomaly)
   AFACT(PatternMatchesOnlyPartOfInput_ThrowsAnomaly)
   AFACT(PatternMismatchesOnCase_ThrowsAnomaly__MessagesTestCase)
   EVIDENCE

   TEST(PatternMatchesAllOfInput_DoesNotThrowException)
   {
      REGEX_MATCHES("", "");
      REGEX_MATCHES("a", "a");
      REGEX_MATCHES("a\\w", "ab");
      REGEX_MATCHES("a\\d", "a1");
      REGEX_MATCHES("\\w\\w\\w", "abc");
      REGEX_MATCHES("error|warning", "error");
      REGEX_MATCHES("error|warning", "warning");
      REGEX_MATCHES("^abc$", "abc");
      REGEX_MATCHES("\nabc\n", "\nabc\n");
   }

   TEST(PatternDoesNotMatchAnyOfInput_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(REGEX_MATCHES("a", "1"), Anomaly, TestUtil::NewlineConcat("",
"  Failed: REGEX_MATCHES(\"a\", \"1\")",
"Expected string to match: \"a\"",
"     Non-matching string: \"1\"",
"File.cpp(1)"));

      const string pattern = "a";
      THROWS_EXCEPTION(REGEX_MATCHES(pattern, "1"), Anomaly, TestUtil::NewlineConcat("",
"  Failed: REGEX_MATCHES(pattern, \"1\")",
"Expected string to match: \"a\"",
"     Non-matching string: \"1\"",
"File.cpp(1)"));

      const string str = "1";
      THROWS_EXCEPTION(REGEX_MATCHES("a", str), Anomaly, TestUtil::NewlineConcat("",
"  Failed: REGEX_MATCHES(\"a\", str)",
"Expected string to match: \"a\"",
"     Non-matching string: \"1\"",
"File.cpp(1)"));
   }

   TEST(PatternMatchesOnlyPartOfInput_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(REGEX_MATCHES("a", "a1"), Anomaly, TestUtil::NewlineConcat("",
"  Failed: REGEX_MATCHES(\"a\", \"a1\")",
"Expected string to match: \"a\"",
"     Non-matching string: \"a1\"",
"File.cpp(1)"));
   }

   TEST(PatternMismatchesOnCase_ThrowsAnomaly__MessagesTestCase)
   {
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(REGEX_MATCHES("a", "A", messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: REGEX_MATCHES(\"a\", \"A\", messageA, messageB)",
"Expected string to match: \"a\"",
"     Non-matching string: \"A\"",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(REGEX_MATCHESTests)
}

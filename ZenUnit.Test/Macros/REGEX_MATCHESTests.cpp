#include "pch.h"
#include "ZenUnit/Macros/REGEX_MATCHES.h"

namespace ZenUnit
{
   TESTS(REGEX_MATCHESTests)
   SPEC(PatternMatchesAllOfInput_DoesNotThrow)
   SPEC(PatternDoesNotMatchAnyOfInput_Throws)
   SPEC(PatternMatchesOnlyPartOfInput_Throws)
   SPEC(PatternMismatchesOnCase_Throws_MessagesTestCase)
   SPECEND

   TEST(PatternMatchesAllOfInput_DoesNotThrow)
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

   TEST(PatternDoesNotMatchAnyOfInput_Throws)
   {
      THROWS(REGEX_MATCHES("a", "1"), Anomaly, R"(
  Failed: REGEX_MATCHES("a", "1")
Expected string to match: "a"
     Non-matching string: "1"
File.cpp(1))");

      const string pattern = "a";
      THROWS(REGEX_MATCHES(pattern, "1"), Anomaly, R"(
  Failed: REGEX_MATCHES(pattern, "1")
Expected string to match: "a"
     Non-matching string: "1"
File.cpp(1))");

      const string str = "1";
      THROWS(REGEX_MATCHES("a", str), Anomaly, R"(
  Failed: REGEX_MATCHES("a", str)
Expected string to match: "a"
     Non-matching string: "1"
File.cpp(1))");
   }

   TEST(PatternMatchesOnlyPartOfInput_Throws)
   {
      THROWS(REGEX_MATCHES("a", "a1"), Anomaly, R"(
  Failed: REGEX_MATCHES("a", "a1")
Expected string to match: "a"
     Non-matching string: "a1"
File.cpp(1))");
   }

   TEST(PatternMismatchesOnCase_Throws_MessagesTestCase)
   {
      const string messageA = "A", messageB = "B";
      THROWS(REGEX_MATCHES("a", "A", messageA, messageB), Anomaly, R"(
  Failed: REGEX_MATCHES("a", "A", messageA, messageB)
Expected string to match: "a"
     Non-matching string: "A"
 Message: "A", "B"
File.cpp(1))");
   }

   }; RUN(REGEX_MATCHESTests)
}

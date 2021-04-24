#pragma once
#include <regex>

#define REGEX_MATCHES(expectedPattern, str, ...) \
   ZenUnit::REGEX_MATCHES_Defined(expectedPattern, #expectedPattern, str, #str, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename PatternStringType, typename StrStringType, typename... MessageTypes>
   NOINLINE void REGEX_MATCHES_ThrowAnomaly(
      const PatternStringType& expectedPattern, const char* expectedPatternText, const StrStringType& str, const char* strText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedLine = String::ConcatStrings("Expected string to match: \"", expectedPattern, "\"");
      const std::string actualLine = String::ConcatStrings("     Non-matching string: \"", str, "\"");
      throw Anomaly("REGEX_MATCHES", expectedPatternText, strText, "", messagesText, Anomaly::Default(),
         expectedLine, actualLine, ExpectedActualFormat::WholeLines, filePathLineNumber, std::forward<MessageTypes>(messages)...);
   }

   template<typename PatternStringType, typename StrStringType, typename... MessageTypes>
   void REGEX_MATCHES_Defined(
      const PatternStringType& expectedPattern, const char* expectedPatternText,
      const StrStringType& str, const char* strText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::regex regexPattern(expectedPattern);
      if (!std::regex_match(str, regexPattern))
      {
         REGEX_MATCHES_ThrowAnomaly(expectedPattern, expectedPatternText, str, strText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

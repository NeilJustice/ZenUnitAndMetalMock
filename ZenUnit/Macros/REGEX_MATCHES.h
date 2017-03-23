#pragma once
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"
#include "ZenUnit/Anomaly/Anomaly.h"

#define REGEX_MATCHES(expectedPattern, str, ...) \
   ZenUnit::REGEX_MATCHES_Defined(VRT(expectedPattern), VRT(str), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename PatternStringType, typename StrStringType, typename... MessageTypes>
   void REGEX_MATCHES_Defined(
      VRText<PatternStringType> expectedPatternVRT,
      VRText<StrStringType> strVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      std::regex regexPattern(expectedPatternVRT.value);
      if (!std::regex_match(strVRT.value, regexPattern))
      {
         std::string expectedLine = String::Concat(
            "Expected string to match: \"", expectedPatternVRT.value, "\"");
         std::string actualLine = String::Concat(
            "     Non-matching string: \"", strVRT.value, "\"");
         Anomaly anomaly(
            "REGEX_MATCHES", expectedPatternVRT.text, strVRT.text, "", messagesText,
            Anomaly::Default,
            expectedLine,
            actualLine,
            ExpectedActualFormat::WholeLines, fileLine, messages...);
         throw anomaly;
      }
   }
}

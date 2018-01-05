#pragma once
//#include <regex>
//
//// Asserts that str std::regex_matches expectedPattern.
//#define REGEX_MATCHES(expectedPattern, str, ...) \
//   ZenUnit::REGEX_MATCHES_Defined(VRT(expectedPattern), VRT(str), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)
//
//namespace ZenUnit
//{
//   template<typename PatternStringType, typename StrStringType, typename... MessageTypes>
//   void REGEX_MATCHES_Throw(
//      VRText<PatternStringType> expectedPatternVRT, VRText<StrStringType> strVRT,
//      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
//   {
//      const std::string expectedLine = String::Concat(
//         "Expected string to match: \"", expectedPatternVRT.value, "\"");
//      const std::string actualLine = String::Concat(
//         "     Non-matching string: \"", strVRT.value, "\"");
//      throw Anomaly(
//         "REGEX_MATCHES", expectedPatternVRT.text, strVRT.text, "", messagesText,
//         Anomaly::Default(),
//         expectedLine,
//         actualLine,
//         ExpectedActualFormat::WholeLines, fileLine, std::forward<MessageTypes>(messages)...);
//   }
//
//   template<typename PatternStringType, typename StrStringType, typename... MessageTypes>
//   void REGEX_MATCHES_Defined(
//      VRText<PatternStringType> expectedPatternVRT,
//      VRText<StrStringType> strVRT,
//      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
//   {
//      const std::regex regexPattern(expectedPatternVRT.value);
//      if (!std::regex_match(strVRT.value, regexPattern))
//      {
//         REGEX_MATCHES_Throw(
//            expectedPatternVRT, strVRT,
//            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
//      }
//   }
//}

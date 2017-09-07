#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/VRText.h"

#define FAIL(testFailureReason, ...) \
   ZenUnit::FAIL_Defined(VRT(testFailureReason), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename StringType, typename... MessageTypes>
   void FAIL_Defined(VRText<StringType> testFailureReasonVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat(" Failed: FAIL(", testFailureReasonVRT.text);
      std::ostringstream whyBodyBuilder;
      const std::string quotedTestFailureReason = String::Concat('"', testFailureReasonVRT.value, '"');
      if (quotedTestFailureReason != testFailureReasonVRT.text)
      {
         whyBodyBuilder << "Because: " << quotedTestFailureReason;
      }
      const std::string whyBody = whyBodyBuilder.str();
      throw Anomaly(failedLinePrefix, whyBody, fileLine, "", messagesText, std::forward<MessageTypes>(messages)...);
   }
}

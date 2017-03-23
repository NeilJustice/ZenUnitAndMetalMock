#pragma once
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/ToStringer/ToStringer.h"

#define ARE_NOT_SAME(notExpectedObject, actualObject, ...) \
   ARE_NOT_SAME_Defined(VRT(notExpectedObject), VRT(actualObject), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_NOT_SAME_Defined(
      const VRText<NotExpectedObjectType>& notExpectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      if (&notExpectedObjectVRT.value == &actualObjectVRT.value)
      {
         std::string toStringedNotExpectedObjectAddress = ToStringer::ToString(&notExpectedObjectVRT.value);
         std::string toStringedActualObjectBAddress = ToStringer::ToString(&actualObjectVRT.value);
         Anomaly anomaly("ARE_NOT_SAME", notExpectedObjectVRT.text, actualObjectVRT.text, "", messagesText,
            Anomaly::Default,
            "Not " + toStringedNotExpectedObjectAddress,
            "    " + toStringedActualObjectBAddress,
            ExpectedActualFormat::Fields, fileLine, messages...);
         throw anomaly;
      }
   }
}

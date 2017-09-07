#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"

#define ARE_NOT_SAME(notExpectedObject, actualObject, ...) \
   ARE_NOT_SAME_Defined(VRT(notExpectedObject), VRT(actualObject), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_NOT_SAME_Throw(
      const VRText<NotExpectedObjectType>& notExpectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = "Not " + ToStringer::ToString(&notExpectedObjectVRT.value);
      const std::string actualField = "    " + ToStringer::ToString(&actualObjectVRT.value);
      throw Anomaly("ARE_NOT_SAME", notExpectedObjectVRT.text, actualObjectVRT.text, "", messagesText,
         Anomaly::Default,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_NOT_SAME_Defined(
      const VRText<NotExpectedObjectType>& notExpectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (&notExpectedObjectVRT.value == &actualObjectVRT.value)
      {
         ARE_NOT_SAME_Throw(
            notExpectedObjectVRT,
            actualObjectVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

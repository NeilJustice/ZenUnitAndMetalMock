#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"

#define ARE_SAME(expectedObject, actualObject, ...) \
   ARE_SAME_Defined(VRT(expectedObject), VRT(actualObject), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_SAME_Throw(
      const VRText<ExpectedObjectType>& expectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(&expectedObjectVRT.value);
      const std::string actualField = ToStringer::ToString(&actualObjectVRT.value);
      throw Anomaly("ARE_SAME", expectedObjectVRT.text, actualObjectVRT.text, "", messagesText,
         Anomaly::Default,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_SAME_Defined(
      const VRText<ExpectedObjectType>& expectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (&expectedObjectVRT.value != &actualObjectVRT.value)
      {
         ARE_SAME_Throw(
            expectedObjectVRT,
            actualObjectVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

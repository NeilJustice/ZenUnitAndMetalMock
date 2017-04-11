#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"

#define IS_NULL(pointer, ...) \
   ZenUnit::IS_NULL_Defined(VRT(pointer), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename PointerType, typename... MessageTypes>
   NOINLINE void IS_NULL_Throw(VRText<PointerType> pointerVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const std::string actualField = ToStringer::ToString(pointerVRT.value);
      throw Anomaly("IS_NULL", pointerVRT.text, "", "", messagesText,
         Anomaly::Default,
         "nullptr",
         actualField,
         ExpectedActualFormat::Fields, fileLine, messages...);
   }

   template<typename PointerType, typename... MessageTypes>
   void IS_NULL_Defined(VRText<PointerType> pointerVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const bool pointerIsNull = pointerVRT.value == nullptr;
      if (!pointerIsNull)
      {
         IS_NULL_Throw(pointerVRT, fileLine, messagesText, messages...);
      }
   }
}

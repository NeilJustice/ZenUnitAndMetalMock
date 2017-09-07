#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/Utils/FileLine.h"

#define IS_NOT_NULL(pointer, ...) \
   ZenUnit::IS_NOT_NULL_Defined(pointer == nullptr, #pointer, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename... MessageTypes>
   NOINLINE void IS_NOT_NULL_Throw(
      const char* pointerText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      throw Anomaly("IS_NOT_NULL", pointerText, "", "", messagesText,
         Anomaly::Default,
         "not nullptr",
         "nullptr",
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename... MessageTypes>
   void IS_NOT_NULL_Defined(bool pointerIsNullptr, const char* pointerText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (pointerIsNullptr)
      {
         IS_NOT_NULL_Throw(pointerText, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

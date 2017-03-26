#pragma once
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/Anomaly/Anomaly.h"

#define IS_NOT_NULL(pointer, ...) \
   ZenUnit::IS_NOT_NULL_Defined(pointer == nullptr, #pointer, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename... MessageTypes>
   NOINLINE void IS_NOT_NULL_Throw(
      const char* pointerText, 
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      Anomaly anomaly("IS_NOT_NULL", pointerText, "", "", messagesText,
         Anomaly::Default,
         "not nullptr",
         "nullptr",
         ExpectedActualFormat::Fields, fileLine, messages...);
      throw anomaly;
   }

   template<typename... MessageTypes>
   void IS_NOT_NULL_Defined(bool pointerIsNullptr, const char* pointerText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      if (pointerIsNullptr)
      {
         IS_NOT_NULL_Throw(pointerText, fileLine, messagesText, messages...);
      }
   }
}

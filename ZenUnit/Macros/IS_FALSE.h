#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Utils/FileLine.h"

#define IS_FALSE(value, ...) \
   ZenUnit::IS_FALSE_Defined(value, #value, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename... MessageTypes>
   NOINLINE void IS_FALSE_Throw(
      const char* valueText, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      throw Anomaly("IS_FALSE", valueText, "", "", messagesText,
         Anomaly::Default,
         "false",
         "true",
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ConvertableToBoolType, typename... MessageTypes>
   void IS_FALSE_Defined(const ConvertableToBoolType& value, const char* valueText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (value)
      {
         IS_FALSE_Throw(valueText, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

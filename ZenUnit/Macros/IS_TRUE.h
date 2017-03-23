#pragma once
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Anomaly/Anomaly.h"

#define IS_TRUE(value, ...) \
   ZenUnit::IS_TRUE_Defined(value, #value, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ConvertibleToBoolType, typename... MessageTypes>
   void IS_TRUE_Defined(const ConvertibleToBoolType& value, const char* valueText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      if (!value)
      {
         Anomaly anomaly("IS_TRUE", valueText, "", "", messagesText,
            Anomaly::Default,
            "true",
            "false",
            ExpectedActualFormat::Fields, fileLine, messages...);
         throw anomaly;
      }
   }
}

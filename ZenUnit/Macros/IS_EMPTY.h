#pragma once
#include "ZenUnit/Utils/VRText.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Anomaly/Anomaly.h"

#define IS_EMPTY(dataStructure, ...) \
   ZenUnit::IS_EMPTY_Defined(VRT(dataStructure), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename DataStructureType, typename... MessageTypes>
   void IS_EMPTY_Defined(VRText<DataStructureType> dataStructureVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      size_t size = dataStructureVRT.value.size();
      if (size > 0)
      {
         std::string expectedField = "empty() == true";
         std::string actualField = "empty() == false (size() == " + std::to_string(size) + ")";
         Anomaly anomaly("IS_EMPTY", dataStructureVRT.text, "", "", messagesText,
            Anomaly::Default,
            expectedField,
            actualField,
            ExpectedActualFormat::Fields, fileLine, messages...);
         throw anomaly;
      }
   }
}

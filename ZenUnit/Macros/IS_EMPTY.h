#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"

#define IS_EMPTY(dataStructure, ...) \
   ZenUnit::IS_EMPTY_Defined(VRT(dataStructure), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename DataStructureType, typename... MessageTypes>
   NOINLINE void IS_EMPTY_Throw(
      VRText<DataStructureType> dataStructureVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const size_t size = dataStructureVRT.value.size();
      const std::string expectedField = "empty() == true";
      const std::string actualField = "empty() == false (size() == " + std::to_string(size) + ")";
      throw Anomaly("IS_EMPTY", dataStructureVRT.text, "", "", messagesText,
         Anomaly::Default,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename DataStructureType, typename... MessageTypes>
   void IS_EMPTY_Defined(
      VRText<DataStructureType> dataStructureVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (!dataStructureVRT.value.empty())
      {
         IS_EMPTY_Throw(dataStructureVRT, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

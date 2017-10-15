#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"

#define IS_EMPTY(collection, ...) \
   ZenUnit::IS_EMPTY_Defined(VRT(collection), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename CollectionType, typename... MessageTypes>
   NOINLINE void IS_EMPTY_Throw(
      VRText<CollectionType> collectionVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const size_t size = collectionVRT.value.size();
      const std::string expectedField = "empty() == true";
      const std::string actualField = "empty() == false (size() == " + std::to_string(size) + ")";
      throw Anomaly("IS_EMPTY", collectionVRT.text, "", "", messagesText,
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_EMPTY_Defined(
      VRText<CollectionType> collectionVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (!collectionVRT.value.empty())
      {
         IS_EMPTY_Throw(collectionVRT, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

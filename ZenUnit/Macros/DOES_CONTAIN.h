#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"

#define DOES_CONTAIN(expectedElement, dataStructure, ...) \
   ZenUnit::CONTAINS_Defined(VRT(expectedElement), VRT(dataStructure), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ElementType, typename DataStructureType, typename... MessageTypes>
   NOINLINE void CONTAINS_Throw(
      VRText<DataStructureType> expectedElementVRT,
      VRText<ElementType> dataStructureVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField =
         "Contains element " + ToStringer::ToString(expectedElementVRT.value);
      throw Anomaly("DOES_CONTAIN", expectedElementVRT.text, dataStructureVRT.text, "", messagesText,
         Anomaly::Default(),
         expectedField,
         "Contains no such element",
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ElementType, typename DataStructureType, typename... MessageTypes>
   void CONTAINS_Defined(
      VRText<DataStructureType> expectedElementVRT,
      VRText<ElementType> dataStructureVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const auto findIter = std::find(
         dataStructureVRT.value.cbegin(),
         dataStructureVRT.value.cend(),
         expectedElementVRT.value);
      if (findIter == dataStructureVRT.value.end())
      {
         CONTAINS_Throw(
            expectedElementVRT,
            dataStructureVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

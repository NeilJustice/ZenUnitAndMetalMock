#pragma once
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/ToStringer/ToStringer.h"

#define CONTAINS(expectedElement, dataStructure, ...) \
   ZenUnit::CONTAINS_Defined(VRT(expectedElement), VRT(dataStructure), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ElementType, typename DataStructureType, typename... MessageTypes>
   NOINLINE void CONTAINS_Throw(
      VRText<DataStructureType> expectedElementVRT, 
      VRText<ElementType> dataStructureVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      std::string expectedField =
         "Contains element " + ToStringer::ToString(expectedElementVRT.value);
      Anomaly anomaly("CONTAINS", expectedElementVRT.text, dataStructureVRT.text, "", messagesText,
         Anomaly::Default,
         expectedField,
         "Contains no such element",
         ExpectedActualFormat::Fields, fileLine, messages...);
      throw anomaly;
   }

   template<typename ElementType, typename DataStructureType, typename... MessageTypes>
   void CONTAINS_Defined(
      VRText<DataStructureType> expectedElementVRT, 
      VRText<ElementType> dataStructureVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      auto findIter = std::find(
         dataStructureVRT.value.cbegin(), 
         dataStructureVRT.value.cend(), 
         expectedElementVRT.value);
      if (findIter == dataStructureVRT.value.end())
      {
         std::string expectedText =
            "Contains element " + ToStringer::ToString(expectedElementVRT.value);
         Anomaly anomaly("CONTAINS", expectedElementVRT.text, dataStructureVRT.text, "", messagesText,
            Anomaly::Default,
            expectedText,
            "Contains no such element",
            ExpectedActualFormat::Fields, fileLine, messages...);
         throw anomaly;
         //CONTAINS_Throw(
         //   expectedElementVRT, 
         //   dataStructureVRT,
         //   fileLine, messagesText, messages...);
      }
   }
}

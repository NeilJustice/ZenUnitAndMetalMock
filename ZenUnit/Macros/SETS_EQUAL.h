#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/CONTAINS.h"

#define SETS_EQUAL(expectedSet, actualSet, ...) \
   ZenUnit::SETS_EQUAL_Defined(VRT(expectedSet), VRT(actualSet), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename SetType, typename... MessageTypes>
   NOINLINE void SETS_EQUAL_Throw(
      const Anomaly& becauseAnomaly,
      VRText<SetType> expectedSetVRT, VRText<SetType> actualSetVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedSet = ToStringer::ToString(expectedSetVRT.value);
      const std::string toStringedActualSet = ToStringer::ToString(actualSetVRT.value);
      throw Anomaly("SETS_EQUAL", expectedSetVRT.text, actualSetVRT.text, "", messagesText,
         becauseAnomaly,
         toStringedExpectedSet,
         toStringedActualSet,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename SetType, typename... MessageTypes>
   void SETS_EQUAL_Defined(VRText<SetType> expectedSetVRT, VRText<SetType> actualSetVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const SetType& expectedSet = expectedSetVRT.value;
      const SetType& actualSet = actualSetVRT.value;
      try
      {
         ARE_EQUAL(expectedSet.size(), actualSet.size());
         for (const auto& expectedElement : expectedSet)
         {
            CONTAINS(expectedElement, actualSet);
         }
      }
      catch (const Anomaly& becauseAnomaly)
      {
         SETS_EQUAL_Throw(
            becauseAnomaly,
            expectedSetVRT, actualSetVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

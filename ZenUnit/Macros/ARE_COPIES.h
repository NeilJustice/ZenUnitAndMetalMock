#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/ARE_NOT_SAME.h"
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"

#define ARE_COPIES(expectedObject, actualObject, ...) \
   ZenUnit::ARE_COPIES_Defined(VRT(expectedObject), VRT(actualObject), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_COPIES_Throw(
      VRText<ExpectedObjectType> expectedObjectVRT,
      VRText<ActualObjectType> actualObjectVRT,
      FileLine fileLine, const Anomaly& becauseAnomaly,
      const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedObject = ToStringer::ToString(expectedObjectVRT.value);
      const std::string toStringedActualObject = ToStringer::ToString(actualObjectVRT.value);
      throw Anomaly("ARE_COPIES", expectedObjectVRT.text, actualObjectVRT.text, "",
         messagesText, becauseAnomaly,
         toStringedExpectedObject,
         toStringedActualObject,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_COPIES_Defined(
      VRText<ExpectedObjectType> expectedObjectVRT,
      VRText<ActualObjectType> actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const ExpectedObjectType& expectedObject = expectedObjectVRT.value;
      const ActualObjectType& actualObject = actualObjectVRT.value;
      try
      {
         ARE_NOT_SAME(expectedObject, actualObject);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_COPIES_Throw(expectedObjectVRT, actualObjectVRT,
            fileLine, becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
      try
      {
         ARE_EQUAL(expectedObject, actualObject);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_COPIES_Throw(expectedObjectVRT, actualObjectVRT,
            fileLine, becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

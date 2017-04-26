#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"

#define ARE_EQUAL(expectedValue, actualValue, ...) \
   ZenUnit::ARE_EQUAL_Defined(VRT(expectedValue), VRT(actualValue), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   NOINLINE void ARE_EQUAL_Throw(
      VRText<ExpectedType> expectedValueVRT, VRText<ActualType> actualValueVRT,
      FileLine fileLine, const Anomaly& becauseAnomaly,
      const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(expectedValueVRT.value);
      const std::string actualField = ToStringer::ToString(actualValueVRT.value);
      throw Anomaly("ARE_EQUAL", expectedValueVRT.text, actualValueVRT.text, "",
         messagesText, becauseAnomaly,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void ARE_EQUAL_Defined(VRText<ExpectedType> expectedValueVRT, VRText<ActualType> actualValueVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         using DecayedExpectedType = typename std::decay<ExpectedType>::type;
         using DecayedActualType = typename std::decay<ActualType>::type;
         std::conditional<std::is_same<DecayedExpectedType, DecayedActualType>::value,
            ::ZenUnitEqualizer<DecayedExpectedType>,
            ::TwoTypeZenUnitEqualizer<DecayedExpectedType, DecayedActualType>>
            ::type::AssertEqual(expectedValueVRT.value, actualValueVRT.value);
      }
      catch (const EqualizerException&)
      {
         ARE_EQUAL_Throw(expectedValueVRT, actualValueVRT, fileLine,
            Anomaly::Default, messagesText, std::forward<MessageTypes>(messages)...);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_EQUAL_Throw(expectedValueVRT, actualValueVRT, fileLine,
            becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}

#include "ZenUnit/Equalizers/VectorEqualizer.h"

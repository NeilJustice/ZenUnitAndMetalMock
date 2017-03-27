#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Anomaly/Anomaly.h"

#define ARE_EQUAL(expectedValue, actualValue, ...) \
   ZenUnit::ARE_EQUAL_Defined(VRT(expectedValue), VRT(actualValue), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   NOINLINE void ARE_EQUAL_ToStringAndRethrow(
      VRText<ExpectedType> expectedVRT, VRText<ActualType> actualVRT,
      FileLine fileLine, const Anomaly& becauseAnomaly,
      const char* messagesText, const MessageTypes&... messages)
   {
      const std::string expectedField = ToStringer::ToString(expectedVRT.value);
      const std::string actualField = ToStringer::ToString(actualVRT.value);
      const Anomaly anomaly("ARE_EQUAL", expectedVRT.text, actualVRT.text, "",
         messagesText, becauseAnomaly,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, messages...);
      throw anomaly;
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void ARE_EQUAL_Defined(VRText<ExpectedType> expectedVRT, VRText<ActualType> actualVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      try
      {
         using DecayedExpectedType = typename std::decay<ExpectedType>::type;
         using DecayedActualType = typename std::decay<ActualType>::type;
         std::conditional<std::is_same<DecayedExpectedType, DecayedActualType>::value,
            ::ZenUnitEqualizer<DecayedExpectedType>,
            ::TwoTypeZenUnitEqualizer<DecayedExpectedType, DecayedActualType>>
            ::type::AssertEqual(expectedVRT.value, actualVRT.value);
      }
      catch (const EqualizerException&)
      {
         ARE_EQUAL_ToStringAndRethrow(expectedVRT, actualVRT, fileLine,
            Anomaly::Default, messagesText, messages...);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_EQUAL_ToStringAndRethrow(expectedVRT, actualVRT, fileLine,
            becauseAnomaly, messagesText, messages...);
      }
   }
}

#include "ZenUnit/Equalizers/VectorEqualizer.h"

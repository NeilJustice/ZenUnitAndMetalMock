#pragma once
#include "ZenUnit/Macros/MacroUtils.h"

#define PAIRS_EQUAL(expectedPair, actualPair, ...) \
   ZenUnit::PAIRS_EQUAL_Defined(VRT(expectedPair), VRT(actualPair), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename PairType, typename... MessageTypes>
   NOINLINE void PAIRS_EQUAL_ToStringAndRethrow(
      const Anomaly& becauseAnomaly,
      VRText<PairType> expectedPairVRT, VRText<PairType> actualPairVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const std::string expected = ToStringer::ToString(expectedPairVRT.value);
      const std::string actual = ToStringer::ToString(actualPairVRT.value);
      throw Anomaly("PAIRS_EQUAL", expectedPairVRT.text, actualPairVRT.text, "", messagesText,
         becauseAnomaly, expected, actual, ExpectedActualFormat::Fields, fileLine, messages...);
   }

   template<typename PairType, typename... MessageTypes>
   void PAIRS_EQUAL_Defined(
      VRText<PairType> expectedPairVRT, VRText<PairType> actualPairVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      try
      {
         const auto& expectedPair = expectedPairVRT.value;
         const auto& actualPair = actualPairVRT.value;
         ARE_EQUAL(expectedPair.first, actualPair.first);
         ARE_EQUAL(expectedPair.second, actualPair.second);
      }
      catch (const Anomaly& anomaly)
      {
         PAIRS_EQUAL_ToStringAndRethrow(anomaly,
            expectedPairVRT, actualPairVRT,
            fileLine, messagesText, messages...);
      }
   }
}

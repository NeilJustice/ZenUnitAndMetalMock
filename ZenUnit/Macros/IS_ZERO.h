#pragma once
#include "ZenUnit/Utils/FileLine.h"
#include "ZenUnit/Utils/VRText.h"
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/ToStringer/ToStringer.h"

#define IS_ZERO(value, ...) \
   ZenUnit::IS_ZERO_Defined(VRT(value), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ValueType, typename ZeroValueType, typename... MessageTypes>
   NOINLINE void IS_ZERO_Throw(VRText<ValueType> valueVRT, const ZeroValueType& zeroValue,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      std::string expectedField = ToStringer::ToString(zeroValue);
      std::string actualField = ToStringer::ToString(valueVRT.value);
      Anomaly anomaly("IS_ZERO", valueVRT.text, "", "", messagesText,
         Anomaly::Default,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, messages...);
      throw anomaly;
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_ZERO_Defined(VRText<ValueType> valueVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      typename std::remove_reference<ValueType>::type zeroValue { 0 };
      bool valueIsZero = valueVRT.value == zeroValue;
      if (!valueIsZero)
      {
         IS_ZERO_Throw(valueVRT, zeroValue, fileLine, messagesText, messages...);
      }
   }
}

#pragma once
#include "ZenUnit/Macros/IS_TRUE.h"
#include "ZenUnit/Macros/IS_NOT_NULL.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

#define FUNCTION_TARGETS(expectedStdFunctionTarget, stdFunction, ...) \
   ZenUnit::FUNCTION_TARGETS_Defined<decltype(expectedStdFunctionTarget)>( \
      expectedStdFunctionTarget, #expectedStdFunctionTarget, VRT(stdFunction), \
      FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ExpectedStdFunctionTargetType, typename StdFunctionType, typename... MessageTypes>
   NOINLINE void FUNCTION_TARGETS_Throw(
      const ExpectedStdFunctionTargetType* expectedStdFunctionTargetValue,
      const char* expectedStdFunctionTargetText,
      VRText<StdFunctionType> stdFunctionVRT,
      const Anomaly& becauseAnomaly,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const std::string expectedField = ToStringer::ToString(expectedStdFunctionTargetValue);
      const std::string actualField = ToStringer::ToString(stdFunctionVRT.value);
      const Anomaly anomaly("FUNCTION_TARGETS", expectedStdFunctionTargetText, stdFunctionVRT.text, "", messagesText,
         becauseAnomaly,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, messages...);
      throw anomaly;
   }

   template<typename ExpectedStdFunctionTargetType, typename StdFunctionType, typename... MessageTypes>
   void FUNCTION_TARGETS_Defined(
      const ExpectedStdFunctionTargetType* expectedStdFunctionTargetValue,
      const char* expectedStdFunctionTargetText,
      VRText<StdFunctionType> stdFunctionVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const StdFunctionType stdFunction = stdFunctionVRT.value;
      try
      {
         IS_TRUE(stdFunction);
         IS_NOT_NULL(stdFunction.template target<ExpectedStdFunctionTargetType*>());
         typename std::add_pointer<ExpectedStdFunctionTargetType>::type
            expectedStdFunctionTarget(expectedStdFunctionTargetValue);
         ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.template target<ExpectedStdFunctionTargetType*>());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         FUNCTION_TARGETS_Throw(
            expectedStdFunctionTargetValue,
            expectedStdFunctionTargetText,
            stdFunctionVRT, 
            becauseAnomaly,
            fileLine, messagesText, messages...);
      }
   }
}

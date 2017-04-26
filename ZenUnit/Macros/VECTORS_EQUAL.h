#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Enums/ExpectedActualFormat.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

#define VECTORS_EQUAL(expectedVector, actualVector, ...) \
   ZenUnit::VECTORS_EQUAL_Defined(expectedVector, #expectedVector, actualVector, #actualVector, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<
      template<typename...>
      class VectorType, typename T, typename Allocator, typename... MessageTypes>
   NOINLINE void VECTORS_EQUAL_Throw(
      const Anomaly& becauseAnomaly,
      const VectorType<T, Allocator>& expectedVector, const char* expectedVectorText,
      const VectorType<T, Allocator>& actualVector, const char* actualVectorText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedVector = ToStringer::ToString(expectedVector);
      const std::string toStringedActualVector = ToStringer::ToString(actualVector);
      throw Anomaly("VECTORS_EQUAL", expectedVectorText, actualVectorText, "", messagesText,
         becauseAnomaly,
         toStringedExpectedVector,
         toStringedActualVector,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<
      template<typename...>
      class VectorType, typename T, typename Allocator, typename... MessageTypes>
   void VECTORS_EQUAL_Defined(
      const VectorType<T, Allocator>& expectedVector, const char* expectedVectorText,
      const VectorType<T, Allocator>& actualVector, const char* actualVectorText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_EQUAL(expectedVector.size(), actualVector.size());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         VECTORS_EQUAL_Throw(becauseAnomaly,
            expectedVector, expectedVectorText,
            actualVector, actualVectorText,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      const size_t expectedVectorSize = expectedVector.size();
      for (size_t i = 0; i < expectedVectorSize; ++i)
      {
         const T& ithExpectedElement = expectedVector[i];
         const T& ithActualElement = actualVector[i];
         const std::string iEqualsIndexMessage = "i=" + std::to_string(i);
         try
         {
            ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage);
         }
         catch (const Anomaly& becauseAnomaly)
         {
            VECTORS_EQUAL_Throw(becauseAnomaly,
               expectedVector, expectedVectorText,
               actualVector, actualVectorText,
               fileLine, messagesText, std::forward<MessageTypes>(messages)...);
         }
      }
   }
}

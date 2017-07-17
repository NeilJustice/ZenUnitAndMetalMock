#pragma once
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/Utils/FileLine.h"

#define ARRAY_WAS_NEWED(smartOrRawArrayPointer, ...) \
   ZenUnit::ARRAY_WAS_NEWED_Defined(smartOrRawArrayPointer, #smartOrRawArrayPointer, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename T>
   struct ArrayDeleter
   {
      static void Delete(T& smartPointer)
      {
         smartPointer.reset();
      }
   };

   template<typename T>
   struct ArrayDeleter<T*>
   {
      static void Delete(T* rawPointer)
      {
         delete[] rawPointer;
      }
   };

   template<typename... MessageTypes>
   NOINLINE void ARRAY_WAS_NEWED_Throw(
      const char* smartOrRawArrayPointerText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      throw Anomaly("ARRAY_WAS_NEWED", smartOrRawArrayPointerText, "", "", messagesText, Anomaly::Default,
         "not a nullptr", "nullptr", ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename PointerType, typename... MessageTypes>
   void ARRAY_WAS_NEWED_Defined(
      PointerType& smartOrRawArrayPointer, const char* smartOrRawArrayPointerText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (smartOrRawArrayPointer == nullptr)
      {
         ARRAY_WAS_NEWED_Throw(
            smartOrRawArrayPointerText,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ArrayDeleter<typename std::remove_reference<
         decltype(smartOrRawArrayPointer)>::type>::Delete(smartOrRawArrayPointer);
   }
}

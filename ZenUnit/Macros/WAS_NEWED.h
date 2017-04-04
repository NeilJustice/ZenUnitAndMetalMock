#pragma once

#define WAS_NEWED(smartOrRawPointer, ...) \
   ZenUnit::WAS_NEWED_Defined(smartOrRawPointer, #smartOrRawPointer, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename T>
   struct ScalarDeleter
   {
      static void Delete(T& smartPointer)
      {
         smartPointer.reset();
      }
   };

   template<typename T>
   struct ScalarDeleter<T*>
   {
      static void Delete(T* rawPointer)
      {
         delete rawPointer;
      }
   };

   template<typename... MessageTypes>
   NOINLINE void WAS_NEWED_Throw(
      const char* smartOrRawPointerText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      throw Anomaly("WAS_NEWED", smartOrRawPointerText, "", "", messagesText, Anomaly::Default,
         "not a nullptr", "nullptr", ExpectedActualFormat::Fields, fileLine, messages...);
   }

   template<typename PointerType, typename... MessageTypes>
   void WAS_NEWED_Defined(
      PointerType& smartOrRawPointer, const char* smartOrRawPointerText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      if (smartOrRawPointer == nullptr)
      {
         WAS_NEWED_Throw(smartOrRawPointerText, fileLine, messagesText, messages...);
      }
      ScalarDeleter<typename std::remove_reference<
         decltype(smartOrRawPointer)>::type>::Delete(smartOrRawPointer);
   }
}

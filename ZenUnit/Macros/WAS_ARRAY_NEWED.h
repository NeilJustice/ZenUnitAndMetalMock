#pragma once

#define WAS_ARRAY_NEWED(smartOrRawArrayPointer, ...) \
   ZenUnit::WAS_ARRAY_NEWED_Defined(smartOrRawArrayPointer, #smartOrRawArrayPointer, \
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

   template<typename PointerType, typename... MessageTypes>
   void WAS_ARRAY_NEWED_Defined(
      PointerType& smartOrRawArrayPointer, const char* smartOrRawArrayPointerText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      if (smartOrRawArrayPointer == nullptr)
      {
         Anomaly anomaly("WAS_ARRAY_NEWED", smartOrRawArrayPointerText, "", "", messagesText, Anomaly::Default,
            "not a nullptr", "nullptr", ExpectedActualFormat::Fields, fileLine, messages...);
         throw anomaly;
      }
      ArrayDeleter<typename std::remove_reference<
         decltype(smartOrRawArrayPointer)>::type>::Delete(smartOrRawArrayPointer);
   }
}

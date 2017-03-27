#pragma once

#define CONFIRM_ARRAY_NEWED(smartOrRawArrayPointer, ...) \
   ZenUnit::CONFIRM_ARRAY_NEWED_Defined(smartOrRawArrayPointer, #smartOrRawArrayPointer, \
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
   NOINLINE void CONFIRM_ARRAY_NEWED_Throw(
      const char* smartOrRawArrayPointerText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const Anomaly anomaly("CONFIRM_ARRAY_NEWED", smartOrRawArrayPointerText, "", "", messagesText, Anomaly::Default,
         "not a nullptr", "nullptr", ExpectedActualFormat::Fields, fileLine, messages...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   void CONFIRM_ARRAY_NEWED_Defined(
      PointerType& smartOrRawArrayPointer, const char* smartOrRawArrayPointerText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      if (smartOrRawArrayPointer == nullptr)
      {
         CONFIRM_ARRAY_NEWED_Throw(smartOrRawArrayPointerText, 
            fileLine, messagesText, messages...);
      }
      ArrayDeleter<typename std::remove_reference<
         decltype(smartOrRawArrayPointer)>::type>::Delete(smartOrRawArrayPointer);
   }
}

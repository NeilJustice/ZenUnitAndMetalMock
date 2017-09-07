#pragma once

#define VRT(value) ZenUnit::VRText<decltype(value)>(value, #value)

namespace ZenUnit
{
   // Value Reference Text
   template<typename T>
   struct VRText
   {
      const T& value;
      const char* text;

      VRText(const T& value, const char* text)
         : value(value), text(text) {}
   };

   template<size_t N>
   struct VRText<char[N]>
   {
      char* value;
      const char* text;

      VRText(char* value, const char* text)
         : value(value), text(text) {}
   };
}

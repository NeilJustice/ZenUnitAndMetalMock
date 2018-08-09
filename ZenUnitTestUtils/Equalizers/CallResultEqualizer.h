#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<CallResult>
   {
      static void AssertEqual(const CallResult& expectedCallResult, const CallResult& actualCallResult);
   };
}

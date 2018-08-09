#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<FullTestName>
   {
      static void AssertEqual(const FullTestName& expectedFullTestName, const FullTestName& actualFullTestName);
   };
}

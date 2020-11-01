#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<FullTestName>
   {
   public:
      static void AssertEqual(const FullTestName& expectedFullTestName, const FullTestName& actualFullTestName);
   };

   template<>
   FullTestName Random();
}

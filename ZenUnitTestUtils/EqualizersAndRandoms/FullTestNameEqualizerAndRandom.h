#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<FullTestName>
   {
   public:
      static void AssertEqual(const FullTestName& expectedFullTestName, const FullTestName& actualFullTestName);
   };

   FullTestName TestableRandomFullTestName(const ZenUnit::RandomGenerator* randomGenerator);
   template<>
   FullTestName Random();
}

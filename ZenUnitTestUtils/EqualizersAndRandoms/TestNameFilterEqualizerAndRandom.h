#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<TestNameFilter>
   {
   public:
      static void AssertEqual(
         const TestNameFilter& expectedTestNameFilter, const TestNameFilter& actualTestNameFilter);
   };

   TestNameFilter TestableRandomTestNameFilter(const RandomGenerator* randomGenerator);
   template<>
   TestNameFilter Random();
}

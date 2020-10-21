#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<TestClassResult>
   {
   public:
      static void AssertEqual(
         const TestClassResult& expectedTestClassResult,
         const TestClassResult& actualTestClassResult);
   };
}

#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<TestClassResult>
   {
      static void AssertEqual(const TestClassResult& expectedTestClassResult, const TestClassResult& actualTestClassResult);
   };
}

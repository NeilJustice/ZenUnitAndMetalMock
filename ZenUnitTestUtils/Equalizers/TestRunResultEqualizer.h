#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<TestRunResult>
   {
      static void AssertEqual(const TestRunResult& expectedTestRunResult, const TestRunResult& actualTestRunResult);
   };
}

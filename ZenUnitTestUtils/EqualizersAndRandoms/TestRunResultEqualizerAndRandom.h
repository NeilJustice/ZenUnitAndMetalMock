#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<TestRunResult>
   {
   public:
      static void AssertEqual(const TestRunResult& expectedTestRunResult, const TestRunResult& actualTestRunResult);
   };
}

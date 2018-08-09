#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<TestResult>
   {
      static void AssertEqual(const TestResult& expectedTestResult, const TestResult& actualTestResult);
   };
}

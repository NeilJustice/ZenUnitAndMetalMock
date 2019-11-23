#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<TestResult>
   {
   public:
      static void AssertEqual(const TestResult& expectedTestResult, const TestResult& actualTestResult);
   };
}

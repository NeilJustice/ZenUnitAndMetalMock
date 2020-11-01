#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<TestResult>
   {
   public:
      static void AssertEqual(const TestResult& expectedTestResult, const TestResult& actualTestResult);
   };

   template<>
   TestResult Random();
   TestResult TestableRandomTestResult(const RandomGenerator* randomGenerator);
}

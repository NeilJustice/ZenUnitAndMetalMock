#pragma once
class ZenUnitTestingRandomGenerator;

namespace ZenUnit
{
   bool operator==(const TestResult& leftTestResult, const TestResult& rightTestResult);

   template<>
   class Equalizer<TestResult>
   {
   public:
      static void AssertEqual(const TestResult& expectedTestResult, const TestResult& actualTestResult);
   };

   TestResult TestableRandomTestResult(const RandomGenerator* randomGenerator, const ZenUnitTestingRandomGenerator* zenUnitTestingRandomGenerator);
   template<>
   TestResult Random();
}

#pragma once

namespace ZenUnit
{
   template<>
   TestResult Random<TestResult>();

   TestResult TestableRandomTestResult(const RandomGenerator& randomGenerator);
}

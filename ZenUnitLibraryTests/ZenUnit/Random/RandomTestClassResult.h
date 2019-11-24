#pragma once

namespace ZenUnit
{
   template<>
   TestClassResult Random<TestClassResult>();

   TestClassResult TestableRandomTestClassResult(const RandomGenerator& randomGenerator);
}

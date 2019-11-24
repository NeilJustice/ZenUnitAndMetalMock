#pragma once

namespace ZenUnit
{
   template<>
   TestPhaseResult Random<TestPhaseResult>();

   TestPhaseResult TestableRandomTestPhaseResult(const RandomGenerator& randomGenerator);
}

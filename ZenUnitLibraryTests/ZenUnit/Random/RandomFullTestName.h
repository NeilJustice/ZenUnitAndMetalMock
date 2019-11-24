#pragma once

namespace ZenUnit
{
   template<>
   FullTestName Random<FullTestName>();

   FullTestName TestableRandomFullTestName(const RandomGenerator& randomGenerator);
}

#pragma once

namespace ZenUnit
{
   inline RunFilter TestableRandomRunFilter(const RandomGenerator& randomGenerator)
   {
      RunFilter randomRunFilter;
      randomRunFilter.testClassNamePattern = randomGenerator.String();
      randomRunFilter.testNamePattern = randomGenerator.String();
      randomRunFilter.testCaseNumber = randomGenerator.UnsignedLongLong();
      return randomRunFilter;
   }

   template<>
   inline RunFilter Random<RunFilter>()
   {
      return TestableRandomRunFilter(RandomGenerator());
   }
}

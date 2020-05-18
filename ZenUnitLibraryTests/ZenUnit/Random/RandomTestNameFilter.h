#pragma once

namespace ZenUnit
{
   inline TestNameFilter TestableRandomTestNameFilter(const RandomGenerator& randomGenerator)
   {
      TestNameFilter randomTestNameFilter;
      randomTestNameFilter.testClassNamePattern = randomGenerator.String();
      randomTestNameFilter.testNamePattern = randomGenerator.String();
      randomTestNameFilter.testCaseNumber = randomGenerator.SizeT();
      return randomTestNameFilter;
   }

   template<>
   inline TestNameFilter Random<TestNameFilter>()
   {
      return TestableRandomTestNameFilter(RandomGenerator());
   }
}

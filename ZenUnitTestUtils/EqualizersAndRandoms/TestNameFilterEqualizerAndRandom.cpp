#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestNameFilter>::AssertEqual(
      const ZenUnit::TestNameFilter& expectedTestNameFilter, const TestNameFilter& actualTestNameFilter)
   {
      ARE_EQUAL(expectedTestNameFilter.testClassNamePattern, actualTestNameFilter.testClassNamePattern);
      ARE_EQUAL(expectedTestNameFilter.testNamePattern, actualTestNameFilter.testNamePattern);
      ARE_EQUAL(expectedTestNameFilter.testCaseNumber, actualTestNameFilter.testCaseNumber);
   }

   TestNameFilter TestableRandomTestNameFilter(const RandomGenerator* randomGenerator)
   {
      TestNameFilter randomTestNameFilter;
      randomTestNameFilter.testClassNamePattern = randomGenerator->String();
      randomTestNameFilter.testNamePattern = randomGenerator->String();
      randomTestNameFilter.testCaseNumber = randomGenerator->SizeT();
      return randomTestNameFilter;
   }

   template<>
   TestNameFilter Random()
   {
      return TestableRandomTestNameFilter(RandomGenerator::Instance());
   }
}
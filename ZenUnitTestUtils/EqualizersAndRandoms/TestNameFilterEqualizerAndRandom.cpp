#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestNameFilter>::AssertEqual(
      const ZenUnit::TestNameFilter& expectedTestNameFilter, const TestNameFilter& actualTestNameFilter)
   {
      FIELDS_ARE_EQUAL(expectedTestNameFilter, actualTestNameFilter, testClassNamePattern);
      FIELDS_ARE_EQUAL(expectedTestNameFilter, actualTestNameFilter, testNamePattern);
      FIELDS_ARE_EQUAL(expectedTestNameFilter, actualTestNameFilter, testCaseNumber);
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

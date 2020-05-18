#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestNameFilterEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestNameFilter>::AssertEqual(const ZenUnit::TestNameFilter& expectedTestNameFilter, const TestNameFilter& actualTestNameFilter)
   {
      ARE_EQUAL(expectedTestNameFilter.testClassNamePattern, actualTestNameFilter.testClassNamePattern);
      ARE_EQUAL(expectedTestNameFilter.testNamePattern, actualTestNameFilter.testNamePattern);
      ARE_EQUAL(expectedTestNameFilter.testCaseNumber, actualTestNameFilter.testCaseNumber);
   }
}

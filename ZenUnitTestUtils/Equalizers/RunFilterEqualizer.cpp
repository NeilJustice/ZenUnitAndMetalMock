#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"

namespace ZenUnit
{
   void Equalizer<RunFilter>::AssertEqual(const ZenUnit::RunFilter& expectedRunFilter, const RunFilter& actualRunFilter)
   {
      ARE_EQUAL(expectedRunFilter.testClassNamePattern, actualRunFilter.testClassNamePattern);
      ARE_EQUAL(expectedRunFilter.testNamePattern, actualRunFilter.testNamePattern);
      ARE_EQUAL(expectedRunFilter.testCaseNumber, actualRunFilter.testCaseNumber);
   }
}

#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestRunResultEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestRunResult>::AssertEqual(const TestRunResult& expectedTestRunResult, const TestRunResult& actualTestRunResult)
   {
      TestRunResult::AssertEqual(expectedTestRunResult, actualTestRunResult);
   }
}

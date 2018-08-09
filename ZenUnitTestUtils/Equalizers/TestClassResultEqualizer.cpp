#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestClassResult>::AssertEqual(const TestClassResult& expectedTestClassResult, const TestClassResult& actualTestClassResult)
   {
      ZenUnit::TestClassResult::AssertEqual(expectedTestClassResult, actualTestClassResult);
   }
}

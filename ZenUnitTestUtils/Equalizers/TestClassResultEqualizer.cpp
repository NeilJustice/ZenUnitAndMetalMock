#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/FileLineEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"

namespace ZenUnit
{
   void Equalizer<TestClassResult>::AssertEqual(const TestClassResult& expectedTestClassResult, const TestClassResult& actualTestClassResult)
   {
      INDEXABLES_ARE_EQUAL(expectedTestClassResult._testResults, actualTestClassResult._testResults);
   }
}

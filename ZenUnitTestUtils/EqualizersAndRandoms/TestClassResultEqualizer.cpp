#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FileLineEqualizer.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestClassResult>::AssertEqual(
      const TestClassResult& expectedTestClassResult,
      const TestClassResult& actualTestClassResult)
   {
      VECTORS_ARE_EQUAL(expectedTestClassResult._testResults, actualTestClassResult._testResults);
   }
}

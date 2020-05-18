#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestNameFilterEqualizer.h"

namespace ZenUnit
{
   void Equalizer<ZenUnitArgs>::AssertEqual(const ZenUnitArgs& expectedZenUnitArgs, const ZenUnitArgs& actualZenUnitArgs)
   {
      ARE_EQUAL(expectedZenUnitArgs.commandLine, actualZenUnitArgs.commandLine);
      VECTORS_EQUAL(expectedZenUnitArgs.testNameFilters, actualZenUnitArgs.testNameFilters);
      ARE_EQUAL(expectedZenUnitArgs.pauseBefore, actualZenUnitArgs.pauseBefore);
      ARE_EQUAL(expectedZenUnitArgs.pauseAfter, actualZenUnitArgs.pauseAfter);
      ARE_EQUAL(expectedZenUnitArgs.alwaysExit0, actualZenUnitArgs.alwaysExit0);
      ARE_EQUAL(expectedZenUnitArgs.failFast, actualZenUnitArgs.failFast);
      ARE_EQUAL(expectedZenUnitArgs.exit1IfTestsSkipped, actualZenUnitArgs.exit1IfTestsSkipped);
      ARE_EQUAL(expectedZenUnitArgs.informalSpecMode, actualZenUnitArgs.informalSpecMode);
      ARE_EQUAL(expectedZenUnitArgs.testRuns, actualZenUnitArgs.testRuns);
      ARE_EQUAL(expectedZenUnitArgs.randomTestOrdering, actualZenUnitArgs.randomTestOrdering);
      ARE_EQUAL(expectedZenUnitArgs.randomSeed, actualZenUnitArgs.randomSeed);
      ARE_EQUAL(expectedZenUnitArgs.randomSeedSetByUser, actualZenUnitArgs.randomSeedSetByUser);
      ARE_EQUAL(expectedZenUnitArgs.maxTestMilliseconds, actualZenUnitArgs.maxTestMilliseconds);
   }
}

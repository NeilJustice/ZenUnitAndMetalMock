#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"

namespace ZenUnit
{
   void Equalizer<ZenUnitArgs>::AssertEqual(const ZenUnitArgs& expectedArguments, const ZenUnitArgs& actualArgs)
   {
      ARE_EQUAL(expectedArguments.commandLine, actualArgs.commandLine);
      VECTORS_EQUAL(expectedArguments.runFilters, actualArgs.runFilters);
      ARE_EQUAL(expectedArguments.pauseBefore, actualArgs.pauseBefore);
      ARE_EQUAL(expectedArguments.pauseAfter, actualArgs.pauseAfter);
      ARE_EQUAL(expectedArguments.alwaysExit0, actualArgs.alwaysExit0);
      ARE_EQUAL(expectedArguments.failFast, actualArgs.failFast);
      ARE_EQUAL(expectedArguments.exit1IfTestsSkipped, actualArgs.exit1IfTestsSkipped);
      ARE_EQUAL(expectedArguments.testRuns, actualArgs.testRuns);
      ARE_EQUAL(expectedArguments.randomTestOrdering, actualArgs.randomTestOrdering);
      ARE_EQUAL(expectedArguments.randomSeed, actualArgs.randomSeed);
      ARE_EQUAL(expectedArguments.randomSeedSetByUser, actualArgs.randomSeedSetByUser);
      ARE_EQUAL(expectedArguments.maxTestMilliseconds, actualArgs.maxTestMilliseconds);
   }
}

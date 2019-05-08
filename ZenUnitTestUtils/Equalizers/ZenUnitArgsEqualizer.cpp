#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/RunFilterEqualizer.h"

namespace ZenUnit
{
   void Equalizer<ZenUnitArgs>::AssertEqual(const ZenUnitArgs& expectedArguments, const ZenUnitArgs& actualArgs)
   {
      ARE_EQUAL(expectedArguments.commandLine, actualArgs.commandLine);
      VECTORS_EQUAL(expectedArguments.runFilters, actualArgs.runFilters);
      ARE_EQUAL(expectedArguments.pause, actualArgs.pause);
      ARE_EQUAL(expectedArguments.wait, actualArgs.wait);
      ARE_EQUAL(expectedArguments.exitZero, actualArgs.exitZero);
      ARE_EQUAL(expectedArguments.failFast, actualArgs.failFast);
      ARE_EQUAL(expectedArguments.noSkips, actualArgs.noSkips);
      ARE_EQUAL(expectedArguments.testRuns, actualArgs.testRuns);
      ARE_EQUAL(expectedArguments.random, actualArgs.random);
      ARE_EQUAL(expectedArguments.randomSeed, actualArgs.randomSeed);
      ARE_EQUAL(expectedArguments.randomSeedSetByUser, actualArgs.randomSeedSetByUser);
      ARE_EQUAL(expectedArguments.maxTestMilliseconds, actualArgs.maxTestMilliseconds);
      ARE_EQUAL(expectedArguments.maxTotalSeconds, actualArgs.maxTotalSeconds);
   }
}

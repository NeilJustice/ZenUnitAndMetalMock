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
      ARE_EQUAL(expectedArguments.exit0, actualArgs.exit0);
      ARE_EQUAL(expectedArguments.failfast, actualArgs.failfast);
      ARE_EQUAL(expectedArguments.noskips, actualArgs.noskips);
      ARE_EQUAL(expectedArguments.testruns, actualArgs.testruns);
      ARE_EQUAL(expectedArguments.random, actualArgs.random);
      ARE_EQUAL(expectedArguments.randomseed, actualArgs.randomseed);
      ARE_EQUAL(expectedArguments.randomseedsetbyuser, actualArgs.randomseedsetbyuser);
      ARE_EQUAL(expectedArguments.maxtestmilliseconds, actualArgs.maxtestmilliseconds);
      ARE_EQUAL(expectedArguments.maxtotalseconds, actualArgs.maxtotalseconds);
   }
}

#include "pch.h"

namespace ZenUnit
{
   TESTS(ZenUnitArgsTests)
   AFACT(DefaultConstructor_SetsFieldsToDefaults)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsToDefaults)
   {
      const ZenUnitArgs defaultZenUnitArgs;
      ZenUnitArgs expectedDefaultZenUnitArgs;
      expectedDefaultZenUnitArgs.commandLine = "";
      expectedDefaultZenUnitArgs.testNameFilters = std::vector<TestNameFilter>{};
      expectedDefaultZenUnitArgs.pauseBefore = false;
      expectedDefaultZenUnitArgs.pauseAfter = false;
      expectedDefaultZenUnitArgs.alwaysExit0 = false;
      expectedDefaultZenUnitArgs.failFast = false;
      expectedDefaultZenUnitArgs.exit1IfTestsSkipped = false;
      expectedDefaultZenUnitArgs.testRuns = 1;
      expectedDefaultZenUnitArgs.randomTestOrdering = false;
      expectedDefaultZenUnitArgs.randomSeed = 0;
      expectedDefaultZenUnitArgs.randomSeedSetByUser = false;
      expectedDefaultZenUnitArgs.maxTestMilliseconds = 0;
      ARE_EQUAL(expectedDefaultZenUnitArgs, defaultZenUnitArgs);
   }

   RUN_TESTS(ZenUnitArgsTests)
}

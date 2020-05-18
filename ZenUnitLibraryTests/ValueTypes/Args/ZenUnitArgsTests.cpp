#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"

namespace ZenUnit
{
   TESTS(ZenUnitArgsTests)
   AFACT(DefaultConstructor_SetsFieldsToDefaults)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsToDefaults)
   {
      ZenUnitArgs zenUnitArgs;
      ARE_EQUAL("", zenUnitArgs.commandLine);
      IS_EMPTY(zenUnitArgs.testNameFilters);
      IS_FALSE(zenUnitArgs.pauseBefore);
      IS_FALSE(zenUnitArgs.pauseAfter);
      IS_FALSE(zenUnitArgs.alwaysExit0);
      IS_FALSE(zenUnitArgs.failFast);
      IS_FALSE(zenUnitArgs.exit1IfTestsSkipped);
      ARE_EQUAL(1, zenUnitArgs.testRuns);
      IS_FALSE(zenUnitArgs.randomTestOrdering);
      ARE_EQUAL(0, zenUnitArgs.randomSeed);
      IS_FALSE(zenUnitArgs.randomSeedSetByUser);
      IS_ZERO(zenUnitArgs.maxTestMilliseconds);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(ZenUnitArgs);
      EQUALIZER_THROWS(ZenUnitArgs, commandLine, "ZenUnitTests.exe");
      EQUALIZER_THROWS(ZenUnitArgs, testNameFilters, vector<TestNameFilter> { TestNameFilter() });
      EQUALIZER_THROWS(ZenUnitArgs, pauseBefore, true);
      EQUALIZER_THROWS(ZenUnitArgs, pauseAfter, true);
      EQUALIZER_THROWS(ZenUnitArgs, alwaysExit0, true);
      EQUALIZER_THROWS(ZenUnitArgs, failFast, true);
      EQUALIZER_THROWS(ZenUnitArgs, exit1IfTestsSkipped, true);
      EQUALIZER_THROWS(ZenUnitArgs, testRuns, 2u);
      EQUALIZER_THROWS(ZenUnitArgs, randomTestOrdering, true);
      EQUALIZER_THROWS(ZenUnitArgs, randomSeed, 3u);
      EQUALIZER_THROWS(ZenUnitArgs, randomSeedSetByUser, true);
      EQUALIZER_THROWS(ZenUnitArgs, maxTestMilliseconds, 4u);
   }

   RUN_TESTS(ZenUnitArgsTests)
}

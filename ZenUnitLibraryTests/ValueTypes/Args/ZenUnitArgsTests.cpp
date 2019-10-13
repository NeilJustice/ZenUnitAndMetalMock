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
      IS_EMPTY(zenUnitArgs.runFilters);
      IS_FALSE(zenUnitArgs.wait);
      IS_FALSE(zenUnitArgs.exitZero);
      IS_FALSE(zenUnitArgs.failFast);
      IS_FALSE(zenUnitArgs.noSkips);
      ARE_EQUAL(1, zenUnitArgs.testRuns);
      IS_FALSE(zenUnitArgs.random);
      ARE_EQUAL(0, zenUnitArgs.randomSeed);
      IS_FALSE(zenUnitArgs.randomSeedSetByUser);
      IS_ZERO(zenUnitArgs.maxTestMilliseconds);
      IS_ZERO(zenUnitArgs.maxTotalSeconds);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(ZenUnitArgs);
      EQUALIZER_THROWS(ZenUnitArgs, commandLine, "ZenUnitTests.exe");
      EQUALIZER_THROWS(ZenUnitArgs, runFilters, vector<RunFilter> { RunFilter() });
      EQUALIZER_THROWS(ZenUnitArgs, pause, true);
      EQUALIZER_THROWS(ZenUnitArgs, wait, true);
      EQUALIZER_THROWS(ZenUnitArgs, exitZero, true);
      EQUALIZER_THROWS(ZenUnitArgs, failFast, true);
      EQUALIZER_THROWS(ZenUnitArgs, noSkips, true);
      EQUALIZER_THROWS(ZenUnitArgs, testRuns, 2u);
      EQUALIZER_THROWS(ZenUnitArgs, random, true);
      EQUALIZER_THROWS(ZenUnitArgs, randomSeed, 3u);
      EQUALIZER_THROWS(ZenUnitArgs, randomSeedSetByUser, true);
      EQUALIZER_THROWS(ZenUnitArgs, maxTestMilliseconds, 4u);
      EQUALIZER_THROWS(ZenUnitArgs, maxTotalSeconds, 5u);
   }

   RUN_TESTS(ZenUnitArgsTests)
}

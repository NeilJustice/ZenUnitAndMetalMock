#include "pch.h"

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
      IS_ZERO(zenUnitArgs.randomSeed);
      IS_FALSE(zenUnitArgs.randomSeedSetByUser);
      IS_ZERO(zenUnitArgs.maxTestMilliseconds);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(ZenUnitArgs);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, commandLine, "ZenUnitTests.exe");
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, testNameFilters, vector<TestNameFilter> { TestNameFilter() });
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, pauseBefore, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, pauseAfter, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, alwaysExit0, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, failFast, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, exit1IfTestsSkipped, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, testRuns, 2u);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, randomTestOrdering, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, randomSeed, 3u);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, randomSeedSetByUser, true);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ZenUnitArgs, maxTestMilliseconds, 4u);
   }

   RUN_TESTS(ZenUnitArgsTests)
}

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
      IS_FALSE(zenUnitArgs.failfast);
      IS_FALSE(zenUnitArgs.noskips);
      ARE_EQUAL(1, zenUnitArgs.testruns);
      IS_FALSE(zenUnitArgs.random);
      ARE_EQUAL(0, zenUnitArgs.randomseed);
      IS_FALSE(zenUnitArgs.randomseedsetbyuser);
      IS_ZERO(zenUnitArgs.maxtestmilliseconds);
      IS_ZERO(zenUnitArgs.maxtotalseconds);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(ZenUnitArgs);
      EQUALIZER_THROWS(ZenUnitArgs, commandLine, "ZenUnitTests.exe");
      EQUALIZER_THROWS(ZenUnitArgs, runFilters, vector<RunFilter> { RunFilter() });
      EQUALIZER_THROWS(ZenUnitArgs, pause, true);
      EQUALIZER_THROWS(ZenUnitArgs, wait, true);
      EQUALIZER_THROWS(ZenUnitArgs, exitZero, true);
      EQUALIZER_THROWS(ZenUnitArgs, failfast, true);
      EQUALIZER_THROWS(ZenUnitArgs, noskips, true);
      EQUALIZER_THROWS(ZenUnitArgs, testruns, 2u);
      EQUALIZER_THROWS(ZenUnitArgs, random, true);
      EQUALIZER_THROWS(ZenUnitArgs, randomseed, static_cast<unsigned short>(3));
      EQUALIZER_THROWS(ZenUnitArgs, randomseedsetbyuser, true);
      EQUALIZER_THROWS(ZenUnitArgs, maxtestmilliseconds, 4u);
      EQUALIZER_THROWS(ZenUnitArgs, maxtotalseconds, 5u);
   }

   RUN_TESTS(ZenUnitArgsTests)
}

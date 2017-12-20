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
      ARE_EQUAL(PrintMode::Normal, zenUnitArgs.printMode);
      IS_EMPTY(zenUnitArgs.runFilters);
      IS_FALSE(zenUnitArgs.wait);
      IS_FALSE(zenUnitArgs.exit0);
      IS_FALSE(zenUnitArgs.failskips);
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
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, commandLine, "ZenUnitTests.exe");
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, printMode, PrintMode::Minimalist);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, runFilters, vector<RunFilter> { RunFilter() });
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, pause, true);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, wait, true);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, exit0, true);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, failskips, true);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, testruns, 2u);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, random, true);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, randomseed, static_cast<unsigned short>(3));
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, randomseedsetbyuser, true);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, maxtestmilliseconds, 4u);
      EQUALIZER_THROWS_FOR_FIELD(ZenUnitArgs, maxtotalseconds, 5u);
   }

   }; RUNTESTS(ZenUnitArgsTests)
}

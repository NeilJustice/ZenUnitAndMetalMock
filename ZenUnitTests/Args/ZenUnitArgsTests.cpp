#include "pch.h"
#include "ZenUnit/Args/ZenUnitArgs.h"

namespace ZenUnit
{
   TESTS(ZenUnitArgsTests)
   SPEC(DefaultConstructor_SetsFieldsToDefaults)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(DefaultConstructor_SetsFieldsToDefaults)
   {
      ZenUnitArgs zenUnitArgs;
      IS_EMPTY(zenUnitArgs.commandLine);
      ARE_EQUAL(PrintMode::Default, zenUnitArgs.printMode);
      IS_FALSE(zenUnitArgs.exit0);
      IS_FALSE(zenUnitArgs.failskips);
      ARE_EQUAL(1, zenUnitArgs.testruns);
      IS_ZERO(zenUnitArgs.maxtestmilliseconds);
      IS_ZERO(zenUnitArgs.maxtotalseconds);
      ARE_EQUAL(5, ZenUnitArgs::NumberOfValidArgs);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(ZenUnitArgs);
      EQUALIZER_THROWS(ZenUnitArgs, commandLine, "ZenUnitTests.exe");
      EQUALIZER_THROWS(ZenUnitArgs, printMode, PrintMode::Minimal);
      EQUALIZER_THROWS(ZenUnitArgs, exit0, true);
      EQUALIZER_THROWS(ZenUnitArgs, failskips, true);
      EQUALIZER_THROWS(ZenUnitArgs, testruns, 10u);
      EQUALIZER_THROWS(ZenUnitArgs, maxtestmilliseconds, 20u);
      EQUALIZER_THROWS(ZenUnitArgs, maxtotalseconds, 30u);
   }

   }; RUN(ZenUnitArgsTests)
}

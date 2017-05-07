#include "pch.h"
#include "ZenUnit/Args/ZenUnitArgs.h"

namespace ZenUnit
{
   TESTS(ZenUnitArgsTests)
   SPEC(DefaultConstructor_SetsFieldsTo0)
   SPEC(ValidArgs_IsExpectedStringSet)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      ZenUnitArgs zenUnitArgs;
      IS_EMPTY(zenUnitArgs.commandLine);
      IS_ZERO(zenUnitArgs.times);
      IS_FALSE(zenUnitArgs.exit0);
      IS_FALSE(zenUnitArgs.noskips);
      IS_ZERO(zenUnitArgs.maxtestmilliseconds);
      IS_ZERO(zenUnitArgs.maxtotalseconds);
   }

   TEST(ValidArgs_IsExpectedStringSet)
   {
      const unordered_set<string> ExpectedValidArgs
      {
         "-exit0",
         "-noskips",
         "-help",
         "--help"
      };
      SETS_EQUAL(ExpectedValidArgs, ZenUnitArgs::ValidArgs);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(ZenUnitArgs);
      EQUALIZER_THROWS(ZenUnitArgs, commandLine, "ZenUnitTests.exe");
      EQUALIZER_THROWS(ZenUnitArgs, times, static_cast<unsigned short>(1));
      EQUALIZER_THROWS(ZenUnitArgs, exit0, true);
      EQUALIZER_THROWS(ZenUnitArgs, noskips, true);
      EQUALIZER_THROWS(ZenUnitArgs, maxtestmilliseconds, 2u);
      EQUALIZER_THROWS(ZenUnitArgs, maxtotalseconds, 3u);
   }

   }; RUN(ZenUnitArgsTests)
}

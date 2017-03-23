#include "pch.h"
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenUnit
{
   const std::unordered_set<std::string> ZenUnitArgs::ValidArgs = std::unordered_set<std::string>
   {
      "-exit0",
      "-noskips",
      "-help",
      "--help"
   };
}

void ZenUnitEqualizer<ZenUnit::ZenUnitArgs>::
AssertEqual(const ZenUnit::ZenUnitArgs& expectedArgs, const ZenUnit::ZenUnitArgs& actualArgs)
{
   ARE_EQUAL(expectedArgs.commandLine, actualArgs.commandLine);
   ARE_EQUAL(expectedArgs.exit0, actualArgs.exit0);
   ARE_EQUAL(expectedArgs.noskips, actualArgs.noskips);
   ARE_EQUAL(expectedArgs.maxtestmilliseconds, actualArgs.maxtestmilliseconds);
   ARE_EQUAL(expectedArgs.maxtotalseconds, actualArgs.maxtotalseconds);
}

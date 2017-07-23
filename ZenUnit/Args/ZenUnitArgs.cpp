#include "pch.h"
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

const size_t ZenUnit::ZenUnitArgs::NumberOfValidArgs = 5;

void ZenUnitEqualizer<ZenUnit::ZenUnitArgs>::
AssertEqual(const ZenUnit::ZenUnitArgs& expectedArgs, const ZenUnit::ZenUnitArgs& actualArgs)
{
   ARE_EQUAL(expectedArgs.commandLine, actualArgs.commandLine);
   ARE_EQUAL(expectedArgs.printMode, actualArgs.printMode);
   ARE_EQUAL(expectedArgs.exit0, actualArgs.exit0);
   ARE_EQUAL(expectedArgs.failskips, actualArgs.failskips);
   ARE_EQUAL(expectedArgs.testruns, actualArgs.testruns);
   ARE_EQUAL(expectedArgs.maxtestmilliseconds, actualArgs.maxtestmilliseconds);
   ARE_EQUAL(expectedArgs.maxtotalseconds, actualArgs.maxtotalseconds);
}

#include "pch.h"
#include "ZenUnitLibraryTests/ValueTypes/Args/ExpectedCommandLineUsage.h"

namespace ZenUnit
{
   TESTS(ZenUnitArgsTests)
   AFACT(VersionNumber_IsExpectedString)
   AFACT(DefaultConstructor_SetsFieldsToDefaults)
   AFACT(CommandLineUsage_IsExpectedString)
   EVIDENCE

   TEST(VersionNumber_IsExpectedString)
   {
      ARE_EQUAL("0.7.1", ZenUnit::VersionNumber);
   }

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
      expectedDefaultZenUnitArgs.globalRandomSeedSetByUser = false;
      expectedDefaultZenUnitArgs.maxTestMilliseconds = 0;
      ARE_EQUAL(expectedDefaultZenUnitArgs, defaultZenUnitArgs);
   }

   TEST(CommandLineUsage_IsExpectedString)
   {
      ARE_EQUAL(ExpectedCommandLineUsage, ZenUnitArgs::CommandLineUsage);
   }

   RUN_TESTS(ZenUnitArgsTests)
}

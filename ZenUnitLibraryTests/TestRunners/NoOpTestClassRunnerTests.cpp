#include "pch.h"
#include "ZenUnitLibraryTests/Random/RandomRunFilter.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"

namespace ZenUnit
{
   TESTS(NoOpTestClassRunnerTests)
   AFACT(TestClassName_ReturnsNoOpTestClassRunner)
   AFACT(NumberOfTestCases_Returns0)
   AFACT(RunTests_ReturnsDefaultTestClassResult)
   AFACT(HasTestThatMatchesRunFilter_ReturnsFalse)
   EVIDENCE

   NoOpTestClassRunner _noOpTestClassRunner;

   TEST(TestClassName_ReturnsNoOpTestClassRunner)
   {
      ARE_EQUAL("NoOpTestClassRunner", _noOpTestClassRunner.TestClassName());
   }

   TEST(NumberOfTestCases_Returns0)
   {
      ARE_EQUAL(0, _noOpTestClassRunner.NumberOfTestCases());
   }

   TEST(RunTests_ReturnsDefaultTestClassResult)
   {
      ARE_EQUAL(TestClassResult(), _noOpTestClassRunner.RunTests());
   }

   TEST(HasTestThatMatchesRunFilter_ReturnsFalse)
   {
      IS_FALSE(_noOpTestClassRunner.HasTestThatMatchesRunFilter(ZenUnit::Random<RunFilter>()));
   }

   RUN_TESTS(NoOpTestClassRunnerTests)
}

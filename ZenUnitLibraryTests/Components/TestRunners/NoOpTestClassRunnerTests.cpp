#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestNameFilter.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"

namespace ZenUnit
{
   TESTS(NoOpTestClassRunnerTests)
   AFACT(TestClassName_ReturnsNoOpTestClassRunner)
   AFACT(NumberOfTestCases_Returns0)
   AFACT(RunTests_ReturnsDefaultTestClassResult)
   AFACT(HasTestThatMatchesTestNameFilter_ReturnsFalse)
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

   TEST(HasTestThatMatchesTestNameFilter_ReturnsFalse)
   {
      IS_FALSE(_noOpTestClassRunner.HasTestThatMatchesTestNameFilter(ZenUnit::Random<TestNameFilter>()));
   }

   RUN_TESTS(NoOpTestClassRunnerTests)
}

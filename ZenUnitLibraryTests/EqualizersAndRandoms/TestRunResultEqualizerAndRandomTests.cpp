#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestRunResultEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(TestRunResultEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(TestRunResult);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestRunResult, _numberOfFailedTestCases, ZenUnit::RandomNon0<size_t>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestRunResult, _skippedFullTestNamesAndSkipReasons, ZenUnit::RandomNonEmptyVector<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestRunResult, _skippedTestClassNamesAndSkipReasons, ZenUnit::RandomNonEmptyVector<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestRunResult, _testClassResults, ZenUnit::RandomNonEmptyVector<TestClassResult>());
   }

   RUN_TESTS(TestRunResultEqualizerAndRandomTests)
}

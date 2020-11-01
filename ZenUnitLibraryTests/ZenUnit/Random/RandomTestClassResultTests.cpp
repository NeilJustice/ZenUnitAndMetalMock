#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestClassResult.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestResult.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(RandomTestClassResultTests)
   AFACT(RandomTestClassResult_CodeCoverage)
   AFACT(TestableRandomTestClassResult_ReturnsTestClassResultWithAllRandomFields)
   EVIDENCE

   TEST(RandomTestClassResult_CodeCoverage)
   {
      const TestClassResult randomTestClassResult = ZenUnit::Random<TestClassResult>();
   }

   TEST(TestableRandomTestClassResult_ReturnsTestClassResultWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;
      //
      const TestClassResult randomTestClassResult = TestableRandomTestClassResult(randomGeneratorMock);
      //
      IS_NOT_EMPTY(randomTestClassResult._testResults);
      for (size_t i = 0; i < randomTestClassResult._testResults.size(); ++i)
      {
         IS_NOT_DEFAULT_VALUE(randomTestClassResult._testResults[i]);
      }
   }

   RUN_TESTS(RandomTestClassResultTests)
}

#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestClassResult.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestResult.h"
#include "ZenUnitTestUtils/Equalizers/TestClassResultEqualizer.h"
#include "ZenUnitTestUtils/Equalizers/TestResultEqualizer.h"

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
      ZenMock::RandomGeneratorMock randomGeneratorMock;
      const vector<TestResult> randomTestResults = ZenUnit::RandomVector<TestResult>();
      //randomGeneratorMock.VectorMock.Return(randomTestResults);
      //
      const TestClassResult randomTestClassResult = TestableRandomTestClassResult(randomGeneratorMock);
      //
      //ZENMOCK(randomGeneratorMock.VectorMock.CalledOnce());
      TestClassResult expectedRandomTestClassResult;
      expectedRandomTestClassResult.AddTestResults(randomTestResults);
      ARE_EQUAL(expectedRandomTestClassResult, randomTestClassResult);
   }

   RUN_TESTS(RandomTestClassResultTests)
}

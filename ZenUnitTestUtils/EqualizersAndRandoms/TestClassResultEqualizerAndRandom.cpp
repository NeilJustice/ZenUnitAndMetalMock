#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<TestClassResult>::AssertEqual(
      const TestClassResult& expectedTestClassResult, const TestClassResult& actualTestClassResult)
   {
      FIELDS_ARE_EQUAL(expectedTestClassResult, actualTestClassResult, _testResults);
   }

   TestClassResult TestableRandomTestClassResult(const RandomGenerator* randomGenerator)
   {
      TestClassResult randomTestClassResult;
      randomTestClassResult._testResults = randomGenerator->NonEmptyVector<TestResult>();
      return randomTestClassResult;
   }

   template<>
   TestClassResult Random()
   {
      return TestableRandomTestClassResult(RandomGenerator::Instance());
   }
}

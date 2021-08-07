#include "pch.h"

namespace ZenUnit
{
   TESTS(TestClassResultEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomTestClassResult_ReturnsTestClassResultWithAllRandomFields)
   AFACT(ZenUnitRandomTestClassResult_DoesNotThrowException)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(TestClassResult);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestClassResult, _testResults, ZenUnit::RandomNonEmptyVector<TestResult>());
   }

   TEST(TestableRandomTestClassResult_ReturnsTestClassResultWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;
      //
      const TestClassResult randomTestClassResult = TestableRandomTestClassResult(&randomGeneratorMock);
      //
      IS_NOT_EMPTY(randomTestClassResult._testResults);
      for (size_t i = 0; i < randomTestClassResult._testResults.size(); ++i)
      {
         IS_NOT_DEFAULT_VALUE(randomTestClassResult._testResults[i]);
      }
   }

   TEST(ZenUnitRandomTestClassResult_DoesNotThrowException)
   {
      const TestClassResult randomTestClassResult = ZenUnit::Random<TestClassResult>();
   }

   RUN_TESTS(TestClassResultEqualizerAndRandomTests)
}

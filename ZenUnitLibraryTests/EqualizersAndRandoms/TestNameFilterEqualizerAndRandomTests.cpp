#include "pch.h"

namespace ZenUnit
{
   TESTS(TestNameFilterEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomTestNameFilter_ReturnsTestNameFilterWithAllRandomFields)
   AFACT(ZenUnitRandomTestNameFilter_DoesNotThrowException)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(TestNameFilter);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestNameFilter, testClassNamePattern, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestNameFilter, testNamePattern, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestNameFilter, testCaseNumber, ZenUnit::RandomNon0<size_t>());
   }

   TEST(TestableRandomTestNameFilter_ReturnsTestNameFilterWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;

      const string testClassNamePattern = ZenUnit::Random<string>();
      const string testNamePattern = ZenUnit::Random<string>();
      randomGeneratorMock.StringMock.ReturnValues(testClassNamePattern, testNamePattern);

      const size_t testCaseNumber = randomGeneratorMock.SizeTMock.ReturnRandom();
      //
      const TestNameFilter randomTestNameFilter = TestableRandomTestNameFilter(&randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.StringMock.CalledNTimes(2));
      METALMOCK(randomGeneratorMock.SizeTMock.CalledOnce());
      TestNameFilter expectedRandomTestNameFilter;
      expectedRandomTestNameFilter.testClassNamePattern = testClassNamePattern;
      expectedRandomTestNameFilter.testNamePattern = testNamePattern;
      expectedRandomTestNameFilter.testCaseNumber = testCaseNumber;
      ARE_EQUAL(expectedRandomTestNameFilter, randomTestNameFilter);
   }

   TEST(ZenUnitRandomTestNameFilter_DoesNotThrowException)
   {
      const TestNameFilter randomTestNameFilter = ZenUnit::Random<TestNameFilter>();
   }

   RUN_TESTS(TestNameFilterEqualizerAndRandomTests)
}

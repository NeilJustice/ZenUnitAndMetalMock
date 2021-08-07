#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(AnomalyEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomAnomaly_ReturnsAnomalyWithAllRandomFields)
   AFACT(ZenUnitRandomAnomaly_CodeCoverage)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Anomaly);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Anomaly, assertExpression, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Anomaly, expectedValueAsStringOrExpectedLine, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Anomaly, actualValueAsStringOrActualLine, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Anomaly, optionalThirdLine, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Anomaly, message, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Anomaly, why, ZenUnit::Random<string>());
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Anomaly, filePathLineNumber, ZenUnit::Random<FilePathLineNumber>());
   }

   TEST(TestableRandomAnomaly_ReturnsAnomalyWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;
      const string assertExpression = ZenUnit::Random<string>();
      const string expectedValueAsStringOrExpectedLine = ZenUnit::Random<string>();
      const string actualValueAsStringOrActualLine = ZenUnit::Random<string>();
      const string optionalThirdLine = ZenUnit::Random<string>();
      const string message = ZenUnit::Random<string>();
      const string why = ZenUnit::Random<string>();
      randomGeneratorMock.StringMock.ReturnValues(
         assertExpression, expectedValueAsStringOrExpectedLine, actualValueAsStringOrActualLine, optionalThirdLine, message, why);
      //
      const Anomaly randomAnomaly = ZenUnit::TestableRandomAnomaly(&randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.StringMock.CalledNTimes(6));
      ARE_EQUAL(assertExpression, randomAnomaly.assertExpression);
      ARE_EQUAL(expectedValueAsStringOrExpectedLine, randomAnomaly.expectedValueAsStringOrExpectedLine);
      ARE_EQUAL(actualValueAsStringOrActualLine, randomAnomaly.actualValueAsStringOrActualLine);
      ARE_EQUAL(optionalThirdLine, randomAnomaly.optionalThirdLine);
      ARE_EQUAL(message, randomAnomaly.message);
      ARE_EQUAL(why, randomAnomaly.why);
      IS_NOT_DEFAULT_VALUE(randomAnomaly.filePathLineNumber);
   }

   TEST(ZenUnitRandomAnomaly_CodeCoverage)
   {
      ZenUnit::Random<Anomaly>();
   }

   RUN_TESTS(AnomalyEqualizerAndRandomTests)
}

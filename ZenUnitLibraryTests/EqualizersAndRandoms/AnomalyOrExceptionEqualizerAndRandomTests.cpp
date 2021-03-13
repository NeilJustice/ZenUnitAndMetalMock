#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyOrExceptionEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(AnomalyOrExceptionEqualizerAndRandomTests)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   AFACT(TestableRandomAnomalyOrException_ReturnsAnomalyOrExceptionWithAllRandomFields)
   AFACT(ZenUnitRandomAnomalyOrException_CodeCoverage)
   EVIDENCE

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(AnomalyOrException);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AnomalyOrException, anomaly, make_shared<Anomaly>(ZenUnit::Random<Anomaly>()));
      const string exceptionTypeName;
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AnomalyOrException, exceptionTypeName, &exceptionTypeName);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AnomalyOrException, exceptionMessage, make_shared<string>(ZenUnit::Random<string>()));
   }

   TEST(TestableRandomAnomalyOrException_ReturnsAnomalyOrExceptionWithAllRandomFields)
   {
      ZenUnit::RandomGeneratorMock randomGeneratorMock;
      const string exceptionMessage = randomGeneratorMock.StringMock.ReturnRandom();
      //
      const AnomalyOrException randomAnomalyOrException = ZenUnit::TestableRandomAnomalyOrException(&randomGeneratorMock);
      //
      METALMOCK(randomGeneratorMock.StringMock.CalledOnce());
      IS_NOT_NULLPTR(randomAnomalyOrException.anomaly);
      IS_NOT_DEFAULT_VALUE(*randomAnomalyOrException.anomaly);
      IS_NULLPTR(randomAnomalyOrException.exceptionTypeName);
      IS_NOT_NULLPTR(randomAnomalyOrException.exceptionMessage);
      IS_NOT_DEFAULT_VALUE(*randomAnomalyOrException.exceptionMessage);
   }

   TEST(ZenUnitRandomAnomalyOrException_CodeCoverage)
   {
      ZenUnit::Random<AnomalyOrException>();
   }

   RUN_TESTS(AnomalyOrExceptionEqualizerAndRandomTests)
}

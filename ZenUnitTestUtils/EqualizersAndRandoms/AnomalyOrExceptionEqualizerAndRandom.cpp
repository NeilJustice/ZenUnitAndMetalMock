#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyOrExceptionEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<AnomalyOrException>::AssertEqual(
      const AnomalyOrException& expectedAnomalyOrException, const AnomalyOrException& actualAnomalyOrException)
   {
      POINTEES_ARE_EQUAL(expectedAnomalyOrException.anomaly, actualAnomalyOrException.anomaly);
      FIELDS_ARE_EQUAL(expectedAnomalyOrException, actualAnomalyOrException, exceptionTypeName);
      POINTEES_ARE_EQUAL(expectedAnomalyOrException.exceptionMessage, actualAnomalyOrException.exceptionMessage);
   }

   AnomalyOrException TestableRandomAnomalyOrException(const RandomGenerator* randomGenerator)
   {
      AnomalyOrException randomAnomalyOrException;
      randomAnomalyOrException.anomaly = make_shared<Anomaly>(ZenUnit::Random<Anomaly>());
      randomAnomalyOrException.exceptionTypeName = nullptr;
      randomAnomalyOrException.exceptionMessage = make_shared<string>(randomGenerator->String());
      return randomAnomalyOrException;
   }

   template<>
   AnomalyOrException Random()
   {
      return TestableRandomAnomalyOrException(RandomGenerator::Instance());
   }
}

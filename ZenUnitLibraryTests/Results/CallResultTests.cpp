#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/TestPhaseResultEqualizer.h"

namespace ZenUnit
{
   TESTS(TestPhaseResultTests)
   AFACT(DefaultConstructor_SetsFieldsTo0)
   AFACT(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      const TestPhaseResult defaultTestPhaseResult;
      TestPhaseResult expectedDefaultTestPhaseResult;
      expectedDefaultTestPhaseResult.testPhase = TestPhase::Unset;
      expectedDefaultTestPhaseResult.testOutcome = TestOutcome::Success;
      expectedDefaultTestPhaseResult.microseconds = 0;
      expectedDefaultTestPhaseResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedDefaultTestPhaseResult, defaultTestPhaseResult);
   }

   TEST(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   {
      const TestPhaseResult testPhaseResult(TestPhase::Constructor);
      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::Constructor;
      expectedTestPhaseResult.testOutcome = TestOutcome::Success;
      expectedTestPhaseResult.microseconds = 0;
      expectedTestPhaseResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(TestPhaseResult);
      EQUALIZER_THROWS(TestPhaseResult, testPhase, TestPhase::Constructor);
      EQUALIZER_THROWS(TestPhaseResult, testOutcome, TestOutcome::Exception);
      EQUALIZER_THROWS(TestPhaseResult, microseconds, 1u);

      shared_ptr<AnomalyOrException> nonDefaultAnomalyOrException = make_shared<AnomalyOrException>(Anomaly());
      nonDefaultAnomalyOrException->anomaly->why = "why";
      EQUALIZER_THROWS(TestPhaseResult, anomalyOrException, nonDefaultAnomalyOrException);
   }

   RUN_TESTS(TestPhaseResultTests)
}

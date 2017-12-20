#include "pch.h"

namespace ZenUnit
{
   TESTS(CallResultTests)
   AFACT(DefaultConstructor_SetsFieldsTo0)
   AFACT(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      const CallResult defaultCallResult;
      CallResult expectedDefaultCallResult;
      expectedDefaultCallResult.testPhase = TestPhase::Unset;
      expectedDefaultCallResult.testOutcome = TestOutcome::Success;
      expectedDefaultCallResult.milliseconds = 0;
      expectedDefaultCallResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedDefaultCallResult, defaultCallResult);
   }

   TEST(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   {
      const CallResult callResult(TestPhase::Constructor);
      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::Constructor;
      expectedCallResult.testOutcome = TestOutcome::Success;
      expectedCallResult.milliseconds = 0;
      expectedCallResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedCallResult, callResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(CallResult);
      EQUALIZER_THROWS_FOR_FIELD(CallResult, testPhase, TestPhase::Constructor);
      EQUALIZER_THROWS_FOR_FIELD(CallResult, testOutcome, TestOutcome::Exception);
      EQUALIZER_THROWS_FOR_FIELD(CallResult, milliseconds, 1u);

      shared_ptr<AnomalyOrException> nonDefaultAnomalyOrException = make_shared<AnomalyOrException>(Anomaly());
      nonDefaultAnomalyOrException->anomaly->why = "why";
      EQUALIZER_THROWS_FOR_FIELD(CallResult, anomalyOrException, nonDefaultAnomalyOrException);
   }

   }; RUNTESTS(CallResultTests)
}

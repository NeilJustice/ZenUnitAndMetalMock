#include "pch.h"
#include "ZenUnit/Results/CallResult.h"

namespace ZenUnit
{
   TESTS(CallResultTests)
   SPEC(DefaultConstructor_SetsFieldsTo0)
   SPEC(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   SPEC(Assign_CopiesCallResultToSelf)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

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

   TEST(Assign_CopiesCallResultToSelf)
   {
      CallResult callResult;
      CallResult callResultArg;
      callResultArg.testPhase = TestPhase::Constructor;
      callResultArg.testOutcome = TestOutcome::Exception;
      callResultArg.milliseconds = 1;
      callResultArg.anomalyOrException = make_shared<AnomalyOrException>(Anomaly());
      ARE_EQUAL(1, callResultArg.anomalyOrException.use_count());
      //
      callResult.Assign(callResultArg);
      //
      ARE_EQUAL(2, callResult.anomalyOrException.use_count());
      ARE_EQUAL(2, callResultArg.anomalyOrException.use_count());
      ARE_EQUAL(callResultArg, callResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(CallResult);
      EQUALIZER_THROWS(CallResult, testPhase, TestPhase::Constructor);
      EQUALIZER_THROWS(CallResult, testOutcome, TestOutcome::Exception);
      EQUALIZER_THROWS(CallResult, milliseconds, 1u);

      shared_ptr<AnomalyOrException> nonDefaultAnomalyOrException = make_shared<AnomalyOrException>(Anomaly());
      nonDefaultAnomalyOrException->anomaly->why = "why";
      EQUALIZER_THROWS(CallResult, anomalyOrException, nonDefaultAnomalyOrException);
   }

   }; RUN(CallResultTests)
}

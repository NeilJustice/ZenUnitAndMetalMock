#include "pch.h"

namespace ZenUnit
{
   TESTS(TestPhaseResultTests)
   AFACT(DefaultConstructor_SetsFieldsTo0)
   AFACT(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      const TestPhaseResult defaultTestPhaseResult;
      TestPhaseResult expectedDefaultTestPhaseResult;
      expectedDefaultTestPhaseResult.testPhase = TestPhase::Unset;
      expectedDefaultTestPhaseResult.testOutcome = TestOutcome::Success;
      expectedDefaultTestPhaseResult.elapsedMicroseconds = 0;
      expectedDefaultTestPhaseResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedDefaultTestPhaseResult, defaultTestPhaseResult);
   }

   TEST(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   {
      const TestPhaseResult testPhaseResult(TestPhase::Constructor);
      TestPhaseResult expectedTestPhaseResult;
      expectedTestPhaseResult.testPhase = TestPhase::Constructor;
      expectedTestPhaseResult.testOutcome = TestOutcome::Success;
      expectedTestPhaseResult.elapsedMicroseconds = 0;
      expectedTestPhaseResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedTestPhaseResult, testPhaseResult);
   }

   RUN_TESTS(TestPhaseResultTests)
}

#include "pch.h"

namespace ZenUnit
{
   TESTS(TestPhaseTranslatorTests)
   FACTS(TestPhaseToTestPhaseSuffix_ReturnsTestPhaseSuffix)
   FACTS(TestPhaseToTestPhaseSuffix_UnsetOrDestructorTestPhase_Throws)
   EVIDENCE

   TestPhaseTranslator _testPhaseTranslator;

   TEST2X2(TestPhaseToTestPhaseSuffix_ReturnsTestPhaseSuffix,
      TestPhase testPhase, const char* expectedTestPhaseSuffix,
      TestPhase::Constructor, " in test class constructor",
      TestPhase::Startup, " in STARTUP",
      TestPhase::TestBody, "",
      TestPhase::Cleanup, " in CLEANUP")
   {
      ARE_EQUAL(expectedTestPhaseSuffix, _testPhaseTranslator.TestPhaseToTestPhaseSuffix(testPhase));
   }

   TEST1X1(TestPhaseToTestPhaseSuffix_UnsetOrDestructorTestPhase_Throws,
      TestPhase testPhase,
      TestPhase::Unset,
      TestPhase::Destructor,
      TestPhase::MaxValue)
   {
      THROWS(_testPhaseTranslator.TestPhaseToTestPhaseSuffix(testPhase),
         invalid_argument, "Invalid testPhase:" + to_string(static_cast<int>(testPhase)));
   }

   RUN_TESTS(TestPhaseTranslatorTests)
}

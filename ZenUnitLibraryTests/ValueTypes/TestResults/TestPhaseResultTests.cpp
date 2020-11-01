#include "pch.h"

namespace ZenUnit
{
   TESTS(TestPhaseTranslatorTests)
   FACTS(TestPhaseToTestPhaseName_TestPhaseIs_Constructor_Startup_TestBody_Or_Cleanup_ReturnsTestPhaseName)
   FACTS(TestPhaseToTestPhaseName_TestPhaseIsNot_Constructor_Startup_TestBody_Or_Cleanup_ThrowsInvalidArgument)
   FACTS(TestPhaseToTestPhaseSuffix_ReturnsTestPhaseSuffix)
   FACTS(TestPhaseToTestPhaseSuffix_UnsetOrDestructorTestPhase_Throws)
   EVIDENCE

   TestPhaseTranslator _testPhaseTranslator;

   TEST2X2(TestPhaseToTestPhaseName_TestPhaseIs_Constructor_Startup_TestBody_Or_Cleanup_ReturnsTestPhaseName,
      TestPhase testPhase, const char* expectedReturnValue,
      TestPhase::Constructor, "test class constructor",
      TestPhase::Startup, "STARTUP",
      TestPhase::TestBody, "test body",
      TestPhase::Cleanup, "CLEANUP")
   {
      const char* const testPhaseName = _testPhaseTranslator.TestPhaseToTestPhaseName(testPhase);
      ARE_EQUAL(expectedReturnValue, testPhaseName);
   }

   TEST1X1(TestPhaseToTestPhaseName_TestPhaseIsNot_Constructor_Startup_TestBody_Or_Cleanup_ThrowsInvalidArgument,
      TestPhase testPhase,
      TestPhase::Unset,
      TestPhase::Destructor,
      TestPhase::MaxValue,
      static_cast<TestPhase>(-1))
   {
      THROWS_EXCEPTION(_testPhaseTranslator.TestPhaseToTestPhaseName(testPhase),
         invalid_argument, "Invalid testPhase:" + std::to_string(static_cast<int>(testPhase)));
   }

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
      THROWS_EXCEPTION(_testPhaseTranslator.TestPhaseToTestPhaseSuffix(testPhase),
         invalid_argument, "Invalid testPhase:" + to_string(static_cast<int>(testPhase)));
   }

   RUN_TESTS(TestPhaseTranslatorTests)
}

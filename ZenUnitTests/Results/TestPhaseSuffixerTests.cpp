#include "pch.h"

TESTS(TestPhaseSuffixerTests)
FACTS(TestPhaseToTestPhaseSuffix_ReturnsTestPhaseSuffix)
FACTS(TestPhaseToTestPhaseSuffix_UnsetOrDestructorTestPhase_Throws)
EVIDENCE

TestPhaseSuffixer _testPhaseSuffixer;

TEST2X2(TestPhaseToTestPhaseSuffix_ReturnsTestPhaseSuffix,
   TestPhase testPhase, const char* expectedTestPhaseSuffix,
   TestPhase::Constructor, " in test class constructor",
   TestPhase::Startup, " in STARTUP",
   TestPhase::TestBody, "",
   TestPhase::Cleanup, " in CLEANUP")
{
   ARE_EQUAL(expectedTestPhaseSuffix, _testPhaseSuffixer.TestPhaseToTestPhaseSuffix(testPhase));
}

TEST1X1(TestPhaseToTestPhaseSuffix_UnsetOrDestructorTestPhase_Throws,
   TestPhase testPhase,
   TestPhase::Unset,
   TestPhase::Destructor)
{
   THROWS(_testPhaseSuffixer.TestPhaseToTestPhaseSuffix(testPhase),
      invalid_argument, "Invalid testPhase");
}

RUN_TESTS(TestPhaseSuffixerTests)

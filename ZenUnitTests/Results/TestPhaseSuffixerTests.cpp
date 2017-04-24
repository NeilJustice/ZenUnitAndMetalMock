#include "pch.h"
#include "ZenUnit/Results/TestPhaseSuffixer.h"

TESTS(TestPhaseSuffixerTests)
SPECX(TestPhaseToTestPhaseSuffix_ReturnsTestPhaseSuffix)
SPECX(TestPhaseToTestPhaseSuffix_UnsetOrDestructorTestPhase_Throws)
SPECEND

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
      logic_error, R"(assert_true(testPhase == TestPhase::Cleanup) failed in TestPhaseToTestPhaseSuffix()
File.cpp(1))");
}

}; RUN(TestPhaseSuffixerTests)

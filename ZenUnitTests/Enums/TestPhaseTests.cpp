#include "pch.h"
#include "ZenUnit/Enums/TestPhase.h"

namespace ZenUnit
{
   TESTS(TestPhaseTests)
   SPECX(TestPhaseToTestPhaseSuffix_ReturnsExpected)
   SPEC(TestPhaseToTestPhaseSuffix_InvalidTestPhase_TriggersAssertion)
   SPECEND

   TEST2X2(TestPhaseToTestPhaseSuffix_ReturnsExpected,
      TestPhase testPhase, const char* expectedTestPhaseSuffix,
      TestPhase::Constructor, " in test class constructor",
      TestPhase::Startup, " in STARTUP",
      TestPhase::TestBody, "",
      TestPhase::Cleanup, " in CLEANUP")
   {
      ARE_EQUAL(expectedTestPhaseSuffix, TestPhaseToTestPhaseSuffix(testPhase));
   }

   TEST(TestPhaseToTestPhaseSuffix_InvalidTestPhase_TriggersAssertion)
   {
      THROWS(TestPhaseToTestPhaseSuffix(TestPhase::Unset), logic_error, 
         R"(assert_true(testPhase == TestPhase::Cleanup) failed in TestPhaseToTestPhaseSuffix()
File.cpp(1))");
      THROWS(TestPhaseToTestPhaseSuffix(TestPhase::Destructor), logic_error, 
         R"(assert_true(testPhase == TestPhase::Cleanup) failed in TestPhaseToTestPhaseSuffix()
File.cpp(1))");
   }

   }; RUN(TestPhaseTests)
}

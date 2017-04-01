#include "pch.h"
#include "TestPhase.h"
#include "Utils/AssertTrue.h"

namespace ZenUnit
{
   const char* TestPhaseToTestPhaseSuffix(TestPhase testPhase)
   {
      switch (testPhase)
      {
      case TestPhase::Constructor:
      {
         return " in test class constructor";
      }
      case TestPhase::Startup:
      {
         return " in STARTUP";
      }
      case TestPhase::TestBody:
      {
         return "";
      }
      default:
      {
         assert_true(testPhase == TestPhase::Cleanup);
         return " in CLEANUP";
      }
      }
   }
}

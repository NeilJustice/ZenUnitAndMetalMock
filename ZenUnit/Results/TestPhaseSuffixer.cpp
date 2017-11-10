#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Enums/TestPhase.h"
#include "ZenUnit/Results/TestPhaseSuffixer.h"
#include "ZenUnit/Utils/AssertTrue.h"

namespace ZenUnit
{
   INLINE const char* TestPhaseSuffixer::TestPhaseToTestPhaseSuffix(TestPhase testPhase) const
   {
      return DoTestPhaseToTestPhaseSuffix(testPhase);
   }

   INLINE const char* TestPhaseSuffixer::DoTestPhaseToTestPhaseSuffix(TestPhase testPhase)
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

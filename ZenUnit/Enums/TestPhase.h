#pragma once

namespace ZenUnit
{
   enum class TestPhase : unsigned char
   {
      Unset,
      Constructor,
      Startup,
      TestBody,
      Cleanup,
      Destructor
   };

   const char* TestPhaseToTestPhaseSuffix(TestPhase testPhase);
}

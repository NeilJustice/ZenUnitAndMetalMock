#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Results/TestFailureNumberer.h"

namespace ZenUnit
{
   INLINE std::string TestFailureNumberer::Next()
   {
      const std::string nextTestFailureNumber = "<" + std::to_string(_testFailureNumber++) + ">";
      return nextTestFailureNumber;
   }

   INLINE void TestFailureNumberer::Reset()
   {
      _testFailureNumber = 1u;
   }
}

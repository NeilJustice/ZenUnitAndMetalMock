#include "pch.h"
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

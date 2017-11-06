#include "pch.h"
#include "ZenUnit/Results/TestFailureNumberer.h"

namespace ZenUnit
{
   inline std::string TestFailureNumberer::Next()
   {
      const std::string nextTestFailureNumber = "<" + std::to_string(_testFailureNumber++) + ">";
      return nextTestFailureNumber;
   }

   inline void TestFailureNumberer::Reset()
   {
      _testFailureNumber = 1u;
   }
}

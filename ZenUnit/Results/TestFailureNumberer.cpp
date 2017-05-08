#include "pch.h"
#include "ZenUnit/Results/TestFailureNumberer.h"

namespace ZenUnit
{
   string TestFailureNumberer::Next()
   {
      const string nextTestFailureNumber = "<" + to_string(_testFailureNumber++) + ">";
      return nextTestFailureNumber;
   }

   void TestFailureNumberer::Reset()
   {
      _testFailureNumber = 1u;
   }
}

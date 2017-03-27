#include "pch.h"
#include "TestFailureNumberer.h"

namespace ZenUnit
{
   string TestFailureNumberer::Next()
   {
      const string nextTestFailureNumber = "<" + to_string(_testFailureNumber++) + ">";
      return nextTestFailureNumber;
   }
}

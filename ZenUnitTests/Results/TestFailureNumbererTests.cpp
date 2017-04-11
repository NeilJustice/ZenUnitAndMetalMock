#include "pch.h"
#include "ZenUnit/Results/TestFailureNumberer.h"

namespace ZenUnit
{
   ZENUNIT(TestFailureNumberer_ConstructorAndNext_ReturnsAngleBracketWrappedIncrementingSequenceStartingFrom1)
   {
      TestFailureNumberer testFailureNumberer;
      ARE_EQUAL("<1>", testFailureNumberer.Next());
      ARE_EQUAL("<2>", testFailureNumberer.Next());
      ARE_EQUAL("<3>", testFailureNumberer.Next());
   }
}

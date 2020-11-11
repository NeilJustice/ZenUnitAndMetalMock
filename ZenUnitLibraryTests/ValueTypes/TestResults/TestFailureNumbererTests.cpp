#include "pch.h"

namespace ZenUnit
{
   TESTS(TestFailureNumbererTests)
   AFACT(TestFailureNumberer_NextNumberedTestFailureArrowReturnsIncreasingNumberedTestFailureArrows)
   EVIDENCE

   TEST(TestFailureNumberer_NextNumberedTestFailureArrowReturnsIncreasingNumberedTestFailureArrows)
   {
      TestFailureNumberer testFailureNumberer;
      ARE_EQUAL(">>-Test Failure 1->", testFailureNumberer.NextNumberedTestFailureArrow());
      ARE_EQUAL(">>-Test Failure 2->", testFailureNumberer.NextNumberedTestFailureArrow());
      ARE_EQUAL(">>-Test Failure 3->", testFailureNumberer.NextNumberedTestFailureArrow());
      testFailureNumberer.ResetTestFailureNumber();
      ARE_EQUAL(">>-Test Failure 1->", testFailureNumberer.NextNumberedTestFailureArrow());
      ARE_EQUAL(">>-Test Failure 2->", testFailureNumberer.NextNumberedTestFailureArrow());
      ARE_EQUAL(">>-Test Failure 3->", testFailureNumberer.NextNumberedTestFailureArrow());
   }

   RUN_TESTS(TestFailureNumbererTests)
}

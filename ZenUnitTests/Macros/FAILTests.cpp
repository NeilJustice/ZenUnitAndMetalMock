#include "pch.h"

namespace ZenUnit
{
   TESTS(FAILTests)
   AFACT(StringLiteralBecause_Throws)
   AFACT(StringVariableBecause_MessagesTestCase_Throws)
   EVIDENCE

   TEST(StringLiteralBecause_Throws)
   {
      THROWS(FAILTEST("Because"), Anomaly, R"(
 Failed: FAILTEST("Because")
File.cpp(1))");
   }

   TEST(StringVariableBecause_MessagesTestCase_Throws)
   {
      const string Because = "BecauseValue";
      const string messageA = "A", messageB = "B";
      THROWS(FAILTEST(Because, messageA, messageB), Anomaly, R"(
 Failed: FAILTEST(Because, messageA, messageB)
Because: "BecauseValue"
Message: "A", "B"
File.cpp(1))");
   }

   }; RUN_TESTS(FAILTests)
}

#include "pch.h"
#include "ZenUnit/Macros/FAIL.h"

namespace ZenUnit
{
   TESTS(FAILTests)
   SPEC(StringLiteralBecause_Throws)
   SPEC(StringVariableBecause_MessagesTestCase_Throws)
   SPECEND

   int variableA = 10;
   string variableB = "valueB";

   TEST(StringLiteralBecause_Throws)
   {
      THROWS(FAIL("Because"), Anomaly, R"(
 Failed: FAIL("Because")
File.cpp(1))");
   }

   TEST(StringVariableBecause_MessagesTestCase_Throws)
   {
      const string Because = "BecauseValue";
      string messageA = "A", messageB = "B";
      THROWS(FAIL(Because, messageA, messageB), Anomaly, R"(
 Failed: FAIL(Because, messageA, messageB)
Because: "BecauseValue"
Message: "A", "B"
File.cpp(1))");
   }

   }; RUN(FAILTests)
}

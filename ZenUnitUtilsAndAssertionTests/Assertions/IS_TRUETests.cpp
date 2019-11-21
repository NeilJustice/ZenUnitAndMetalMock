#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_TRUETests)
   AFACT(TrueBoolLiteral_DoesNotThrow)
   AFACT(TrueBoolVariable_DoesNotThrow)
   AFACT(FalseBoolLiteral_Throws)
   AFACT(FalseBoolVariable_Throws_MessagesTestCase)
   AFACT(StdFunctionPointsToAFunction_DoesNotThrow)
   AFACT(StdFunctionDoesNotPointToAFunction_Throws)
   AFACT(UserTypeConvertsToTrue_DoesNotThrow)
   AFACT(UserTypeConvertsToFalse_Throws)
   EVIDENCE

   TEST(TrueBoolLiteral_DoesNotThrow)
   {
      IS_TRUE(true);
   }

   TEST(TrueBoolVariable_DoesNotThrow)
   {
      const bool trueBool = true;
      IS_TRUE(trueBool);
   }

   TEST(FalseBoolLiteral_Throws)
   {
      THROWS_EXCEPTION(IS_TRUE(false), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_TRUE(false)",
"Expected: true",
"  Actual: false",
"File.cpp(1)"));
   }

   TEST(FalseBoolVariable_Throws_MessagesTestCase)
   {
      const bool falseBool = false;
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_TRUE(falseBool, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_TRUE(falseBool, messageA, messageB)",
"Expected: true",
"  Actual: false",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   TEST(StdFunctionPointsToAFunction_DoesNotThrow)
   {
      const function<void(int)> nonemptyStdFunction = exit;
      IS_TRUE(nonemptyStdFunction);
   }

   TEST(StdFunctionDoesNotPointToAFunction_Throws)
   {
      const function<void()> emptyStdFunction;
      THROWS_EXCEPTION(IS_TRUE(emptyStdFunction), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_TRUE(emptyStdFunction)",
"Expected: true",
"  Actual: false",
"File.cpp(1)"));
   }

   TEST(UserTypeConvertsToTrue_DoesNotThrow)
   {
      const UserType trueUserType(1);
      IS_TRUE(trueUserType);
   }

   TEST(UserTypeConvertsToFalse_Throws)
   {
      const UserType falseUserType(0);
      THROWS_EXCEPTION(IS_TRUE(falseUserType), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_TRUE(falseUserType)",
"Expected: true",
"  Actual: false",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_TRUETests)
}

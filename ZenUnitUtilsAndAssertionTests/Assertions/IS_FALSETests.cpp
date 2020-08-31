#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_FALSETests)
   AFACT(BoolIsFalse_DoesNotThrowException)
   AFACT(BoolIsTrue_Throws)
   AFACT(BoolVariableIsTrue_Throws_MessagesTestCase)
   AFACT(StdFunctionDoesNotPointToAFunction_DoesNotThrowException)
   AFACT(StdFunctionPointsToAFunction_Throws)
   AFACT(UserTypeConvertsToFalse_DoesNotThrowException)
   AFACT(UserTypeConvertsToTrue_Throws)
   EVIDENCE

   TEST(BoolIsFalse_DoesNotThrowException)
   {
      IS_FALSE(false);
      const bool falseBool = false;
      IS_FALSE(falseBool);
   }

   TEST(BoolIsTrue_Throws)
   {
      THROWS_EXCEPTION(IS_FALSE(true), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_FALSE(true)",
"Expected: false",
"  Actual: true",
"File.cpp(1)"));
   }

   TEST(BoolVariableIsTrue_Throws_MessagesTestCase)
   {
      const bool trueBool = true;
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_FALSE(trueBool, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_FALSE(trueBool, messageA, messageB)",
"Expected: false",
"  Actual: true",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   TEST(StdFunctionDoesNotPointToAFunction_DoesNotThrowException)
   {
      const function<void()> barrenStdFunction;
      IS_FALSE(barrenStdFunction);
   }

   TEST(StdFunctionPointsToAFunction_Throws)
   {
      const function<void(int)> nonemptyStdFunction = exit;
      THROWS_EXCEPTION(IS_FALSE(nonemptyStdFunction), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_FALSE(nonemptyStdFunction)",
"Expected: false",
"  Actual: true",
"File.cpp(1)"));
   }

   TEST(UserTypeConvertsToFalse_DoesNotThrowException)
   {
      const UserType falseUserType(0);
      IS_FALSE(falseUserType);
   }

   TEST(UserTypeConvertsToTrue_Throws)
   {
      const UserType trueUserType(1);
      THROWS_EXCEPTION(IS_FALSE(trueUserType), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_FALSE(trueUserType)",
"Expected: false",
"  Actual: true",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_FALSETests)
}

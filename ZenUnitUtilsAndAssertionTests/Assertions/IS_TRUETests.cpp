#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_TRUETests)
   AFACT(TrueBoolLiteral_DoesNotThrowException)
   AFACT(TrueBoolVariable_DoesNotThrowException)
   AFACT(FalseBoolLiteral_ThrowsAnomaly)
   AFACT(FalseBoolVariable_ThrowsAnomaly__MessagesTestCase)
   AFACT(StdFunctionPointsToAFunction_DoesNotThrowException)
   AFACT(StdFunctionDoesNotPointToAFunction_ThrowsAnomaly)
   AFACT(UserTypeConvertsToTrue_DoesNotThrowException)
   AFACT(UserTypeConvertsToFalse_ThrowsAnomaly)
   EVIDENCE

   TEST(TrueBoolLiteral_DoesNotThrowException)
   {
      IS_TRUE(true);
   }

   TEST(TrueBoolVariable_DoesNotThrowException)
   {
      const bool trueBool = true;
      IS_TRUE(trueBool);
   }

   TEST(FalseBoolLiteral_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(IS_TRUE(false), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_TRUE(false)",
"Expected: true",
"  Actual: false",
"File.cpp(1)"));
   }

   TEST(FalseBoolVariable_ThrowsAnomaly__MessagesTestCase)
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

   TEST(StdFunctionPointsToAFunction_DoesNotThrowException)
   {
      const function<void(int)> nonemptyStdFunction = exit;
      IS_TRUE(nonemptyStdFunction);
   }

   TEST(StdFunctionDoesNotPointToAFunction_ThrowsAnomaly)
   {
      const function<void()> emptyStdFunction;
      THROWS_EXCEPTION(IS_TRUE(emptyStdFunction), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_TRUE(emptyStdFunction)",
"Expected: true",
"  Actual: false",
"File.cpp(1)"));
   }

   TEST(UserTypeConvertsToTrue_DoesNotThrowException)
   {
      const UserType trueUserType(1);
      IS_TRUE(trueUserType);
   }

   TEST(UserTypeConvertsToFalse_ThrowsAnomaly)
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

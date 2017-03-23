#include "pch.h"
#include "ZenUnit/Macros/IS_TRUE.h"

namespace ZenUnit
{
   TESTS(IS_TRUETests)
   SPEC(TrueBoolLiteral_DoesNotThrow)
   SPEC(TrueBoolVariable_DoesNotThrow)
   SPEC(FalseBoolLiteral_Throws)
   SPEC(FalseBoolVariable_Throws_MessagesTestCase)
   SPEC(StdFunctionPointsToAFunction_DoesNotThrow)
   SPEC(StdFunctionDoesNotPointToAFunction_Throws)
   SPEC(UserTypeConvertsToTrue_DoesNotThrow)
   SPEC(UserTypeConvertsToFalse_Throws)
   SPECEND

   TEST(TrueBoolLiteral_DoesNotThrow)
   {
      IS_TRUE(true);
   }

   TEST(TrueBoolVariable_DoesNotThrow)
   {
      bool trueBool = true;
      IS_TRUE(trueBool);
   }

   TEST(FalseBoolLiteral_Throws)
   {
      THROWS(IS_TRUE(false), Anomaly, R"(
  Failed: IS_TRUE(false)
Expected: true
  Actual: false
File.cpp(1))");
   }

   TEST(FalseBoolVariable_Throws_MessagesTestCase)
   {
      bool falseBool = false;
      string messageA = "A", messageB = "B";
      THROWS(IS_TRUE(falseBool, messageA, messageB), Anomaly, R"(
  Failed: IS_TRUE(falseBool, messageA, messageB)
Expected: true
  Actual: false
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(StdFunctionPointsToAFunction_DoesNotThrow)
   {
      std::function<void(int)> nonemptyStdFunction = exit;
      IS_TRUE(nonemptyStdFunction);
   }

   TEST(StdFunctionDoesNotPointToAFunction_Throws)
   {
      std::function<void()> emptyStdFunction;
      THROWS(IS_TRUE(emptyStdFunction), Anomaly, R"(
  Failed: IS_TRUE(emptyStdFunction)
Expected: true
  Actual: false
File.cpp(1))");
   }

   TEST(UserTypeConvertsToTrue_DoesNotThrow)
   {
      UserType trueUserType(1);
      IS_TRUE(trueUserType);
   }

   TEST(UserTypeConvertsToFalse_Throws)
   {
      UserType falseUserType(0);
      THROWS(IS_TRUE(falseUserType), Anomaly, R"(
  Failed: IS_TRUE(falseUserType)
Expected: true
  Actual: false
File.cpp(1))");
   }

   }; RUN(IS_TRUETests)
}

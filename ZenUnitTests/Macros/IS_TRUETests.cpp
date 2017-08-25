#include "pch.h"
#include "ZenUnit/Macros/IS_TRUE.h"

namespace ZenUnit
{
   TESTS(IS_TRUETests)
   FACT(TrueBoolLiteral_DoesNotThrow)
   FACT(TrueBoolVariable_DoesNotThrow)
   FACT(FalseBoolLiteral_Throws)
   FACT(FalseBoolVariable_Throws_MessagesTestCase)
   FACT(StdFunctionPointsToAFunction_DoesNotThrow)
   FACT(StdFunctionDoesNotPointToAFunction_Throws)
   FACT(UserTypeConvertsToTrue_DoesNotThrow)
   FACT(UserTypeConvertsToFalse_Throws)
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
      THROWS(IS_TRUE(false), Anomaly, R"(
  Failed: IS_TRUE(false)
Expected: true
  Actual: false
File.cpp(1))");
   }

   TEST(FalseBoolVariable_Throws_MessagesTestCase)
   {
      const bool falseBool = false;
      const string messageA = "A", messageB = "B";
      THROWS(IS_TRUE(falseBool, messageA, messageB), Anomaly, R"(
  Failed: IS_TRUE(falseBool, messageA, messageB)
Expected: true
  Actual: false
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(StdFunctionPointsToAFunction_DoesNotThrow)
   {
      const std::function<void(int)> nonemptyStdFunction = exit;
      IS_TRUE(nonemptyStdFunction);
   }

   TEST(StdFunctionDoesNotPointToAFunction_Throws)
   {
      const std::function<void()> emptyStdFunction;
      THROWS(IS_TRUE(emptyStdFunction), Anomaly, R"(
  Failed: IS_TRUE(emptyStdFunction)
Expected: true
  Actual: false
File.cpp(1))");
   }

   TEST(UserTypeConvertsToTrue_DoesNotThrow)
   {
      const UserType trueUserType(1);
      IS_TRUE(trueUserType);
   }

   TEST(UserTypeConvertsToFalse_Throws)
   {
      const UserType falseUserType(0);
      THROWS(IS_TRUE(falseUserType), Anomaly, R"(
  Failed: IS_TRUE(falseUserType)
Expected: true
  Actual: false
File.cpp(1))");
   }

   }; RUNTESTS(IS_TRUETests)
}

#include "pch.h"
#include "ZenUnit/Macros/IS_FALSE.h"

namespace ZenUnit
{
   TESTS(IS_FALSETests)
   SPEC(BoolIsFalse_DoesNotThrow)
   SPEC(BoolIsTrue_Throws)
   SPEC(BoolVariableIsTrue_Throws_MessagesTestCase)
   SPEC(StdFunctionDoesNotPointToAFunction_DoesNotThrow)
   SPEC(StdFunctionPointsToAFunction_Throws)
   SPEC(UserTypeConvertsToFalse_DoesNotThrow)
   SPEC(UserTypeConvertsToTrue_Throws)
   SPECEND

   TEST(BoolIsFalse_DoesNotThrow)
   {
      IS_FALSE(false);
      bool falseBool = false;
      IS_FALSE(falseBool);
   }

   TEST(BoolIsTrue_Throws)
   {
      THROWS(IS_FALSE(true), Anomaly, R"(
  Failed: IS_FALSE(true)
Expected: false
  Actual: true
File.cpp(1))");
   }

   TEST(BoolVariableIsTrue_Throws_MessagesTestCase)
   {
      bool trueBool = true;
      string messageA = "A", messageB = "B";
      THROWS(IS_FALSE(trueBool, messageA, messageB), Anomaly, R"(
  Failed: IS_FALSE(trueBool, messageA, messageB)
Expected: false
  Actual: true
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(StdFunctionDoesNotPointToAFunction_DoesNotThrow)
   {
      std::function<void()> barrenStdFunction;
      IS_FALSE(barrenStdFunction);
   }

   TEST(StdFunctionPointsToAFunction_Throws)
   {
      std::function<void(int)> nonemptyStdFunction = exit;
      THROWS(IS_FALSE(nonemptyStdFunction), Anomaly, R"(
  Failed: IS_FALSE(nonemptyStdFunction)
Expected: false
  Actual: true
File.cpp(1))");
   }

   TEST(UserTypeConvertsToFalse_DoesNotThrow)
   {
      UserType falseUserType(0);
      IS_FALSE(falseUserType);
   }

   TEST(UserTypeConvertsToTrue_Throws)
   {
      UserType trueUserType(1);
      THROWS(IS_FALSE(trueUserType), Anomaly, R"(
  Failed: IS_FALSE(trueUserType)
Expected: false
  Actual: true
File.cpp(1))");
   }

   }; RUN(IS_FALSETests)
}

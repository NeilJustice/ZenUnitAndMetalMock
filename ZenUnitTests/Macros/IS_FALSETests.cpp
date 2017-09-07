#include "pch.h"
#include "ZenUnit/Macros/IS_FALSE.h"

namespace ZenUnit
{
   TESTS(IS_FALSETests)
   AFACT(BoolIsFalse_DoesNotThrow)
   AFACT(BoolIsTrue_Throws)
   AFACT(BoolVariableIsTrue_Throws_MessagesTestCase)
   AFACT(StdFunctionDoesNotPointToAFunction_DoesNotThrow)
   AFACT(StdFunctionPointsToAFunction_Throws)
   AFACT(UserTypeConvertsToFalse_DoesNotThrow)
   AFACT(UserTypeConvertsToTrue_Throws)
   EVIDENCE

   TEST(BoolIsFalse_DoesNotThrow)
   {
      IS_FALSE(false);
      const bool falseBool = false;
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
      const bool trueBool = true;
      const string messageA = "A", messageB = "B";
      THROWS(IS_FALSE(trueBool, messageA, messageB), Anomaly, R"(
  Failed: IS_FALSE(trueBool, messageA, messageB)
Expected: false
  Actual: true
 Message: "A", "B"
File.cpp(1))");
   }

   TEST(StdFunctionDoesNotPointToAFunction_DoesNotThrow)
   {
      const std::function<void()> barrenStdFunction;
      IS_FALSE(barrenStdFunction);
   }

   TEST(StdFunctionPointsToAFunction_Throws)
   {
      const std::function<void(int)> nonemptyStdFunction = exit;
      THROWS(IS_FALSE(nonemptyStdFunction), Anomaly, R"(
  Failed: IS_FALSE(nonemptyStdFunction)
Expected: false
  Actual: true
File.cpp(1))");
   }

   TEST(UserTypeConvertsToFalse_DoesNotThrow)
   {
      const UserType falseUserType(0);
      IS_FALSE(falseUserType);
   }

   TEST(UserTypeConvertsToTrue_Throws)
   {
      const UserType trueUserType(1);
      THROWS(IS_FALSE(trueUserType), Anomaly, R"(
  Failed: IS_FALSE(trueUserType)
Expected: false
  Actual: true
File.cpp(1))");
   }

   }; RUNTESTS(IS_FALSETests)
}

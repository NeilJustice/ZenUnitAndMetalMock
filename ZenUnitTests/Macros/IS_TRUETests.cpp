#include "pch.h"
//#include "ZenUnitTests/Testing/UserType.h"
//
//namespace ZenUnit
//{
//   TESTS(IS_TRUETests)
//   AFACT(TrueBoolLiteral_DoesNotThrow)
//   AFACT(TrueBoolVariable_DoesNotThrow)
//   AFACT(FalseBoolLiteral_Throws)
//   AFACT(FalseBoolVariable_Throws_MessagesTestCase)
//   AFACT(StdFunctionPointsToAFunction_DoesNotThrow)
//   AFACT(StdFunctionDoesNotPointToAFunction_Throws)
//   AFACT(UserTypeConvertsToTrue_DoesNotThrow)
//   AFACT(UserTypeConvertsToFalse_Throws)
//   EVIDENCE
//
//   TEST(TrueBoolLiteral_DoesNotThrow)
//   {
//      IS_TRUE(true);
//   }
//
//   TEST(TrueBoolVariable_DoesNotThrow)
//   {
//      const bool trueBool = true;
//      IS_TRUE(trueBool);
//   }
//
//   TEST(FalseBoolLiteral_Throws)
//   {
//      THROWS(IS_TRUE(false), Anomaly, R"(
//  Failed: IS_TRUE(false)
//Expected: true
//  Actual: false
//File.cpp(1))");
//   }
//
//   TEST(FalseBoolVariable_Throws_MessagesTestCase)
//   {
//      const bool falseBool = false;
//      const string messageA = "A", messageB = "B";
//      THROWS(IS_TRUE(falseBool, messageA, messageB), Anomaly, R"(
//  Failed: IS_TRUE(falseBool, messageA, messageB)
//Expected: true
//  Actual: false
// Message: "A", "B"
//File.cpp(1))");
//   }
//
//   TEST(StdFunctionPointsToAFunction_DoesNotThrow)
//   {
//      const function<void(int)> nonemptyStdFunction = exit;
//      IS_TRUE(nonemptyStdFunction);
//   }
//
//   TEST(StdFunctionDoesNotPointToAFunction_Throws)
//   {
//      const function<void()> emptyStdFunction;
//      THROWS(IS_TRUE(emptyStdFunction), Anomaly, R"(
//  Failed: IS_TRUE(emptyStdFunction)
//Expected: true
//  Actual: false
//File.cpp(1))");
//   }
//
//   TEST(UserTypeConvertsToTrue_DoesNotThrow)
//   {
//      const UserType trueUserType(1);
//      IS_TRUE(trueUserType);
//   }
//
//   TEST(UserTypeConvertsToFalse_Throws)
//   {
//      const UserType falseUserType(0);
//      THROWS(IS_TRUE(falseUserType), Anomaly, R"(
//  Failed: IS_TRUE(falseUserType)
//Expected: true
//  Actual: false
//File.cpp(1))");
//   }
//
//   }; RUNTESTS(IS_TRUETests)
//}

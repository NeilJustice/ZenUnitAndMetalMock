#include "pch.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(TwoArgMemberFunctionCallerTests, ReturnType, Arg1Type, Arg2Type)
AFACT(ConstCall_CallsConstNonVoidMemberFunctionOnce_ReturnsReturnValue)
EVIDENCE

class Class
{
public:
   mutable vector<pair<Arg1Type, Arg2Type>> calls;
   mutable ReturnType returnValue;

   ReturnType ConstNonVoidFunction(Arg1Type arg1, Arg2Type arg2) const
   {
      calls.emplace_back(arg1, arg2);
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }
};

TEST(ConstCall_CallsConstNonVoidMemberFunctionOnce_ReturnsReturnValue)
{
   TwoArgMemberFunctionCaller<ReturnType, Class, Arg1Type, Arg2Type> nonVoidTwoArgMemberFunctionCaller;
   const Class classInstance{};

   const Arg1Type arg1A = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2A = ZenUnit::Random<Arg2Type>();
   //
   const ReturnType returnValueA = nonVoidTwoArgMemberFunctionCaller.ConstCall(&classInstance, &Class::ConstNonVoidFunction, arg1A, arg2A);
   //
   const vector<pair<Arg1Type, Arg2Type>> expectedCallsA =
   {
      { arg1A, arg2A }
   };
   VECTORS_EQUAL(expectedCallsA, classInstance.calls);
   ARE_EQUAL(classInstance.returnValue, returnValueA);


   const Arg1Type arg1B = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2B = ZenUnit::Random<Arg2Type>();
   //
   const ReturnType returnValueB = nonVoidTwoArgMemberFunctionCaller.ConstCall(&classInstance, &Class::ConstNonVoidFunction, arg1B, arg2B);
   //
   const vector<pair<Arg1Type, Arg2Type>> expectedCallsB =
   {
      { arg1A, arg2A },
      { arg1B, arg2B }
   };
   VECTORS_EQUAL(expectedCallsB, classInstance.calls);
   ARE_EQUAL(classInstance.returnValue, returnValueB);
}

RUN_TEMPLATE_TESTS(TwoArgMemberFunctionCallerTests, char, int, int)
THEN_RUN_TEMPLATE_TESTS(TwoArgMemberFunctionCallerTests, int, double, unsigned)

#include "pch.h"

template<typename ReturnType, typename Arg1Type>
TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, ReturnType, Arg1Type)
AFACT(NonConstCall_CallsNonConstMemberFunctionOnce_ReturnsReturnValue)
EVIDENCE

class Class
{
public:
   vector<Arg1Type> calls;
   ReturnType returnValue;

   ReturnType NonVoidOneArgFunction(Arg1Type arg1)
   {
      calls.emplace_back(arg1);
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }
};

TEST(NonConstCall_CallsNonConstMemberFunctionOnce_ReturnsReturnValue)
{
   OneArgMemberFunctionCaller<ReturnType, Class, Arg1Type> oneArgMemberFunctionCaller;
   Class classInstance{};

   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   //
   const ReturnType returnValueA = oneArgMemberFunctionCaller.NonConstCall(&classInstance, &Class::NonVoidOneArgFunction, arg1);
   //
   const vector<Arg1Type> expectedCallsA =
   {
      arg1
   };
   VECTORS_EQUAL(expectedCallsA, classInstance.calls);
   ARE_EQUAL(classInstance.returnValue, returnValueA);


   const Arg1Type arg2 = ZenUnit::Random<Arg1Type>();
   //
   const ReturnType returnValueB = oneArgMemberFunctionCaller.NonConstCall(&classInstance, &Class::NonVoidOneArgFunction, arg2);
   //
   const vector<Arg1Type> expectedCallsB =
   {
      arg1, arg2
   };
   VECTORS_EQUAL(expectedCallsB, classInstance.calls);
   ARE_EQUAL(classInstance.returnValue, returnValueB);
}

};
RUN_TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, char, int)
RUN_TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, int, double)

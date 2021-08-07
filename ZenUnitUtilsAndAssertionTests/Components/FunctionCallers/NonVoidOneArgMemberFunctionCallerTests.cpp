#include "pch.h"

namespace ZenUnit
{
   template<typename ReturnType, typename Arg1Type>
   TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, ReturnType, Arg1Type)
   AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce_ReturnsReturnValue)
   AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce_ReturnsReturnValue)
   EVIDENCE

   class Class
   {
   public:
      mutable vector<Arg1Type> calls;
      mutable ReturnType returnValue = ReturnType{};

      ReturnType NonVoidOneArgConstFunction(Arg1Type arg1) const
      {
         calls.emplace_back(arg1);
         returnValue = ZenUnit::Random<ReturnType>();
         return returnValue;
      }

      ReturnType NonVoidOneArgFunction(Arg1Type arg1)
      {
         calls.emplace_back(arg1);
         returnValue = ZenUnit::Random<ReturnType>();
         return returnValue;
      }
   };

   NonVoidOneArgMemberFunctionCaller<ReturnType, Class, Arg1Type> _nonVoidOneArgMemberFunctionCaller;
   Class _classInstance;

   TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce_ReturnsReturnValue)
   {
      const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
      //
      const ReturnType returnValueA = _nonVoidOneArgMemberFunctionCaller.CallConstMemberFunction(
         &_classInstance, &Class::NonVoidOneArgConstFunction, arg1);
      //
      const vector<Arg1Type> expectedCallsA =
      {
         arg1
      };
      VECTORS_ARE_EQUAL(expectedCallsA, _classInstance.calls);
      ARE_EQUAL(_classInstance.returnValue, returnValueA);


      const Arg1Type arg2 = ZenUnit::Random<Arg1Type>();
      //
      const ReturnType returnValueB = _nonVoidOneArgMemberFunctionCaller.CallConstMemberFunction(
         &_classInstance, &Class::NonVoidOneArgConstFunction, arg2);
      //
      const vector<Arg1Type> expectedCallsB =
      {
         arg1, arg2
      };
      VECTORS_ARE_EQUAL(expectedCallsB, _classInstance.calls);
      ARE_EQUAL(_classInstance.returnValue, returnValueB);
   }

   TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce_ReturnsReturnValue)
   {
      const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
      //
      const ReturnType returnValueA = _nonVoidOneArgMemberFunctionCaller.CallNonConstMemberFunction(
         &_classInstance, &Class::NonVoidOneArgFunction, arg1);
      //
      const vector<Arg1Type> expectedCallsA =
      {
         arg1
      };
      VECTORS_ARE_EQUAL(expectedCallsA, _classInstance.calls);
      ARE_EQUAL(_classInstance.returnValue, returnValueA);


      const Arg1Type arg2 = ZenUnit::Random<Arg1Type>();
      //
      const ReturnType returnValueB = _nonVoidOneArgMemberFunctionCaller.
         CallNonConstMemberFunction(&_classInstance, &Class::NonVoidOneArgFunction, arg2);
      //
      const vector<Arg1Type> expectedCallsB =
      {
         arg1, arg2
      };
      VECTORS_ARE_EQUAL(expectedCallsB, _classInstance.calls);
      ARE_EQUAL(_classInstance.returnValue, returnValueB);
   }

   RUN_TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, char, int)
   THEN_RUN_TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, int, double)
}

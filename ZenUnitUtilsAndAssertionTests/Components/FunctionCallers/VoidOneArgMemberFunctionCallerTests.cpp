#include "pch.h"

namespace ZenUnit
{
   template<typename Arg1Type>
   TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, Arg1Type)
   AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce)
   AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
   EVIDENCE

   class Class
   {
   public:
      mutable vector<Arg1Type> calls;

      void ConstVoidOneArgFunction(Arg1Type arg1) const
      {
         calls.emplace_back(arg1);
      }

      void NonConstVoidOneArgFunction(Arg1Type arg1)
      {
         calls.emplace_back(arg1);
      }
   };

   VoidOneArgMemberFunctionCaller<Class, Arg1Type> _voidOneArgMemberFunctionCaller;
   Class _classInstance;

   TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce)
   {
      const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
      //
      _voidOneArgMemberFunctionCaller.CallConstMemberFunction(&_classInstance, &Class::ConstVoidOneArgFunction, arg1);
      //
      const vector<Arg1Type> expectedCallsA =
      {
         arg1
      };
      VECTORS_ARE_EQUAL(expectedCallsA, _classInstance.calls);


      const Arg1Type arg2 = ZenUnit::Random<Arg1Type>();
      //
      _voidOneArgMemberFunctionCaller.CallConstMemberFunction(&_classInstance, &Class::ConstVoidOneArgFunction, arg2);
      //
      const vector<Arg1Type> expectedCallsB =
      {
         arg1, arg2
      };
      VECTORS_ARE_EQUAL(expectedCallsB, _classInstance.calls);
   }

   TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
   {
      const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
      //
      _voidOneArgMemberFunctionCaller.CallNonConstMemberFunction(&_classInstance, &Class::NonConstVoidOneArgFunction, arg1);
      //
      const vector<Arg1Type> expectedCallsA =
      {
         arg1
      };
      VECTORS_ARE_EQUAL(expectedCallsA, _classInstance.calls);


      const Arg1Type arg2 = ZenUnit::Random<Arg1Type>();
      //
      _voidOneArgMemberFunctionCaller.CallNonConstMemberFunction(&_classInstance, &Class::NonConstVoidOneArgFunction, arg2);
      //
      const vector<Arg1Type> expectedCallsB =
      {
         arg1, arg2
      };
      VECTORS_ARE_EQUAL(expectedCallsB, _classInstance.calls);
   }

   RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, int)
   THEN_RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, unsigned long long)
}

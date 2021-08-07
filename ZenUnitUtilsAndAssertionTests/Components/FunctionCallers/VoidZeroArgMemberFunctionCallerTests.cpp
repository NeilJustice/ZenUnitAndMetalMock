#include "pch.h"

namespace ZenUnit
{
   TESTS(VoidZeroArgMemberFunctionCallerTests)
   AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce)
   AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
   EVIDENCE

   class Class
   {
   public:
      mutable unsigned numberOfCalls = 0;

      void ConstMemberZeroArgFunction() const
      {
         ++numberOfCalls;
      }

      void NonConstMemberZeroArgFunction()
      {
         ++numberOfCalls;
      }
   };

   Class _classInstance;
   VoidZeroArgMemberFunctionCaller<Class> _voidZeroArgMemberFunctionCaller;

   TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce)
   {
      IS_ZERO(_classInstance.numberOfCalls);
      //
      _voidZeroArgMemberFunctionCaller.CallConstMemberFunction(&_classInstance, &Class::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, _classInstance.numberOfCalls);
      //
      _voidZeroArgMemberFunctionCaller.CallConstMemberFunction(&_classInstance, &Class::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, _classInstance.numberOfCalls);
   }

   TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
   {
      IS_ZERO(_classInstance.numberOfCalls);
      //
      _voidZeroArgMemberFunctionCaller.CallNonConstMemberFunction(&_classInstance, &Class::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, _classInstance.numberOfCalls);
      //
      _voidZeroArgMemberFunctionCaller.CallNonConstMemberFunction(&_classInstance, &Class::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, _classInstance.numberOfCalls);
   }

   RUN_TESTS(VoidZeroArgMemberFunctionCallerTests)
}

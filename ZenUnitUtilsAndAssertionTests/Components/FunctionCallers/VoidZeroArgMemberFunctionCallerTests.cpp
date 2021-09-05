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
      mutable unsigned numberOfFunctionCalls = 0;

      void ConstMemberZeroArgFunction() const
      {
         ++numberOfFunctionCalls;
      }

      void NonConstMemberZeroArgFunction()
      {
         ++numberOfFunctionCalls;
      }
   };

   Class _classInstance;
   VoidZeroArgMemberFunctionCaller<Class> _voidZeroArgMemberFunctionCaller;

   TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce)
   {
      IS_ZERO(_classInstance.numberOfFunctionCalls);
      //
      _voidZeroArgMemberFunctionCaller.CallConstMemberFunction(&_classInstance, &Class::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, _classInstance.numberOfFunctionCalls);
      //
      _voidZeroArgMemberFunctionCaller.CallConstMemberFunction(&_classInstance, &Class::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, _classInstance.numberOfFunctionCalls);
   }

   TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
   {
      IS_ZERO(_classInstance.numberOfFunctionCalls);
      //
      _voidZeroArgMemberFunctionCaller.CallNonConstMemberFunction(&_classInstance, &Class::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, _classInstance.numberOfFunctionCalls);
      //
      _voidZeroArgMemberFunctionCaller.CallNonConstMemberFunction(&_classInstance, &Class::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, _classInstance.numberOfFunctionCalls);
   }

   RUN_TESTS(VoidZeroArgMemberFunctionCallerTests)
}

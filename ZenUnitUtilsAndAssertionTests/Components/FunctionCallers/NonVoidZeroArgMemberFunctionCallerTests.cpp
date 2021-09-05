#include "pch.h"

namespace ZenUnit
{
   template<typename ReturnType>
   TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, ReturnType)
   AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce)
   AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
   EVIDENCE

   class Class
   {
   public:
      mutable size_t numberOfFunctionCalls = 0;
      ReturnType returnValue = ZenUnit::Random<ReturnType>();

      ReturnType ConstMemberZeroArgFunction() const
      {
         ++numberOfFunctionCalls;
         return returnValue;
      }

      ReturnType NonConstMemberZeroArgFunction()
      {
         ++numberOfFunctionCalls;
         return returnValue;
      }
   };

   Class _classInstance;
   NonVoidZeroArgMemberFunctionCaller<ReturnType, Class> _nonVoidZeroArgMemberFunctionCaller;

   TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce)
   {
      IS_ZERO(_classInstance.numberOfFunctionCalls);
      //
      const ReturnType returnValueA = _nonVoidZeroArgMemberFunctionCaller.CallConstMemberFunction(
         &_classInstance, &Class::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, _classInstance.numberOfFunctionCalls);
      ARE_EQUAL(_classInstance.returnValue, returnValueA);
      //
      const ReturnType returnValueB = _nonVoidZeroArgMemberFunctionCaller.CallConstMemberFunction(
         &_classInstance, &Class::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, _classInstance.numberOfFunctionCalls);
      ARE_EQUAL(_classInstance.returnValue, returnValueB);
   }

   TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
   {
      IS_ZERO(_classInstance.numberOfFunctionCalls);
      //
      const ReturnType returnValueA = _nonVoidZeroArgMemberFunctionCaller.
         CallNonConstMemberFunction(&_classInstance, &Class::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, _classInstance.numberOfFunctionCalls);
      ARE_EQUAL(_classInstance.returnValue, returnValueA);
      //
      const ReturnType returnValueB = _nonVoidZeroArgMemberFunctionCaller.
         CallNonConstMemberFunction(&_classInstance, &Class::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, _classInstance.numberOfFunctionCalls);
      ARE_EQUAL(_classInstance.returnValue, returnValueB);
   }

   RUN_TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, int)
   THEN_RUN_TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, char)
}

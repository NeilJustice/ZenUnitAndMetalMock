#include "pch.h"

namespace ZenUnit
{
   template<typename ReturnType>
   TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, ReturnType)
   AFACT(ConstCall_CallsConstMemberFunctionOnce)
   AFACT(NonConstCall_CallsNonConstMemberFunctionOnce)
   EVIDENCE

   struct C
   {
      mutable unsigned numberOfCalls = 0;
      ReturnType returnValue = ZenUnit::Random<ReturnType>();

      ReturnType ConstMemberZeroArgFunction() const
      {
         ++numberOfCalls;
         return returnValue;
      }

      ReturnType NonConstMemberZeroArgFunction()
      {
         ++numberOfCalls;
         return returnValue;
      }
   };

   C c;
   ZeroArgMemberFunctionCaller<ReturnType, C> nonVoidZeroArgMemberFunctionCaller;

   TEST(ConstCall_CallsConstMemberFunctionOnce)
   {
      ARE_EQUAL(0, c.numberOfCalls);
      //
      const ReturnType returnValueA = nonVoidZeroArgMemberFunctionCaller.ConstCall(&c, &C::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, c.numberOfCalls);
      ARE_EQUAL(c.returnValue, returnValueA);
      //
      const ReturnType returnValueB = nonVoidZeroArgMemberFunctionCaller.ConstCall(&c, &C::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, c.numberOfCalls);
      ARE_EQUAL(c.returnValue, returnValueB);
   }

   TEST(NonConstCall_CallsNonConstMemberFunctionOnce)
   {
      ARE_EQUAL(0, c.numberOfCalls);
      //
      const ReturnType returnValueA = nonVoidZeroArgMemberFunctionCaller.NonConstCall(&c, &C::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, c.numberOfCalls);
      ARE_EQUAL(c.returnValue, returnValueA);
      //
      const ReturnType returnValueB = nonVoidZeroArgMemberFunctionCaller.NonConstCall(&c, &C::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, c.numberOfCalls);
      ARE_EQUAL(c.returnValue, returnValueB);
   }

   RUN_TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, int)
   THEN_RUN_TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, char)
}

#include "pch.h"

namespace ZenUnit
{
   TESTS(VoidZeroArgMemberFunctionCallerTests)
   AFACT(ConstCall_CallsConstMemberFunctionOnce)
   AFACT(NonConstCall_CallsNonConstMemberFunctionOnce)
   EVIDENCE

   struct C
   {
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

   C c;
   ZeroArgMemberFunctionCaller<void, C> voidZeroArgMemberFunctionCaller;

   TEST(ConstCall_CallsConstMemberFunctionOnce)
   {
      ARE_EQUAL(0, c.numberOfCalls);
      //
      voidZeroArgMemberFunctionCaller.ConstCall(&c, &C::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, c.numberOfCalls);
      //
      voidZeroArgMemberFunctionCaller.ConstCall(&c, &C::ConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, c.numberOfCalls);
   }

   TEST(NonConstCall_CallsNonConstMemberFunctionOnce)
   {
      ARE_EQUAL(0, c.numberOfCalls);
      //
      voidZeroArgMemberFunctionCaller.NonConstCall(&c, &C::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(1, c.numberOfCalls);
      //
      voidZeroArgMemberFunctionCaller.NonConstCall(&c, &C::NonConstMemberZeroArgFunction);
      //
      ARE_EQUAL(2, c.numberOfCalls);
   }

   RUN_TESTS(VoidZeroArgMemberFunctionCallerTests)
}

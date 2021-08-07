#include "pch.h"

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type>
   TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, Arg1Type, Arg2Type)
   AFACT(CallConstMemberFunction_CallsConstVoidMemberFunctionOnce_ReturnsReturnValue)
   EVIDENCE

   class Class
   {
   public:
      mutable vector<pair<Arg1Type, Arg2Type>> calls;

      void ConstVoidTwoArgFunction(Arg1Type arg1, Arg2Type arg2) const
      {
         calls.emplace_back(arg1, arg2);
      }
   };

   TEST(CallConstMemberFunction_CallsConstVoidMemberFunctionOnce_ReturnsReturnValue)
   {
      const VoidTwoArgMemberFunctionCaller<Class, Arg1Type, Arg2Type> nonVoidTwoArgMemberFunctionCaller{};
      const Class classInstance{};

      const Arg1Type arg1A = ZenUnit::Random<Arg1Type>();
      const Arg2Type arg2A = ZenUnit::Random<Arg2Type>();
      //
      nonVoidTwoArgMemberFunctionCaller.CallConstMemberFunction(&classInstance, &Class::ConstVoidTwoArgFunction, arg1A, arg2A);
      //
      const vector<pair<Arg1Type, Arg2Type>> expectedCallsA =
      {
         { arg1A, arg2A }
      };
      VECTORS_ARE_EQUAL(expectedCallsA, classInstance.calls);


      const Arg1Type arg1B = ZenUnit::Random<Arg1Type>();
      const Arg2Type arg2B = ZenUnit::Random<Arg2Type>();
      //
      nonVoidTwoArgMemberFunctionCaller.CallConstMemberFunction(&classInstance, &Class::ConstVoidTwoArgFunction, arg1B, arg2B);
      //
      const vector<pair<Arg1Type, Arg2Type>> expectedCallsB =
      {
         { arg1A, arg2A },
         { arg1B, arg2B }
      };
      VECTORS_ARE_EQUAL(expectedCallsB, classInstance.calls);
   }

   RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, double, unsigned)
}

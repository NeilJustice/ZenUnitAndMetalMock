#include "pch.h"

namespace ZenUnit
{
   template<typename ReturnType, typename Arg1Type, typename Arg2Type>
   TEMPLATE_TESTS(NonVoidTwoArgMemberFunctionCallerTests, ReturnType, Arg1Type, Arg2Type)
   AFACT(CallConstMemberFunction_CallsConstNonVoidMemberFunctionOnce_ReturnsReturnValue)
   AFACT(CallNonConstMemberFunction_CallsNonConstNonVoidMemberFunctionOnce_ReturnsReturnValue)
   EVIDENCE

   NonVoidTwoArgMemberFunctionCallerTests()
   {
   }

   class Class
   {
   public:
      mutable vector<pair<Arg1Type, Arg2Type>> functionCallArguments;
      mutable ReturnType returnValue;

      ReturnType ConstNonVoidFunction(Arg1Type arg1, Arg2Type arg2) const
      {
         functionCallArguments.emplace_back(arg1, arg2);
         returnValue = ZenUnit::Random<ReturnType>();
         return returnValue;
      }

      ReturnType NonConstNonVoidFunction(Arg1Type arg1, Arg2Type arg2)
      {
         functionCallArguments.emplace_back(arg1, arg2);
         returnValue = ZenUnit::Random<ReturnType>();
         return returnValue;
      }
   };

   const NonVoidTwoArgMemberFunctionCaller<ReturnType, Class, Arg1Type, Arg2Type> _nonVoidTwoArgMemberFunctionCaller;

   TEST(CallConstMemberFunction_CallsConstNonVoidMemberFunctionOnce_ReturnsReturnValue)
   {
      const Class constClassInstance{};

      const Arg1Type arg1A = ZenUnit::Random<Arg1Type>();
      const Arg2Type arg2A = ZenUnit::Random<Arg2Type>();
      //
      const ReturnType returnValueA = _nonVoidTwoArgMemberFunctionCaller.CallConstMemberFunction(
         &constClassInstance, &Class::ConstNonVoidFunction, arg1A, arg2A);
      //
      const vector<pair<Arg1Type, Arg2Type>> expectedCallsA =
      {
         { arg1A, arg2A }
      };
      VECTORS_ARE_EQUAL(expectedCallsA, constClassInstance.functionCallArguments);
      ARE_EQUAL(constClassInstance.returnValue, returnValueA);


      const Arg1Type arg1B = ZenUnit::Random<Arg1Type>();
      const Arg2Type arg2B = ZenUnit::Random<Arg2Type>();
      //
      const ReturnType returnValueB = _nonVoidTwoArgMemberFunctionCaller.CallConstMemberFunction(
         &constClassInstance, &Class::ConstNonVoidFunction, arg1B, arg2B);
      //
      const vector<pair<Arg1Type, Arg2Type>> expectedCallsB =
      {
         { arg1A, arg2A },
         { arg1B, arg2B }
      };
      VECTORS_ARE_EQUAL(expectedCallsB, constClassInstance.functionCallArguments);
      ARE_EQUAL(constClassInstance.returnValue, returnValueB);
   }

   TEST(CallNonConstMemberFunction_CallsNonConstNonVoidMemberFunctionOnce_ReturnsReturnValue)
   {
      Class nonConstClassInstance{};

      const Arg1Type arg1A = ZenUnit::Random<Arg1Type>();
      const Arg2Type arg2A = ZenUnit::Random<Arg2Type>();
      //
      const ReturnType returnValueA = _nonVoidTwoArgMemberFunctionCaller.CallNonConstMemberFunction(
         &nonConstClassInstance, &Class::NonConstNonVoidFunction, arg1A, arg2A);
      //
      const vector<pair<Arg1Type, Arg2Type>> expectedFunctionCallsA =
      {
         { arg1A, arg2A }
      };
      VECTORS_ARE_EQUAL(expectedFunctionCallsA, nonConstClassInstance.functionCallArguments);
      ARE_EQUAL(nonConstClassInstance.returnValue, returnValueA);


      const Arg1Type arg1B = ZenUnit::Random<Arg1Type>();
      const Arg2Type arg2B = ZenUnit::Random<Arg2Type>();
      //
      const ReturnType returnValueB = _nonVoidTwoArgMemberFunctionCaller.CallNonConstMemberFunction(
         &nonConstClassInstance, &Class::NonConstNonVoidFunction, arg1B, arg2B);
      //
      const vector<pair<Arg1Type, Arg2Type>> expectedFunctionCallsB =
      {
         { arg1A, arg2A },
         { arg1B, arg2B }
      };
      VECTORS_ARE_EQUAL(expectedFunctionCallsB, nonConstClassInstance.functionCallArguments);
      ARE_EQUAL(nonConstClassInstance.returnValue, returnValueB);
   }

   RUN_TEMPLATE_TESTS(NonVoidTwoArgMemberFunctionCallerTests, char, int, int)
   THEN_RUN_TEMPLATE_TESTS(NonVoidTwoArgMemberFunctionCallerTests, int, double, unsigned)
}

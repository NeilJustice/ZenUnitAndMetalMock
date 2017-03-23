#include "pch.h"
#include "ZenUnit/Utils/Iteration/ForEacherTwoExtraArgs.h"

namespace ZenUnit
{
   TESTS(ForEacherTwoExtraArgsTests)
   SPEC(ForEach_EmptyIterable_DoesNothing)
   SPEC(ForEach_OneItemIterable_CallsFuncOnItemOnce)
   SPEC(ForEach_TwoItemIterable_CallsFuncOnItemTwice)
   SPECEND

   using ForEacherType = ForEacherTwoExtraArgs<vector<int>,
      function<void(int, char, string)>, char, string>;
   ForEacherType _forEacherTwoExtraArgs;

   vector<tuple<int, char, string>> _funcCalls;
   void Func(int element, char extraArg1, string extraArg2)
   {
      _funcCalls.emplace_back(element, extraArg1, extraArg2);
   }

   auto Bind()
   {
      return std::bind(&ForEacherTwoExtraArgsTests::Func,
         this, placeholders::_1, placeholders::_2, placeholders::_3);
   }

   TEST(ForEach_EmptyIterable_DoesNothing)
   {
      vector<int> emptyVector;
      //
      _forEacherTwoExtraArgs.ForEach(&emptyVector, Bind(), '0', string());
      //
      IS_EMPTY(_funcCalls);
   }

   TEST(ForEach_OneItemIterable_CallsFuncOnItemOnce)
   {
      vector<int> oneItemVector = { 1 };
      //
      _forEacherTwoExtraArgs.ForEach(&oneItemVector, Bind(), '0', string());
      //
      vector<tuple<int, char, string>> expectedFuncCalls =
      {
         { 1, '0', string() }
      };
      VECTORS_EQUAL(expectedFuncCalls, _funcCalls);
   }

   TEST(ForEach_TwoItemIterable_CallsFuncOnItemTwice)
   {
      vector<int> oneItemVector = { 1, 2 };
      //
      _forEacherTwoExtraArgs.ForEach(&oneItemVector, Bind(), 'a', "message");
      //
      vector<tuple<int, char, string>> expectedFuncCalls =
      {
         { 1, 'a', "message" },
         { 2, 'a', "message" }
      };
      VECTORS_EQUAL(expectedFuncCalls, _funcCalls);
   }

   }; RUN(ForEacherTwoExtraArgsTests)
}


#include "pch.h"
#include "ZenUnit/Utils/Iteration/TwoExtraArgsForEacher.h"

namespace ZenUnit
{
   TESTS(TwoExtraArgsForEacherTests)
   AFACT(ForEach_EmptyIterable_DoesNothing)
   AFACT(ForEach_OneItemIterable_CallsFuncOnItemOnce)
   AFACT(ForEach_TwoItemIterable_CallsFuncOnItemTwice)
   EVIDENCE

   using ForEacherType = TwoExtraArgsForEacher<vector<int>,
      function<void(int, char, string)>, char, string>;
   ForEacherType _forEacherTwoExtraArgs;

   vector<tuple<int, char, string>> _funcCalls;
   void Func(int element, char extraArg1, string extraArg2)
   {
      _funcCalls.emplace_back(element, extraArg1, extraArg2);
   }

   auto Bind()
   {
      return bind(&TwoExtraArgsForEacherTests::Func,
         this, placeholders::_1, placeholders::_2, placeholders::_3);
   }

   TEST(ForEach_EmptyIterable_DoesNothing)
   {
      const vector<int> emptyVector;
      //
      _forEacherTwoExtraArgs.ForEach(&emptyVector, Bind(), '0', string());
      //
      IS_EMPTY(_funcCalls);
   }

   TEST(ForEach_OneItemIterable_CallsFuncOnItemOnce)
   {
      const vector<int> oneItemVector { 1 };
      char c = Random<char>();
      string s = Random<string>();
      //
      _forEacherTwoExtraArgs.ForEach(&oneItemVector, Bind(), c, s);
      //
      const vector<tuple<int, char, string>> expectedFuncCalls
      {
         { 1, c, s }
      };
      VECTORS_EQUAL(expectedFuncCalls, _funcCalls);
   }

   TEST(ForEach_TwoItemIterable_CallsFuncOnItemTwice)
   {
      const vector<int> oneItemVector { 1, 2 };
      char c = Random<char>();
      string s = Random<string>();
      //
      _forEacherTwoExtraArgs.ForEach(&oneItemVector, Bind(), c, s);
      //
      const vector<tuple<int, char, string>> expectedFuncCalls
      {
         { 1, c, s },
         { 2, c, s }
      };
      VECTORS_EQUAL(expectedFuncCalls, _funcCalls);
   }

   }; RUNTESTS(TwoExtraArgsForEacherTests)
}


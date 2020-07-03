#include "pch.h"

namespace ZenUnit
{
   TESTS(ThreeArgForEacherTests)
   AFACT(ThreeArgForEach_EmptyCollection_DoesNothing)
   AFACT(ThreeArgForEach_OneItemCollection_CallsFuncOnItemOnce)
   AFACT(ThreeArgForEach_TwoItemCollection_CallsFuncOnItemTwice)
   EVIDENCE

   using ForEacherType = ThreeArgForEacher<vector<int>,
   function<void(int, char, string)>, char, string>;
   ForEacherType _threeArgForEacher;

   vector<tuple<int, char, string>> _funcCalls;
   void Func(int element, char arg2, string arg3)
   {
      _funcCalls.emplace_back(element, arg2, arg3);
   }

   auto Bind()
   {
      return std::bind(&ThreeArgForEacherTests::Func, this, placeholders::_1, placeholders::_2, placeholders::_3);
   }

   TEST(ThreeArgForEach_EmptyCollection_DoesNothing)
   {
      const vector<int> emptyVector;
      //
      _threeArgForEacher.ThreeArgForEach(&emptyVector, Bind(), '0', string());
      //
      IS_EMPTY(_funcCalls);
   }

   TEST(ThreeArgForEach_OneItemCollection_CallsFuncOnItemOnce)
   {
      const vector<int> oneItemVector{ 1 };
      char c = Random<char>();
      string s = Random<string>();
      //
      _threeArgForEacher.ThreeArgForEach(&oneItemVector, Bind(), c, s);
      //
      const vector<tuple<int, char, string>> expectedFuncCalls
      {
         { 1, c, s }
      };
      VECTORS_ARE_EQUAL(expectedFuncCalls, _funcCalls);
   }

   TEST(ThreeArgForEach_TwoItemCollection_CallsFuncOnItemTwice)
   {
      const vector<int> oneItemVector{ 1, 2 };
      char c = Random<char>();
      string s = Random<string>();
      //
      _threeArgForEacher.ThreeArgForEach(&oneItemVector, Bind(), c, s);
      //
      const vector<tuple<int, char, string>> expectedFuncCalls
      {
         { 1, c, s },
         { 2, c, s }
      };
      VECTORS_ARE_EQUAL(expectedFuncCalls, _funcCalls);
   }

   RUN_TESTS(ThreeArgForEacherTests)
}

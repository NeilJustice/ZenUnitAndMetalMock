#include "pch.h"
#include "ZenUnit/Utils/Iteration/ForEacherExtraArg.h"

namespace ZenUnit
{
   TESTS(ForEacherExtraArgTests)
   SPEC(ForEach_EmptyIterable_DoesNothing)
   SPEC(ForEach_OneItemIterable_CallsFuncOnItemOnce)
   SPEC(ForEach_TwoItemIterable_CallsFuncOnItemTwice)
   SPECEND

   ForEacherExtraArg<vector<int>, function<void(int, int)>, int> _forEacherExtraArg;

   vector<pair<int, int>> calls;
   void Func(int element, int extraArg)
   {
      calls.emplace_back(element, extraArg);
   }

   auto Bind()
   {
      return std::bind(&ForEacherExtraArgTests::Func, this, placeholders::_1, placeholders::_2);
   }

   TEST(ForEach_EmptyIterable_DoesNothing)
   {
      vector<int> emptyVector;
      //
      _forEacherExtraArg.ForEach(&emptyVector, Bind(), 0);
      //
      ARE_EQUAL(0, calls.size());
   }

   TEST(ForEach_OneItemIterable_CallsFuncOnItemOnce)
   {
      vector<int> oneItemVector = { 1 };
      //
      _forEacherExtraArg.ForEach(&oneItemVector, Bind(), 0);
      //
      vector<pair<int, int>> expectedCalls =
      {
         { 1, 0 }
      };
      VECTORS_EQUAL(expectedCalls, calls);
   }

   TEST(ForEach_TwoItemIterable_CallsFuncOnItemTwice)
   {
      vector<int> oneItemVector = { 1, 2 };
      //
      _forEacherExtraArg.ForEach(&oneItemVector, Bind(), 0);
      //
      vector<pair<int, int>> expectedCalls =
      {
         { 1, 0 },
         { 2, 0 }
      };
      VECTORS_EQUAL(expectedCalls, calls);
   }

   }; RUN(ForEacherExtraArgTests)
}

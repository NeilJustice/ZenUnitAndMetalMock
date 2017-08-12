#include "pch.h"
#include "ZenUnit/Utils/Iteration/ForEacherExtraArg.h"

namespace ZenUnit
{
   TESTS(ForEacherExtraArgTests)
   FACT(ForEach_EmptyIterable_DoesNothing)
   FACT(ForEach_OneItemIterable_CallsFuncOnItemOnce)
   FACT(ForEach_TwoItemIterable_CallsFuncOnItemTwice)
   BEGINPROOF

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
      const vector<int> emptyVector;
      //
      _forEacherExtraArg.ForEach(&emptyVector, Bind(), 0);
      //
      ARE_EQUAL(0, calls.size());
   }

   TEST(ForEach_OneItemIterable_CallsFuncOnItemOnce)
   {
      const vector<int> oneItemVector { 1 };
      //
      _forEacherExtraArg.ForEach(&oneItemVector, Bind(), 0);
      //
      const vector<pair<int, int>> expectedCalls
      {
         { 1, 0 }
      };
      VECTORS_EQUAL(expectedCalls, calls);
   }

   TEST(ForEach_TwoItemIterable_CallsFuncOnItemTwice)
   {
      const vector<int> oneItemVector { 1, 2 };
      //
      _forEacherExtraArg.ForEach(&oneItemVector, Bind(), 0);
      //
      const vector<pair<int, int>> expectedCalls
      {
         { 1, 0 },
         { 2, 0 }
      };
      VECTORS_EQUAL(expectedCalls, calls);
   }

   }; RUN(ForEacherExtraArgTests)
}

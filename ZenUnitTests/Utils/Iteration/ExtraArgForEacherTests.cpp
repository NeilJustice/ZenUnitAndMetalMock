#include "pch.h"
#include "ZenUnit/Utils/Iteration/ExtraArgForEacher.h"

namespace ZenUnit
{
   TESTS(ForEacherExtraArgTests)
   AFACT(ExtraArgForEach_EmptyIterable_DoesNothing)
   AFACT(ExtraArgForEach_OneItemIterable_CallsFuncOnItemOnce)
   AFACT(ExtraArgForEach_TwoItemIterable_CallsFuncOnItemTwice)
   EVIDENCE

   ExtraArgForEacher<vector<int>, function<void(int, int)>, int> _forEacherExtraArg;

   vector<pair<int, int>> calls;
   void Func(int element, int extraArg)
   {
      calls.emplace_back(element, extraArg);
   }

   auto Bind()
   {
      return bind(&ForEacherExtraArgTests::Func, this, placeholders::_1, placeholders::_2);
   }

   TEST(ExtraArgForEach_EmptyIterable_DoesNothing)
   {
      const vector<int> emptyVector;
      //
      _forEacherExtraArg.ExtraArgForEach(&emptyVector, Bind(), 0);
      //
      ARE_EQUAL(0, calls.size());
   }

   TEST(ExtraArgForEach_OneItemIterable_CallsFuncOnItemOnce)
   {
      const vector<int> oneItemVector { 1 };
      //
      _forEacherExtraArg.ExtraArgForEach(&oneItemVector, Bind(), 0);
      //
      const vector<pair<int, int>> expectedCalls
      {
         { 1, 0 }
      };
      VECTORS_EQUAL(expectedCalls, calls);
   }

   TEST(ExtraArgForEach_TwoItemIterable_CallsFuncOnItemTwice)
   {
      const vector<int> oneItemVector { 1, 2 };
      //
      _forEacherExtraArg.ExtraArgForEach(&oneItemVector, Bind(), 0);
      //
      const vector<pair<int, int>> expectedCalls
      {
         { 1, 0 },
         { 2, 0 }
      };
      VECTORS_EQUAL(expectedCalls, calls);
   }

   }; RUNTESTS(ForEacherExtraArgTests)
}
